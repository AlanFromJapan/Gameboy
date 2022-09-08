#include <stdio.h>
#include "transitionsFlow.h"
#include "maps.h"


#include "maps/Map_bridge1.h"
#include "maps/Map_Intro.h"
#include "maps/Map_VilleRuine1.h"
#include "maps/Map_Chapelle1.h"


#define CURRENT_MAP_IS(cur,test) (cur == &test)

/**
 * Move from one predefined map to the next
 * Param map WILL be edited so NOT constant
 */
struct map* nextMap (struct map* map){

    if (map == NULL){
        //First time heh?
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
    return &mapMap_Intro;
}