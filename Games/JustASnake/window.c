#include "window.h"
#include "my_lib01.h"
#include <stdlib.h>
#include <string.h>


#define WINDOW_W    20
#define WINDOW_H    8

//20 tiles on a screen line, -2 for the borders
#define WINDOW_TEXT_MAXLEN  (WINDOW_W-2)


unsigned char _winBuffer[WINDOW_W * WINDOW_H];


unsigned char _wintextBuffer[WINDOW_TEXT_MAXLEN+1];


inline void windowClean(){
    for (UINT8 wx = 0; wx < WINDOW_W; wx++){
        for (UINT8 wy = 0; wy < WINDOW_H; wy++){
            _winBuffer[WINDOW_W * wy + wx] = TILE_BLACK;
        }
    }

    // UINT8 z = TILE_BLACK;
    // for (UINT8 wx2 = 0; wx2 < 32; wx2++){
    //     for (UINT8 wy2 = 0; wy2 < 32; wy2++){
    //         set_win_tiles(wx2, wy2, 1, 1, &z);
    //     }
    // }    
}

inline void windowWaitForCloseCondition (UINT8 timeoutSec){
    if (timeoutSec != 0){
        delay (1000 * timeoutSec);
    }
    else {
        while (1){
            if(joypad() & J_A) {
                break;
            }
            delay(20);
        
        }
    }

    delay(200);
}

/**
 * Fill in the tiles array with the tile representation of the text.
 * YOU MUST INIT THE ARRAY AND FREE IT BEFORE.
 */
void string2tile(char* msg, UINT8* tiles){

    for (UINT8 i =0; msg[i] != 0; i++){
        UINT8 c = msg[i];

        if (c >='a' && c <= 'z'){
            tiles[i] = (UINT8)c - (UINT8)'a' + (UINT8)TILE_LETTER_LOWER_1;
        }
        else {
            if (c >='0' && c <= '9'){ 
                tiles[i] = (UINT8)c - (UINT8)'0' + (UINT8)TILE_NUMBER_BLACK_1;
            }
            else {
                if (c >='A' && c <= 'Z'){
                    tiles[i] = (UINT8)c - (UINT8)'A' + (UINT8)TILE_LETTER_UPPER_1;              
                }
                else {
                    switch(c){
                        case ' ':
                            tiles[i] = TILE_BLACK;
                            break;
                        case '.':
                            tiles[i] = TILE_LETTER_DOT;
                            break;
                        // case '?':
                        //     tiles[i] = TILE_Q;
                        //     break;
                        case '!':
                            tiles[i] = TILE_LETTER_EXCLAMATION;
                            break;                        
                        case ',':
                            tiles[i] = TILE_LETTER_COMA;
                            break;
                    }
                }
            }
        }

        
    }
}

/**
 * Shows a message in the window, with scroll on press or timeout.
 * Closes after timeout.
 * 
 * Timeout=0 means no timeout
 * 
 */
void windowShowText(char* msg, UINT8 timeoutSec){
    HIDE_WIN;

    windowClean();

    UINT8* tiles = (UINT8*)malloc(WINDOW_TEXT_MAXLEN +1);
    UINT8 lnum = 1;

    for (char* p = msg; ; p += WINDOW_TEXT_MAXLEN) {
        UINT8 vEnd = 0;
        for (UINT8 i = 0; i < WINDOW_TEXT_MAXLEN; i++) {
            _wintextBuffer[i]=p[i];
            if (p[i] == 0)
                vEnd = 1;
        }
        _wintextBuffer[WINDOW_TEXT_MAXLEN] = 0;
        
        string2tile(_wintextBuffer, tiles);

        for (UINT8 i = 0; i < WINDOW_TEXT_MAXLEN && p[i] != 0; i++) {
            _winBuffer[WINDOW_W * lnum + 1 + i] = tiles[i];
        }

        if (vEnd != 0){
            break;
        }
        else {
            lnum++;

            //already inc lnum so next line num is 3, 5, 7, ... odd number
            if ((lnum & 0x01) != 0){
                //...and we still have some text to show
                _winBuffer[WINDOW_H * WINDOW_W -1] = TILE_SNAKE_HEAD;

                set_win_tiles(0,0,WINDOW_W,WINDOW_H, _winBuffer);
                move_win(8, 8*10);

                SHOW_WIN;

                windowWaitForCloseCondition(timeoutSec);

                HIDE_WIN;

                windowClean();

                lnum = 1;
            }
        }
    }
    


    free(tiles);

    set_win_tiles(0,0,WINDOW_W,WINDOW_H, _winBuffer);
    move_win(8, 8 * 10);

    SHOW_WIN;

    windowWaitForCloseCondition(timeoutSec);

    HIDE_WIN;
}