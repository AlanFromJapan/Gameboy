
/*************************
**
** Autogenerated stub for basic program that just displays the first Map.
** Made by GbReaper at 3/21/2020 8:44:00 AM
** AlanFromJapan - https://electrogeek.cc
**
*/

#include <gb/gb.h>
#include <gb/drawing.h>

#include "my_lib01.h"
#include "Map_Intro.h"
#include "transitions.h"


#define SCREENW         GRAPHICS_WIDTH
#define SCREENH         GRAPHICS_HEIGHT
#define HSCROLLLEFT     32
#define HSCROLLRIGHT    128


unsigned int x = 50;
unsigned int y = 50;

unsigned int bgx = 0;
unsigned int bgy = 0;

unsigned int lastJoypad = 0;
unsigned int stepCount = 0;

unsigned char *currentMap;
unsigned int currentMapW_Px = SCREENW;
unsigned int currentMapW_Tile = 20;
unsigned int currentMapH_Tile = 18;

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


//Move the Hero to x,y
#define MV_HERO(x,y)    move_sprite(0, x, y); move_sprite(1, x+8, y);
//Returns the background tile at XX,YY
#define GET_BG_TILE(XX, YY)     (currentMap[(YY / 8) * currentMapW_Tile + (XX / 8)])
//Returns the position of the player on the map (different than on the screen!)
#define GET_MAP_X(dx)   (bgx + x + (dx * (INT8)8)) /* +8 because x is in the middle of the 16x16 */
#define GET_MAP_Y(dy)   (bgy + y + dy -8) /* -8 to put the collision detection center of the body */

//Results of the checkCollision()
#define MOVE_CHECK_OK           0
#define MOVE_CHECK_COLLISION    1
#define MOVE_CHECK_TRANSITION   2
UINT8 lastMoveCheck = MOVE_CHECK_OK;


/**
 * Check if collision, return 0 if no collision and edits the delta x & y, 1 if collision, 2 if transition
 */
UINT8 inline checkCollision (INT8 *dx, INT8 *dy){
    //x,y are in the bottom-middle of the Sprite
    UINT8 nx = GET_MAP_X(*dx);
    UINT8 ny = GET_MAP_Y(*dy);

    UINT8 tile = GET_BG_TILE(nx, ny);

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

/**
 * Vertical blank interrupt: where we "draw" memory while screen is not updated
 */
void vblint(){
    move_bkg(bgx, 0);

    MV_HERO(x, y);

}

/**
 * Map transition: small anim and load new bg
 * 
 */
void doMapTransition(){
    HIDE_BKG;
    delay (500);
    HIDE_SPRITES;
    delay (500);

    //LOAD!
    mapTransition(
        &currentMap, 
        &x, 
        &y, 
        &currentMapW_Tile, 
        &currentMapH_Tile
        );

    bgx =0;
    bgy =0;
    currentMapW_Px = currentMapW_Tile * 8;

    vblint();

    SHOW_SPRITES;
    delay (500);
    SHOW_BKG;
    delay (500);

}




/**
 * MAIN method
 */
void main() {
  
    SPRITES_8x16;

    set_sprite_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_data(0, my_lib01_COUNT, my_lib01);

    set_bkg_tiles(bgx, bgy, Map_Intro_WIDTH, Map_Intro_HEIGHT, Map_Intro);
    currentMap = Map_Intro;
    currentMapW_Tile = Map_Intro_WIDTH;
    currentMapH_Tile = Map_Intro_HEIGHT;
    currentMapW_Px = currentMapW_Tile * 8;

    set_sprite_tile(0, TILE_HERO_NW);
    set_sprite_tile(1, TILE_HERO_NE);
    
    MV_HERO(x, y);
    
    SHOW_BKG;
    SHOW_SPRITES;

    wait_vbl_done();
    //branch interrup handler for VBlank
    add_VBL(vblint);

    while(1) {
        INT8 dx = 0;
        INT8 dy = 0;

        lastJoypad = joypad();
        if(lastJoypad & J_RIGHT && x < SCREENW-8) {
            dx=1;
        }
        if(lastJoypad & J_LEFT && x > 8) {
            dx = -1;
        }
        if(lastJoypad & J_UP && y > 16) {
            dy = -1;
        }
        if(lastJoypad & J_DOWN && y < SCREENH) {
            dy = 1;
        }

        lastMoveCheck = checkCollision (&dx, &dy);

        if (lastMoveCheck == MOVE_CHECK_TRANSITION){
            //transition!
            doMapTransition();
        }
        else {
            //move or collide
            x += dx;
            y += dy;

            //move bg Left ? only on big maps
            if (dx > 0 && currentMapW_Px > SCREENW && bgx < (currentMapW_Px - SCREENW) &&  x > HSCROLLRIGHT) {
                x--;
                bgx ++;

            }
            else {
                //move bg Right ? only on big maps
                if (currentMapW_Px > SCREENW && bgx > 0  &&  x < HSCROLLRIGHT) {
                    x++;
                    bgx --;
                }
            }

            //moved? change appearance
            if (dx != 0 || dy != 0){
                stepCount++;    

                if ((stepCount & 0x01) == 0){
                    set_sprite_tile(0, TILE_HERO_NW);
                    set_sprite_tile(1, TILE_HERO_NE);
                }
                else {
                    set_sprite_tile(0, TILE_HERO2_NW);
                    set_sprite_tile(1, TILE_HERO2_NE);
                }

            }
        }

        //debouncing on the cheap
        delay(10);


    }
}


