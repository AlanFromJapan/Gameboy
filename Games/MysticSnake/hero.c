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
UINT8 checkCollision (UINT8 x, UINT8 y, INT8 *dx, INT8 *dy){
    //x,y are in the bottom-middle of the Sprite
    // UINT8 nx = GET_MAP_X(x, *dx);
    // UINT8 ny = GET_MAP_Y(y, *dy);

    UINT8 tileX = 0, tileY = 0;
    UINT8 result = MOVE_CHECK_OK;

    // tileX = GET_BG_TILE(bgx + x  + *dx ,   bgy + y -1);
    // tileY = GET_BG_TILE(bgx + x - 8 - 1,                    bgy + y + *dy -1);
    // tileX = GET_BG_TILE( GET_MAP_X(x, *dx),     GET_MAP_Y(y, 0));
    // tileY = GET_BG_TILE( GET_MAP_X(x, 0),       GET_MAP_Y(y, *dy));

    //X, Y are the **BOTTOM RIGHT** point of the sprite  (therefore __middle bottom__ of a 16x16 sprite)!
    
    if (*dx < 0){
        //going LEFT
        tileX = GET_BG_TILE(bgx + x + *dx -8, bgy + y + *dy - 4);
    }
    if (*dx > 0){
        //going RIGHT
        tileX = GET_BG_TILE(bgx + x + *dx + 8, bgy + y + *dy - 4);
    }

    if (*dy < 0){
        //going UP
        tileY = GET_BG_TILE(bgx + x + *dx , bgy + y + *dy -16);
    }
    if (*dy > 0){
        //going DOWN
        tileY = GET_BG_TILE(bgx + x + *dx , bgy + y + *dy );
    }

/*
    //DEBUG
    if (tileX != 0)
        set_bkg_tiles(0, 0, 1, 1, &tileX);
    if (tileY != 0)
        set_bkg_tiles(0, 1, 1, 1, &tileY);
*/   


    //OPTIMIZATION: put all the collision tiles at begining or end of tile list and just make a > or < instead
    for (UINT8 i = 0; i < COLLISION_TILE_LEN; i++){
        if (*dx != 0 && tileX == COLLISION_TILE[i]){
            //collision
            *dx = 0;
            result = MOVE_CHECK_COLLISION;
        }
        //no "else" because AI might be in a corner
        if (*dy != 0 && tileY == COLLISION_TILE[i]){
            //collision
            *dy = 0;
            result = MOVE_CHECK_COLLISION;
        }

        //There's less transition than collision so it works
        if (i < TRANSITION_TILE_LEN){
            //not sure optimizer left-right
            if (tileX == TRANSITION_TILE[i] || tileY == TRANSITION_TILE[i]){
                result = MOVE_CHECK_TRANSITION;
            }
        }
        

        //quit or continue?
        if (result != MOVE_CHECK_OK)
            return result;
        
    }
    //all good
    return MOVE_CHECK_OK;
}