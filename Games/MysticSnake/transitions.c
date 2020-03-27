
#include "transitions.h"

#include "Map_Intro.h"
#include "Map_Room1.h"

/**
 * When transition from a given map, by a transition at point x,y (MAP coordinate)
 * 
 */
void mapTransition(UINT8** map, UINT8* x, UINT8* y, UINT8* wtile, UINT8* htile){

    *x=16;
    *y=32;

    *map = Map_Room1;
    *wtile = Map_Room1_WIDTH;
    *htile = Map_Room1_HEIGHT;

    set_bkg_tiles(0, 0, *wtile, *htile, *map );
}