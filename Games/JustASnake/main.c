
/*************************
**
** Autogenerated stub for basic program that just displays the first Map.
** Made by GbReaper at 4/21/2020 8:31:18 AM
** AlanFromJapan - https://electrogeek.cc
**
*/

#include <gb/gb.h>
#include <gb/drawing.h>

#include "my_lib01.h"
#include "Map_SplashScreen.h"
#include "Map_About.h"
#include "Map_Arene.h"
#include "window.h"
#include "transition.h"


#define SPEED_START 250
#define SPEED_MIN   60
UINT8 speed = SPEED_START;

#define SNAKE_SIZE  32

//The snake body [tile num 0 = head][x,y in TILES not px]
UINT8 snake[SNAKE_SIZE][2];
UINT8 snakeLen = 1;
#define HEAD        snake[0]
#define TAIL        snake[snakeLen-1]

#define GETX(v)     (v[0])
#define GETY(v)     (v[1])

#define SETX(v, x)  v[0] = x;
#define SETY(v, y)  v[1] = y;

#define ITEMS_SIZE  10


UINT8 backgroundTile = TILE_EMPTY;
UINT8* currentArenaMap = Map_Arene;


UINT16 score = 1234;

/**
 * Shows title screen
 * 
 */
inline void showTitle(){
    set_bkg_tiles(0, 0, Map_SplashScreen_WIDTH, Map_SplashScreen_HEIGHT, Map_SplashScreen);
    SHOW_BKG;

    while(1) {
        if(joypad() & J_START) {
            break;
        }
        delay(10);
    }

    //debouncing
    delay(200);
}


/**
 * Shows arena screen
 * 
 */
void showArena(){
    set_bkg_tiles(0, 0, Map_Arene_WIDTH, Map_Arene_HEIGHT, Map_Arene);
    SHOW_BKG;

}

/**
 * Set a background tile to the tile in parameter
 */
void putTile(UINT8 tile, UINT8 x, UINT8 y){
    //NOT inline so tile is a byte in the call stack so you can ref its address
    set_bkg_tiles(x, y, 1, 1, &tile);

}


void placeItem(UINT8 tile, UINT8 x, UINT8 y){
    
    putTile(tile, x ,y);

}



void updateScore(){
    UINT8 v = 0;

    v = score % 10;
    putTile(TILE_NUMBER_BLACK_1 + v, Map_Arene_WIDTH-2, Map_Arene_HEIGHT-1);
    v = (score / 10) % 10;
    putTile(TILE_NUMBER_BLACK_1 + v, Map_Arene_WIDTH-3, Map_Arene_HEIGHT-1);
    v = (score / 100) % 10;
    putTile(TILE_NUMBER_BLACK_1 + v, Map_Arene_WIDTH-4, Map_Arene_HEIGHT-1);
    v = (score / 1000) % 10;
    putTile(TILE_NUMBER_BLACK_1 + v, Map_Arene_WIDTH-5, Map_Arene_HEIGHT-1);
}

void moveTo(UINT8 x, UINT8 y){

    //erase tail
    putTile(backgroundTile, GETX(TAIL), GETY(TAIL));

    //slide every items 
    for(UINT8 i =snakeLen; snakeLen > 1 && i > 0; i--){
        SETX (snake[i-1], GETX(snake[i-2]));
        SETY (snake[i-1], GETY(snake[i-2]));
    }

    UINT8 nextTile = 0;
    get_bkg_tiles(x, y, 1, 1, &nextTile);
    switch (nextTile) {

        case TILE_BONBON:
            //copy the snake content to one more cell backward
            for(UINT8 i =snakeLen; snakeLen > 1 && i > 0; i--){
                SETX (snake[i], GETX(snake[i-1]));
                SETY (snake[i], GETY(snake[i-1]));
            }

            //grow
            snakeLen ++;

            //remove the bonbon
            putTile(backgroundTile, x, y);

            //speedup
            speed = speed - (speed/8);

            //get points
            score += 100;
            updateScore();
            break;
        
    }


    SETY(HEAD, y);
    SETX(HEAD, x);
}

/**
 * Shows gameover
 */
void gameOver(){
    windowShowText("Game Over!", 0);
}

/**
 * Voids all the arena cells
 */
void initArena(){

}


/**
 * Transition to next arena
 */
void nextArena(){

    arenaTransition(&currentArenaMap, &backgroundTile, &(GETX(HEAD)), &(GETY(HEAD)));
    snakeLen = 1;
    speed = SPEED_START;

    set_bkg_tiles(0, 0, Map_Arene_WIDTH, Map_Arene_HEIGHT, currentArenaMap);
}

/**
 * Vertical blank interrupt: where we "draw" memory while screen is not updated
 */
void vblint(){

    for (UINT8 i = 0; i < snakeLen; i++){
        if (i == 0)
            putTile(TILE_SNAKE_HEAD, GETX(snake[i]), GETY(snake[i]));
        else
            putTile(TILE_SNAKE_BODY, GETX(snake[i]), GETY(snake[i]));
    }
}

/*****************************************************************************************
 * 
 * Main()
 * 
 */
void main() {
    SPRITES_8x8;

    set_sprite_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_data(0, my_lib01_COUNT, my_lib01);

    SHOW_BKG;

    showTitle();

    initArena();
    showArena();
    SHOW_SPRITES;

    wait_vbl_done();    

    //init the snake
    SETX(HEAD, 10);
    SETY(HEAD, 9);
    snakeLen = 1;


    placeItem(TILE_BONBON, 4, 4);
    placeItem(TILE_BONBON, 4, 5);
    placeItem(TILE_BONBON, 4, 6);
    placeItem(TILE_BONBON, 4, 7);

    updateScore();

    

    //branch interrup handler for VBlank
    add_VBL(vblint);

    INT8 dx = -1;
    INT8 dy = 0;
    while (1) {
        UINT8 t = 0;
        while (t < speed) {
            UINT8 lastJoypad = joypad();
            if(dx == 0 && lastJoypad & J_RIGHT ) {
                dx=1;
                dy=0;
            }
            if(dx == 0 && lastJoypad & J_LEFT ) {
                dx=-1;
                dy=0;
            }
            if(dy == 0 && lastJoypad & J_UP ) {
                dy=-1;
                dx=0;
            }
            if(dy == 0 && lastJoypad & J_DOWN) {
                dy=1;
                dx=0;
            }


            /* DEBUG TEST MOVE TO NEXT ARENA */
            if (lastJoypad & J_SELECT){
                nextArena();
                //debouncd
                delay(200);
            }


            t += 10;
            delay(10);
        }

        UINT8 newx = GETX(HEAD) + dx;
        UINT8 newy = GETY(HEAD) + dy;
        if (dx != 0 && newx >0 && newx < Map_Arene_WIDTH-1){
            moveTo(newx, GETY(HEAD));
        }
        else {
            if (dx != 0) {
                //TODO HIT A WALL
                gameOver();
            }
        }
        if (dy != 0 && newy > 0 && newy < Map_Arene_HEIGHT -2){
            moveTo(GETX(HEAD), newy);
        }
        else {
            if (dy != 0) {
                //TODO HIT A WALL
                gameOver();
            }
        }

    }
}


