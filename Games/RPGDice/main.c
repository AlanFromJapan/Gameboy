
#include <gb/gb.h>
#include <gb/drawing.h>

//for rand()
#include <stdlib.h>

#include "rolling_dice.h"
#include "my_lib01.h"
#include "Map_Screen1.h"
#include "Map_splash.h"

//available dice types
const UINT8 DiceTypes[] = {4, 6, 8, 10, 12, 20, 100};

//Sprites constants
#define SPRITE_DICE_LEFT     2
#define SPRITE_DICE_RIGHT    (SPRITE_DICE_LEFT+1)
#define SPRITE_MONSTER_LEFT  4
#define SPRITE_MONSTER_RIGHT (SPRITE_MONSTER_LEFT+1)

//frame divider
#define FRAME_DIVIDER 10

//button temporization
#define BUTTON_TEMPORISATION 15

//main loop temporization (ms)
#define MAIN_LOOP_TEMPORISATION 5

//Some tiles defintions
#define TILE_DIGIT_0 TILE_LETTER_15
#define TILE_EMPTY   0

//Digit value to tile index
const UINT8 Digits2Tile[] = {
    TILE_DIGIT_0, TILE_DIGIT_1, TILE_DIGIT_2, TILE_DIGIT_3, TILE_DIGIT_4, TILE_DIGIT_5, TILE_DIGIT_6, TILE_DIGIT_7, TILE_DIGIT_8, TILE_DIGIT_9
};

//rightmost digit of the dice type X,Y position
#define DICE_TYPE_MOST_X 4
#define DICE_TYPE_MOST_Y 8

//rightmost digit of the dice value X,Y position
#define DICE_VALUE_MOST_X 10
#define DICE_VALUE_MOST_Y 7

/**
 * Set a background tile to the tile in parameter
 */
void putTile(UINT8 tile, UINT8 x, UINT8 y){
    //NOT inline so tile is a byte in the call stack so you can ref its address
    set_bkg_tiles(x, y, 1, 1, &tile);
}

/**
 * Shows a 3 digits number on the background
 */
void bgShow3Digits(const UINT8 val, const UINT8 tileX, const UINT8 tileY) {
    //clear
    putTile(TILE_EMPTY, tileX, tileY);
    putTile(TILE_EMPTY, tileX-1, tileY);
    putTile(TILE_EMPTY, tileX-2, tileY);

    //display
    UINT8 d = val;
    putTile(Digits2Tile[d % 10], tileX, tileY);

    d = d / (UINT8)10;
    if (d > 0){
        putTile(Digits2Tile[d % 10], tileX -1, tileY);
    }

    d = d / (UINT8)10;
    if (d > 0){
        putTile(Digits2Tile[d % 10], tileX -2, tileY);
    }
}

/**
 * Updates the displayed dice type
 */
void bgShowDiceType(UINT8 dice){
    bgShow3Digits(dice, DICE_TYPE_MOST_X, DICE_TYPE_MOST_Y);
}

/**
 * Updates the displayed dice result
 */
void bgShowDiceValue(UINT8 val){
    bgShow3Digits(val, DICE_VALUE_MOST_X, DICE_VALUE_MOST_Y);
}


/*
 ***********************************************************************************************
 * MAIN method
 ***********************************************************************************************
 */
void main() {
    UINT8 diceX, diceY, monsterX, monsterY, framecounter, framedivider, diceTypeIdx, buttonTemporisation;
    INT8 dx, dy;

    SPRITES_8x16;

    //Using different lib of tiles for the sprites and the background
    set_sprite_data(0, TILE_COUNT, my_tiles);
    set_bkg_data(0, my_lib01_COUNT, my_lib01);

    set_bkg_tiles(0, 0, Map_splash_WIDTH, Map_splash_HEIGHT, Map_splash);
    
    SHOW_BKG;

    wait_vbl_done();
    while(joypad() == 0x00){delay(10);}//wait for user to press a button

    //init random seed
    srand(DIV_REG);

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

    //Write the default dice value of 6 (index 1 in the DiceTypes array)
    diceTypeIdx = 1;
    bgShowDiceType(DiceTypes[diceTypeIdx]);

    wait_vbl_done();

    framecounter = 0;
    framedivider = 0;
    buttonTemporisation = 0;
    while(1) {

        wait_vbl_done();

        //tempo
        if (buttonTemporisation > 0){
            buttonTemporisation--;
        }

        // read joypad
        UINT8 joypadState = joypad();
        if (buttonTemporisation == 0 && (joypadState & J_LEFT || joypadState & J_DOWN)){
            diceTypeIdx--;
            if (diceTypeIdx >= sizeof(DiceTypes)){
                diceTypeIdx = 0;
            }

            bgShowDiceType(DiceTypes[diceTypeIdx]);
            bgShowDiceValue(0);

            //tempo
            buttonTemporisation = BUTTON_TEMPORISATION;
        }
        if (buttonTemporisation == 0 && (joypadState & J_RIGHT || joypadState & J_UP)){
            diceTypeIdx++;
            if (diceTypeIdx >= sizeof(DiceTypes)){
                diceTypeIdx = sizeof(DiceTypes)-1;
            }

            bgShowDiceType(DiceTypes[diceTypeIdx]);
            bgShowDiceValue(0);

            //tempo
            buttonTemporisation = BUTTON_TEMPORISATION;
        }


        if (buttonTemporisation == 0 && joypadState & J_A){
            UINT8 diceValue = (rand() % (DiceTypes[diceTypeIdx])) + 1;
            bgShowDiceValue(diceValue);

            //tempo
            buttonTemporisation = BUTTON_TEMPORISATION;
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

        framedivider++;
        if (framedivider > FRAME_DIVIDER) {
            framedivider = 0;

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

            framecounter++;
        }

        //------------------------------------------------
        // End of frame
        //------------------------------------------------
        delay(MAIN_LOOP_TEMPORISATION);
    }
}


