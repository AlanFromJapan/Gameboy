
/*************************
**
** Autogenerated stub for basic program that just displays the first Map.
** Made by GbReaper at 3/18/2020 7:58:19 AM
** AlanFromJapan - https://electrogeek.cc
**
*/

#include <gb/gb.h>
#include <gb/drawing.h>

#include "my_lib01.c"
#include "Map_A.h"

void main() {
    SPRITES_8x8;

    set_sprite_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_data(0, my_lib01_COUNT, my_lib01);
    set_bkg_tiles(0, 0, Map_A_WIDTH, Map_A_HEIGHT, Map_A);

    SHOW_BKG;
    SHOW_SPRITES;

    wait_vbl_done();

    while (1) {
        wait_vbl_done();

    }
}

