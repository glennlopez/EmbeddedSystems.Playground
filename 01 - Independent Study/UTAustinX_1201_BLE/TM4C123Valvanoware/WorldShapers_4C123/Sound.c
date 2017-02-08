// Sound.c
// Runs on TM4C123 or MSP432 on top of BSP
// Prototypes for basic functions to play sounds 
// Uses 1-bit buzzer on MK-II
// Jonathan Valvano and Daniel Valvano
// October 11, 2016

#include <stdint.h>
#include "Sound.h"
#include "BSP.h"
// ------------Sound_Init------------
// Initialize sound channel
// Input: none
// Output: none
void Sound_Init(void){
  BSP_Buzzer_Init(0); // buzzer used for sound
}

uint32_t soundTime=0;
uint32_t soundDuration=0;
uint16_t soundVolume=256;
void soundTask(void){
  soundTime++;
  if(soundTime > soundDuration){
    BSP_Buzzer_Set(0); // off
    BSP_PeriodicTask_StopC();
  }else{
    BSP_Buzzer_Set(soundVolume*(soundTime&1)); // on/off
  }
}
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
void Sound_PlayTone(uint32_t freq, uint16_t volume, uint32_t duration) {
  soundTime=0;
  if((volume<10)||(volume>256)) return;
  soundVolume = volume;
  soundDuration = (duration*freq)/1000;
  if(soundDuration<2) return; // not possible
  BSP_PeriodicTask_InitC(&soundTask, freq, 6);
}
// Frequency of notes in Hz 
#define E1  1319 
#define D1  1175 
#define DF1 1109
#define C   1047 
#define B   988 
#define BF  932 
#define A   880 
#define AF  831
#define G   784 
#define GF  740 
#define F   699 
#define E   659 
#define EF  622
#define D   587
#define DF  554 
#define C0  523
#define B0  494 
#define BF0 466 
#define A0  440 
#define AF0 415
#define G0  392 
#define GF0 370 
#define F0  350 
#define tempo 240  // quarternotes per minute
// following are durations in ms
#define N16    (15000/tempo)   // 16th note
#define D16    (22500/tempo)   // dotted 16th note
#define N8     (30000/tempo)   // 8th note
#define D8     (45000/tempo)   // dotted 8th note
#define N4     (60000/tempo)   // quarter note
#define D4     (90000/tempo)   // dotted quarter note
#define N2     (120000/tempo)  // half note
#define D2     (180000/tempo)  // dotted half note
#define N1     (240000/tempo)  // whole note
// sound volumes 10 to 256
#define HI     256    // full volume
#define MI      64    // mid volume
#define LO      10    // quiet
const uint32_t *SongFreq;
const uint32_t *SongDuration;
const uint16_t *SongVolume;
uint32_t MaxNote;

uint32_t SongCount;
// runs in timer ISR
void songTask(void){
  soundTime++;
  if(soundTime > soundDuration){
    SongCount++;
    if(SongCount>=MaxNote){
      SongCount=0;
      BSP_Buzzer_Set(0); // off
      BSP_PeriodicTask_StopC();
    }else{
      BSP_PeriodicTask_InitC(&songTask, SongFreq[SongCount], 0);
      soundTime = 0;
      soundDuration = (SongFreq[SongCount]*SongDuration[SongCount])/1000;
    }
  }else{
    BSP_Buzzer_Set(SongVolume[SongCount]*(soundTime&1)); // on/off with volume and freq
  }
}
void PlaySong(const uint32_t *freq,
  const uint32_t *duration, const uint16_t *volume, 
    const uint32_t max) {
  SongFreq = freq;         // array of frequencies
  SongDuration = duration; // array of times
  SongVolume = volume;     // array of volumes
  MaxNote = max;           // size of arrays
  SongCount = 0;
  soundTime=0;
  BSP_PeriodicTask_InitC(&songTask, SongFreq[SongCount], 0);
  soundTime = 0;
  soundDuration = (SongFreq[SongCount]*SongDuration[SongCount])/1000;
}
		
//-------------------------------------------------------

#define EYESMAXNOTE 15
const uint32_t EyesFreq[EYESMAXNOTE]=    {D,     G, D, G, D, G, A, B, G,    C, C, C, G, A, B}; // Eyes of Texas
const uint32_t EyesDuration[EYESMAXNOTE]={D4,D4+N4,N8,N4,N8,N4,N8,D2,D2,D4+N8,N8,N8,D4,D4,N1};
const uint16_t EyesVolume[EYESMAXNOTE]  ={HI,   HI,HI,HI,HI,HI,HI,HI,HI,   HI,LO,HI,HI,HI,HI};

// ------------Sound_EyesOfTexas------------
// Play the song, "Eyes of Texas"
// Input: none
// Output: none
void Sound_EyesOfTexas(void){
  PlaySong(EyesFreq,EyesDuration,EyesVolume,EYESMAXNOTE);
}

// ------------Sound_EyesOfTexasPieces------------
uint32_t static Eyescount=0;
// Play pieces of the Eyes of Texas song, 
// Input: none
// Output: none
void Sound_EyesOfTexasPieces(void){
  if(Eyescount==0){
    PlaySong(&EyesFreq[0],&EyesDuration[0],&EyesVolume[0],2);
    Eyescount++;
  }else if(Eyescount==1){
    PlaySong(&EyesFreq[2],&EyesDuration[2],&EyesVolume[2],7);
    Eyescount++;
  }else if(Eyescount==2){
    PlaySong(&EyesFreq[9],&EyesDuration[9],&EyesVolume[9],3);
    Eyescount++;
  }else{
    PlaySong(&EyesFreq[12],&EyesDuration[12],&EyesVolume[12],3);
    Eyescount=0;
  }
}

//-------------------------------------------------------

// ------------Sound_Shoot------------
// Make a sound for shoot
// Input: none
// Output: none
void Sound_Shoot(void){
  Sound_PlayTone(C,HI,N16);
}

//-------------------------------------------------------

#define KILLEDMAXNOTE 6
const uint32_t KilledFreq[KILLEDMAXNOTE]={F,E,F,E,F,E}; 
const uint32_t KilledDuration[KILLEDMAXNOTE]={N16,N16,N16,N16,N16,N16};
const uint16_t KilledVolume[KILLEDMAXNOTE]={HI,MI,HI,MI,HI,MI};
// ------------Sound_Killed------------
// Make a sound for killed
// Input: none
// Output: none
void Sound_Killed(void){
  PlaySong(KilledFreq,KilledDuration,KilledVolume,KILLEDMAXNOTE);
}

//-------------------------------------------------------

#define ROCKETMAXNOTE 6
const uint32_t RocketFreq[ROCKETMAXNOTE]={E,C,G,E,C,G}; 
const uint32_t RocketDuration[ROCKETMAXNOTE]={N16,N16,N8,N16,N16,N8};
const uint16_t RocketVolume[ROCKETMAXNOTE]={HI,HI,MI,HI,HI,MI};
// ------------Sound_MissileRocket------------
// Make a sound for the missile
// Input: none
// Output: none
void Sound_MissileRocket(void){
  PlaySong(RocketFreq,RocketDuration,RocketVolume,ROCKETMAXNOTE);
}

//-------------------------------------------------------

#define EXPLOSIONMAXNOTE 3
const uint32_t ExplosionFreq[EXPLOSIONMAXNOTE]={A,B,A}; 
const uint32_t ExplosionDuration[EXPLOSIONMAXNOTE]={N16,N16,N16};
const uint16_t ExplosionVolume[EXPLOSIONMAXNOTE]={MI,HI,MI};
// ------------Sound_Explosion------------
// Make a sound for explosion
// Input: none
// Output: none
void Sound_Explosion(void){
  PlaySong(ExplosionFreq,ExplosionDuration,ExplosionVolume,EXPLOSIONMAXNOTE);
}

//-------------------------------------------------------
#define LOWPITCHMAXNOTE 6
const uint32_t LowpitchFreq[LOWPITCHMAXNOTE]={C0,DF,C0,DF,C0,DF}; 
const uint32_t LowpitchDuration[LOWPITCHMAXNOTE]={N8,N16,D8,N16,N8,N16};
const uint16_t LowpitchVolume[LOWPITCHMAXNOTE]={MI,MI,MI,MI,MI,MI};
// ------------Sound_Lowpitch------------
// Make a low-pitched sound 
// Input: none
// Output: none
void Sound_Lowpitch(void){
  PlaySong(LowpitchFreq,LowpitchDuration,LowpitchVolume,LOWPITCHMAXNOTE);
}
