
/*************************
**
** Autogenerated stub for basic program that just displays the first Map.
** Made by GbReaper at 5/13/2020 11:55:25 PM
** AlanFromJapan - https://electrogeek.cc
**
*/

#include <gb/gb.h>
#include <gb/drawing.h>

#include "my_lib01.h"
#include "Map_SplashScreen.h"

void main() {
    SPRITES_8x8;

    set_sprite_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_tiles(0, 0, Map_SplashScreen_WIDTH, Map_SplashScreen_HEIGHT, Map_SplashScreen);

    SHOW_BKG;
    SHOW_SPRITES;

    wait_vbl_done();

    while (1) {
        wait_vbl_done();

    }
}


