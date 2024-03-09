/*##########################################################
# GameBoyClock-snddbg
#
# Sends a byte at a time and displays it on the screen
#
*/

#include <gb/gb.h>
#include <gb/drawing.h>

//for rand()
#include <stdlib.h>

#include "my_lib01.h"
#include "Map_Screen1.h"



//main loop temporization (ms)
#define MAIN_LOOP_TEMPORISATION 1000

//flag
#define FLAG_X  18
#define FLAG_Y  1

//Some tiles defintions
#define TILE_DIGIT_0 TILE_LETTER_15
#define TILE_EMPTY   0

//Digit value to tile index
const UINT8 Digits2Tile[] = {
    TILE_DIGIT_0, TILE_DIGIT_1, TILE_DIGIT_2, TILE_DIGIT_3, TILE_DIGIT_4, TILE_DIGIT_5, TILE_DIGIT_6, TILE_DIGIT_7, TILE_DIGIT_8, TILE_DIGIT_9
};


#define MAX_ROW (18-1)
#define MIN_ROW 1
volatile UINT8 _waiting = 0;
volatile UINT8 _currentRow = 1;

const char MESSAGE[] = "Hello World";
volatile UINT8 _currenctChar = 0;

/**
 * Set a background tile to the tile in parameter
 */
void putTile(UINT8 tile, UINT8 x, UINT8 y){
    //NOT inline so tile is a byte in the call stack so you can ref its address
    set_bkg_tiles(x, y, 1, 1, &tile);
}

/**
 * Clears the row
 */
void bgClearRow(const UINT8 tileY){
    //clear except the borders
    for (UINT8 i = 1; i < 20-1; i++){
        putTile(TILE_EMPTY, i, tileY);
    }
}

/**
 * Shows a 3 digits number on the background
 */
void bgShow3Digits(const UINT8 val, const UINT8 tileX, const UINT8 tileY) {

    //display
    UINT8 d = val;
    putTile(Digits2Tile[d % 10], tileX +2, tileY);

    d = d / (UINT8)10;
    putTile(Digits2Tile[d % 10], tileX +2 -1, tileY);

    d = d / (UINT8)10;
    putTile(Digits2Tile[d % 10], tileX +2 -2, tileY);

}



/**
 * Shows a value on the screen
 * @param val the CHAR to display
 */
void showValue (const char val){
    //format : |x ddd  ...|
    //x : 1 if the value as a char (caps only), ddd the decimal value

    //x
    UINT8 x = val - 'A';
    if (val >= 'a' && val <= 'z')
        x = val - 'a';

    putTile(x + TILE_LETTER_1, 1, _currentRow);

    //ddd
    bgShow3Digits(val, 3, _currentRow);


    //go next line and clear it
    _currentRow++;
    if (_currentRow >= MAX_ROW)
        _currentRow = MIN_ROW;
    bgClearRow(_currentRow);
}

void receptionFlagON(){
    putTile(TILE_CROIX, FLAG_X, FLAG_Y);
}
void receptionFlagOFF(){
    putTile(TILE_EMPTY, FLAG_X, FLAG_Y);
}


/**
 * SEND one byte from the serial port
 */
void sendByte(){
    _waiting = 1;

    receptionFlagON();

    showValue(MESSAGE[_currenctChar]);
    _io_out =  MESSAGE[_currenctChar];
    _currenctChar++;
    if (_currenctChar >= sizeof(MESSAGE))
        _currenctChar = 0;

    //send
    send_byte();
}

/**
 * Serial transfer completion (vector interrupt)
 */
void sioInt() {
    receptionFlagOFF();

    //stop waiting
    _waiting = 0;
}




/*
 ***********************************************************************************************
 * MAIN method
 ***********************************************************************************************
 */
void main() {

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

    while(1) {
        wait_vbl_done();

        //get time
        sendByte();

        //WAIT
        while(_waiting) ;


        delay(MAIN_LOOP_TEMPORISATION );        
    }
}



