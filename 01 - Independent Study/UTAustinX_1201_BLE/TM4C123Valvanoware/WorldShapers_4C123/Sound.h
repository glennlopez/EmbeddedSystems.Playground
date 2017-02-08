// Sound.h
// Runs on TM4C123 or MSP432 on top of BSP
// Prototypes for basic functions to play sounds 
// Uses 1-bit buzzer on MK-II
// Jonathan Valvano and Daniel Valvano
// October 8, 2016

// ------------Sound_Init------------
// Initialize sound channel
// Input: none
// Output: none
void Sound_Init(void);

// ------------Sound_Shoot------------
// Make a sound for shoot
// Input: none
// Output: none
void Sound_Shoot(void);

// ------------Sound_Killed------------
// Make a sound for killed
// Input: none
// Output: none
void Sound_Killed(void);

// ------------Sound_Explosion------------
// Make a sound for explosion
// Input: none
// Output: none
void Sound_Explosion(void);
// ------------Sound_EyesOfTexas------------
// Play the song, "Eyes of Texas"
// Input: none
// Output: none
void Sound_EyesOfTexas(void);

// ------------Sound_EyesOfTexasPieces------------
// Play pieces of the Eyes of Texas song, 
// Input: none
// Output: none
void Sound_EyesOfTexasPieces(void);

// ------------Sound_Lowpitch------------
// Make a low-pitched sound 
// Input: none
// Output: none
void Sound_Lowpitch(void);

// ------------Sound_MissileRocket------------
// Make a sound for the missile
// Input: none
// Output: none
void Sound_MissileRocket(void);

// ------------Sound_PlayTone------------
// Generate sound at one frequency by oscillating the buzzer
// This function starts the sound and returns right away
// Input: freq of toggling in Hz (tone will be at 0.5*freq)
//        duration in ms
//        volume 10 to 256
// Output: none
// ISR will interrupt at freq Hz, priority 6
// ISR will toggle the buzzer on/off
// ISR will occur (duration*freq/1000) times
// No sound if (duration*freq)<2000 (must toggle at least twice)
void Sound_PlayTone(uint32_t freq, uint16_t volume, uint32_t duration);
