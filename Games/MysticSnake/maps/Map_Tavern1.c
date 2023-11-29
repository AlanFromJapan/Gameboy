

#include "Map_Tavern1.h"
#include "../maps.h"


// Project libraries
#include "my_lib01.h"


const unsigned char Map_Tavern1[] =
{

0x1D,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1F
,0x1D,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x4E,0x50,0x6E,0x70,0x6E,0x70,0x4E,0x50,0x1F
,0x1D,0x6E,0x70,0x6E,0x70,0x6E,0x70,0x29,0x29,0x29,0x29,0x4F,0x51,0x6F,0x71,0x6F,0x71,0x4F,0x51,0x1F
,0x1D,0x6F,0x71,0x6F,0x71,0x6F,0x71,0x29,0x01,0x03,0x29,0x4E,0x50,0x6E,0x70,0x6E,0x70,0x4E,0x50,0x1F
,0x1D,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0xF5,0x03,0x29,0x4F,0x51,0x6F,0x71,0x6F,0x71,0x4F,0x51,0x1F
,0x1D,0x01,0x02,0x02,0x02,0x02,0x02,0xF4,0xF4,0x03,0x29,0x4E,0x50,0x6E,0x70,0x6E,0x70,0x4E,0x50,0x1F
,0x1D,0x01,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x03,0x29,0x4F,0x51,0x6F,0x71,0x6F,0x71,0x4F,0x51,0x1F
,0x1D,0x29,0x29,0xD0,0xD2,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x1F
,0x1D,0x29,0x29,0xD1,0xD3,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x1F
,0x1D,0xD0,0xD2,0xF5,0x40,0x29,0x29,0x29,0x3E,0xF4,0xD0,0xD2,0x29,0x3E,0xF5,0x29,0x29,0x29,0x29,0x1F
,0x1D,0xD1,0xD3,0x3F,0x41,0x29,0x29,0x29,0x3F,0x41,0xD1,0xD3,0x29,0x3F,0x41,0x29,0x29,0x29,0x29,0x1F
,0x1D,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0xD0,0xD2,0x29,0x29,0x29,0xD0,0xD2,0x29,0x29,0x29,0x29,0x1F
,0x1D,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0xD1,0xD3,0x29,0x29,0x29,0xD1,0xD3,0x29,0x29,0x29,0x29,0x1F
,0x1D,0xD0,0xD2,0x3E,0xF4,0x29,0xD0,0xD2,0xF5,0xF5,0xD0,0xD2,0x29,0x3E,0x40,0x29,0x29,0x29,0x29,0x1F
,0x1D,0xD1,0xD3,0x3F,0x41,0x29,0xD1,0xD3,0x3F,0x41,0xD1,0xD3,0x29,0x3F,0x41,0x29,0x29,0x29,0x29,0x32
,0x1D,0x4E,0x50,0xD0,0xD2,0x29,0x29,0x29,0xD0,0xD2,0x29,0x29,0x29,0xD0,0xD2,0x29,0x29,0x29,0x29,0x33
,0x1D,0x4F,0x51,0xD1,0xD3,0x29,0x29,0x29,0xD1,0xD3,0x29,0x29,0x29,0xD1,0xD3,0x29,0x29,0x29,0x29,0x1F
,0x1D,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1F

};

//Map object declaration
const struct map mapMap_Tavern1 = {
    .data = Map_Tavern1,
    .tilesW = Map_Tavern1_WIDTH,
    .tilesH = Map_Tavern1_HEIGHT,
    .floorTile = TILE_EMPTY,
    .heroStartX = 142,
    .heroStartY = 129
};

