
#include <gb/gb.h>
#include <gb/drawing.h>

//for rand()
#include <stdlib.h>

#include "rolling_dice.h"
#include "my_lib01.h"
#include "Map_Screen1.h"
#include "Map_splash.h"

//available dice types
const UINT8 DiceTypes[] = {2, 4, 6, 8, 10, 12, 20, 100};

//Sprites constants
#define SPRITE_DICE_LEFT     2
#define SPRITE_DICE_RIGHT    (SPRITE_DICE_LEFT+1)
#define SPRITE_MONSTER_LEFT  4
#define SPRITE_MONSTER_RIGHT (SPRITE_MONSTER_LEFT+1)

//frame divider
#define FRAME_DIVIDER 10

//bouncing
#define BOUNCE_MAX 20
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
 * Clears the 3 digits number on the background
 */
void bgClearDigits(const UINT8 tileX, const UINT8 tileY){
    //clear
    putTile(TILE_EMPTY, tileX, tileY);
    putTile(TILE_EMPTY, tileX-1, tileY);
    putTile(TILE_EMPTY, tileX-2, tileY);
}

/**
 * Shows a 3 digits number on the background
 */
void bgShow3Digits(const UINT8 val, const UINT8 tileX, const UINT8 tileY) {
    //clear
    bgClearDigits(tileX, tileY);

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

/**
 * Hides a 16x16 sprite (2 consequent sprites in fact)
 */
void hide_sprite(const UINT8 spriteId){
    move_sprite(spriteId, 200, 0);
    move_sprite(spriteId+1, 200, 0);
}

/*
 ***********************************************************************************************
 * MAIN method
 ***********************************************************************************************
 */
void main() {
    UINT8 diceX, diceY, monsterX, monsterY, framecounter, framedivider, diceTypeIdx, buttonTemporisation, bounceRound;
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
    diceY = 50;
    //Remember that the sprite is 16x16 so the X and Y are the BOTTOM-MIDDLE of the sprite
    monsterX = 160 -8;
    monsterY = 144;
    dx = -3;
    dy = 1;

    move_sprite(SPRITE_DICE_LEFT, diceX, diceY);
    move_sprite(SPRITE_DICE_RIGHT, diceX+8, diceY);

    hide_sprite(SPRITE_DICE_LEFT);

    set_sprite_tile(SPRITE_MONSTER_LEFT, MONSTER_A);
    set_sprite_tile(SPRITE_MONSTER_RIGHT, MONSTER_A+2);
    move_sprite(SPRITE_MONSTER_LEFT, monsterX, monsterY);
    move_sprite(SPRITE_MONSTER_RIGHT, monsterX+8, monsterY);

    
    //Write the default dice value of 6 (index 2 in the DiceTypes array)
    diceTypeIdx = 2;
    bgShowDiceType(DiceTypes[diceTypeIdx]);

    wait_vbl_done();

    framecounter = 0;
    framedivider = 0;
    buttonTemporisation = 0;
    bounceRound = 0;
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
            
            //clear and display the value, little blink to show it was updated
            bgClearDigits(DICE_VALUE_MOST_X, DICE_VALUE_MOST_Y);
            delay(50);
            bgShowDiceValue(diceValue);

            //tempo
            buttonTemporisation = BUTTON_TEMPORISATION;
        }



        framedivider++;
        if (framedivider > FRAME_DIVIDER) {
            framedivider = 0;

            //------------------------------------------------
            //Dice
            //------------------------------------------------
            if (bounceRound < BOUNCE_MAX){

                //move
                diceY = diceY + dy;
                diceX = diceX + dx;

                //gravity: if falling (dy > 0) then accelerate it, otherwise decelerate it
                dy ++;

                //X is the MIDDLE of the 16x16 sprite
                if ((diceX - 8) > SCREENWIDTH || (diceX + 8) > SCREENWIDTH)
                    //overflow to the left or crossing border to the right
                    dx=-dx;

                //Y is the BOTTOM of the 16x16 sprite
                //GOING UP : check if the top of the dice is out of the TOP of screen (overflow to bottom of the screen)
                //... don't care, won't make it bounce that high

                //GOING DOWN: is the bottom of the dice going too low?
                if (diceY >= SCREENHEIGHT){
                    //bounce
                    //was going DOWN so dy is positive => make it negative and reduce it by a factor and a constant amount
                    dy = -(dy * 3 / 4 - 1);
                    if (dy > 0)
                        dy = 0;

                    diceY = SCREENHEIGHT; // it's the BOTTOM of the sprite
                    bounceRound++;
                }


                move_sprite(SPRITE_DICE_LEFT, diceX, diceY);
                move_sprite(SPRITE_DICE_RIGHT, diceX+8, diceY);


                //rotate dice sprite
                // skip first 4 tiles, then 4 tiles per sprite, animation is over 3 sprites (frame)
                UINT8 s = 4 + 4 * (framecounter % 3); 
                set_sprite_tile(SPRITE_DICE_LEFT, s);
                set_sprite_tile(SPRITE_DICE_RIGHT, s+2);


                

                if (bounceRound >= BOUNCE_MAX){
                    //hide dice
                    dx =0;
                    dy=0;
                    hide_sprite(SPRITE_DICE_LEFT);
                }
            }

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


