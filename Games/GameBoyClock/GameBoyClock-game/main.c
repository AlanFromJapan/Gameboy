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
#define MAIN_LOOP_TEMPORISATION 100


//UI
#define REFRESH_X 0
#define REFRESH_Y 0


//////////////////////////////////////////////
//tile definitions
#define TILE_EMPTY      0x0C
#define TILE_DOT        0x09
#define TILE_REFRESH    0x1a


//////////////////////////////////////////////
//tiles for the BIG digits : horizontal, vertical, top left, top right,  bottom left, bottom right, mid-left, mid-right
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


//////////////////////////////////////////////
// Tiles for seconds
#define DIGIT_SECONDS_0 0x2e

//////////////////////////////////////////////
// Tiles for logo and URL
const UINT8 LogoTiles[] = {0x1D, 0x1e, 0x1f};
const UINT8 UrlTiles[] = {0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e};

UINT8 *currentTiles = DigitsClearTiles;

//////////////////////////////////////////////
// Link port Serial related

//give a little time to the daughter board to get ready (though way faster than present GB)
#define SERIAL_REQUEST_RESPONSE_BUFFER_MS 5
//different states of waiting
#define WAITING_NOTHING 0
#define WAITING_RECEIVE 1
#define WAITING_SEND 2
volatile UINT8 _waiting = WAITING_NOTHING;

#define WAITING_FOR_H 'H'
#define WAITING_FOR_M 'M'
#define WAITING_FOR_S 'S'
volatile UINT8 _waiting_for = WAITING_FOR_H;


//////////////////////////////////////////////
//the time
volatile UINT8 h = 0;
volatile UINT8 m = 0;
volatile UINT8 s = 0;

volatile UINT8 oldh = 255;
volatile UINT8 oldm = 255;
volatile UINT8 olds = 255;

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


void blinkDots(){
    //add the dots
    if (s % 2 == 0){
        putTile(TILE_DOT, 8, 5+1);
        putTile(TILE_DOT, 8, 5+3);
    } else {
        putTile(TILE_EMPTY, 8, 5+1);
        putTile(TILE_EMPTY, 8, 5+3);
    }
}


/**
 * Clears the screen
*/
void bgClearScreen (){
    for (UINT8 i = 0; i < 18; i++){
        bgClearRow(i);
    }

    //add the dots
    blinkDots();

    //add the title
    for (UINT8 i = 0; i < 3; i++){
        putTile(LogoTiles[i], 9 + i, 18-2);
    }
    //add the URL
    for (UINT8 i = 0; i < 7; i++){
        putTile(UrlTiles[i], 7 + i, 18-1);
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
        //CLEARS the digit (= fill with empty)
        putTile(TILE_EMPTY, x, y);
        putTile(TILE_EMPTY, x+1, y);
        putTile(TILE_EMPTY, x+2, y);

        putTile(TILE_EMPTY, x, y+1);
        putTile(TILE_EMPTY, x+2, y+1);

        putTile(TILE_EMPTY, x, y+2);
        putTile(TILE_EMPTY, x+1, y+2);
        putTile(TILE_EMPTY, x+2, y+2);

        putTile(TILE_EMPTY, x, y+3);
        putTile(TILE_EMPTY, x+2, y+3);

        putTile(TILE_EMPTY, x, y+4);
        putTile(TILE_EMPTY, x+1, y+4);
        putTile(TILE_EMPTY, x+2, y+4);        
        break;
    }
}


//Checks if the digit has changed and redraws it if needed (to avoid flickering)
// ie: time moved from --:34 to --:35, only the last digit should be redrawn
inline void bgShowTimeDigit (const UINT8 old, const UINT8 new, const UINT8 x, const UINT8 y){
    if (old != new){
        //if changed clear and rewrite
        bgDrawDigit(255, x, y, currentTiles);
        bgDrawDigit(new, x, y, currentTiles);
    }
}

/**
 * Shows the time centered on the background in current selected tileset
*/
void bgShowTime () {
#define TIME_Y 5
#define TIME_X 2

    if (oldh != h){
        bgShowTimeDigit(oldh/10, h/10, TIME_X, TIME_Y);
        bgShowTimeDigit(oldh%10, h%10, TIME_X +3 , TIME_Y);
    }

    if (oldm != m){
        bgShowTimeDigit(oldm/10, m/10, TIME_X+ 3 + 4, TIME_Y);
        bgShowTimeDigit(oldm%10, m%10, TIME_X+ 3 + 4 +3, TIME_Y);
    }

    if (olds != s){
        putTile(DIGIT_SECONDS_0 + s/10, TIME_X+ 3 + 4 +3 + 4, TIME_Y +4);
        putTile(DIGIT_SECONDS_0 + s%10, TIME_X+ 3 + 4 +3 + 4 +1, TIME_Y +4);

        blinkDots();
    }

    oldh = h;
    oldm = m;
    olds = s;

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
 * SEND one byte from the serial port
 */
void sendByte(){
    _waiting = WAITING_SEND;

    receptionFlagON();

    //_waiting_for is already the CHAR to send (NEXT time component to get)
    _io_out = (UINT8)_waiting_for;

    //send
    send_byte();
}

/**
 * Get one byte from the serial port
 */
void getByte(){
    _waiting = WAITING_RECEIVE;

    receptionFlagON();

    receive_byte_self_clock();
}

/**
 * Serial transfer completion (vector interrupt)
 */
void sioInt() {
    UINT8 v = _io_in;

    if (_waiting == WAITING_RECEIVE){
        //store the value, then prepare to wait for the next one
        switch (_waiting_for)
        {
            case WAITING_FOR_H:
                h = v;
                _waiting_for = WAITING_FOR_M;
                break;
            case WAITING_FOR_M:
                m = v;
                _waiting_for = WAITING_FOR_S;
                break;
            case WAITING_FOR_S:
                s = v;
                _waiting_for = WAITING_FOR_H;
                break;
        }
    }

    receptionFlagOFF();

    //stop waiting
    _waiting = WAITING_NOTHING;
}

/**
 * Vertical blank interrupt: where we "draw" memory while screen is not updated
 */
void vblint(){

    bgShowTime();

}


/*
 ***********************************************************************************************
 * MAIN method
 ***********************************************************************************************
 */
void main() {

    //init time 
    h = 0;
    m = 0;
    s = 0;

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
    //branch interrup handler for VBlank
    add_VBL(vblint);

    while(1) {
        wait_vbl_done();

        UINT8 lastJoypad = joypad();
        if (lastJoypad & J_A){
            currentTiles = DigitsDarkTiles;
            //force refresh
            oldh = 255;
            oldm = 255;
            olds = 255;
        } 
        if (lastJoypad & J_B){
            currentTiles = DigitsClearTiles;
            //force refresh
            oldh = 255;
            oldm = 255;
            olds = 255;
        } 

        //send a byte to ask for H or M or S
        sendByte();

        //WAIT
        while(_waiting) ;

        //give time to the daughter board to get ready
        delay(SERIAL_REQUEST_RESPONSE_BUFFER_MS);

        //get the time info
        getByte();

        //WAIT
        while(_waiting) ;

        delay(MAIN_LOOP_TEMPORISATION );        
    }
}



