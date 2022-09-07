#include <stdio.h>
#include "transitionsFlow.h"
#include "maps.h"
#include "hero.h"


#include "maps/Map_bridge1.h"
#include "maps/Map_Intro.h"
#include "maps/Map_VilleRuine1.h"
#include "maps/Map_Chapelle1.h"

inline struct map* loadMap (struct map* map, const struct map* newMap, UINT8 herox, UINT8 heroy){
    (*map).data = (*newMap).data;
    (*map).tilesW = (*newMap).tilesW;
    (*map).tilesH = (*newMap).tilesH;
    (*map).floorTile = (*newMap).floorTile;
    //like that until editor supports to set hero start
    (*map).heroStartX = herox;
    (*map).heroStartY = heroy;

    return map;
}

//#define CURRENT_MAP_IS(cur,test) ((*(cur)).data == ((test).data))
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
        //return loadMap(map, &mapMap_bridge1, 8, 80);

        return &mapMap_bridge1;
    }
    if (CURRENT_MAP_IS(map, mapMap_bridge1)){
        //bridge1 -> ville ruine 1
        return &mapMap_VilleRuine1;
        //return loadMap(map, &mapMap_VilleRuine1, 8, 144-24);
    }
    if (CURRENT_MAP_IS(map, mapMap_VilleRuine1)){
        //ville ruine1 -> chappelle 1
        //return loadMap(map, &mapMap_Chapelle1, mapMap_Chapelle1.tilesW *8/2, (mapMap_Chapelle1.tilesH -1) *8);
        return &mapMap_Chapelle1;
    }

    //shouldn't happen ... back to square 1
    return &mapMap_Intro;

/*
    if ((*map).data == Map_Chapelle1){
        //Cemetary -> enter in Room1
        hero.x=24;
        hero.y=40;
        (*map).data = Map_Room1;
        (*map).tilesW = Map_Room1_WIDTH;
        (*map).tilesH = Map_Room1_HEIGHT;
        (*map).floorTile = TILE_SAND;

        //mMapTransitionModeFlag = 1; //stay out of the random map loop
        break;
    }

    if ((*map).data == Map_Room1) {
        //Room1 -> BigRoom1
        hero.x=24;
        hero.y=24;
        (*map).data = Map_BigRoom1;
        (*map).tilesW = Map_BigRoom1_WIDTH;
        (*map).tilesH = Map_BigRoom1_HEIGHT;
        (*map).floorTile = TILE_EMPTY;

        //From that point on move to random maps (set flag to 1)
        mMapTransitionModeFlag = 1;

        //seed the random generator
        srand(DIV_REG);

        break;
    }
*/
}