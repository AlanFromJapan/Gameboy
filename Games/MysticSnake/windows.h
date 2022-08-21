#ifndef __WINDOWS_H__
#define __WINDOWS_H__


#include <gb/gb.h>

void windowShowText(char* msg, UINT8 timeoutSec);

/**
 * Shows the HUD
 */
void showHUD();

/**
 * Updates the info displayed on the HUD (hearts, points, ...)
 */
void updateHUD();

#endif
