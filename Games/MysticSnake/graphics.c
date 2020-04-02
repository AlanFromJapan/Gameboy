#include "graphics.h"
#include "my_lib01.h"
#include "inputs.h"

/**
 *  THE dynamic map to use and reuse
 */
unsigned char dynmap[DynMap_MAX_WIDTH * DynMap_MAX_HEIGHT];
//The CURRENT size of the dynamic map (showable space if you want)
UINT8 dynmapW = DynMap_MAX_WIDTH;
UINT8 dynmapH = DynMap_MAX_HEIGHT;

/**
 * The shift of the background compared to origin (top left = 0,0)
 */
unsigned int bgx = 0;
unsigned int bgy = 0;



/**
 * Writes a string on the background at (x.y) in Tiles.
 * Works only with the dynamic background.
 * Accepts [a-zA-Z.,?!]
 */
void writetextBG (UINT8 px, UINT8 py, char* msg){

    for (UINT8 i =0; msg[i] != 0; i++){
        UINT8 c = msg[i];
        UINT16 pos = px + py * DynMap_MAX_HEIGHT;

        if (c >='a' && c <= 'z'){
            dynmap[pos] = (UINT8)c - (UINT8)'A' - ('a' - 'A') + (UINT8)TILE_LETTER_1;
        }
        else {
            if (c >='1' && c <= '9'){ //zero is special below
                dynmap[pos] = (UINT8)c - (UINT8)'1' + (UINT8)TILE_NUMBER_2; //2 is '1' in fact ... don't ask
            }
            else {
                if (c >='A' && c <= 'Z'){
                    dynmap[pos] = (UINT8)c - (UINT8)'A' + (UINT8)TILE_LETTER_1;
                }
                else {
                    switch(c){
                        case ' ':
                            dynmap[pos] = TILE_EMPTY;
                            break;
                        case '.':
                            dynmap[pos] = TILE_LETTER_DOT;
                            break;
                        case '?':
                            dynmap[pos] = TILE_LETTER_QUESTION;
                            break;
                        case '!':
                            dynmap[pos] = TILE_LETTER_EXCL;
                            break;
                        case '0':
                            dynmap[pos] = TILE_LETTER_15; //capital O is the zero
                            break;
                    }
                }
            }
        }

        px++;
        //Trick is here since the showable map is SMALLER than the full map, this allows proper line wrap.
        if (px >= dynmapW){
            px = 0;
            py ++;
        }
    }

}

/**
 * Fills the Dynmap with the parameter tile 
 */
void clearDynmap(UINT8 tile){
    for (UINT16 i = 0; i < DynMap_MAX_WIDTH * DynMap_MAX_HEIGHT; i++)
        dynmap[i] = tile;
}