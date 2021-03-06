#ifndef __GAME_H__
#define __GAME_H__

#include <gb/gb.h>
#include "my_lib01.h"

#define DIFFICULTY_NORMAL   0
#define DIFFICULTY_HARD     1
extern UINT8 gameDifficulty; 

#define ITEMS_PER_LEVEL_NORMAL      10
#define ITEMS_PER_LEVEL_HARD        15
extern UINT8 maxItemNumber ;
extern UINT8 currentItemNumber ;

#define HEART_DEFAULT   3
#define HEART_MAX   5
extern UINT8 heartsCount ;

extern UINT8 backgroundTile ;
extern UINT8* currentArenaMap ;

extern UINT16 score;


#define SPEED_START_NORMAL  250
#define SPEED_START_HARD    200
#define SPEED_MIN   40
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
 * Puts a heart somewhere on the map randomly
 */
void drop_heart();

/**
 * Remove all items from the map (except bonbon)
 */
void clearExtraItems();

/**
 * Update the hearts display
 */
void updateHearts();

/**
 * Update the score display
 */
void updateScore();

/**
 * Shows Pause screen
 */
void showPause();

/**
 * Draws the "Level xx" label
 * 
 * Should have been drawned in the map, or calculated once and kept in mem, so let's say it's a tradeoff space vx complexity
 */
inline void drawLevelLabel();


/**
 * Turns the game in HARD MODE
 */
inline void setHardMode();

#endif //__GAME_H__
