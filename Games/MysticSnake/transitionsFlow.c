#include <stdio.h>
#include "transitionsFlow.h"
#include "maps.h"


#include "maps/Map_BigRoom1.h"
#include "maps/Map_bridge1.h"
#include "maps/Map_bridge2.h"
#include "maps/Map_Chapelle1.h"
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

/**
 * Move from one predefined map to the next
 * Param map WILL be edited so NOT constant
 */
struct map* nextMap (struct map* map){


    if (map == NULL){
        //First time heh?
        return &mapMap_MaisonDebut;
    }

    if (CURRENT_MAP_IS(map, mapMap_MaisonDebut)){
        return &mapMap_Intro;
    }

    if (CURRENT_MAP_IS(map, mapMap_Intro)){
        //Intro -> bridge1
        return &mapMap_bridge1;
    }
    if (CURRENT_MAP_IS(map, mapMap_bridge1)){
        //bridge1 -> ville ruine 1
        return &mapMap_VilleRuine1;
    }
    if (CURRENT_MAP_IS(map, mapMap_VilleRuine1)){
        //ville ruine1 -> chappelle 1
        return &mapMap_Chapelle1;
    }
    //shouldn't happen ... back to square 1
    return &mapMap_MaisonDebut;
}