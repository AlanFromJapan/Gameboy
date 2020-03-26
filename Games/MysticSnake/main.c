
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

#define SCREENW         160
#define SCREENH         144
#define HSCROLLLEFT     32
#define HSCROLLRIGHT    128


#define MV_HERO(x,y) move_sprite(0, x, y); move_sprite(1, x+8, y);
unsigned int x = 50;
unsigned int y = 50;

unsigned int bgx = 0;
unsigned int bgy = 0;

unsigned int lastJoypad = 0;

unsigned char *currentMap;
unsigned int currentMapW_Px = SCREENW;
unsigned int currentMapW_Tile = 20;
unsigned int currentMapH_Tile = 18;

//List of tiles that are considered as not-walkable (should be the first ones or the last ones for performance sake)
#define COLLISION_TILE_LEN  8
UINT8 const COLLISION_TILE[] = {TILE_SAPIN_NW, TILE_SAPIN_NE, TILE_SAPIN_SW, TILE_SAPIN_SE, 
TILE_PALMTREE_NW, TILE_PALMTREE_NE, TILE_PALMTREE_SW,TILE_PALMTREE_SE};


/**
 * Check if collision, return 0 if no collision and edits the delta x & y
 */
UINT8 inline checkCollision (INT8 *dx, INT8 *dy){
    //x,y are in the bottom-middle of the Sprite
    UINT8 nx = bgx + x + (*dx * (INT8)8); //+8 because x is in the middle of the 16x16
    UINT8 ny = bgy + y + *dy -8 ; //-8 to put the collision detection center of the body

    UINT8 tile = currentMap[(ny / 8) * currentMapW_Tile + (nx / 8)];

    unsigned int i =0;
    for (; i < COLLISION_TILE_LEN; i++){
        if (tile == COLLISION_TILE[i]){
            //collision
            *dx = 0;
            *dy = 0;
            return 1;
        }
    }
    //all good
    return 0;
}

/**
 * Vertical blank interrupt: where we "draw" memory while screen is not updated
 */
void vblint(){
    SCX_REG = bgx;

    MV_HERO(x, y);
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

        checkCollision (&dx, &dy);
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


        //debouncing on the cheap
        delay(10);
    }
}


