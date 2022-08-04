#include "ai.h"
#include "my_lib01.h"
#include "maps.h"
#include "graphics.h"

#include "hero.h"

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
            move_sprite(2 + 2 * i, 0, 0);
            move_sprite(2 + 2 * i +1, 0, 0);
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
            if ((*map).data [y * ((*map).tilesW) + x] == (*map).floorTile) {
                //the floor is free, accept otherwise try again

                //center it in the tile
                (*ai).x = ((*ai).x / 8) * 8 + 4;
                //at the bottom
                (*ai).y = ((*ai).y / 8) * 8 + 7;

                break;
            }
        }
    }

}

//Inits the currentMapAI with the proper AIs for this map
void setMapAI(struct map* map){
    //in case
    clearAllAI();  

    //Up to 3 AI with 50% of 0
    currentMapAICount = 2;// (rand() & 0x03) * (rand() & 0x01);
    currentMapAI = (struct ai*)malloc(sizeof(struct ai) * currentMapAICount);

    for (UINT8 i = 0; i < currentMapAICount; i++){
        currentMapAI[i].hp = 1 + (rand() & 0x0f);
        currentMapAI[i].tileID = TILE_SNAKE_NW;

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
void moveAI(){
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

    //Calculate new position : just a simple right line toward player
    for (UINT8 i = 0; i < currentMapAICount; i++){
        INT8 dx, dy;

        //big bakground offset (> 160) mean in fact SMALL room being centered so need to adapt the formula
        if (bgx > 160)
            dx = (hero.x - (255 - bgx)) < currentMapAI[i].x ? -1 : +1;
        else
            dx = (hero.x + bgx) < currentMapAI[i].x ? -1 : +1;

        //big bakground offset (> 160) mean in fact SMALL room being centered so need to adapt the formula
        if (bgy > 160)
            dy = (hero.y - (255 - bgy)) < currentMapAI[i].y ? -1 : +1;
        else 
            dy = (hero.y + bgy) < currentMapAI[i].y ? -1 : +1;

        //is move valid?
        if (checkCollision(currentMapAI[i].x, currentMapAI[i].y, &dx, &dy) != MOVE_CHECK_COLLISION) {
            currentMapAI[i].x = currentMapAI[i].x + dx;
            currentMapAI[i].y = currentMapAI[i].y + dy;
        }
    }

    //Move the sprites
    backgroundMoveEventAI ();
}


//If bg moved on bug map, need to reflect the impact on the sprites visible positions
void backgroundMoveEventAI (){
    if (currentMapAI == NULL || currentMapAICount == 0){
        return;
    } 

    //SCROLL the APPARENT position of the sprites
    for (UINT8 i = 0; i < currentMapAICount; i++){
        //move taking account of background offset
        move_sprite(2 + 2 * i, currentMapAI[i].x - bgx, currentMapAI[i].y - bgy);
        move_sprite(2 + 2 * i + 1, currentMapAI[i].x - bgx + 8, currentMapAI[i].y - bgy);
    }
}