
#include <gb/gb.h>
#include <gb/drawing.h>

#include "rolling_dice.h"
#include "my_lib01.h"
#include "Map_Screen1.h"
#include "Map_splash.h"


#define SPRITE_DICE_LEFT     2
#define SPRITE_DICE_RIGHT    (SPRITE_DICE_LEFT+1)
#define SPRITE_MONSTER_LEFT  4
#define SPRITE_MONSTER_RIGHT (SPRITE_MONSTER_LEFT+1)



/**
 * Set a background tile to the tile in parameter
 */
void putTile(UINT8 tile, UINT8 x, UINT8 y){
    //NOT inline so tile is a byte in the call stack so you can ref its address
    set_bkg_tiles(x, y, 1, 1, &tile);

}

/*
 ***********************************************************************************************
 * MAIN method
 ***********************************************************************************************
 */
void main() {
    UINT8 diceX, diceY, monsterX, monsterY, framecounter;
    INT8 dx, dy;

    SPRITES_8x16;

    //Using different lib of tiles for the sprites and the background
    set_sprite_data(0, TILE_COUNT, my_tiles);
    set_bkg_data(0, my_lib01_COUNT, my_lib01);

    set_bkg_tiles(0, 0, Map_splash_WIDTH, Map_splash_HEIGHT, Map_splash);
    
    SHOW_BKG;

    wait_vbl_done();
    while(joypad() == 0x00){delay(10);}//wait for user to press a button

    //load the normal BG and change the tile lib
    set_bkg_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_tiles(0, 0, Map_Screen1_WIDTH, Map_Screen1_HEIGHT, Map_Screen1);
    
    SHOW_SPRITES;


    diceX = 100;
    diceY = 100;
    //Remember that the sprite is 16x16 so the X and Y are the BOTTOM-MIDDLE of the sprite
    monsterX = 160 -8;
    monsterY = 144;
    dx = 0;
    dy = 0;

    move_sprite(SPRITE_DICE_LEFT, diceX, diceY);
    move_sprite(SPRITE_DICE_RIGHT, diceX+8, diceY);

    set_sprite_tile(SPRITE_MONSTER_LEFT, MONSTER_A);
    set_sprite_tile(SPRITE_MONSTER_RIGHT, MONSTER_A+2);
    move_sprite(SPRITE_MONSTER_LEFT, monsterX, monsterY);
    move_sprite(SPRITE_MONSTER_RIGHT, monsterX+8, monsterY);

    //Write the default dice value of 6
    putTile(TILE_DIGIT_6, 4, 8);

    wait_vbl_done();

    framecounter = 0;
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


        diceX = diceX + dx;
        diceY = diceY + dy;

        //TODO: fix this it's copy pasted from other project that was for 16x16 sprites
        //X is the MIDDLE of the 16x16 sprite
        if (diceX <= (8+8) || diceX >= ((20-1) * 8 -8) )
            dx=-dx;

        //Y is the BOTTOM of the 16x16 sprite
        if (diceY <= (8+16) || diceY >= ((18-1) *8) )
            dy=-dy;

        move_sprite(SPRITE_DICE_LEFT, diceX, diceY);
        move_sprite(SPRITE_DICE_RIGHT, diceX+8, diceY);


        //------------------------------------------------
        //Dice
        //------------------------------------------------

        //rotate dice sprite
        // skip first 4 tiles, then 4 tiles per sprite, animation is over 3 sprites (frame)
        UINT8 s = 4 + 4 * (framecounter % 3); 
        set_sprite_tile(SPRITE_DICE_LEFT, s);
        set_sprite_tile(SPRITE_DICE_RIGHT, s+2);

        //------------------------------------------------
        //Monster
        //------------------------------------------------
        if (framecounter % 2 == 0){
            set_sprite_tile(SPRITE_MONSTER_LEFT, MONSTER_A);
            set_sprite_tile(SPRITE_MONSTER_RIGHT, MONSTER_A+2);
        }
        else {
            set_sprite_tile(SPRITE_MONSTER_LEFT, MONSTER_B);
            set_sprite_tile(SPRITE_MONSTER_RIGHT, MONSTER_B+2);
        }

        monsterX -= 2;
        move_sprite(SPRITE_MONSTER_LEFT, monsterX, monsterY);
        move_sprite(SPRITE_MONSTER_RIGHT, monsterX+8, monsterY);

        //------------------------------------------------
        // End of frame
        //------------------------------------------------
        delay(150);
        framecounter++;
    }
}


