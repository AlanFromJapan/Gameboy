#include "game.h"

#include <gb/gb.h>
#include <gb/drawing.h>

#include "my_lib01.h"


#define SPRITE_MIRROR   0x20

#define SCREENH_TILE    18
#define SCREENW_TILE    20
#define SCREENW_TILE_TOTAL    32

UINT8 dynMap[SCREENW_TILE_TOTAL * SCREENH_TILE];
UINT8 speed = 1;
UINT8 X = 0;
UINT8 Y = 0;
UINT8 xoffset = 0;

void beep1(){
    NR10_REG = 0x38U;
    NR11_REG = 0x70U;
    NR12_REG = 0xE0U;
    NR13_REG = 0x0AU;
    NR14_REG = 0xC6U;

    NR51_REG |= 0x11;
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
    dynMap[x+1 + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_2;
    dynMap[x+2 + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_3;


    for (y++; y < SCREENH_TILE-1; y++){
        dynMap[x + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_4;
        dynMap[x+1 + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_5;
        dynMap[x+2 + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_6;                
    }

}

/**
 * Draws a pipe that protrudes from the top of the screen.
 * X,Y are the pipe bottom left angle
 */
inline void addPipeTop (UINT8 x, UINT8 y){
    dynMap[x + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_1;
    dynMap[x+1 + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_2;
    dynMap[x+2 + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_3;


    for (y--; y != 255; y--){
        dynMap[x + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_4;
        dynMap[x+1 + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_5;
        dynMap[x+2 + y * SCREENW_TILE_TOTAL] = TILE_TUYAUX_6;                
    }

}

/**
 * Write decoration on the background like a sprite (16x16)
 */
inline void drawSpriteBg(UINT8 topleftTile, UINT8 x, UINT8 y){
    dynMap[x + y * SCREENW_TILE_TOTAL] = topleftTile;
    dynMap[x + (y+1) * SCREENW_TILE_TOTAL] = topleftTile+1;
    dynMap[(x+1) + y * SCREENW_TILE_TOTAL] = topleftTile+2;
    dynMap[(x+1) + (y+1) * SCREENW_TILE_TOTAL] = topleftTile+3;
}

/**
 * Init the player sprite
 */
inline void makeGhostSprite(){
    //create the character ghost sprite
    set_sprite_tile(2, TILE_GHOST_A_NE);
    set_sprite_tile(3, TILE_GHOST_A_NW);
    set_sprite_prop(2, SPRITE_MIRROR);
    set_sprite_prop(3, SPRITE_MIRROR);

    X = 8*6;
    Y = 8*9;
    move_sprite(2, X, Y);
    move_sprite(3, X+8, Y);
}

/**
 * Vertical blank interrupt: where we "draw" memory while screen is not updated
 */
void vblint(){
    scroll_bkg(speed, 0);
    xoffset += speed;

    move_sprite(2, X, Y);
    move_sprite(3, X+8, Y);
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
        tiles[0] <= TILE_TUYAUX_6 || 
        tiles[1] <= TILE_TUYAUX_6 ) {
        //hit a pipe !
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

    //make a pipe
    addPipeBottom (1, 14);
    addPipeTop (14, 6);

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
            beep1();
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

