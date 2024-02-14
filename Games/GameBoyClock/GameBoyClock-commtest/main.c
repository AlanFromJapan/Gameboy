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
#define MAIN_LOOP_TEMPORISATION 500


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

volatile UINT8 _hours = 12;
volatile UINT8 _minutes = 34;

//flag
#define FLAG_X  1
#define FLAG_Y  1

//state of the communication
#define STATE_ASK_HOURS 0
#define STATE_ASK_MINUTES 1
#define STATE_ASK_END 2
volatile UINT8 _state = STATE_ASK_HOURS;

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
    putTile(Digits2Tile[d % 10], tileX -1, tileY);
    
}


void showTime(){
    bgClearDigits(TIME_VALUE_MOST_X, TIME_VALUE_MOST_Y);
    bgClearDigits(TIME_VALUE_MOST_X + 3, TIME_VALUE_MOST_Y);

    bgShow3Digits(_hours, TIME_VALUE_MOST_X, TIME_VALUE_MOST_Y);
    bgShow3Digits(_minutes, TIME_VALUE_MOST_X + 3, TIME_VALUE_MOST_Y);
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
 * Get the time from the RTC via Link data cable
 */
void getTime(){

    switch (_state)
    {
        case STATE_ASK_HOURS:
            //send the hours
            receptionFlagON();

            _state = STATE_ASK_MINUTES;
            _io_out = 'H';
            receive_byte_self_clock();
            break;
        case STATE_ASK_MINUTES: 
            //send the minutes
            _state = STATE_ASK_END;
            _io_out = 'M';
            receive_byte_self_clock();
            break;
        case STATE_ASK_END:
            //show time
            showTime();
            
            receptionFlagOFF();

            //end of communication
            _state = STATE_ASK_HOURS;
            break;
    
    }


}

/**
 * Serial transfer completion (vector interrupt)
 */
void sioInt() {

    switch (_state)
    {
        case STATE_ASK_MINUTES:
            //got the hours
            _hours = _io_in;
            //get the mins
            getTime();
            break;
        case STATE_ASK_END:
            //got the minutes
            __asm__(
                "LD     A,(0x01)    ;put SB (buffer) in A\n"
                "LD	    (__io_in),A ;put the A in __io_in\n"
            );
            _minutes = _io_in;
            //show time
            getTime();
            break;
    }
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
        getTime();


        // _minutes++;
        // if (_minutes >= 60){
        //     _minutes = 0;
        //     _hours++;
        //     if (_hours >= 24){
        //         _hours = 0;
        //     }
        // }




    
        //------------------------------------------------
        // End of frame
        //------------------------------------------------
        delay(MAIN_LOOP_TEMPORISATION);
    }
}



