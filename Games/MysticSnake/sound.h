#ifndef __SOUND_H__
#define __SOUND_H__

#include <gb/gb.h>

//Hero receive damages
extern const UINT8 SOUND_HURT[];
//Hero inflict damages
extern const UINT8 SOUND_HIT[];


//Call once to init sound generation
void initSound();

//Plays a sound 
void playSound(const UINT8* snd);

#endif //__SOUND_H__