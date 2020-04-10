
#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include <gb/gb.h>

#include "Map_Intro.h"
#include "Map_Room1.h"


void mapTransition(UINT8 * * map, UINT8* x, UINT8* y, UINT8* wtile, UINT8* htile);
void mapMakeVerticalMessage (UINT8 * * map, UINT8 bgTile);


#endif // __TRANSITION_H__

