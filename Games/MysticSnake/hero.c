#include "graphics.h"
#include "hero.h"
#include "my_lib01.h"
#include "transitions.h"

//THE HERO one and unique
struct hero hero;



//List of tiles that are considered as not-walkable (should be the first ones or the last ones for performance sake)
#define COLLISION_TILE_LEN  25
UINT8 const COLLISION_TILE[] = {
TILE_SAPIN_NW, TILE_SAPIN_NE, TILE_SAPIN_SW, TILE_SAPIN_SE, 
TILE_PALMTREE_NW, TILE_PALMTREE_NE, TILE_PALMTREE_SW, TILE_PALMTREE_SE,
TILE_PALMTREE_NW, TILE_PALMTREE_NE, TILE_PALMTREE_SW, TILE_PALMTREE_SE,
TILE_ROCK_NW, TILE_ROCK_NE, TILE_ROCK_SW, TILE_ROCK_SE, 
TILE_COLUMN_NW, TILE_COLUMN_NE, TILE_COLUMN_SW, TILE_COLUMN_SE, 
TILE_TOWER_1, TILE_TOWER_2, TILE_TOWER_3, TILE_TOWER_4, TILE_TOWER_5
};



//List of transition tiles: walk on it but do something special
#define TRANSITION_TILE_LEN     12
UINT8 const TRANSITION_TILE[] = {
TILE_DOOR_NW, TILE_DOOR_NE, TILE_DOOR_SW, TILE_DOOR_SE,
TILE_STAIRS_UP_NW, TILE_STAIRS_UP_NE, TILE_STAIRS_UP_SW, TILE_STAIRS_UP_SE, 
TILE_STAIRS_DOWN_NW, TILE_STAIRS_DOWN_NE, TILE_STAIRS_DOWN_SW, TILE_STAIRS_DOWN_SE
};



/**
 * Check if collision, return 0 if no collision and edits the delta x & y, 1 if collision, 2 if transition
 */
UINT8  checkCollision (UINT8 x, UINT8 y, INT8 *dx, INT8 *dy){
    //x,y are in the bottom-middle of the Sprite
    UINT8 nx = GET_MAP_X(x, *dx);
    UINT8 ny = GET_MAP_Y(y, *dy);

    UINT8 tile = GET_BG_TILE(nx, ny);

    //OPTIMIZATION: put all the collision tiles at begining or end of tile list and just make a > or < instead
    unsigned int i =0;
    for (; i < COLLISION_TILE_LEN; i++){
        if (tile == COLLISION_TILE[i]){
            //collision
            *dx = 0;
            *dy = 0;
            return MOVE_CHECK_COLLISION;
        }

        if (i < TRANSITION_TILE_LEN){
            //not sure optimizer left-right
            if (tile == TRANSITION_TILE[i]){
                return MOVE_CHECK_TRANSITION;
            }

        }
    }
    //all good
    return MOVE_CHECK_OK;
}