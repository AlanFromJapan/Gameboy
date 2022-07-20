
#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include <gb/gb.h>

#include "Map_Intro.h"
#include "Map_Room1.h"

extern unsigned char *currentMap;
extern unsigned int currentMapW_Tile;
extern unsigned int currentMapH_Tile;

//Returns the background tile at XX,YY
#define GET_BG_TILE(XX, YY)     (currentMap[(YY / 8) * currentMapW_Tile + (XX / 8)])

/**
 * When transition from a given map, by a transition at point x,y (MAP coordinate)
 * 
 */
void mapTransition(UINT8 * * map, UINT8* x, UINT8* y, UINT8* wtile, UINT8* htile);
void mapMakeVerticalMessage (UINT8 * * map, UINT8 bgTile);

/**
 * Map transition: small anim and load new bg
 * 
 */
void doMapTransition(UINT8* x, UINT8* y);
void showInitialMap();
void showStartupScroller();

#endif // __TRANSITION_H__

