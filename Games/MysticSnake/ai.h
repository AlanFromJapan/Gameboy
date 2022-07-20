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

#endif //__AI_H__

