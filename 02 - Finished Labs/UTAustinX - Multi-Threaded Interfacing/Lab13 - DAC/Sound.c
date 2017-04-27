#include "Sound.h"
#include "DAC.h"

unsigned char index = 0;
const unsigned char SineWave[48] = {
     0,0,1,1,1,2,2,3,4,5,6,7,8,9,10,11,12,13,13,14,14,14,15,15,
     15,15,14,14,14,13,13,12,11,10,9,8,7,6,5,4,3,2,2,1,1,1,0,0
};

/************************
 * Sound_Init
 ************************/
// Input: none
// Output: none
void Sound_Init(void){

    DAC_Init(); //initialize the DAC

    NVIC_ST_CTRL_R = 0;
    NVIC_ST_CURRENT_R = 0;

    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000;
    NVIC_ST_CTRL_R = 0x07;

}


/************************
 * Sound_Tone
 ************************/
// Input: interrupt period
//   Units of period are 12.5ns
//   Maximum is 2^24-1
//   Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
// this routine sets the RELOAD and starts SysTick
    NVIC_ST_RELOAD_R = period;
}


/************************
 * Sound_Off - NOT IN USE
 ************************/
// stop outputing to DAC
// Output: none
void Sound_Off(void){
// this routine stops the sound output
}


/************************
 * SysTick_Handler
 ************************/
// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
	
    if(index < 49){
        index++;
        if(index == 48){
            index = 0;
        }
    }

    DAC_Out(SineWave[index]);
}
