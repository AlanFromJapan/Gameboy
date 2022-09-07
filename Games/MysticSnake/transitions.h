
#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include <gb/gb.h>

#include "maps.h"

#define TRANSITIONS_DELAY_MS    300

//Returns the background tile at XX,YY
#define GET_BG_TILE(XX, YY)     ((*currentMap).data[((YY) / 8) * (*currentMap).tilesW + ((XX) / 8)])

/**
 * When transition from a given map, by a transition at point x,y (MAP coordinate)
 * 
 */
struct map* mapTransition(struct map* map);
void mapMakeVerticalMessage(struct map* map, UINT8 bgTile);

/**
 * Map transition: small anim and load new bg
 * 
 */
void doMapTransition();
void showInitialMap();
void showStartupScroller();

#endif // __TRANSITION_H__

