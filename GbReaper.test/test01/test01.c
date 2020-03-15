#include <gb/gb.h>
#include <gb/drawing.h>
#include <rand.h>

#include "my_lib01.c"
#include "Map_01.c"

void main() 
{  
  SPRITES_8x8;

  set_sprite_data(0, my_lib01_COUNT, my_lib01);
  set_bkg_data(0, my_lib01_COUNT, my_lib01);
  set_bkg_tiles(0, 0, Map_01_WIDTH, Map_01_HEIGHT, Map_01);

  SHOW_BKG;
  SHOW_SPRITES;

  wait_vbl_done();
  //resetGame();

  while (1) {
    wait_vbl_done();
    //vFrameCount++;

  }
}
