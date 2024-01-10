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


volatile UINT8 lastVal = 0;

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
 * Updates the displayed dice result
 */
void bgShowDiceValue(UINT8 val){
    bgShow3Digits(val, DICE_VALUE_MOST_X, DICE_VALUE_MOST_Y);
}

void sioInt() {
    lastVal = _io_in;    
    bgShowDiceValue(lastVal);
}

/*
 ***********************************************************************************************
 * MAIN method
 ***********************************************************************************************
 */
void main() {
    UINT8  framecounter, framedivider, buttonTemporisation;

    SPRITES_8x16;

    wait_vbl_done();
 
    //init random seed
    srand(DIV_REG);

    //load the normal BG and change the tile lib
    set_bkg_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_tiles(0, 0, Map_Screen1_WIDTH, Map_Screen1_HEIGHT, Map_Screen1);
    
    SHOW_BKG;
    SHOW_SPRITES;

    //handle serial transfer completion
    add_SIO(sioInt);

    
    wait_vbl_done();

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

            //R-C-V
            putTile(TILE_LETTER_18, 0, 0);  
            putTile(TILE_LETTER_3, 1, 0);  
            putTile(TILE_LETTER_22, 2, 0);  
            putTile(TILE_EMPTY, 3, 0);   



            //clear and display the value, little blink to show it was updated
            bgClearDigits(DICE_VALUE_MOST_X, DICE_VALUE_MOST_Y);
            

            receive_byte();
            
            //tempo
            buttonTemporisation = BUTTON_TEMPORISATION;
        }
        if (buttonTemporisation == 0 && (joypadState & J_RIGHT || joypadState & J_UP)){
            //SEND

            //S-E-N-D
            putTile(TILE_LETTER_19, 0, 0);  
            putTile(TILE_LETTER_5, 1, 0);  
            putTile(TILE_LETTER_14, 2, 0);  
            putTile(TILE_LETTER_4, 3, 0);   


            UINT8 diceValue = (rand() % 100) + 1;
            //clear and display the value, little blink to show it was updated
            bgClearDigits(DICE_VALUE_MOST_X, DICE_VALUE_MOST_Y);

            // sendSerialByte(diceValue);
            _io_out = diceValue;
            send_byte();

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


