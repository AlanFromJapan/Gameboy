#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <gb/gb.h>

#define DynMap_MAX_WIDTH   32
#define DynMap_MAX_HEIGHT  32


extern UINT8 dynmapW;
extern UINT8 dynmapH;
extern unsigned char dynmap[];


/**
 * Writes a string on the background at (x.y) in Tiles.
 * Works only with the dynamic background.
 *
 */
void writetext (UINT8 px, UINT8 py, char* msg);

#endif //__GRAPHICS_H__
