
#include "transitions.h"

#include "my_lib01.h"
#include "Map_Intro.h"
#include "Map_Room1.h"
#include "Map_BigRoom1.h"

#include "graphics.h"

//#include <gb/rand.h>
#include <stdlib.h>

UINT8 mLastMapId=0;

#define MAX(A,B)    ((A) > (B)? (A): (B))

/**
 * Generates a random map
 * 
 */
void makeRandomMap(UINT8** map, UINT8* x, UINT8* y, UINT8* wtile, UINT8* htile){
    //hero start point
    *x=16;
    *y=16;

    //Map size
    *map = dynmap;
    //W: up to 32, min 6
    dynmapW = ((UINT8)(rand() & 0x1f));
    dynmapW = MAX(10, dynmapW);
    //H: up to 8 min 6
    dynmapH = 3 + ((UINT8)(rand() & 0x0f));//max 18
    dynmapH = MAX(9, dynmapH);

    *wtile = dynmapW;
    *htile = dynmapH;

    //make the ground
    switch (rand() & 0x03) {
        case 0:
            clearDynmap(TILE_SAND);
            break;
        case 1:
            clearDynmap(TILE_GRASS_1);
            break;
        default:
            clearDynmap(TILE_EMPTY);
            break;
        
    }

    //put some decorations
    UINT8 vx ;
    UINT8 vy ;
    UINT8 n = rand() & 0x0f;
    for (UINT8 i = 0; i < n; i++){
        //don't care if outside of map
        vx = rand() & 0x1f;
        vy = rand() & 0x0f;

        switch (rand() & 0x03) {
            case 0:
                DYNMAP_PUT_TILE(TILE_GRASS_1, vx, vy);
                break;
            case 1:
                DYNMAP_PUT_TILE(TILE_GRASS_2, vx, vy);
                break;
            case 2:
                DYNMAP_PUT_TILE(TILE_REMAINS_NW, vx, vy);
                DYNMAP_PUT_TILE(TILE_REMAINS_NE, vx+1, vy);
                DYNMAP_PUT_TILE(TILE_REMAINS_SW, vx, vy+1);
                DYNMAP_PUT_TILE(TILE_REMAINS_SE, vx+1, vy+1);
                break;
            case 3:
                DYNMAP_PUT_TILE(TILE_GROUND1_NW, vx, vy);
                DYNMAP_PUT_TILE(TILE_GROUND1_NE, vx+1, vy);
                DYNMAP_PUT_TILE(TILE_GROUND1_SW, vx, vy+1);
                DYNMAP_PUT_TILE(TILE_GROUND1_SE, vx+1, vy+1);
                break;
        default:
            break;
        }
    }


    //put a wall all around
    for (UINT8 i = 0; i < dynmapW; i++){
        //top
        DYNMAP_PUT_TILE(TILE_TOWER_3, i, 0);
        //bottom
        DYNMAP_PUT_TILE(TILE_TOWER_3, i, dynmapH-1);        
    }
    for (UINT8 i = 0; i < dynmapH; i++){
        //left
        DYNMAP_PUT_TILE(TILE_TOWER_3, 0, i);
        //right
        DYNMAP_PUT_TILE(TILE_TOWER_3, dynmapW-1, i);
    }

    //put a door somewhere
    vx = rand() & 0x1f;
    vy = rand() & 0x0f;

    if (vx >= dynmapW)
        vx=dynmapW -2;
    if (vy >= dynmapH)
        vy=dynmapH -2;

    if (vx == 0 || vy == 0 || vx==dynmapW -2 || vy == dynmapH -2) {
        //against a WALL is a DOOR
        DYNMAP_PUT_TILE(TILE_DOOR_NW, vx, vy);
        DYNMAP_PUT_TILE(TILE_DOOR_NE, vx+1, vy);
        DYNMAP_PUT_TILE(TILE_DOOR_SW, vx, vy+1);
        DYNMAP_PUT_TILE(TILE_DOOR_SE, vx+1, vy+1);
    }
    else {
        //otherwise stairs
        DYNMAP_PUT_TILE(TILE_STAIRS_DOWN_NW, vx, vy);
        DYNMAP_PUT_TILE(TILE_STAIRS_DOWN_NE, vx+1, vy);
        DYNMAP_PUT_TILE(TILE_STAIRS_DOWN_SW, vx, vy+1);
        DYNMAP_PUT_TILE(TILE_STAIRS_DOWN_SE, vx+1, vy+1);
    }


}

/**
 * Makes a map 20w x 32h filled with bgTile
 * 
 */
inline void mapMakeVerticalMessage (UINT8 * * map, UINT8 bgTile){

    *map = dynmap;
    dynmapW = 20;
    dynmapH = 32;

    clearDynmap(bgTile);

}

/**
 * When transition from a given map, by a transition at point x,y (MAP coordinate)
 * 
 */
void mapTransition(UINT8** map, UINT8* x, UINT8* y, UINT8* wtile, UINT8* htile){
    if (mLastMapId == 0) {

        if (*map == Map_Room1) {
            //Room1 -> BigRoom1
            *x=16;
            *y=16;
            *map = Map_BigRoom1;
            *wtile = Map_BigRoom1_WIDTH;
            *htile = Map_BigRoom1_HEIGHT;
            mLastMapId = 1;
        }
        else {
            //enter in Room1
            *x=16;
            *y=32;
            *map = Map_Room1;
            *wtile = Map_Room1_WIDTH;
            *htile = Map_Room1_HEIGHT;
            //mLastMapId = 1; //stay out of the random map loop
        }

        srand(DIV_REG);
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

