// SysTickInts.c
// Runs on TM4C123
// Use the SysTick timer to request interrupts at 10 Hz.
// Daniel Valvano
// February 9, 2016

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016

   Program 5.12, section 5.7

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
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

// oscilloscope or logic analyzer to profile the system
// J3.27/PE1 Profile 0
// J3.28/PE2 Profile 1
#include <stdint.h>
#include "CortexM.h"
#include "Profile.h"

// **************SysTick_Init*********************
// Initialize SysTick periodic interrupts
// Input: interrupt period
//        Units of period are 62.5ns (assuming 16 MHz clock)
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR
// Output: none
volatile uint32_t Counts = 0;
void SysTick_Init(uint32_t period){
  Profile_Init();
  Counts = 0;
  STCTRL = 0;         // disable SysTick during setup
  STRELOAD = period-1;// reload value
  STCURRENT = 0;      // any write to current clears it
  SYSPRI3 = (SYSPRI3&0x00FFFFFF)|0x40000000; // priority 2         
  STCTRL = 0x07;      // enable, core clock, interrupts
}
// Interrupt service routine
// Executed every 62.5ns*(period)
void SysTick_Handler(void){
  Profile_Toggle0();          // toggle bit
  Profile_Toggle0();          // toggle bit
  Counts = Counts + 1;
  Profile_Toggle0();          // toggle bit
}

int main(void){// bus clock at 16 MHz
  SysTick_Init(1600000);      // initialize SysTick timer
  EnableInterrupts();
  while(1){                   // interrupts every 100ms, 5 Hz flash
    Profile_Toggle1();        // toggle bit
  }
}
