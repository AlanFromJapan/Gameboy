
/*************************
**
** Shows the sprites exported from Aseprite 
**      => https://github.com/AlanFromJapan/gbdk-sprite-exporter
** AlanFromJapan - https://electrogeek.cc
**
*/

#include <gb/gb.h>
#include <gb/drawing.h>

#include "BG-sprites.h"
#include "Map_Screen1.h"



void main() {
    UINT8 X,Y ;
    INT8 dx, dy, SPRITE_FRAME;

    SPRITES_8x8;

    set_sprite_data(0, TILE_COUNT, my_tiles);
    set_bkg_data(0, TILE_COUNT, my_tiles);
    set_bkg_tiles(0, 0, Map_Screen1_WIDTH, Map_Screen1_HEIGHT, Map_Screen1);

    SHOW_BKG;

    //stick to bank 0 for GB DMG compatibility
    VBK_REG = 0;

   

    wait_vbl_done();


    while (1) {
        wait_vbl_done();
    }
}


