#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <gb/gb.h>

//A GB screen shows only 20 tiles in width
#define SCREEN_TILES_WIDTH 20
//A GB screen shows only 18 tiles in height
#define SCREEN_TILES_HEIGHT 18


//Dynamic map maximum Width IN TILES
#define DynMap_MAX_WIDTH   32
//Dynamic map maximum height IN TILES
#define DynMap_MAX_HEIGHT  32 


extern signed int bgx ;
extern signed int bgy ;

extern UINT8 dynmapW;
extern UINT8 dynmapH;
extern unsigned char dynmap[];


#define DYNMAP_PUT_TILE(T,X,Y)  dynmap[(Y) * dynmapW + (X)] = T;
#define DYNMAP_GET_TILE(X,Y)    dynmap[(Y) * dynmapW + (X)]

#define MAP2SCREEN_X(mapx)     (mapx - bgx)
#define MAP2SCREEN_Y(mapy)     (mapy - bgy)
#define SCREEN2MAP_X(screenx)  (screenx + bgx)
#define SCREEN2MAP_Y(screeny)  (screeny + bgy)


/**
 * Fill in the tiles array with the tile representation of the text.
 * YOU MUST INIT THE ARRAY AND FREE IT BEFORE.
 */
void string2tile(char* msg, UINT8* tiles);

/**
 * Writes a string on the background at (x.y) in Tiles.
 * Works only with the dynamic background.
 *
 */
void writetextBG (UINT8 px, UINT8 py, char* msg);

/**
 * Fills the Dynmap with the parameter tile 
 */
void clearDynmap(UINT8 tile);

#endif //__GRAPHICS_H__
