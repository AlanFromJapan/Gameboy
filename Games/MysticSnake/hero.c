#include "graphics.h"
#include "hero.h"
#include "my_lib01.h"
#include "transitions.h"

//THE HERO one and unique
struct hero hero;



//List of tiles that are considered as not-walkable (should be the first ones or the last ones for performance sake)
//OPTIMIZED: it's all tiles with ID smaller than TILE_EMPTY
#define COLLIDE_MAX_TILEID  (TILE_EMPTY -1)



//List of transition tiles: walk on it but do something special
#define TRANSITION_TILE_LEN     12
UINT8 const TRANSITION_TILE[] = {
TILE_DOOR_NW, TILE_DOOR_NE, TILE_DOOR_SW, TILE_DOOR_SE,
TILE_STAIRS_UP_NW, TILE_STAIRS_UP_NE, TILE_STAIRS_UP_SW, TILE_STAIRS_UP_SE, 
TILE_STAIRS_DOWN_NW, TILE_STAIRS_DOWN_NE, TILE_STAIRS_DOWN_SW, TILE_STAIRS_DOWN_SE
};

#define COLLIDE_SIDES_OVERLAP_L     2
#define COLLIDE_SIDES_OVERLAP_R     3
#define COLLIDE_VERT_FOOT           1
#define COLLIDE_VERT_HEIGHT         12


/**
 * Check if collision, return 0 if no collision and edits the delta x & y, 1 if collision, 2 if transition
 */
UINT8 checkCollision (UINT8 x, UINT8 y, INT8 *dx, INT8 *dy, UINT8 checkTransition){
    ///////////////////////////////////////////////
    //
    // X, Y are the **BOTTOM RIGHT** point of the LEFT sprite  (therefore **middle bottom** of a 16x16 sprite)!
    //
    ///////////////////////////////////////////////


    UINT8 tileX = 0, tileY = 0, tileX2 = 0, tileY2 = 0;
    UINT8 result = MOVE_CHECK_OK;

    
    //Zelda style (?) detection
    // to respect the feeling of depth, feet can't get onto walls, but head a little, and L/R just 1 pixel
    // Therefore the calculation of collision is a sub-zone of the sprite : 1 px short L&R, bottom aligned and maybe 12 pixels high 
    // THAT ZONE never overlaps with colliding tiles.
    // ANd there's MAX 2 tiles you are trying to visually enter
    if (*dx < 0){
        //going LEFT: tileX is the upper one, tileX2 bottom one
        tileX  = GET_BG_TILE(bgx + x + *dx -8 + COLLIDE_SIDES_OVERLAP_L, bgy + y + *dy - COLLIDE_VERT_HEIGHT);
        tileX2 = GET_BG_TILE(bgx + x + *dx -8 + COLLIDE_SIDES_OVERLAP_L, bgy + y + *dy - COLLIDE_VERT_FOOT);
    }
    if (*dx > 0){
        //going RIGHT: tileX is the upper one, tileX2 bottom one
        tileX  = GET_BG_TILE(bgx + x + *dx + 8 - COLLIDE_SIDES_OVERLAP_R, bgy + y + *dy - COLLIDE_VERT_HEIGHT);
        tileX2 = GET_BG_TILE(bgx + x + *dx + 8 - COLLIDE_SIDES_OVERLAP_R, bgy + y + *dy - COLLIDE_VERT_FOOT);
    }

    if (*dy < 0){
        //going UP : tileY is the left one, tileY2 is the right one
        tileY  = GET_BG_TILE(bgx + x + *dx - 8 + COLLIDE_SIDES_OVERLAP_L, bgy + y + *dy - COLLIDE_VERT_HEIGHT);
        tileY2 = GET_BG_TILE(bgx + x + *dx + 8 - COLLIDE_SIDES_OVERLAP_R, bgy + y + *dy - COLLIDE_VERT_HEIGHT);
    }
    if (*dy > 0){
        //going DOWN: tileY is the left one, tileY2 is the right one
        tileY  = GET_BG_TILE(bgx + x + *dx - 8 + COLLIDE_SIDES_OVERLAP_L, bgy + y + *dy - COLLIDE_VERT_FOOT);
        tileY2 = GET_BG_TILE(bgx + x + *dx + 8 - COLLIDE_SIDES_OVERLAP_R, bgy + y + *dy - COLLIDE_VERT_FOOT);
    }

/*
    //DEBUG
    if (tileX != 0)
        set_bkg_tiles(0, 0, 1, 1, &tileX);
    if (tileY != 0)
        set_bkg_tiles(0, 1, 1, 1, &tileY);
*/   


    //OPTIMIZATION: put all the collision tiles at begining of tile list and just make  a comparison
    if (*dx != 0 && (tileX <= COLLIDE_MAX_TILEID || tileX2 <= COLLIDE_MAX_TILEID)){
        //collision
        *dx = 0;
        result = MOVE_CHECK_COLLISION;
    }
    //no "else" because AI might be in a corner
    if (*dy != 0 && (tileY <= COLLIDE_MAX_TILEID || tileY2 <= COLLIDE_MAX_TILEID)){
        //collision
        *dy = 0;
        result = MOVE_CHECK_COLLISION;
    }

    //do same optimization here one day ...
    if (checkTransition != 0) {
        UINT8 TILE_TRAN;
        for (UINT8 i = 0; i < TRANSITION_TILE_LEN; i++){
            if (i < TRANSITION_TILE_LEN){
                TILE_TRAN = TRANSITION_TILE[i];

                //not sure optimizer left-right
                if (tileX == TILE_TRAN || tileY == TILE_TRAN || tileX2 == TILE_TRAN || tileY2 == TILE_TRAN){
                    result = MOVE_CHECK_TRANSITION;
                }
            }
        }
    }


    return result;
}



//Hero tiles have the alternate (left foot / right foot) stored one after the other, so once you have one the rest is just adding offset
inline void updateHeroSprite(const UINT8 baseSprite){
    if ((hero.stepCount & 0x01) == 0){
        set_sprite_tile(0, baseSprite);
        set_sprite_tile(1, baseSprite + 2);
    }
    else {
        set_sprite_tile(0, baseSprite + 4);
        set_sprite_tile(1, baseSprite + 6);
    }
}