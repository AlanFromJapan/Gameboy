#ifndef __GAME_H__
#define __GAME_H__

#include <gb/gb.h>
#include "my_lib01.h"

#define ITEMS_PER_LEVEL     10
extern UINT8 currentItemNumber ;

#define HEART_DEFAULT   3
#define HEART_MAX   5
extern UINT8 heartsCount ;

extern UINT8 backgroundTile ;
extern UINT8* currentArenaMap ;

extern UINT16 score;


#define SPEED_START 250
#define SPEED_MIN   60
extern UINT8 speed;

/**
 * Set a background tile to the tile in parameter
 */
void putTile(UINT8 tile, UINT8 x, UINT8 y);

/**
 * Puts a bonbon somewhere on the map randomly
 */
void drop_bonbon();


/**
 * Update the hearts display
 */
void updateHearts();

/**
 * Update the score display
 */
void updateScore();


#endif //__GAME_H__
