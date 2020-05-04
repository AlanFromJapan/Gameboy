#include "transition.h"

#include "Map_Arene.h"
#include "Map_Arene2.h"
#include "Map_Arene3.h"
#include "Map_Arene4.h"
#include "Map_Arene5.h"
#include "Map_Arene6.h"
#include "Map_Arene7.h"
#include "Map_Arene8.h"
#include "Map_Arene9.h"
#include "Map_Arene10.h"
#include "Map_Arene11.h"
#include "Map_Arene12.h"
#include "Map_Arene13.h"
#include "Map_Arene14.h"
#include "Map_Arene15.h"
#include "Map_Arene16.h"
#include "Map_Arene17.h"

#include "my_lib01.h"

struct ArenaBucket {
    UINT8*  arena;
    UINT8   bgTile;
    UINT8   startX;
    UINT8   startY;
};


const struct ArenaBucket _arenas[] = {
    {Map_Arene,     TILE_EMPTY,             10, 8},
    {Map_Arene2,    TILE_EMPTY,             10, 8},
    {Map_Arene3,    TILE_EMPTY,             10, 2},
    {Map_Arene4,    TILE_EMPTY,             3, 3},
    {Map_Arene5,    TILE_SAND,              10, 8},
    {Map_Arene6,    TILE_EMPTY,             10, 8},
    {Map_Arene7,    TILE_SAND,              10, 8},
    {Map_Arene8,    TILE_SAND,              10, 8},
    {Map_Arene9,    TILE_DIAGBRICK2,        10, 4},
    {Map_Arene10,   TILE_DIAGBRICK2,        10, 4},
    {Map_Arene11,   TILE_EMPTY,             10, 4},
    {Map_Arene12,   TILE_SAND,              10, 4},
    {Map_Arene13,   TILE_DIAGBRICK2,        10, 4},
    {Map_Arene14,   TILE_EMPTY,             10, 4},
    {Map_Arene15,   TILE_DIAGBRICK,         10, 4},
    {Map_Arene16,   TILE_DIAGBRICK2,        10, 4},
    {Map_Arene17,   TILE_EMPTY,             10, 4},
};
UINT8 _currentArenaId = 0; 
#define ARENAS_COUNT    17


void arenaTransition(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY) {
    _currentArenaId = (_currentArenaId +1) % ARENAS_COUNT;

    *nextArena = _arenas[_currentArenaId].arena;
    *backgroundTile = _arenas[_currentArenaId].bgTile;
    *startX = _arenas[_currentArenaId].startX;
    *startY = _arenas[_currentArenaId].startY;
}


void arenaTransitionBackToLevel1(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY) {
    //trick so when called it turns to zero = the first level
    _currentArenaId = ARENAS_COUNT-1;

    arenaTransition(nextArena, backgroundTile, startX, startY);
}

void arenaReset(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY) {
    *nextArena = _arenas[_currentArenaId].arena;
    *backgroundTile = _arenas[_currentArenaId].bgTile;
    *startX = _arenas[_currentArenaId].startX;
    *startY = _arenas[_currentArenaId].startY;
}

inline UINT8 getCurrentArenaId(){
    return _currentArenaId;
}