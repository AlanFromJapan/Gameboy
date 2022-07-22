
#include "transitions.h"

#include "my_lib01.h"
#include "Map_Intro.h"
#include "Map_Room1.h"
#include "Map_BigRoom1.h"

#include "graphics.h"
#include <gb/drawing.h>

//#include <gb/rand.h>
#include <stdlib.h>

//Flag defining which map we are in. Default is 0 (fixed rooms), or >=1 means various random maps.
UINT8 mMapTransitionModeFlag=0;


unsigned char *currentMap;
unsigned int currentMapW_Tile = SCREEN_TILES_WIDTH;
unsigned int currentMapH_Tile = SCREEN_TILES_HEIGHT;


#define MAX(A,B)    ((A) > (B)? (A): (B))
#define MIN(A,B)    ((A) < (B)? (A): (B))

#define RAND_ROOM_MIN_WIDTH     6

//const UINT8 _RoomDecorationsCount = 8;
const UINT8 _RoomDecorations[] = {TILE_PENTAGRAM_NW, TILE_TABLE_NW, TILE_MARBLE_STELE_NW, TILE_TORCH_NW, TILE_CRANE_NW, TILE_CRYSTAL_NW, TILE_REMAINS_NW, TILE_REMAINS_NW};

/**
 * Generates a random map with rooms
 * 
 */
void makeRandomMapRooms(UINT8** map, UINT8* x, UINT8* y, UINT8* wtile, UINT8* htile){
    UINT8 gnd = 0;
    UINT8 vx ;
    UINT8 vy ;
    UINT8 wx ;
    UINT8 wy ;

    UINT8 prevCenterX;
    UINT8 prevCenterY;

    //hero start point
    *x=16;
    *y=16;

    //Map size
    *map = dynmap;
    dynmapW = 32;
    dynmapH = 32;

    *wtile = dynmapW;
    *htile = dynmapH;

    //fill with walls
    clearDynmap(TILE_TOWER_3);

    //make the ground
    switch (rand() & 0x03) {
        case 0:
            gnd = TILE_SAND;
            break;
        case 1:
            gnd = TILE_GRASS_1;
            break;
        default:
            gnd = TILE_EMPTY;
            break;        
    }

    //Make start room
    for (UINT8 i = 1; i <= 5; i++){
        for (UINT8 j = 1; j <= 5; j++){
            DYNMAP_PUT_TILE(gnd, i, j);
        }
    }

    prevCenterX= 3;
    prevCenterY= 3;

    //make a few rooms
    UINT8 rmax = (rand() & 0x03) + 2;
    for (UINT8 r =0; r < rmax; r++){
        vx = 1 + (rand() & 0x1f);
        vy = 1 + (rand() & 0x1f);

        vx = MIN(vx, dynmapW- 2 - RAND_ROOM_MIN_WIDTH);
        vy = MIN(vy, dynmapH- 2 - RAND_ROOM_MIN_WIDTH);

        wx = vx + RAND_ROOM_MIN_WIDTH + (rand() & 0x08);
        wy = vy + RAND_ROOM_MIN_WIDTH + (rand() & 0x08);

        wx = MIN(wx, dynmapW-2);//max -1 -1 
        wy = MIN(wy, dynmapH-2);

        for (UINT8 i = vx; i <= wx; i++){
            for (UINT8 j = vy; j <= wy; j++){
                DYNMAP_PUT_TILE(gnd, i, j);
            }
        }

        //room is created. link to previous room. 
        vx += (wx - vx)/2;
        vy += (wy - vy)/2;

        //try to make corridor between room centers.
        //prevCenter is the cursor. Can start X first or Y first, X code is copy paste with a rand() to allow to start X first or not
        //same code and the cursor moves so no wasted circle (at worse we do X, then Y, then X again but we're already here so leaves immediately)
        if ((rand() & 0x01) == 0) {
            while (prevCenterX != vx){
                DYNMAP_PUT_TILE(gnd, prevCenterX, prevCenterY);
                DYNMAP_PUT_TILE(gnd, prevCenterX, prevCenterY+1);
                if (vx > prevCenterX)
                    prevCenterX++;
                else
                    prevCenterX--;            
            }
        }

        while (prevCenterY != vy){
            DYNMAP_PUT_TILE(gnd, prevCenterX, prevCenterY);
            DYNMAP_PUT_TILE(gnd, prevCenterX+1, prevCenterY);
            if (vy > prevCenterY)
                prevCenterY++;
            else
                prevCenterY--;            
        }

        while (prevCenterX != vx){
            DYNMAP_PUT_TILE(gnd, prevCenterX, prevCenterY);
            DYNMAP_PUT_TILE(gnd, prevCenterX, prevCenterY+1);
            if (vx > prevCenterX)
                prevCenterX++;
            else
                prevCenterX--;            
        }

    }


    //Draw the stairs in the center of the LAST room drawn
    DYNMAP_PUT_TILE(TILE_STAIRS_DOWN_NW, prevCenterX, prevCenterY);
    DYNMAP_PUT_TILE(TILE_STAIRS_DOWN_NE, prevCenterX+1, prevCenterY);
    DYNMAP_PUT_TILE(TILE_STAIRS_DOWN_SW, prevCenterX, prevCenterY+1);
    DYNMAP_PUT_TILE(TILE_STAIRS_DOWN_SE, prevCenterX+1, prevCenterY+1);


    //decorate the rooms
    rmax = (rand() & 0x03) + 1;
    for (UINT8 r =0; r < rmax; ){
        vx = 1 + (rand() & 0x1f);
        vy = 1 + (rand() & 0x1f);

        if (
            DYNMAP_GET_TILE(vx, vy) == gnd && 
            DYNMAP_GET_TILE(vx+1, vy) == gnd &&
            DYNMAP_GET_TILE(vx, vy+1) == gnd &&
            DYNMAP_GET_TILE(vx+1, vy+1) == gnd ){

            UINT8 t = _RoomDecorations[rand() & 0x07];
            DYNMAP_PUT_TILE(t++, vx, vy);
            DYNMAP_PUT_TILE(t++, vx, vy+1);
            DYNMAP_PUT_TILE(t++, vx+1, vy);
            DYNMAP_PUT_TILE(t, vx+1, vy+1);

            //one done
            r++;
        }
    }    

}

/**
 * Generates a random map EMPTY
 * 
 */
void makeRandomSingleRoom(UINT8** map, UINT8* x, UINT8* y, UINT8* wtile, UINT8* htile){
    
    //clear the full dynmap, refresh the screen since this room will be less than 1 screen so remove garbage
    clearDynmap(TILE_EMPTY);
    set_bkg_tiles(0, 0, DynMap_MAX_WIDTH, DynMap_MAX_HEIGHT, dynmap);

    //hero start point
    *x=16;
    *y=16;

    //Map size
    *map = dynmap;
    //W: up to 32, min 6
    dynmapW = ((UINT8)(rand() & 0x1f));
    dynmapW = MAX(8, dynmapW);
    //H: up to 32 min 8
    dynmapH = ((UINT8)(rand() & 0x1f));
    dynmapH = MAX(8, dynmapH);

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

/* ============================================================================================================================================= */

/**
 * When transition from a given map, by a transition at point x,y (MAP coordinate)
 * 
 */
void mapTransition(UINT8** map, UINT8* x, UINT8* y, UINT8* wtile, UINT8* htile){
    switch(mMapTransitionModeFlag){
        /* ---------------------------------------------------------------------------------------------- */
        case 0:
            /* 
                mMapTransitionModeFlag == 0 : we're in the STATIC transition mode. Predefined order of move between rooms. 
                Hardcoding now, todo rewrite as a static array of transitions later if more rooms.
            */
            if (*map == Map_Intro){
                //Intro -> enter in Room1
                *x=16;
                *y=32;
                *map = Map_Room1;
                *wtile = Map_Room1_WIDTH;
                *htile = Map_Room1_HEIGHT;

                //mMapTransitionModeFlag = 1; //stay out of the random map loop
                break;
            }

            if (*map == Map_Room1) {
                //Room1 -> BigRoom1
                *x=16;
                *y=16;
                *map = Map_BigRoom1;
                *wtile = Map_BigRoom1_WIDTH;
                *htile = Map_BigRoom1_HEIGHT;

                //From that point on move to random maps (set flag to 1)
                mMapTransitionModeFlag = 1;

                //seed the random generator
                srand(DIV_REG);

                break;
            }


            break;
        /* ---------------------------------------------------------------------------------------------- */
        case 1:
            //make a new map with rooms
            makeRandomMapRooms (map, x, y, wtile, htile);        
            //stay on this type of map or alternate
            mMapTransitionModeFlag = 1 + (rand() & 0x01);
            break;
        /* ---------------------------------------------------------------------------------------------- */
        case 2:
        default:
            //make a new map
            makeRandomSingleRoom (map, x, y, wtile, htile);        

            //stay on this type of map or alternate
            mMapTransitionModeFlag = 1 + (rand() & 0x01);
            break;
    }

    set_bkg_tiles(0, 0, *wtile, *htile, *map );
}


/**
 * Map transition: small anim and load new bg
 * 
 */
void doMapTransition(UINT8* x, UINT8* y){
    HIDE_BKG;
    delay (500);
    HIDE_SPRITES;
    delay (500);

    //LOAD!
    mapTransition(
        &currentMap, 
        x, 
        y, 
        &currentMapW_Tile, 
        &currentMapH_Tile
        );

    if (currentMapW_Tile >= SCREEN_TILES_WIDTH) {
        //if wider than a screen, align left
        bgx=0;
    }
    else {

        bgx = (GRAPHICS_WIDTH - currentMapW_Tile * 8) / 2 ;
        *x += bgx;
        bgx = 255 - bgx;        
    }
    
    if (currentMapH_Tile >= SCREEN_TILES_HEIGHT) {
        //if taller than a screen, align top
        bgy=0;
    }
    else {
        //centers the new map vertically in the screen (no vertical scroll)
        bgy = (GRAPHICS_HEIGHT - currentMapH_Tile * 8) / 2 ;
        *y += bgy;
        bgy = 255 - bgy; 
    }


    SHOW_SPRITES;
    delay (500);
    SHOW_BKG;
    delay (500);

}


/**
 * Shows the first map at beginning, after is all transitions
 */
inline void showInitialMap(){
    set_bkg_tiles(bgx, bgy, Map_Intro_WIDTH, Map_Intro_HEIGHT, Map_Intro);
    currentMap = Map_Intro;
    currentMapW_Tile = Map_Intro_WIDTH;
    currentMapH_Tile = Map_Intro_HEIGHT;
}



/**
 * Displays a fullscreen scroller for the story intro.
 * 
 */
inline void showStartupScroller(){
    HIDE_BKG;

    mapMakeVerticalMessage(&currentMap, TILE_EMPTY);
    currentMapW_Tile = SCREEN_TILES_WIDTH;
    currentMapH_Tile = 32;

    writetextBG(1,1, "Dans un future    lointain, le monde a ete ravage par une etrange maladie.Tous les humains ont disparu peu apeu, laissant une terre vide qui retomba petit a petitdans un monde moyenageux ou la  technologie a ete oubliee.");
    writetextBG(1,14, "Notre hero part a la recherche de laverite, se basant sur des legendes  parlant d un mage qui vivait dans   une tour cachee   dans la foret...");

    set_bkg_tiles(bgx, bgy, currentMapW_Tile, currentMapH_Tile, currentMap);

    SHOW_BKG;
    UINT8 vy =180;

    while(1) {
        
        if (vy >= 180 || vy <100) {
            move_bkg(0, vy++);
            delay(100);
        }
        else {
            delay(3000);
            break;
        }
    }

}