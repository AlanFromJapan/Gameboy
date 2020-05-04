
/*************************
**
** Just A Snake 
** April 2020
**
** AlanFromJapan - https://electrogeek.cc
**
*/

#include <gb/gb.h>
#include <gb/drawing.h>

//#include <gb/rand.h>
#include <stdlib.h>

#include "my_lib01.h"
#include "Map_SplashScreen.h"
#include "Map_About.h"
#include "Map_Arene.h"
#include "window.h"
#include "transition.h"
#include "game.h"


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

INT8 dx = -1;
INT8 dy = 0;


/**
 * Draws the "Level xx" label
 * 
 * Should have been drawned in the map, or calculated once and kept in mem, so let's say it's a tradeoff space vx complexity
 */
#define LEVEL_LABEL_LEN 10
inline void drawLevelLabel(){
    //Label
    char* lbl = " Level xx ";
    UINT8 lblTiles[LEVEL_LABEL_LEN+1];
    lbl[LEVEL_LABEL_LEN] = 0;

    //make tiles 
    string2tile(lbl, lblTiles);

    //overwrite the xx with the arena number (start = 1)
    UINT8 lvl = getCurrentArenaId() +1;
    if (lvl < 10){
        lblTiles[7] = TILE_NUMBER_BLACK_1; //0        
    }
    else {
        lblTiles[7] = TILE_NUMBER_BLACK_1 + (lvl / 10); 
    }
    lblTiles[8] = TILE_NUMBER_BLACK_1 + (lvl % 10); 
    
    //write it on the background
    for (UINT8 t = 0; t < LEVEL_LABEL_LEN; t++){
        putTile(lblTiles[t], (20-LEVEL_LABEL_LEN)/2 + t, 0);
    }

}

#define NEXTARENA_NEXT      0
#define NEXTARENA_FIRST     1
#define NEXTARENA_RESET     2

/**
 * Transition to next arena
 * pReinit: 0= NEXT level, 1= back to level 1, 2= restart current level
 */
void nextArena(UINT8 pReinit){
    //disable to avoid dirty writes on the background
    disable_interrupts();
    UINT8 x,y;

    switch (pReinit){
        case NEXTARENA_NEXT:
            //Go to next level
            arenaTransition(&currentArenaMap, &backgroundTile, &x, &y);
            break;

        case NEXTARENA_FIRST:
            //Go to level 1
            arenaTransitionBackToLevel1(&currentArenaMap, &backgroundTile, &x, &y);
            score = 0;
            heartsCount = HEART_DEFAULT;
            //no break: do the reset just below
            
        case NEXTARENA_RESET:
            //reset current level
            arenaReset(&currentArenaMap, &backgroundTile, &x, &y);
    }


    SETX(HEAD, x);
    SETY(HEAD, y);
    snakeLen = 1;
    speed = SPEED_START;

    set_bkg_tiles(0, 0, Map_Arene_WIDTH, Map_Arene_HEIGHT, currentArenaMap);

    updateScore();
    updateHearts();

    drop_bonbon();

    currentItemNumber = 1;

    //force the initial direction to left
    dx = -1;
    dy = 0;

    //add the "Level xx"
    drawLevelLabel();

    //at last: back in business
    enable_interrupts();
}

/**
 * Shows gameover
 */
void gameOver(){
    windowShowText("Game Over!", 0);

    nextArena(NEXTARENA_FIRST);
}

/**
 * Move the snake to x,y.
 * It's NOT the arena border, but no other check done.
 */
void moveTo(UINT8 x, UINT8 y){
    //disable to avoid dirty writes on the background
    disable_interrupts();

    //erase tail
    putTile(backgroundTile, GETX(TAIL), GETY(TAIL));

    //slide every items 
    for(UINT8 i =snakeLen; snakeLen >= 1 && i > 0; i--){
        SETX (snake[i-1], GETX(snake[i-2]));
        SETY (snake[i-1], GETY(snake[i-2]));
    }

    //them move head
    SETY(HEAD, y);
    SETX(HEAD, x);

    UINT8 nextTile = 0;
    get_bkg_tiles(x, y, 1, 1, &nextTile);
    switch (nextTile) {

        /* ------------- Bonbon ------------- */
        case TILE_BONBON:
            //copy the snake content to one more cell backward
            for(UINT8 i =snakeLen; snakeLen >= 1 && i > 0; i--){
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

            //more sweets or next map?
            currentItemNumber++;
            if (currentItemNumber > ITEMS_PER_LEVEL){
                //next level!
                windowShowText("Bravo ! On to the next level!", 0);
                
                //get bonus points
                score += 150 * heartsCount;

                nextArena(NEXTARENA_NEXT);
            }
            else {
                //add next item
                drop_bonbon();
            }
            break;
        
        /* ------------- Ground tiles ok to cross ------------- */
        case TILE_EMPTY:
        case TILE_SAND:
        case TILE_DIAGBRICK:
        case TILE_DIAGBRICK2:
            break;
        
        /* ------------- Other tile : you shouldn't be here ------------- */
        default:   
            hitWall();
            break;
    }

    enable_interrupts();
}


/**
 * If you hit a wall, might lead to a gameover
 */
void hitWall(){
    heartsCount --;
    if (heartsCount == 0){
        //sorry finished
        heartsCount = HEART_DEFAULT;
        gameOver();
    }
    else{
        //update hearts
        updateHearts();

        windowShowText("Ouch! Resetting\nlevel...", 0);

        //restart level
        nextArena(NEXTARENA_RESET);
    }
}


/**
 * Vertical blank interrupt: where we "draw" memory while screen is not updated
 */
void vblint(){

    //Draw from the tail to the head, so that the head is always visible (because drawn last)
    UINT8 i = snakeLen -1;
    while(1){
        if (i == 0)
            putTile(TILE_SNAKE_HEAD, GETX(snake[i]), GETY(snake[i]));
        else
            putTile(TILE_SNAKE_BODY, GETX(snake[i]), GETY(snake[i]));            


        if (i == 0)
            break;
        else
            i--;        
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
    SHOW_SPRITES;

    UINT8 mnu = showTitle();

    switch(mnu){
        case TITLEMENU_CREDITS:
            showCredits();
            break;
        case TITLEMENU_OPTIONS:
            showOptions();
            break;
    }

    //anyway, after the menu or if player picked play, let's start preparing the game from this point
    wait_vbl_done();    

    //init the snake
    SETX(HEAD, 10);
    SETY(HEAD, 9);
    snakeLen = 1;

    //init random generator
    srand(DIV_REG);

    //just to be sure all the initial level is loaded fine
    nextArena(NEXTARENA_FIRST);
    SHOW_BKG;

    //branch interrup handler for VBlank
    add_VBL(vblint);

    while (1) {
        UINT8 t = 0;
        //Read often (every n millisec) but move only every /speed/ millisec
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
                nextArena(NEXTARENA_NEXT);
                //debounce
                delay(200);
            }


            t += 10;
            delay(10);
        }

        //move calculations
        UINT8 newx = GETX(HEAD) + dx;
        UINT8 newy = GETY(HEAD) + dy;
        if (dx != 0 && newx >0 && newx < Map_Arene_WIDTH-1){
            moveTo(newx, GETY(HEAD));
        }
        else {
            if (dx != 0) {
                hitWall();
            }
        }
        if (dy != 0 && newy > 0 && newy < Map_Arene_HEIGHT -2){
            moveTo(GETX(HEAD), newy);
        }
        else {
            if (dy != 0) {
                hitWall();
            }
        }

    }
}


