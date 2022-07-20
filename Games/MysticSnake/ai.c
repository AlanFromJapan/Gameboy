#include "ai.h"
#include "my_lib01.h"

#include <stdio.h>
#include <stdlib.h>

#define SPRITE_MAX_COUNT 40

struct ai* currentMapAI = NULL;
UINT8 currentMapAICount = 0;

//Inits the currentMapAI with the proper AIs for this map
void setMapAI(unsigned char* map){
    if (currentMapAI != NULL){
        //hide the previous AIs
        for (UINT8 i = 0; i < currentMapAICount; i++){
            //start at 2 since sprite 0 & 1 are for main character
            //go 2 by 2 sine one character is 2 sprites
            set_sprite_tile(2 + 2 * i, TILE_EMPTY);
            set_sprite_tile(2 + 2 * i + 1, TILE_EMPTY);
        }

        free(currentMapAI);
        currentMapAI = NULL;
        currentMapAICount = 0;
    }

    //for now just make 1
    currentMapAICount = 1;
    currentMapAI = (struct ai*)malloc(sizeof(struct ai) * currentMapAICount);

    currentMapAI[0].hp = 2;
    currentMapAI[0].x = 60;
    currentMapAI[0].y = 60;
    currentMapAI[0].tileID = TILE_SNOWMAN_NW;

    for (UINT8 i = 0; i < currentMapAICount; i++){
        //start at 2 since sprite 0 & 1 are for main character
        //go 2 by 2 sine one character is 2 sprites
        move_sprite(2 + 2 * i, currentMapAI[i].x, currentMapAI[i].y);
        move_sprite(2 + 2 * i + 1, currentMapAI[i].x + 8, currentMapAI[i].y);

        set_sprite_tile(2 + 2 * i, currentMapAI[i].tileID);
        set_sprite_tile(2 + 2 * i + 1 , currentMapAI[i].tileID+2); //+2 tile ID since it's stored NW SW NE SE
    }
}