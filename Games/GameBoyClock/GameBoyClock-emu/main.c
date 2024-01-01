/*##########################################################
# GameBoyClock-emu
#
# Simulates the GameBoyClock SERIAL RTC module
#
*/

#include <gb/gb.h>
#include <gb/drawing.h>

//for rand()
#include <stdlib.h>

#include "my_lib01.h"
#include "Map_Screen1.h"

//available dice types
const UINT8 DiceTypes[] = {2, 4, 6, 8, 10, 12, 20, 100};

//Sprites constants
#define SPRITE_DICE_LEFT     2
#define SPRITE_DICE_RIGHT    (SPRITE_DICE_LEFT+1)


//main loop temporization (ms)
#define MAIN_LOOP_TEMPORISATION 5
//button temporization
#define BUTTON_TEMPORISATION 15

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

void sendSerialByte(UINT8 byte){
    //https://gbdev.gg8.se/wiki/articles/Serial_Data_Transfer_(Link_Cable)
    //byte to send
    SB_REG = byte;
    //start transfer (normal speed, internal clock)
    SC_REG = 0x81;

    while(SC_REG & 0x81){
        //wait for transfer to complete
        ;
    }
} 

UINT8 receiveSerialByte(){
    //https://gbdev.gg8.se/wiki/articles/Serial_Data_Transfer_(Link_Cable)
    //byte to send
    SB_REG = 0x00;
    //start transfer (normal speed, EXTERNAL clock)
    SC_REG = 0x80;

    while(SC_REG & 0x80){
        //wait for transfer to complete
        ;
    }

    return SB_REG;
}   

/*
 ***********************************************************************************************
 * MAIN method
 ***********************************************************************************************
 */
void main() {
    UINT8  framecounter, framedivider, diceTypeIdx, buttonTemporisation;

    SPRITES_8x16;

  
    SHOW_BKG;

    wait_vbl_done();
 
    //init random seed
    srand(DIV_REG);

    //load the normal BG and change the tile lib
    set_bkg_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_tiles(0, 0, Map_Screen1_WIDTH, Map_Screen1_HEIGHT, Map_Screen1);
    
    SHOW_SPRITES;



    //Remember that the sprite is 16x16 so the X and Y are the BOTTOM-MIDDLE of the sprite


   
    //Write the default dice value of 6 (index 2 in the DiceTypes array)
    diceTypeIdx = 2;
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
                        //RECEIVE

            //clear and display the value, little blink to show it was updated
            bgClearDigits(DICE_VALUE_MOST_X, DICE_VALUE_MOST_Y);
            bgShowDiceValue(111);

            UINT8 diceValue = receiveSerialByte();

            bgShowDiceValue(diceValue);
            
            //tempo
            buttonTemporisation = BUTTON_TEMPORISATION;
        }
        if (buttonTemporisation == 0 && (joypadState & J_RIGHT || joypadState & J_UP)){
            //SEND
            UINT8 diceValue = (rand() % (DiceTypes[diceTypeIdx])) + 1;
            //clear and display the value, little blink to show it was updated
            bgClearDigits(DICE_VALUE_MOST_X, DICE_VALUE_MOST_Y);
            delay(50);
            bgShowDiceValue(222);

            sendSerialByte(diceValue);

            bgShowDiceValue(diceValue);

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



        
        //------------------------------------------------
        // End of frame
        //------------------------------------------------
        delay(MAIN_LOOP_TEMPORISATION);
    }
}


