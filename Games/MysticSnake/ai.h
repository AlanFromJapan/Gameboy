#ifndef __AI_H__
#define __AI_H__

#include <gb/gb.h>
#include "maps.h"

//Distance in pixels how far the AI can "see" the player. THIS IS NOT A TRUE DISTANCE (use a square not a circle)
#define AI_SEE_RADIUS   80
#define ENABLE_AI_SEE_RADIUS


#define AI_NO_HIT   0
#define AI_HIT_HERO 1


struct ai {
    UINT8 tileID;
    INT8 hp;
    UINT8 x;
    UINT8 y;
};

extern struct ai* currentMapAI;

//Removes all the AI (in memory and onscreen sprites)
void clearAllAI();

//Inits the currentMapAI with the proper AIs for this map
void setMapAI(struct map* map);

//Moves each AI and returns if hit with player occured
UINT8 moveAI();

//If bg moved on bug map, need to reflect the impact on the sprites visible positions
void backgroundMoveEventAI ();

#endif //__AI_H__

