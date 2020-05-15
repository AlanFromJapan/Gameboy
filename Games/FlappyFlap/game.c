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


inline void drawSpriteBg(UINT8 topleftTile, UINT8 x, UINT8 y){
    dynMap[x + y * SCREENW_TILE_TOTAL] = topleftTile;
    dynMap[x + (y+1) * SCREENW_TILE_TOTAL] = topleftTile+1;
    dynMap[(x+1) + y * SCREENW_TILE_TOTAL] = topleftTile+2;
    dynMap[(x+1) + (y+1) * SCREENW_TILE_TOTAL] = topleftTile+3;
}

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

    move_sprite(2, X, Y);
    move_sprite(3, X+8, Y);
}


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

