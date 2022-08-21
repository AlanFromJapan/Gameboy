#include "tests.h"
#include "graphics.h"
#include "maps/my_lib01.h"
#include "inputs.h"
#include "windows.h"
#include "transitions.h"

#include "maps/Map_Outside1.h"


void test_text(){
    clearDynmap(TILE_EMPTY);

    dynmapW = 20;
    dynmapH = 18;

    dynmap[4 * DynMap_MAX_WIDTH + 3] = TILE_LETTER_1;
    dynmap[4 * DynMap_MAX_WIDTH + 4] = TILE_LETTER_20;
    dynmap[4 * DynMap_MAX_WIDTH + 5] = TILE_NUMBER_2;

    writetextBG(4, 5, "Alexandre TROP MIGNON CHOUPINOU!!");
    writetextBG(4, 10, "ABCD 0123");

    bgx = 0;
    bgy = 0;

    set_bkg_tiles(0, 0, dynmapW, dynmapH, dynmap);

    SHOW_BKG;

    delay(500);

    while(1) {
        lastJoypad = joypad();
        if(lastJoypad & J_START) {
            break;
        }
    }

}


void test_windows() {
    windowShowText("Bonjour 2sec", 2);    
    windowShowText("un message long   qui se coupe bien", 0);
    windowShowText("un message tres    long qui depasse  mais passe a la   page suivante !", 0);
    windowShowText("Alors du delire   un message sur 3  pages carement    c est fou fou fou et tres beau.", 0);
}


/**
 * Shows the Big map 
 */
void showBigMapOutside(){

    
    set_bkg_tiles(bgx, bgy, Map_Outside1_WIDTH, Map_Outside1_HEIGHT, Map_Outside1);
    currentMap.data = Map_Outside1;
    currentMap.tilesW = Map_Outside1_WIDTH;
    currentMap.tilesH = Map_Outside1_HEIGHT;
    currentMap.floorTile = TILE_EMPTY;
}
