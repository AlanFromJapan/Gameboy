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

#include "resources/BG-sprites.h"



//main loop temporization (ms)
#define MAIN_LOOP_TEMPORISATION 1000


//UI
#define REFRESH_X 0
#define REFRESH_Y 0


//tile definitions
#define TILE_EMPTY      0x0C
#define TILE_DOT        0x09
#define TILE_REFRESH    0x1a


//tiles for the digits : horizontal, vertical, top left, top right,  bottom left, bottom right, mid-left, mid-right
#define DIGIT_H 0
#define DIGIT_V 1
#define DIGIT_TL 2
#define DIGIT_TR 3
#define DIGIT_BL 4
#define DIGIT_BR 5
#define DIGIT_ML 6
#define DIGIT_MR 7
#define DIGIT_UP 8
#define DIGIT_DOWN 9
#define DIGIT_LEFT 10
#define DIGIT_RIGHT 11

const UINT8 DigitsClearTiles[] = {
    0x01, 0x08, 0x00, 0x02, 0x10, 0x12, 0x18, 0x19, 0x06, 0x07, 0x0E, 0x0F
};
const UINT8 DigitsDarkTiles[] = {
    0x04, 0x0B, 0x03, 0x05, 0x13, 0x15, 0x1B, 0x1C, 0x20, 0x21, 0x28, 0x29
};

UINT8 *currentTiles = DigitsClearTiles;

// Link port Serial related
volatile UINT8 _waiting = 0;



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
    for (UINT8 i = 0; i < 20; i++){
        putTile(TILE_EMPTY, i, tileY);
    }
}

/**
 * Clears the screen
*/
void bgClearScreen (){
    for (UINT8 i = 0; i < 18; i++){
        bgClearRow(i);
    }
}

/**
 * Paints a digit on the background at (x,y) as top left position
*/
void bgDrawDigit(const UINT8 digit, const UINT8 x, const UINT8 y, const UINT8 *tiles){
    switch (digit)
    {
    // 0000000000000000000000000000000000000000000000000000000
    case 0:
        putTile(tiles[DIGIT_TL], x, y);
        putTile(tiles[DIGIT_H], x+1, y);
        putTile(tiles[DIGIT_TR], x+2, y);

        putTile(tiles[DIGIT_V], x, y+1);
        putTile(tiles[DIGIT_V], x+2, y+1);

        putTile(tiles[DIGIT_V], x, y+2);
        putTile(tiles[DIGIT_V], x+2, y+2);

        putTile(tiles[DIGIT_V], x, y+3);
        putTile(tiles[DIGIT_V], x+2, y+3);

        putTile(tiles[DIGIT_BL], x, y+4);
        putTile(tiles[DIGIT_H], x+1, y+4);
        putTile(tiles[DIGIT_BR], x+2, y+4);

        break;
    // 1111111111111111111111111111111111111111111111111111111
    case 1:
        putTile(tiles[DIGIT_UP], x+2, y);

        putTile(tiles[DIGIT_V], x+2, y+1);

        putTile(tiles[DIGIT_V], x+2, y+2);

        putTile(tiles[DIGIT_V], x+2, y+3);

        putTile(tiles[DIGIT_DOWN], x+2, y+4);
        break;        

    // 22222222222222222222222222222222222222222222222222222222
    case 2:
        putTile(tiles[DIGIT_LEFT], x, y);
        putTile(tiles[DIGIT_H], x+1, y);
        putTile(tiles[DIGIT_TR], x+2, y);

        putTile(tiles[DIGIT_V], x+2, y+1);

        putTile(tiles[DIGIT_TL], x, y+2);
        putTile(tiles[DIGIT_H], x+1, y+2);
        putTile(tiles[DIGIT_BR], x+2, y+2);

        putTile(tiles[DIGIT_V], x, y+3);

        putTile(tiles[DIGIT_BL], x, y+4);
        putTile(tiles[DIGIT_H], x+1, y+4);
        putTile(tiles[DIGIT_RIGHT], x+2, y+4);

        break;        

    // 33333333333333333333333333333333333333333333333333333333
    case 3:
        putTile(tiles[DIGIT_LEFT], x, y);
        putTile(tiles[DIGIT_H], x+1, y);
        putTile(tiles[DIGIT_TR], x+2, y);

        putTile(tiles[DIGIT_V], x+2, y+1);

        putTile(tiles[DIGIT_LEFT], x, y+2);
        putTile(tiles[DIGIT_H], x+1, y+2);
        putTile(tiles[DIGIT_MR], x+2, y+2);

        putTile(tiles[DIGIT_V], x+2, y+3);

        putTile(tiles[DIGIT_LEFT], x, y+4);
        putTile(tiles[DIGIT_H], x+1, y+4);
        putTile(tiles[DIGIT_BR], x+2, y+4);

        break;

    // 44444444444444444444444444444444444444444444444444444444
    case 4:
        putTile(tiles[DIGIT_UP], x, y);
        putTile(tiles[DIGIT_UP], x+2, y);

        putTile(tiles[DIGIT_V], x, y+1);
        putTile(tiles[DIGIT_V], x+2, y+1);

        putTile(tiles[DIGIT_BL], x, y+2);
        putTile(tiles[DIGIT_H], x+1, y+2);
        putTile(tiles[DIGIT_MR], x+2, y+2);

        putTile(tiles[DIGIT_V], x+2, y+3);

        putTile(tiles[DIGIT_DOWN], x+2, y+4);

        break;
    // 55555555555555555555555555555555555555555555555555555555
    case 5:
        putTile(tiles[DIGIT_TL], x, y);
        putTile(tiles[DIGIT_H], x+1, y);
        putTile(tiles[DIGIT_RIGHT], x+2, y);

        putTile(tiles[DIGIT_V], x, y+1);

        putTile(tiles[DIGIT_BL], x, y+2);
        putTile(tiles[DIGIT_H], x+1, y+2);
        putTile(tiles[DIGIT_TR], x+2, y+2);

        putTile(tiles[DIGIT_V], x+2, y+3);

        putTile(tiles[DIGIT_LEFT], x, y+4);
        putTile(tiles[DIGIT_H], x+1, y+4);
        putTile(tiles[DIGIT_BR], x+2, y+4);

        break;

    // 66666666666666666666666666666666666666666666666666666666
    case 6:
        putTile(tiles[DIGIT_TL], x, y);
        putTile(tiles[DIGIT_H], x+1, y);
        putTile(tiles[DIGIT_RIGHT], x+2, y);

        putTile(tiles[DIGIT_V], x, y+1);

        putTile(tiles[DIGIT_ML], x, y+2);
        putTile(tiles[DIGIT_H], x+1, y+2);
        putTile(tiles[DIGIT_TR], x+2, y+2);

        putTile(tiles[DIGIT_V], x, y+3);
        putTile(tiles[DIGIT_V], x+2, y+3);

        putTile(tiles[DIGIT_BL], x, y+4);
        putTile(tiles[DIGIT_H], x+1, y+4);
        putTile(tiles[DIGIT_BR], x+2, y+4);

        break;

    // 77777777777777777777777777777777777777777777777777777777
    case 7:
        putTile(tiles[DIGIT_LEFT], x, y);
        putTile(tiles[DIGIT_H], x+1, y);
        putTile(tiles[DIGIT_TR], x+2, y);

        putTile(tiles[DIGIT_V], x+2, y+1);

        putTile(tiles[DIGIT_V], x+2, y+2);

        putTile(tiles[DIGIT_V], x+2, y+3);

        putTile(tiles[DIGIT_DOWN], x+2, y+4);

        break;

    // 88888888888888888888888888888888888888888888888888888888
    case 8:
        putTile(tiles[DIGIT_TL], x, y);
        putTile(tiles[DIGIT_H], x+1, y);
        putTile(tiles[DIGIT_TR], x+2, y);

        putTile(tiles[DIGIT_V], x, y+1);
        putTile(tiles[DIGIT_V], x+2, y+1);

        putTile(tiles[DIGIT_ML], x, y+2);
        putTile(tiles[DIGIT_H], x+1, y+2);
        putTile(tiles[DIGIT_MR], x+2, y+2);

        putTile(tiles[DIGIT_V], x, y+3);
        putTile(tiles[DIGIT_V], x+2, y+3);

        putTile(tiles[DIGIT_BL], x, y+4);
        putTile(tiles[DIGIT_H], x+1, y+4);
        putTile(tiles[DIGIT_BR], x+2, y+4);

        break;
    // 99999999999999999999999999999999999999999999999999999999
    case 9:
        putTile(tiles[DIGIT_TL], x, y);
        putTile(tiles[DIGIT_H], x+1, y);
        putTile(tiles[DIGIT_TR], x+2, y);

        putTile(tiles[DIGIT_V], x, y+1);
        putTile(tiles[DIGIT_V], x+2, y+1);

        putTile(tiles[DIGIT_BL], x, y+2);
        putTile(tiles[DIGIT_H], x+1, y+2);
        putTile(tiles[DIGIT_MR], x+2, y+2);

        putTile(tiles[DIGIT_V], x+2, y+3);

        putTile(tiles[DIGIT_LEFT], x, y+4);
        putTile(tiles[DIGIT_H], x+1, y+4);
        putTile(tiles[DIGIT_BR], x+2, y+4);

        break;

    default:
        break;
    }
}


/**
 * Shows the time centered on the background in current selected tileset
*/
void bgShowTime (const UINT8 h, const UINT8 m) {
    //clear the screen
    bgClearScreen();

    //draw the time    
    bgDrawDigit(h/10, 2, 5, currentTiles);
    bgDrawDigit(h%10, 2 +3 +1, 5, currentTiles);
    
    putTile(TILE_DOT, 10, 5+1);
    putTile(TILE_DOT, 10, 5+3);

    bgDrawDigit(m/10, 11, 5, currentTiles);
    bgDrawDigit(m%10, 11 +3 +1, 5, currentTiles);
}


void receptionFlagON(){
    putTile(TILE_REFRESH, REFRESH_X, REFRESH_Y);
}
void receptionFlagOFF(){
    putTile(TILE_EMPTY, REFRESH_X, REFRESH_Y);
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

    //showValue(v);

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
    set_bkg_data(0, TILE_COUNT, my_tiles);
    bgClearScreen();

    SHOW_BKG;
    //SHOW_SPRITES;

    //handle serial transfer completion
    add_SIO(sioInt);
    
    wait_vbl_done();

    UINT8 h = 9;
    UINT8 m = 45;

    while(1) {
        wait_vbl_done();

        //show time
        m++;
        if (m == 60){
            m = 0;
            h++;
            if (h == 24){
                h = 0;
            }
        }
        bgShowTime(h, m);

        //get time
        getByte();

        //WAIT
        while(_waiting) ;

        delay(MAIN_LOOP_TEMPORISATION );        
    }
}



