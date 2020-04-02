
#include "transitions.h"

#include "my_lib01.h"
#include "Map_Intro.h"
#include "Map_Room1.h"

#include "graphics.h"

#include <gb/rand.h>

UINT8 mLastMapId=0;


void makeRandomMap(UINT8** map, UINT8* x, UINT8* y, UINT8* wtile, UINT8* htile){
    *x=16;
    *y=32;

    *map = dynmap;
    dynmapW = 10 + ((UINT8)(rand() & 0x0f));
    dynmapH = 10 + ((UINT8)(rand() & 0x0f));
    *wtile = dynmapW;
    *htile = dynmapH;

    //make the ground
    clearDynmap(TILE_SAND);

    //put a door somewhere
    UINT8 vx = ((UINT16)dynmapW * (UINT16)_rand()) / (UINT16)256 ;
    UINT8 vy = ((UINT16)dynmapH * (UINT16)_rand()) / (UINT16)256 ;



    DYNMAP_PUT_TILE(TILE_DOOR_NW, vx, vy);
    DYNMAP_PUT_TILE(TILE_DOOR_NE, vx+1, vy);
    DYNMAP_PUT_TILE(TILE_DOOR_SW, vx, vy+1);
    DYNMAP_PUT_TILE(TILE_DOOR_SE, vx+1, vy+1);


    dynmap[1] = TILE_DOOR_NW;
    dynmap[2] = TILE_DOOR_NE;
    dynmap[dynmapW * 1 +1] = TILE_DOOR_SW;
    dynmap[dynmapW * 1 + 2] = TILE_DOOR_SE;

}


/**
 * When transition from a given map, by a transition at point x,y (MAP coordinate)
 * 
 */
void mapTransition(UINT8** map, UINT8* x, UINT8* y, UINT8* wtile, UINT8* htile){

    
    if (mLastMapId == 0) {
        *x=16;
        *y=32;

        *map = Map_Room1;
        *wtile = Map_Room1_WIDTH;
        *htile = Map_Room1_HEIGHT;
        mLastMapId = 1;

        initrand(DIV_REG); 
    }
    else {
        //clear the full dynmap, refresh the screen
        clearDynmap(TILE_EMPTY);
        set_bkg_tiles(0, 0, DynMap_MAX_WIDTH, DynMap_MAX_HEIGHT, dynmap);

        //make a new map
        makeRandomMap (map, x, y, wtile, htile);        
    }


    set_bkg_tiles(0, 0, *wtile, *htile, *map );
}

