

#include "Map_bridge2.h"
#include "../maps.h"


// Project libraries
#include "my_lib01.h"


const unsigned char Map_bridge2[] =
{

0x08,0x0A,0x2C,0x2C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x2C,0x2C,0x0D
,0x09,0x0B,0x08,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x0C,0x0E,0x2C
,0x2C,0x2C,0x09,0x0B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x0D,0x0F,0x2C
,0x2C,0x2C,0x08,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x2C,0x2C,0x2C
,0x2C,0x2C,0x09,0x0B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x2C,0x2C,0x2C
,0x2C,0x2C,0x2C,0x2C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x2C,0x2C,0x2C
,0x32,0x34,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C
,0x33,0x35,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C,0x2C
,0x2C,0x2C,0x2C,0x2C,0x1C,0x1D,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1F,0x20,0x2C,0x2C,0x2C,0x2C
,0x2C,0x2C,0x2C,0x2C,0x00,0x00,0x00,0x00,0x25,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x27,0x00,0x00,0x00,0x00,0x08,0x0A,0x2C,0x2C
,0x2C,0x2C,0x08,0x0A,0x00,0x00,0x00,0x00,0x25,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x27,0x00,0x00,0x00,0x00,0x09,0x0B,0x2C,0x2C
,0x0C,0x0E,0x09,0x0B,0x00,0x00,0x00,0x00,0x25,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x27,0x00,0x00,0x00,0x00,0x2C,0x2C,0x2C,0x2C
,0x0D,0x0F,0x2C,0x2C,0x00,0x00,0x00,0x00,0x25,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x27,0x00,0x00,0x00,0x00,0x2C,0x2C,0x08,0x0A
,0x2C,0x0C,0x0E,0x2C,0x00,0x00,0x00,0x00,0x26,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x26,0x28,0x00,0x00,0x00,0x00,0x2C,0x2C,0x09,0x0B

};

//Map object declaration
const struct map mapMap_bridge2 = {
    .data = Map_bridge2,
    .tilesW = Map_bridge2_WIDTH,
    .tilesH = Map_bridge2_HEIGHT,
    .floorTile = TILE_SAND,
    .heroStartX = 200,
    .heroStartY = 61
};

