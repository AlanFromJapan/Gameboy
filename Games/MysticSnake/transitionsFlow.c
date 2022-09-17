#include <stdio.h>
#include "transitionsFlow.h"
#include "maps.h"


#include "maps/Map_BigRoom1.h"
#include "maps/Map_bridge1.h"
#include "maps/Map_bridge2.h"
#include "maps/Map_Chapelle1.h"
#include "maps/Map_court1.h"
#include "maps/Map_CrystalCave1.h"
#include "maps/Map_Foret1.h"
#include "maps/Map_Foret2.h"
#include "maps/Map_Intro.h"
#include "maps/Map_MaisonDebut.h"
#include "maps/Map_Outside1.h"
#include "maps/Map_Room1.h"
#include "maps/Map_Sprites.h"
#include "maps/Map_Tavern1.h"
#include "maps/Map_Title.h"
#include "maps/Map_VilleRuine1.h"
//#include "maps/my_lib01.h"



#define CURRENT_MAP_IS(cur,test) (cur == &test)
#define START_MAP   mapMap_MaisonDebut

/**
 * Move from one predefined map to the next
 * Param map WILL be edited so NOT constant
 */
struct map* nextMap (struct map* map){


    if (map == NULL){
        //First time heh?
        return &START_MAP;
    }

    if (CURRENT_MAP_IS(map, mapMap_MaisonDebut)){
        return &mapMap_VilleRuine1;
    }
    if (CURRENT_MAP_IS(map, mapMap_VilleRuine1)){
        return &mapMap_bridge1;
    }
    if (CURRENT_MAP_IS(map, mapMap_bridge1)){
        return &mapMap_Foret2;
    }
    if (CURRENT_MAP_IS(map, mapMap_Foret2)){
        return &mapMap_Foret1;
    }
    if (CURRENT_MAP_IS(map, mapMap_Foret1)){
        return &mapMap_Intro;
    }
    if (CURRENT_MAP_IS(map, mapMap_Intro)){
        return &mapMap_court1;
    }
    if (CURRENT_MAP_IS(map, mapMap_court1)){
        return &mapMap_Chapelle1;
    }
    if (CURRENT_MAP_IS(map, mapMap_Chapelle1)){
        return &mapMap_Room1;
    }
    if (CURRENT_MAP_IS(map, mapMap_Room1)){
        return &mapMap_BigRoom1;
    }
    if (CURRENT_MAP_IS(map, mapMap_BigRoom1)){
        return &mapMap_CrystalCave1;
    }

    //shouldn't happen ... back to square 1
    return &START_MAP;
}