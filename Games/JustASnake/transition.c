#include "transition.h"

#include "Map_Arene.h"
#include "Map_Arene2.h"
#include "Map_Arene3.h"
#include "Map_Arene4.h"
#include "Map_Arene5.h"
#include "Map_Arene6.h"
#include "Map_Arene7.h"
#include "Map_Arene8.h"
#include "Map_Arene9.h"
#include "Map_Arene10.h"
#include "Map_Arene11.h"
#include "Map_Arene12.h"
#include "Map_Arene13.h"
#include "Map_Arene14.h"
#include "Map_Arene15.h"
#include "Map_Arene16.h"
#include "Map_Arene17.h"
#include "Map_Arene18.h"
#include "Map_Arene19.h"
#include "Map_Arene20.h"

#include "my_lib01.h"

#include "Map_SplashScreen.h"
#include "Map_About.h"
#include "Map_Options.h"
#include "window.h"

#include "game.h"

struct ArenaBucket {
    UINT8*  arena;
    UINT8   bgTile;
    UINT8   startX;
    UINT8   startY;
};

/*******************************************************************************************/
/**  ARENAS List for transition on victory                                                **/
/*******************************************************************************************/
#define ARENAS_COUNT    20
const struct ArenaBucket _arenas[] = {
    /* Map          Background tile        Start X,Y          */
    {Map_Arene,     TILE_EMPTY,             10, 8}, //Level 1
    {Map_Arene2,    TILE_EMPTY,             10, 8}, //Level 2
    {Map_Arene3,    TILE_EMPTY,             10, 2}, //Level 3
    {Map_Arene9,    TILE_DIAGBRICK2,        10, 4}, //Level 4
    {Map_Arene6,    TILE_EMPTY,             10, 8}, //Level 5
    {Map_Arene8,    TILE_SAND,              10, 8}, //Level 6
    {Map_Arene15,   TILE_DIAGBRICK2,        10, 2}, //Level 7
    {Map_Arene7,    TILE_SAND,              10, 5}, //Level 8
    {Map_Arene10,   TILE_DIAGBRICK2,        10, 4}, //Level 9
    {Map_Arene4,    TILE_EMPTY,             10, 2}, //Level 10
    {Map_Arene18,   TILE_SAND,              12, 3}, //Level 11
    {Map_Arene16,   TILE_DIAGBRICK2,        10, 2}, //Level 12
    {Map_Arene5,    TILE_SAND,              12, 9}, //Level 13
    {Map_Arene11,   TILE_EMPTY,             10, 1}, //Level 14
    {Map_Arene12,   TILE_SAND,              10, 3}, //Level 15
    {Map_Arene13,   TILE_DIAGBRICK2,        12, 3}, //Level 16
    {Map_Arene19,   TILE_SAND,              12, 1}, //Level 17
    {Map_Arene20,   TILE_DIAGBRICK2,        12, 1}, //Level 18
    {Map_Arene17,   TILE_EMPTY,             12, 1}, //Level 19
    {Map_Arene14,   TILE_EMPTY,             12, 1}, //Level 20
};
UINT8 _currentArenaId = 0; 
/*******************************************************************************************/


void arenaTransition(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY) {
    _currentArenaId = (_currentArenaId +1) % ARENAS_COUNT;

    *nextArena = _arenas[_currentArenaId].arena;
    *backgroundTile = _arenas[_currentArenaId].bgTile;
    *startX = _arenas[_currentArenaId].startX;
    *startY = _arenas[_currentArenaId].startY;
}


void arenaTransitionBackToLevel1(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY) {
    //trick so when called it turns to zero = the first level
    _currentArenaId = ARENAS_COUNT-1;

    arenaTransition(nextArena, backgroundTile, startX, startY);
}

void arenaReset(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY) {
    *nextArena = _arenas[_currentArenaId].arena;
    *backgroundTile = _arenas[_currentArenaId].bgTile;
    *startX = _arenas[_currentArenaId].startX;
    *startY = _arenas[_currentArenaId].startY;
}

inline UINT8 getCurrentArenaId(){
    return _currentArenaId;
}

/**
 * Shows title screen
 * 
 */
UINT8 showTitle(){
    set_bkg_tiles(0, 0, Map_SplashScreen_WIDTH, Map_SplashScreen_HEIGHT, Map_SplashScreen);
    SHOW_BKG;

    //create the first sprit as option marker
    set_sprite_tile(0, TILE_PLAYER_SMALL);


    UINT8 t = 0;
    UINT8 stat = 0;
    UINT8 tmax = 15;
    UINT8 mnu = TITLEMENU_PLAY;
    while(1) {
        if(joypad() & J_A || joypad() & J_START) {
            break;
        }
        if(joypad() & J_DOWN) {
            mnu = (mnu + 1)% 3;
        }
        if(joypad() & J_UP) {
            mnu = mnu -1;
            if (mnu == 255)
                mnu = 2;
        }

        switch (mnu){
            case TITLEMENU_PLAY:
                move_sprite(0, 8* 8, 8* 13);
                putTile(TILE_EMPTY, 7, 11);
                putTile(TILE_BLACK, 2, 14);
                putTile(TILE_BLACK, 10, 14);
                break;
            case TITLEMENU_OPTIONS:
                move_sprite(0, 8* 3, 8* 16);
                putTile(TILE_BLACK, 7, 11);
                putTile(TILE_EMPTY, 2, 14);
                putTile(TILE_BLACK, 10, 14);
                break;
            case TITLEMENU_CREDITS:
                move_sprite(0, 8* 11, 8* 16);
                putTile(TILE_BLACK, 7, 11);
                putTile(TILE_BLACK, 2, 14);
                putTile(TILE_EMPTY, 10, 14);
                break;
        }


        delay(100);
        t++;

        if (t== tmax){
            if (stat == 0){
                set_sprite_tile(0, TILE_PLAYER_ALT);
                stat = 1;
                tmax = 1;
                t = 0;
            }
            else {
                set_sprite_tile(0, TILE_PLAYER_SMALL);
                stat = 0;
                tmax = 15;
                t=0;
            }
            
        }
    }

    HIDE_BKG;
    HIDE_SPRITES;

    //debouncing
    delay(200);

    return mnu;
}

#define USE_BUILD_TIME
/**
 * Shows credits screen
 * 
 */
void showCredits(){
    set_bkg_tiles(0, 0, Map_About_WIDTH, Map_About_HEIGHT, Map_About);
    SHOW_BKG;

#ifdef USE_BUILD_TIME
    UINT8 lblTiles[11+1];

    //make tiles from the time based on the __DATE__ compile time variable
    string2tile(__DATE__, lblTiles);
    
    //write it on the background
    for (UINT8 t = 0; t < 11; t++){
        putTile(lblTiles[t], 8+t, 16);
    }
#endif 

    while(1) {
        if(joypad() & J_A) {
            break;
        }
        if(joypad() & J_START) {
            break;
        }

        delay(10);
    }


    //debouncing
    delay(200);
}

/**
 * Shows options screen
 * 
 */
void showOptions(){
    set_bkg_tiles(0, 0, Map_Options_WIDTH, Map_Options_HEIGHT, Map_Options);
    SHOW_BKG;

    while(1) {
        if(joypad() & J_A) {
            break;
        }
        if(joypad() & J_START) {
            break;
        }

        delay(10);
    }


    //debouncing
    delay(200);
}