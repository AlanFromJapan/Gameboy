
/*************************
**
** Autogenerated stub for basic program that just displays the first Map.
** Made by GbReaper at 3/21/2020 8:44:00 AM
** AlanFromJapan - http://electrogeek.tokyo
**
*/

#include <gb/gb.h>
#include <gb/drawing.h>

#include "maps.h"
#include "my_lib01.h"
#include "Map_Intro.h"
#include "Map_Title.h"
#include "transitions.h"
#include "graphics.h"
#include "inputs.h"
#include "windows.h"
#include "ai.h"
#include "hero.h"

//#define SHOW_INTRO

//#define RUN_TESTS
#define SELECT_NEXT_LEVEL

#ifdef RUN_TESTS
#include "tests.h"
#endif //RUN_TESTS

//Width of the playable area in pixels
#define SCREENW         GRAPHICS_WIDTH
//Height of the playable area in pixels : added a -8 to provision for the bottom HUD that steals 1 line of visibility
#define SCREENH         (GRAPHICS_HEIGHT -8)
//Scrolling limits
#define HSCROLLLEFT         32
#define HSCROLLRIGHT        (GRAPHICS_WIDTH - 32)
#define VSCROLLTOP          40
#define VSCROLLBOTTOM       (GRAPHICS_HEIGHT -40)





/**
 * Vertical blank interrupt: where we "draw" memory while screen is not updated
 */
void vblint(){
    move_bkg(bgx, bgy);

    MV_HERO();

}



/**
 * Shows title screen
 * 
 */
void showTitle(){
    set_bkg_tiles(0, 0, Map_Title_WIDTH, Map_Title_HEIGHT, Map_Title);
    SHOW_BKG;

    while(1) {
        lastJoypad = joypad();
        if(lastJoypad & J_START) {
            break;
        }
        delay(10);
    }

    //debouncing
    delay(200);
}




/**
 * Move to next screen 
 */
inline void doTransition(){
    clearAllAI();
    doMapTransition();
    setMapAI(&currentMap);
}


/*
 ***********************************************************************************************
 * MAIN method
 ***********************************************************************************************
 */
void main() {
  
    SPRITES_8x16;

    set_sprite_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_data(0, my_lib01_COUNT, my_lib01);

    //Shows the title screen
    showTitle();

    //TEST
#ifdef RUN_TESTS    
    test_text();
    
    //Show a sample of 32x32 map
    //showBigMapOutside();
#endif

#ifdef SHOW_INTRO
    //Intro scroller
    showStartupScroller();
#endif //SHOW_INTRO

    //show the landing map
    showInitialMap();

    //make the hero and move to start point
    set_sprite_tile(0, TILE_HERO_NW);
    set_sprite_tile(1, TILE_HERO_NE);
    
    MV_HERO();
    
    SHOW_BKG;
    SHOW_SPRITES;

    wait_vbl_done();
    //branch interrup handler for VBlank
    add_VBL(vblint);

    //HUD
    showHUD();

    while(1) {
        INT8 dx = 0;
        INT8 dy = 0;

        lastJoypad = joypad();
        if(lastJoypad & J_RIGHT && MAP2SCREEN_X(hero.x) < SCREENW-8) {
            dx=1;
            hero.heroLook = HERO_LOOK_RIGHT;
        }
        if(lastJoypad & J_LEFT && MAP2SCREEN_X(hero.x) > 8) {
            dx = -1;
            hero.heroLook = HERO_LOOK_LEFT;
        }
        if(lastJoypad & J_UP && MAP2SCREEN_Y(hero.y) > 16) {
            dy = -1;
            hero.heroLook = HERO_LOOK_UP;
        }
        if(lastJoypad & J_DOWN && MAP2SCREEN_Y(hero.y) < SCREENH -1) { 
            dy = 1;
            hero.heroLook = HERO_LOOK_DOWN;
        }

        //TEST
#ifdef SELECT_NEXT_LEVEL    
        if(lastJoypad & J_SELECT) {
            doTransition();
        }
#endif

        //TEST
#ifdef RUN_TESTS            
    
        if(lastJoypad & J_START) {
            test_windows();
        }
        
#endif 

        //--------------------------------------------------- PLAYER APPEARANCE --------------------------------------------------------
        //ATTEMPT to move? at least change sprite even if movement will be impossible
        //
        // About the sprites, remember they must be on an EVEN tile index. If on ODD index they won't display right. 
        //Sprites are set alternate full sprite one after the other to ease the code
        if (dx != 0 || dy != 0){
            switch(hero.heroLook){
                case HERO_LOOK_DOWN:
                    updateHeroSprite(TILE_HERO_NW);
                    break;

                case HERO_LOOK_LEFT:
                    updateHeroSprite(TILE_HERO_LEFT_NW);
                    break;

                case HERO_LOOK_UP:
                    updateHeroSprite(TILE_HERO_UP_NW);
                    break;


                case HERO_LOOK_RIGHT:
                    //use the LEFT tiles but swapped and then mirrored (next step)
                    if ((hero.stepCount & 0x01) == 0){
                        set_sprite_tile(0, TILE_HERO_LEFT_NW + 2);
                        set_sprite_tile(1, TILE_HERO_LEFT_NW );
                    }
                    else {
                        set_sprite_tile(0, TILE_HERO_LEFT_NW + 6);
                        set_sprite_tile(1, TILE_HERO_LEFT_NW + 4);
                    }
                    break;
            }



            switch(hero.heroLook){

                case HERO_LOOK_DOWN:
                case HERO_LOOK_UP:
                case HERO_LOOK_LEFT:
                    set_sprite_prop(0, 0x00); //NO flip
                    set_sprite_prop(1, 0x00); //NO flip
                    break;
                case HERO_LOOK_RIGHT:
                    set_sprite_prop(0, 0x20); //Flip L/R
                    set_sprite_prop(1, 0x20); //Flip L/R
                    break;
            }

        }

        //--------------------------------------------------- COLLISION --------------------------------------------------------

        UINT8 lastMoveCheck = checkCollision (hero.x, hero.y, &dx, &dy, CHECK_FOR_TRANSITION);

        if (lastMoveCheck == MOVE_CHECK_TRANSITION){
            //transition!
            doTransition();
        }
        else {
            //move or collide
            hero.x += dx;
            hero.y += dy;

            //change steps (sprite animation)
            if (dx != 0 || dy != 0){
                hero.stepCount++;   
            } 

            //move bg Left ? only on big maps
            if (dx > 0 && currentMap.tilesW * 8 > SCREENW && bgx < (currentMap.tilesW * 8 - SCREENW) &&  MAP2SCREEN_X(hero.x) > HSCROLLRIGHT) {
                bgx ++;
                backgroundMoveEventAI();
            }
            else {
                //move bg Right ? only on big maps
                if (currentMap.tilesW * 8 > SCREENW && bgx > 0  &&  MAP2SCREEN_X(hero.x) < HSCROLLLEFT) {
                    bgx --;
                    backgroundMoveEventAI();
                }
            }


            //move bg Up ? only on big maps
            if (dy > 0 && currentMap.tilesH * 8 > SCREENH && bgy < (currentMap.tilesH * 8 - SCREENH) && MAP2SCREEN_Y(hero.y) > VSCROLLBOTTOM) {
                bgy ++;
                backgroundMoveEventAI();
            }
            else {
                //move bg Down ? only on big maps
                if (currentMap.tilesH * 8 > SCREENH && bgy > 0  && MAP2SCREEN_Y(hero.y) < VSCROLLTOP) {
                    bgy --;
                    backgroundMoveEventAI();
                }
            }


            //Now AI's turn to move
            moveAI();
        }

        //debouncing on the cheap: replace me with frame skipping if needed
        delay(10);


    }
}


