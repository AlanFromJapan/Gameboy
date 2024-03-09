/*##########################################################
# GameBoyClock-rcvdbg
#
# Shows the received byte as byte, char and binary
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
 * Shows number as binary
 */
void bgShowBinary(const UINT8 val, const UINT8 tileX, const UINT8 tileY) {
    
    UINT8 d = val;
    for (UINT8 i = 0; i < 8; i++){
        putTile(Digits2Tile[d % 2], tileX + 8 - i, tileY);
        d = d >> 1;
    }
}


void showValue (UINT8 val){
    //format : |x ddd bbbbbbbb ...|
    //x : 1 if the value as a char (caps only), ddd the decimal value, bbbbbbbb the binary value

    //x
    putTile(val + TILE_LETTER_1, 1, _currentRow);

    //ddd
    bgShow3Digits(val, 3, _currentRow);

    //bbbbbbbb
    bgShowBinary(val, 8, _currentRow);

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
 * Serial reception start BUT using the INTERNAL clock of the GB
 */
void receive_byte_self_clock(){
    ///modified version of _receive_byte() in serial.s to use *INTERNAL* clock of the GB
    __asm__(

"LD	A,#0x02   ;.IO_RECEIVING\n"
"LD	(__io_status),A ; Store status\n"
"LD	A,#0x01             ; <== CHANGED from XOR A\n" 
"LDH	(0x02),A		; Use ***INTERNAL*** clock\n"
"LD	A,#0x55    ;.DT_RECEIVING\n"
"LDH	(0x01),A		; Send RECEIVING byte\n"
"LD	A,#0x81             ; <== CHANGED HERE from 0x80\n"
"LDH	(0x02),A		; Use ***INTERNAL*** clock\n"


    );


}

/**
 * Get one byte from the serial port
 */
void getByte(){
    _waiting = 1;

    receptionFlagON();

    receive_byte_self_clock();
}

/**
 * Serial transfer completion (vector interrupt)
 */
void sioInt() {
    UINT8 v = _io_in;

    showValue(v);

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
        getByte();

        //WAIT
        while(_waiting) ;

        delay(MAIN_LOOP_TEMPORISATION );        
    }
}



