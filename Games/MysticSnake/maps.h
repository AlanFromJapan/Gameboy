#ifndef __MAPS_H__
#define __MAPS_H__

#include <gb/gb.h>

struct map {
    unsigned char* data;
    UINT8 tilesW;
    UINT8 tilesH;
    UINT8 floorTile;
    UINT8 heroStartX;
    UINT8 heroStartY;
};

//THE current map showed now (extern here to avoid multiple redefinition)
extern struct map* currentMap;

#endif //__MAPS_H__