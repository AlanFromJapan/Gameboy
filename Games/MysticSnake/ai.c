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
            if (
                (*map).data [y * ((*map).tilesW) + x] == (*map).floorTile 
                && (*map).data [y * ((*map).tilesW) + x + 1] == (*map).floorTile
                && (*map).data [(y +1) * ((*map).tilesW) + x] == (*map).floorTile 
                && (*map).data [(y +1) * ((*map).tilesW) + x + 1] == (*map).floorTile
            ) {
                //the floor is free, accept otherwise try again

                //center it in the tile
                (*ai).x = x * 8 + 8;
                //at the bottom
                (*ai).y = y * 8 + 15;

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
    currentMapAICount = (rand() & 0x03); // * (rand() & 0x01);
    if (currentMapAICount == 0)
        return;

    currentMapAI = (struct ai*)malloc(sizeof(struct ai) * currentMapAICount);

    for (UINT8 i = 0; i < currentMapAICount; i++){
        currentMapAI[i].hp = 1 + (rand() & 0x0f);
        currentMapAI[i].tileID = TILE_SNAKE_NW;

        //set the ai somewhere the floor is free within the room
        setAIRandomPosition (&(currentMapAI[i]), map);

        //start at 2 since sprite 0 & 1 are for main character
        //go 2 by 2 sine one character is 2 sprites
        move_sprite(2 + 2 * i, MAP2SCREEN_X(currentMapAI[i].x), MAP2SCREEN_Y(currentMapAI[i].y));
        move_sprite(2 + 2 * i + 1, MAP2SCREEN_X(currentMapAI[i].x) + 8, MAP2SCREEN_Y(currentMapAI[i].y));

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

        dx = hero.x < currentMapAI[i].x ? -1 : hero.x == currentMapAI[i].x ? 0 : +1;
        dy = hero.y < currentMapAI[i].y ? -1 : hero.y == currentMapAI[i].y ? 0 : +1;


#ifdef ENABLE_AI_SEE_RADIUS
        //can the AI "see" the player?
        //use a dirty square zone to speed up and avoid doing sqrt() calc on a 8bit Z80 :D
        if (dx > 0 && hero.x - currentMapAI[i].x > AI_SEE_RADIUS)
            continue;
        if (dx < 0 && currentMapAI[i].x - hero.x > AI_SEE_RADIUS)
            continue;
        if (dy > 0 && hero.y - currentMapAI[i].y > AI_SEE_RADIUS)
            continue;
        if (dy < 0 && currentMapAI[i].y - hero.y > AI_SEE_RADIUS)
            continue;
#endif //ENABLE_AI_SEE_RADIUS        


        //is move valid? ignore result but let the function update dx/dy
        checkCollision(currentMapAI[i].x, currentMapAI[i].y, &dx, &dy, IGNORE_TRANSITION);
        //this allows to move along a wall if at least one direction is possible if not both
        currentMapAI[i].x = currentMapAI[i].x + dx;
        currentMapAI[i].y = currentMapAI[i].y + dy;
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
        move_sprite(2 + 2 * i, MAP2SCREEN_X(currentMapAI[i].x), MAP2SCREEN_Y(currentMapAI[i].y));
        move_sprite(2 + 2 * i + 1, MAP2SCREEN_X(currentMapAI[i].x) + 8, MAP2SCREEN_Y(currentMapAI[i].y));
    }
}