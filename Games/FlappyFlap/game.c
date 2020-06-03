#include "game.h"

#include <gb/gb.h>
#include <gb/drawing.h>

#include <stdlib.h>

#include "my_lib01.h"


#define SPRITE_MIRROR   0x20
#define SPRITE_PALETTE  0x02

#define SCREENH_TILE    18
#define SCREENW_TILE    20
#define SCREENW_TILE_TOTAL    32

#define PIPE_WIDTH  3

UWORD bgPalette[] = {
	RGB_WHITE, RGB_GREEN, RGB_DARKGREEN, RGB_BLACK,
	RGB_WHITE, RGB_RED, RGB_ORANGE, RGB_YELLOW,
	0, RGB_LIGHTGRAY, RGB_BLACK, RGB_DARKGRAY,
	0, RGB_BLACK, RGB_DARKGRAY, RGB_WHITE
};

UINT8 dynMap[SCREENW_TILE_TOTAL * SCREENH_TILE];
UINT8 speed = 1;
UINT8 X = 0;
UINT8 Y = 0;
UINT8 xoffset = 0;

//position of the leftmost part of the rightmost pipe IN TILES
UINT8 rightmostPipe = 0;

void beep1(){
    NR10_REG = 0x38U;
    NR11_REG = 0x70U;
    NR12_REG = 0xE0U;
    NR13_REG = 0x0AU;
    NR14_REG = 0xC6U;

    NR51_REG |= 0x11;
}


//Source https://gist.github.com/gingemonster/600c33f7dd97ecbf785eca8c84772c9a
void jumpSound1(){

    // see https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
    // chanel 1 register 0, Frequency sweep settings
    // 7	Unused
    // 6-4	Sweep time(update rate) (if 0, sweeping is off)
    // 3	Sweep Direction (1: decrease, 0: increase)
    // 2-0	Sweep RtShift amount (if 0, sweeping is off)
    // 0001 0110 is 0x16, sweet time 1, sweep direction increase, shift ammount per step 110 (6 decimal)
    NR10_REG = 0x16; 

    // chanel 1 register 1: Wave pattern duty and sound length
    // Channels 1 2 and 4
    // 7-6	Wave pattern duty cycle 0-3 (12.5%, 25%, 50%, 75%), duty cycle is how long a quadrangular  wave is "on" vs "of" so 50% (2) is both equal.
    // 5-0 sound length (higher the number shorter the sound)
    // 01000000 is 0x40, duty cycle 1 (25%), wave length 0 (long)
    NR11_REG = 0x40;

    // chanel 1 register 2: Volume Envelope (Makes the volume get louder or quieter each "tick")
    // On Channels 1 2 and 4
    // 7-4	(Initial) Channel Volume
    // 3	Volume sweep direction (0: down; 1: up)
    // 2-0	Length of each step in sweep (if 0, sweeping is off)
    // NOTE: each step is n/64 seconds long, where n is 1-7	
    // 0111 0011 is 0x73, volume 7, sweep down, step length 3
    NR12_REG = 0x73;  

    // chanel 1 register 3: Frequency LSbs (Least Significant bits) and noise options
    // for Channels 1 2 and 3
    // 7-0	8 Least Significant bits of frequency (3 Most Significant Bits are set in register 4)
    NR13_REG = 0x00;   

    // chanel 1 register 4: Playback and frequency MSbs
    // Channels 1 2 3 and 4
    // 7	Initialize (trigger channel start, AKA channel INIT) (Write only)
    // 6	Consecutive select/length counter enable (Read/Write). When "0", regardless of the length of data on the NR11 register, sound can be produced consecutively.  When "1", sound is generated during the time period set by the length data contained in register NR11.  After the sound is ouput, the Sound 1 ON flag, at bit 0 of register NR52 is reset.
    // 5-3	Unused
    // 2-0	3 Most Significant bits of frequency
    // 1100 0011 is 0xC3, initialize, no consecutive, frequency = MSB + LSB = 011 0000 0000 = 0x300
    NR14_REG = 0xC3;	    

}

void beep2(){
    NR10_REG = 0x00U;
    NR11_REG = 0x43U;
    NR12_REG = 0x43U;
    NR13_REG = 0x73U;
    NR14_REG = 0x86U;

    NR51_REG |= 0x11;
}


/**
 * Draws a pipe that raises from the bottom of the screen.
 * X,Y are the pipe top left angle
 */
inline void addPipeBottom (UINT8 x, UINT8 y){
    dynMap[x + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_1;
    dynMap[(x+1)% SCREENW_TILE_TOTAL + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_2;
    dynMap[(x+2)% SCREENW_TILE_TOTAL + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_3;


    for (y++; y < SCREENH_TILE-1; y++){
        dynMap[x + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_4;
        dynMap[(x+1)% SCREENW_TILE_TOTAL + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_5;
        dynMap[(x+2)% SCREENW_TILE_TOTAL + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_6;                
    }

}

/**
 * Draws a pipe that protrudes from the top of the screen.
 * X,Y are the pipe bottom left angle
 */
inline void addPipeTop (UINT8 x, UINT8 y){
    dynMap[x + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_1;
    dynMap[(x+1)% SCREENW_TILE_TOTAL + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_2;
    dynMap[(x+2)% SCREENW_TILE_TOTAL + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_3;


    for (y--; y != 255; y--){
        dynMap[x + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_4;
        dynMap[(x+1)% SCREENW_TILE_TOTAL + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_5;
        dynMap[(x+2)% SCREENW_TILE_TOTAL + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_6;                
    }

}

/**
 * Write decoration on the background like a sprite (16x16)
 */
inline void drawSpriteBg(UINT8 topleftTile, UINT8 x, UINT8 y){
    dynMap[x + y * SCREENW_TILE_TOTAL] = topleftTile;
    dynMap[x + (y+1) * SCREENW_TILE_TOTAL] = topleftTile+1;
    dynMap[(x+1)% SCREENW_TILE_TOTAL + y * SCREENW_TILE_TOTAL] = topleftTile+2;
    dynMap[(x+1)% SCREENW_TILE_TOTAL + (y+1) * SCREENW_TILE_TOTAL] = topleftTile+3;
}

/**
 * Init the player sprite
 */
inline void makeGhostSprite(){
    //create the character ghost sprite
    set_sprite_tile(2, TILE_GHOST_A_NE);
    set_sprite_tile(3, TILE_GHOST_A_NW);
    set_sprite_prop(2, SPRITE_MIRROR | SPRITE_PALETTE);
    set_sprite_prop(3, SPRITE_MIRROR | SPRITE_PALETTE);

    

    X = 8*6;
    Y = 8*9;
    move_sprite(2, X, Y);
    move_sprite(3, X+8, Y);
}

/**
 * Draws the rest of the autoscroller on the right hand
 */
inline void updateAutoscrollerBuffer(){
    //idea is consider all is drawn until rightmostPipeX (in TILE)
    UINT8 lTile = xoffset / 8;
    UINT8 rTile = (lTile + 20) % SCREENW_TILE_TOTAL;


    if (rightmostPipe > rTile || rightmostPipe < lTile ){
        //rightmost pipe not shown, nothing to do
        //Doc case 1,2,3
        return;
    }


    //now here we KNOW we have to draw something at the right of the buffer
    UINT8 currentrmp = rightmostPipe;
    rightmostPipe+= 
        PIPE_WIDTH /* width of the pipe*/
        //+ 4 /* blank space */
        + (rand() & 0x07) /* a bit of random space*/
        ;

    
    //clear everything between the last pipe RIGHT and the future pipe's RIGHT
    currentrmp += PIPE_WIDTH; //pipe width
    for (; currentrmp < rightmostPipe; currentrmp ++){
        UINT8 x = currentrmp % SCREENW_TILE_TOTAL;
        for (UINT8 y = 0; y < SCREENH_TILE -1; y++){
            dynMap[x + y * SCREENW_TILE_TOTAL] = TILE_EMPTY;
        }
    }

    rightmostPipe = rightmostPipe % SCREENW_TILE_TOTAL;

    //make a pipe
    addPipeBottom (rightmostPipe, 14);
    addPipeTop (rightmostPipe, 6);    

    //update background
    set_bkg_tiles(0, 0, SCREENW_TILE_TOTAL, SCREENH_TILE, dynMap);

}

/**
 * Vertical blank interrupt: where we "draw" memory while screen is not updated
 */
void vblint(){
    //scroll
    scroll_bkg(speed, 0);
    xoffset += speed;

    //move
    move_sprite(2, X, Y);
    move_sprite(3, X+8, Y);

    //draw the rest of the zone
    updateAutoscrollerBuffer();
}


/**
 * Collision detection logic
 * Returns 0 ok, 1 if collision
 */
inline UINT8 checkCollision(){
    //will hit from the front and top/bottom (-1 because ground)
    //Y is the sprite BOTTOM (hence -16 for top), the bottom-2 check is because the sprite is not centered vertically
    if (Y < 16 || Y >= (8*(SCREENH_TILE-1) +2)) {
        return 1;
    }

    UINT8 tiles[2];
    UINT8 xx = (xoffset + X +8)/8;
    get_bkg_tiles(xx, (Y+1)/8 -2, 1, 1, tiles); //-1 because the sprite top is not at the top of the sprite zone
    get_bkg_tiles(xx, (Y-2)/8 -1, 1, 1, tiles +1); //-2 same, because 2 void pixels at the bottom

    //Trick: the "walls" are all the first tiles so a simple lessthan compare is good for a hit check
    if (
        tiles[0] <= TILE_MOSS_SE || 
        tiles[1] <= TILE_MOSS_SE ) {
        //hit a pipe or somthing else you can't go through!
        return 1;
    }


    //if you arrive here all is ok
    return 0;
}


/**
 * The real game main loop
 * 
 */
inline void autoscroller(){

    srand(DIV_REG);

    //fill blank
    for (UINT8 x = 0; x < SCREENW_TILE_TOTAL; x++){
        for (UINT8 y = 0; y < SCREENH_TILE; y++){
            dynMap[x + y * SCREENW_TILE_TOTAL] = TILE_EMPTY;
        }
    }

    //ground
    for (UINT8 x = 0; x < SCREENW_TILE_TOTAL; x++){
        if ((x & 0x01) == 0)
            dynMap[(SCREENH_TILE -1) * SCREENW_TILE_TOTAL + x] = TILE_GROUND1;
        else
            dynMap[(SCREENH_TILE -1) * SCREENW_TILE_TOTAL + x] = TILE_GROUND2;
    }

    //some bg decorations
    drawSpriteBg(TILE_BG_FLOWER_NW, 10, 10);
    drawSpriteBg(TILE_BG_STAR_NW, 14, 14);

/*
    //make a pipe
    addPipeBottom (1, 14);
    addPipeTop (14, 6);
    addPipeBottom (22, 16);
    rightmostPipe = 22;
*/

    //display
    set_bkg_tiles(0, 0, SCREENW_TILE_TOTAL, SCREENH_TILE, dynMap);

    makeGhostSprite();
    SHOW_SPRITES;

    //branch interrup handler for VBlank
    add_VBL(vblint);

    //infinite game loop
    while (1){

        if(joypad() & J_DOWN) {
            beep2();
            Y++;
        }
        if(joypad() & J_UP) {
            jumpSound1();
            Y--;
        }
        if((joypad() & J_A) && speed <255) {
            speed++;
        }
        if((joypad() & J_B) && speed > 1) {
            speed--;
        }

        if (checkCollision()) {
            speed = 0;
            while(1) {
                wait_vbl_done();
            }
            //reset();
        }

        delay(10);
    }
}

