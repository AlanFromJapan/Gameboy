#include "game.h"

#include <gb/gb.h>
#include <gb/drawing.h>

//#include <gb/rand.h>
#include <stdlib.h>

#include "Map_SplashScreen.h"
#include "Map_About.h"
#include "Map_Arene.h"

#include "window.h"

UINT8 currentItemNumber = 1;
UINT8 maxItemNumber = ITEMS_PER_LEVEL_NORMAL;

UINT8 heartsCount = HEART_DEFAULT;

UINT8 backgroundTile = TILE_EMPTY;
UINT8* currentArenaMap = Map_Arene;

UINT16 score = 0;

UINT8 speed = SPEED_START;


/**
 * Set a background tile to the tile in parameter
 */
void putTile(UINT8 tile, UINT8 x, UINT8 y){
    //NOT inline so tile is a byte in the call stack so you can ref its address
    set_bkg_tiles(x, y, 1, 1, &tile);

}

/**
 * Finds an empty space fit for dropping item
 */
inline void findEmptyDropTile (UINT8* x, UINT8* y){
    UINT8 t;

    //loop until it works
    while (1){
        *x = rand() & 0x1f; //max 32
        *y = rand() & 0x0f; //max 16
        if (*x >= Map_Arene_WIDTH)
            *x = (*x)/2;
        
        get_bkg_tiles(*x, *y, 1, 1, &t);
        if (t == backgroundTile){
            //empty spot!
            //exit the loop
            return;
        }
    }
}

/**
 * Puts a bonbon somewhere on the map randomly
 */
void drop_bonbon(){
    UINT8 x, y;

    findEmptyDropTile(&x, &y);

    putTile(TILE_BONBON, x, y);    
}


/**
 * Puts a heart somewhere on the map randomly
 */
void drop_heart(){
    UINT8 x, y;

    findEmptyDropTile(&x, &y);

    putTile(TILE_HEART_FULL, x, y);    
}




/**
 * Update the score display
 */
void updateScore(){
    UINT8 v = 0;

    v = score % 10;
    putTile(TILE_NUMBER_BLACK_1 + v, Map_Arene_WIDTH-2, Map_Arene_HEIGHT-1);
    v = (score / 10) % 10;
    putTile(TILE_NUMBER_BLACK_1 + v, Map_Arene_WIDTH-3, Map_Arene_HEIGHT-1);
    v = (score / 100) % 10;
    putTile(TILE_NUMBER_BLACK_1 + v, Map_Arene_WIDTH-4, Map_Arene_HEIGHT-1);
    v = (score / 1000) % 10;
    putTile(TILE_NUMBER_BLACK_1 + v, Map_Arene_WIDTH-5, Map_Arene_HEIGHT-1);
}


/**
 * Update the hearts display
 */
void updateHearts(){
    
    UINT8 i = 0;
    for (i=0; i < HEART_MAX; i++){
        putTile(TILE_HEART_0, 2+i, Map_Arene_HEIGHT-1);
    }
    for (i=0; i < heartsCount; i++){
        putTile(TILE_HEART_FULL, 2+i, Map_Arene_HEIGHT-1);
    }

}

/**
 * Shows Pause screen
 */
void showPause(){
    windowShowText("Quick pause...\n\n\n\n\nPress A or Start", 0);

}