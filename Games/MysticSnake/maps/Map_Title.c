

#include "Map_Title.h"
#include "../maps.h"


// Project libraries
#include "my_lib01.h"


const unsigned char Map_Title[] =
{

0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29
,0x29,0x7E,0x80,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29
,0x29,0x7F,0x81,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29
,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29
,0x29,0x1C,0x1D,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1F,0x20,0x29
,0x29,0x1C,0x1D,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x1F,0x20,0x29
,0x29,0x1C,0x1D,0x29,0xAA,0xB6,0xB0,0xB1,0xA6,0xA0,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x1F,0x20,0x29
,0x29,0x1C,0x1D,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0xB0,0xAB,0x9E,0xA8,0xA2,0x29,0x29,0x1F,0x20,0x29
,0x29,0x1C,0x1D,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x1F,0x20,0x29
,0x29,0x1C,0x1D,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1F,0x20,0x29
,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x7A,0x7C,0x29
,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x7B,0x7D,0x29
,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29
,0x96,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x97,0x98
,0x99,0xAD,0xAC,0xB2,0xAF,0x29,0x9E,0xA9,0xA2,0xB5,0x9E,0xAB,0xA1,0xAF,0xA2,0x29,0x29,0x29,0x29,0x9A
,0x99,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x29,0x2E,0x30,0x9A
,0x99,0x29,0x29,0x29,0xAA,0x9E,0xAF,0xB0,0x29,0xC2,0xAC,0xC2,0xAC,0xCC,0xC2,0xC2,0x29,0x2F,0x31,0x9A
,0x9B,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9C,0x9D

};

//Map object declaration
const struct map mapMap_Title = {
    .data = Map_Title,
    .tilesW = Map_Title_WIDTH,
    .tilesH = Map_Title_HEIGHT,
    .floorTile = TILE_EMPTY,
    .heroStartX = 0,
    .heroStartY = 0
};


