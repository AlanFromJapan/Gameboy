#include "sound.h"

//First value is the channel number, then is the registers
const UINT8 SOUND_HURT[] =      {4, 0x3a, 0xa1, 0x52, 0xc0};
const UINT8 SOUND_HIT[] =       {1, 0x29, 0x83, 0x51, 0x5b, 0x86};
const UINT8 SOUND_HIT2[] =      {1, 0x4a, 0x41, 0x45, 0xba, 0x86};


//Call once to init sound generation
void initSound(){
    //Thanks to https://laroldsjubilantjunkyard.com/tutorials/how-to-make-a-gameboy-game/sounds-and-audio/

    // This enables Sound
    // these registers must be in this specific order!
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels

}



//Plays a sound 
void playSound(const UINT8* snd){
    switch (snd[0]){
        case 1:
            //channel 1
            NR10_REG=snd[1];
            NR11_REG=snd[2];
            NR12_REG=snd[3];
            NR13_REG=snd[4];
            NR14_REG=snd[5];        
            break;
        case 4:
            //channel 4: noise generator
            NR41_REG=snd[1];
            NR42_REG=snd[2];
            NR43_REG=snd[3];
            NR44_REG=snd[4];
            break;
    }
}