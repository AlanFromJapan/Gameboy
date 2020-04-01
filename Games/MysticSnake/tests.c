#include "tests.h"
#include "graphics.h"
#include "my_lib01.h"
#include "inputs.h"

void test_text(){
    for (UINT16 i = 0 ; i < DynMap_MAX_HEIGHT*DynMap_MAX_WIDTH; i++){
        dynmap[i] = TILE_EMPTY;
    }

    dynmap[4 * DynMap_MAX_WIDTH + 3] = TILE_LETTER_1;
    dynmap[4 * DynMap_MAX_WIDTH + 4] = TILE_LETTER_20;
    dynmap[4 * DynMap_MAX_WIDTH + 5] = TILE_NUMBER_2;

    writetextBG(4, 5, "Alexandre TROP MIGNON CHOUPINOU!!");
    writetextBG(4, 10, "ABCD 0123");

    bgx = 0;
    bgy = 0;

    set_bkg_tiles(0, 0, DynMap_MAX_WIDTH, DynMap_MAX_HEIGHT, dynmap);

    SHOW_BKG;

    delay(500);

    while(1) {
        lastJoypad = joypad();
        if(lastJoypad & J_START) {
            break;
        }
    }

}