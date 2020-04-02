#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <gb/gb.h>

#define DynMap_MAX_WIDTH   32
#define DynMap_MAX_HEIGHT  32


extern unsigned int bgx ;
extern unsigned int bgy ;

extern UINT8 dynmapW;
extern UINT8 dynmapH;
extern unsigned char dynmap[];


#define DYNMAP_PUT_TILE(T,X,Y) dynmap[(Y) * dynmapW + (X)] = T;

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
