
#include <gb/gb.h>
#include <gb/drawing.h>

#include "rolling_dice.h"
#include "my_lib01.h"
#include "Map_Screen1.h"

#include "lib_splash.h"
#include "Map_splash.h"



/*
 ***********************************************************************************************
 * MAIN method
 ***********************************************************************************************
 */
void main() {
    UINT8 X,Y ;
    INT8 dx, dy, SPRITE_FRAME;

    SPRITES_8x16;

    //Using different lib of tiles for the sprites and the background
    set_sprite_data(0, TILE_COUNT, my_tiles);
    set_bkg_data(0, my_lib_splash_COUNT, my_lib_splash);

    set_bkg_tiles(0, 0, Map_Screen1_WIDTH, Map_splash_HEIGHT, Map_splash);
    
    SHOW_BKG;

    wait_vbl_done();
    while(joypad() == 0x00){delay(10);}//wait for user to press a button

    //load the normal BG and change the tile lib
    set_bkg_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_tiles(0, 0, Map_Screen1_WIDTH, Map_Screen1_HEIGHT, Map_Screen1);
    
    SHOW_SPRITES;


    X = 100;
    Y = 100;
    dx = 0;
    dy = 0;

    SPRITE_FRAME=0;

    set_sprite_tile(0, SPRITE_1);
    set_sprite_tile(1, SPRITE_1+2);
    move_sprite(0, 20, 20);
    move_sprite(1, 20+8, 20);


    move_sprite(2, X, Y);
    move_sprite(3, X+8, Y);


    wait_vbl_done();

    while(1) {

        wait_vbl_done();
        if (joypad() & J_UP){
            dy--;
        }
        if (joypad() & J_DOWN){
            dy++;
        }
        if (joypad() & J_LEFT){
            dx--;
        }
        if (joypad() & J_RIGHT){
            dx++;
        }


        X = X + dx;
        Y = Y + dy;

        //TODO: fix this it's copy pasted from other project that was for 16x16 sprites
        //X is the MIDDLE of the 16x16 sprite
        if (X <= (8+8) || X >= ((20-1) * 8 -8) )
            dx=-dx;

        //Y is the BOTTOM of the 16x16 sprite
        if (Y <= (8+16) || Y >= ((18-1) *8) )
            dy=-dy;

        move_sprite(2, X, Y);
        move_sprite(3, X+8, Y);

        //rotate sprite
        SPRITE_FRAME = (SPRITE_FRAME + 1) % 3;
        UINT8 s = 4 + 4 * SPRITE_FRAME;

            
        set_sprite_tile(2, s);
        set_sprite_tile(3, s+2);
        delay(150);
    }
}


