#ifndef __TRANSITION_H__
#define  __TRANSITION_H__


#include <gb/gb.h>

#define TITLEMENU_PLAY      0
#define TITLEMENU_OPTIONS   1
#define TITLEMENU_CREDITS   2

#define OPTIONSMENU_NORMAL  0
#define OPTIONSMENU_HARD    1


void arenaTransition(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY);
void arenaTransitionBackToLevel1(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY);
void arenaReset(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY);
inline UINT8 getCurrentArenaId();
/**
 * Shows title screen
 * 
 */
UINT8 showTitle();
/**
 * Shows credits screen
 * 
 */
void showCredits();
/**
 * Shows options screen
 * 
 */
UINT8 showOptions();

#endif // __TRANSITION_H__