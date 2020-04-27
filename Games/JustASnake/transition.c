#include "transition.h"
#include "Map_Arene.h"
#include "Map_Arene2.h"
#include "Map_Arene3.h"
#include "my_lib01.h"

void arenaTransition(UINT8** currentArena, UINT8** nextArena, UINT8* backgroundTile) {
    // switch ((UINT16)*currentArena){
    //     case (const UINT16)&Map_Arene:
    //         *nextArena = Map_Arene2;
    //         *backgroundTile = TILE_SAND;
    //         break;
    //     case (const UINT16)&Map_Arene2:
    //         *nextArena = Map_Arene3;
    //         *backgroundTile = TILE_SAND;
    //         break;

    // }

            *nextArena = Map_Arene3;
            *backgroundTile = TILE_SAND;
}