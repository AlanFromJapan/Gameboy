#ifndef __AI_H__
#define __AI_H__

#include <gb/gb.h>
#include "maps.h"

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

//Moves each AI 
void moveAI(UINT8 herox, UINT8 heroy);

//If bg moved on bug map, need to reflect the impact on the sprites visible positions
void backgroundMoveEventAI ();

#endif //__AI_H__

