#ifndef __TRANSITION_H__
#define  __TRANSITION_H__


#include <gb/gb.h>

void arenaTransition(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY);
void arenaTransitionBackToLevel1(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY);
void arenaReset(UINT8** nextArena, UINT8* backgroundTile, UINT8* startX, UINT8* startY);
inline UINT8 getCurrentArenaId();
/**
 * Shows title screen
 * 
 */
inline void showTitle();

#endif // __TRANSITION_H__