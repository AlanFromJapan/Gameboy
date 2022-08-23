#include "windows.h"
#include "maps/my_lib01.h"
#include <stdlib.h>
#include <string.h>
#include "hero.h"
#include "graphics.h"

//20 tiles on a screen line, -2 for the borders
#define WINDOW_TEXT_MAXLEN  18

#define WINDOW_W    20
#define WINDOW_H    4

unsigned char _winBuffer[] = {
    TILE_WINDOW_1, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_2, TILE_WINDOW_3,
    TILE_WINDOW_4, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_WINDOW_5,
    TILE_WINDOW_4, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_WINDOW_5,
    TILE_WINDOW_6, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_7, TILE_WINDOW_8,

};

unsigned char _wintextBuffer[WINDOW_TEXT_MAXLEN+1];

//HUD size
#define HUD_WIDTH       20
#define HUD_HEIGHT      1

//The buffer for HUD window: just 1 line (20 tiles)
unsigned char _hudBuffer[HUD_WIDTH * HUD_HEIGHT];


inline void windowClean(){
    for (UINT8 wx = 1; wx < 1+WINDOW_TEXT_MAXLEN; wx++){
        for (UINT8 wy = 1; wy < 3; wy++){
            _winBuffer[WINDOW_W * wy + wx] = TILE_EMPTY;
        }
    }

    _winBuffer[20*4-1] = TILE_WINDOW_8;
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
            _winBuffer[20 * lnum + 1 + i] = tiles[i];
        }

        if (vEnd != 0){
            break;
        }
        else {
            lnum++;

            //already inc lnum so next line num is 3, 5, 7, ... odd number
            if ((lnum & 0x01) != 0){
                //...and we still have some text to show
                _winBuffer[20*4-1] = TILE_HEART_HALF;

                set_win_tiles(0,0,WINDOW_W,WINDOW_H, _winBuffer);
                move_win(7, 8 * (12+2));

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
    move_win(7, 8 * (12+2));

    SHOW_WIN;

    windowWaitForCloseCondition(timeoutSec);

    HIDE_WIN;
}

/**
 * Shows the HUD
 */
void showHUD(){
    //init
    for (UINT8 i = 0; i < HUD_HEIGHT * HUD_WIDTH; i++){
        _hudBuffer[i] = TILE_EMPTY;
    }
    
    updateHUD();

    SHOW_WIN;
    //screen bottom: align to X=8 to be fit to the border (0 makes strange results) #shrug
    move_win(8, SCREENHEIGHT - 8);
}

/**
 * Updates the info displayed on the HUD (hearts, points, ...)
 */
void updateHUD(){
    //fills the heart bar
    //LIFE is DOUBLED to use the half hearts
    for (UINT8 i = 0; i < hero.lifeMax /2; i++){
        _hudBuffer[i] = TILE_HEART_0;
    }
    for (UINT8 i = 0; i < hero.life/2; i++){
        _hudBuffer[i] = TILE_HEART_FULL;
    }
    if (hero.life % 2 == 1){
        //half heart
        _hudBuffer[hero.life/2] = TILE_HEART_HALF;
    }

    //score or something ... we'll see
    _hudBuffer[17] = TILE_NUMBER_2;
    _hudBuffer[18] = TILE_NUMBER_3;
    _hudBuffer[19] = TILE_NUMBER_4;

    set_win_tiles(0,0,HUD_WIDTH,HUD_HEIGHT, _hudBuffer);
}


