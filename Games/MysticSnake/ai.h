#ifndef __AI_H__
#define __AI_H__

#include <gb/gb.h>


struct ai {
    UINT8 tileID;
    INT8 hp;
    UINT8 x;
    UINT8 y;
};

extern struct ai* currentMapAI;

void setMapAI(unsigned char* map);

void moveAI(UINT8 herox, UINT8 heroy);

void backgroundMoveEventAI (INT8 dx, INT8 dy);

#endif //__AI_H__

