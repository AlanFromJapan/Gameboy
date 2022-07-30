#include "ai.h"
#include "my_lib01.h"
#include "maps.h"

#include <stdio.h>
#include <stdlib.h>


//HOw many sprites a DMG can show
#define SPRITE_MAX_COUNT    40
//SLow down the AI to move/act only onces every nth times (one setting for all for now)
#define AI_THROTTLE         7

struct ai* currentMapAI = NULL;
UINT8 currentMapAICount = 0;
UINT8 aiThrottleCounter = 0;

//Removes all the AI (in memory and onscreen sprites)
void clearAllAI(){
    if (currentMapAI != NULL){
        //hide the previous AIs
        for (UINT8 i = 0; i < currentMapAICount; i++){
            //start at 2 since sprite 0 & 1 are for main character
            //go 2 by 2 sine one character is 2 sprites
            
            //taken from gbdk-2020 : move the sprite off the screen is the fastest way to hide it: so be it!
            move_sprite(2 + 2 * i, 255, 255);
            move_sprite(2 + 2 * i +1, 255, 255);
        }

        free(currentMapAI);
        currentMapAI = NULL;
        currentMapAICount = 0;
    }
}

//finds a proper random position for the ai to start (In the map and on the floor)
void setAIRandomPosition (struct ai* ai, struct map* map) {
    while (1){
        UINT8 x, y;

        x = rand();
        y = rand();
        (*ai).x = x;
        (*ai).y = y;

        //in the map (avoid the border for it's most likely a wall)
        if (x > 8 && x < ((*map).tilesW -2) * 8 && y > 8 && y < ((*map).tilesH -2) * 8){
            //map to tiles => div by 8 => shift right by 3
            x = x / 8;
            y = y / 8;
            //from here x and y are in TILES not pixels
            if ((*map).data [y * ((*map).tilesW) + x] == (*map).floorTile)
                //the floor is free, accept otherwise try again
                break;
        }
    }

}

//Inits the currentMapAI with the proper AIs for this map
void setMapAI(struct map* map){
    //in case
    clearAllAI();  

    //for now just make 1
    currentMapAICount = 2;
    currentMapAI = (struct ai*)malloc(sizeof(struct ai) * currentMapAICount);

    currentMapAI[0].hp = 2;
    currentMapAI[0].tileID = TILE_SNOWMAN_NW;

    currentMapAI[1].hp = 4;
    currentMapAI[1].tileID = TILE_DWARF_NW;

    for (UINT8 i = 0; i < currentMapAICount; i++){
        //set the ai somewhere the floor is free within the room
        setAIRandomPosition (&(currentMapAI[i]), map);

        //start at 2 since sprite 0 & 1 are for main character
        //go 2 by 2 sine one character is 2 sprites
        move_sprite(2 + 2 * i, currentMapAI[i].x, currentMapAI[i].y);
        move_sprite(2 + 2 * i + 1, currentMapAI[i].x + 8, currentMapAI[i].y);

        set_sprite_tile(2 + 2 * i, currentMapAI[i].tileID);
        set_sprite_tile(2 + 2 * i + 1 , currentMapAI[i].tileID+2); //+2 tile ID since it's stored NW SW NE SE
    }
}

//Moves each AI 
void moveAI(UINT8 herox, UINT8 heroy){
    if (currentMapAI == NULL || currentMapAICount == 0){
        return;
    }

    //slow down the AIs
    aiThrottleCounter++;
    if (aiThrottleCounter< AI_THROTTLE){
        return;
    }

    //Ok time to do something
    aiThrottleCounter = 0;

    //Move
    for (UINT8 i = 0; i < currentMapAICount; i++){
        INT8 dx = herox < currentMapAI[i].x ? -1 : +1;
        INT8 dy = heroy < currentMapAI[i].y ? -1 : +1;

        currentMapAI[i].x = currentMapAI[i].x + dx;
        currentMapAI[i].y = currentMapAI[i].y + dy;
        
        //move insteda of scroll?
        scroll_sprite(2 + 2 * i, dx, dy);
        scroll_sprite(2 + 2 * i + 1, dx, dy);
    }
}


//If bg moved on bug map, need to reflect the impact on the sprites visible positions
void backgroundMoveEventAI (INT8 dx, INT8 dy){
    if (currentMapAI == NULL || currentMapAICount == 0){
        return;
    } 

    //SCROLL the APPARENT position of the sprites
    for (UINT8 i = 0; i < currentMapAICount; i++){
        
        //move instead of scroll? 
        //FIXME a bit buggy when big maps between the hero position apparent and on screen ...
        scroll_sprite(2 + 2 * i, dx, dy);
        scroll_sprite(2 + 2 * i + 1, dx, dy);
    }
}