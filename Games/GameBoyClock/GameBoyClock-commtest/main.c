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



//main loop temporization (ms)
#define MAIN_LOOP_TEMPORISATION 20
//button temporization
#define BUTTON_TEMPORISATION 10


//Some tiles defintions
#define TILE_DIGIT_0 TILE_LETTER_15
#define TILE_EMPTY   0

//Digit value to tile index
const UINT8 Digits2Tile[] = {
    TILE_DIGIT_0, TILE_DIGIT_1, TILE_DIGIT_2, TILE_DIGIT_3, TILE_DIGIT_4, TILE_DIGIT_5, TILE_DIGIT_6, TILE_DIGIT_7, TILE_DIGIT_8, TILE_DIGIT_9
};


//rightmost digit of the time value X,Y position
#define TIME_VALUE_MOST_X 3
#define TIME_VALUE_MOST_Y 7

UINT8 _hours = 12;
UINT8 _minutes = 34;

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


void showTime(){
    bgClearDigits(TIME_VALUE_MOST_X, TIME_VALUE_MOST_Y);
    bgClearDigits(TIME_VALUE_MOST_X + 4, TIME_VALUE_MOST_Y);

    bgShow3Digits(_hours, TIME_VALUE_MOST_X, TIME_VALUE_MOST_Y);
    bgShow3Digits(_minutes, TIME_VALUE_MOST_X + 4, TIME_VALUE_MOST_Y);
}

void sioInt() {
    
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
 

    //load the normal BG and change the tile lib
    set_bkg_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_tiles(0, 0, Map_Screen1_WIDTH, Map_Screen1_HEIGHT, Map_Screen1);
    
    SHOW_BKG;
    SHOW_SPRITES;

    //handle serial transfer completion
    add_SIO(sioInt);

    
    wait_vbl_done();


    buttonTemporisation = BUTTON_TEMPORISATION;
    while(1) {

        wait_vbl_done();

        //tempo
        if (buttonTemporisation > 0){
            buttonTemporisation--;
        }

        // read joypad
        UINT8 joypadState = joypad();

        if (buttonTemporisation == 0){
            //show time
            showTime();

            //tempo
            buttonTemporisation = BUTTON_TEMPORISATION;
        }


        
        //------------------------------------------------
        // End of frame
        //------------------------------------------------
        delay(MAIN_LOOP_TEMPORISATION);
    }
}



