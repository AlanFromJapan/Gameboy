
#include "transitions.h"

#include "my_lib01.h"
#include "Map_Intro.h"
#include "Map_Room1.h"
#include "Map_BigRoom1.h"
#include "Map_Cemetary1.h"
#include "Map_Chapelle1.h"
#include "Map_Dedale1.h"

#include "graphics.h"
#include <gb/drawing.h>

//#include <gb/rand.h>
#include <stdlib.h>
#include "maps.h"
#include "hero.h"

//Flag defining which map we are in. Default is 0 (fixed rooms), or >=1 means various random maps.
UINT8 mMapTransitionModeFlag=0;




#define MAX(A,B)    ((A) > (B)? (A): (B))
#define MIN(A,B)    ((A) < (B)? (A): (B))

#define RAND_ROOM_MIN_WIDTH     6

//const UINT8 _RoomDecorationsCount = 8;
const UINT8 _RoomDecorations[] = {TILE_PENTAGRAM_NW, TILE_TABLE_NW, TILE_MARBLE_STELE_NW, TILE_TORCH_NW, TILE_CRANE_NW, TILE_CRYSTAL_NW, TILE_REMAINS_NW, TILE_REMAINS_NW};

/**
 * Generates a random map with rooms in a 32x32 tiles room
 * 
 */
void makeRandomMapRooms(struct map* map){
    UINT8 gnd = 0;
    UINT8 vx ;
    UINT8 vy ;
    UINT8 wx ;
    UINT8 wy ;

    UINT8 prevCenterX;
    UINT8 prevCenterY;

    //hero start point
    hero.x=16;
    hero.y=16;

    //Map size
    (*map).data = dynmap;
    dynmapW = 32;
    dynmapH = 32;

    (*map).tilesW = dynmapW;
    (*map).tilesH = dynmapH;

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
    //memorize
    (*map).floorTile = gnd;

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
void makeRandomSingleRoom(struct map* map){
    UINT8 gnd = 0;

    //clear the full dynmap, refresh the screen since this room will be less than 1 screen so remove garbage
    clearDynmap(TILE_EMPTY);
    set_bkg_tiles(0, 0, DynMap_MAX_WIDTH, DynMap_MAX_HEIGHT, dynmap);

    //Map size
    (*map).data = dynmap;
    //W: up to 32, min 8
    dynmapW = ((UINT8)(rand() & 0x1f));
    dynmapW = MAX(8, dynmapW);
    //H: up to 32 min 8
    dynmapH = ((UINT8)(rand() & 0x1f));
    dynmapH = MAX(8, dynmapH);

    (*map).tilesW = dynmapW;
    (*map).tilesH = dynmapH;


    //hero start point : find a place within the map
    for(;;){  
        hero.x = 8 + ((UINT8)(rand() & 0x7f)); //0x7f means max is 128 so always within first half of screen
        if (hero.x < SCREENWIDTH && hero.x < ((dynmapW -2) * 8))
            break;
    }
    for(;;){  
        hero.y = 16 + ((UINT8)(rand() & 0x7f)); //0x7f means max is 128 so always within first half of screen
        if (hero.y < SCREENHEIGHT && hero.y < ((dynmapH -2) * 8))
            break;
    }


    //pick the ground
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
    //apply ground
    clearDynmap(gnd);
    //memorize
    (*map).floorTile = gnd;


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
inline void mapMakeVerticalMessage (struct map* map, UINT8 bgTile){

    (*map).data = dynmap;
    dynmapW = 20;
    dynmapH = 32;
    (*map).tilesW = dynmapW;
    (*map).tilesH = dynmapH;
    (*map).floorTile = bgTile;

    clearDynmap(bgTile);

}

/* ============================================================================================================================================= */

/**
 * When transition from a given map, by a transition at point x,y (MAP coordinate)
 * 
 */
void mapTransition(struct map* map){
    switch(mMapTransitionModeFlag){
        /* ---------------------------------------------------------------------------------------------- */
        case 0:
            /* 
                mMapTransitionModeFlag == 0 : we're in the STATIC transition mode. Predefined order of move between rooms. 
                Hardcoding now, todo rewrite as a static array of transitions later if more rooms.
            */
            if ((*map).data == Map_Intro){
                //Intro -> cemetary
                hero.x=8;
                hero.y=144-24;
                (*map).data = Map_Cemetary1;
                (*map).tilesW = Map_Cemetary1_WIDTH;
                (*map).tilesH = Map_Cemetary1_HEIGHT;
                (*map).floorTile = TILE_SAND;

                //mMapTransitionModeFlag = 1; //stay out of the random map loop
                break;
            }

            if ((*map).data == Map_Cemetary1){
                //Cemetary -> enter in Chapelle1
                hero.x=Map_Chapelle1_WIDTH*8/2;
                hero.y= (Map_Chapelle1_HEIGHT -1)*8;
                (*map).data = Map_Chapelle1;
                (*map).tilesW = Map_Chapelle1_WIDTH;
                (*map).tilesH = Map_Chapelle1_HEIGHT;
                (*map).floorTile = TILE_EMPTY;

                //mMapTransitionModeFlag = 1; //stay out of the random map loop
                break;
            }


            if ((*map).data == Map_Chapelle1){
                //Cemetary -> enter in Room1
                hero.x=24;
                hero.y=40;
                (*map).data = Map_Room1;
                (*map).tilesW = Map_Room1_WIDTH;
                (*map).tilesH = Map_Room1_HEIGHT;
                (*map).floorTile = TILE_SAND;

                //mMapTransitionModeFlag = 1; //stay out of the random map loop
                break;
            }

            if ((*map).data == Map_Room1) {
                //Room1 -> BigRoom1
                hero.x=24;
                hero.y=24;
                (*map).data = Map_BigRoom1;
                (*map).tilesW = Map_BigRoom1_WIDTH;
                (*map).tilesH = Map_BigRoom1_HEIGHT;
                (*map).floorTile = TILE_EMPTY;

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
            makeRandomMapRooms (map);        
            //stay on this type of map or alternate
            mMapTransitionModeFlag = 1 + (rand() & 0x01);
            break;
        /* ---------------------------------------------------------------------------------------------- */
        case 2:
        default:
            //make a new map
            makeRandomSingleRoom (map);        

            //stay on this type of map or alternate
            mMapTransitionModeFlag = 1 + (rand() & 0x01);
            break;
    }

    set_bkg_tiles(0, 0, (*map).tilesW, (*map).tilesH, (*map).data );
}


/**
 * Map transition: small anim and load new bg
 * 
 */
void doMapTransition(){
    HIDE_BKG;
    delay (TRANSITIONS_DELAY_MS);
    HIDE_SPRITES;
    delay (TRANSITIONS_DELAY_MS);

    //LOAD!
    mapTransition(&currentMap);

    if (currentMap.tilesW >= SCREEN_TILES_WIDTH) {
        //if wider than a screen, shw the quadrant with the hero
        if (hero.x < MAP_MAX_TILES_W * 8 / 2){
            bgx = 0;
        }
        else {
            bgx = (MAP_MAX_TILES_W -2) * 8 /2;
        }
    }
    else {
        //centers the new map horizontally in the screen (no horizontal scroll)
        bgx = -(GRAPHICS_WIDTH - currentMap.tilesW * 8) / 2 ;
    }
    
    if (currentMap.tilesH >= SCREEN_TILES_HEIGHT) {
        //if taller than a screen, show quadrant with the hero
        if (hero.y < MAP_MAX_TILES_H * 8 / 2 ){
            bgy = 0;
        }
        else {
            bgy = (MAP_MAX_TILES_H -2) * 8 /2;
        }
    }
    else {
        //centers the new map vertically in the screen (no vertical scroll)
        bgy = -(GRAPHICS_HEIGHT - currentMap.tilesH * 8) / 2 ;
    }


    SHOW_SPRITES;
    delay (TRANSITIONS_DELAY_MS);
    SHOW_BKG;
    delay (TRANSITIONS_DELAY_MS);

}


/**
 * Shows the first map at beginning, after is all transitions
 */
inline void showInitialMap(){
    set_bkg_tiles(bgx, bgy, Map_Intro_WIDTH, Map_Intro_HEIGHT, Map_Intro);
    currentMap.data = Map_Intro;
    currentMap.tilesW = Map_Intro_WIDTH;
    currentMap.tilesH = Map_Intro_HEIGHT;
    currentMap.floorTile = TILE_EMPTY;

    hero.x = 20;
    hero.y = 20;
}



/**
 * Displays a fullscreen scroller for the story intro.
 * 
 */
inline void showStartupScroller(){
    HIDE_BKG;

    mapMakeVerticalMessage(&currentMap, TILE_EMPTY);
    currentMap.tilesW = SCREEN_TILES_WIDTH;
    currentMap.tilesH = 32;

    writetextBG(1,1, "Dans un future    lointain, le monde a ete ravage par une etrange maladie.Tous les humains ont disparu peu apeu, laissant une terre vide qui retomba petit a petitdans un monde moyenageux ou la  technologie a ete oubliee.");
    writetextBG(1,14, "Notre hero part a la recherche de laverite, se basant sur des legendes  parlant d un mage qui vivait dans   une tour cachee   dans la foret...");

    set_bkg_tiles(bgx, bgy, currentMap.tilesW, currentMap.tilesH, currentMap.data);

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