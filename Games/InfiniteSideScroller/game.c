#include "game.h"

#include <gb/gb.h>
#include <gb/drawing.h>

#include <stdlib.h>

#include "my_lib01.h"

#define MAX(a,b) ((a) > (b)? (a) : (b))
#define MIN(a,b) ((a) < (b)? (a) : (b))

#define SPRITE_MIRROR   0x20
#define SPRITE_PALETTE  0x02

#define SCREENH_TILE    18
#define SCREENW_TILE    20
#define SCREENW_TILE_TOTAL    32


UWORD bgPalette[] = {
	RGB_WHITE, RGB_GREEN, RGB_DARKGREEN, RGB_BLACK, /* for the background */
	RGB_WHITE, RGB_RED, RGB_ORANGE, RGB_YELLOW,
	0, RGB_LIGHTGRAY, RGB_BLACK, RGB_DARKGRAY /* For the ghost sprite */ 
};

UINT8 dynMap[SCREENW_TILE_TOTAL * SCREENH_TILE];
UINT8 speed = 1;
UINT8 X = 0;
UINT8 Y = 0;
UINT8 xoffset = 0;



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


    //display
    set_bkg_tiles(0, 0, SCREENW_TILE_TOTAL, SCREENH_TILE, dynMap);

    makeGhostSprite();
    SHOW_SPRITES;

    //branch interrup handler for VBlank
    add_VBL(vblint);

    //infinite game loop
    while (1){

        if(joypad() & J_DOWN) {
            Y++;
        }
        if(joypad() & J_UP) {
            Y--;
        }
        if((joypad() & J_A) && speed <255) {
            speed++;
        }
        if((joypad() & J_B) && speed > 1) {
            speed--;
        }


        delay(10);
    }
}

