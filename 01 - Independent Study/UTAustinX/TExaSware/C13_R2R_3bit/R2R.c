// R2R.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a single 440Hz sine wave
// Daniel Valvano, Jonathan Valvano
// September 15, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Port B bits 2-0 have the 3-bit DAC
// Port F is onboard LaunchPad switches and LED
// Port F bit 4 is negative logic switch to play sound, SW1
// SysTick ISR: PF3 ISR heartbeat


#include "../tm4c123gh6pm.h"
#include "PLL.h"
#include "Sound.h"
#include "Switch.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
// need to generate a 100 Hz sine wave
// table size is 16, so need 100Hz*16=1.6 kHz interrupt
// bus is 80MHz, so SysTick period is 80000kHz/1.6kHz = 50000
int main(void){ unsigned long i,input,previous;     
  DisableInterrupts();    
  PLL_Init();          // bus clock at 80 MHz
  Switch_Init();       // Port F is onboard switches, LEDs, profiling
  Sound_Init(50000);   // initialize SysTick timer, 100 Hz
// Initial testing, law of superposition
  DAC_Out(1);
  DAC_Out(2);
  DAC_Out(4);
// static testing, single step and record Vout
  for(i=0;i<8;i++){
    DAC_Out(i);
  }
// dynamic testing, push SW1 for sound
  previous = Switch_In()&0x10;
  while(1){ 
    input = Switch_In()&0x10; // bit 4 means SW1 pressed
    if(input&&(previous==0)){ // just pressed     
      EnableInterrupts();
      Sound_Init(50000);      // Play 100 Hz wave
    }
    if(previous&&(input==0)){ // just released     
      DisableInterrupts();    // stop sound
    }
    previous = input; 
    Delay10ms();  // remove switch bounce    
  }  
}



