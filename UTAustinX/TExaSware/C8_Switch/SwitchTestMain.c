// SwitchTestMain.c
// Runs on LM4F120/TM4C123
// Test the switch initialization functions by setting the LED
// color according to the status of the switches.
// Daniel and Jonathan Valvano
// September 12, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013
   Example 2.3, Program 2.9, Figure 2.36

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

// negative logic switches connected to PF0 and PF4 on the Launchpad
// red LED connected to PF1 on the Launchpad
// blue LED connected to PF2 on the Launchpad
// green LED connected to PF3 on the Launchpad
// NOTE: The NMI (non-maskable interrupt) is on PF0.  That means that
// the Alternate Function Select, Pull-Up Resistor, Pull-Down Resistor,
// and Digital Enable are all locked for PF0 until a value of 0x4C4F434B
// is written to the Port F GPIO Lock Register.  After Port F is
// unlocked, bit 0 of the Port F GPIO Commit Register must be set to
// allow access to PF0's control registers.  On the LM4F120, the other
// bits of the Port F GPIO Commit Register are hard-wired to 1, meaning
// that the rest of Port F can always be freely re-configured at any
// time.  Requiring this procedure makes it unlikely to accidentally
// re-configure the JTAG pins as GPIO, which can lock the debugger out
// of the processor and make it permanently unable to be debugged or
// re-programmed.

#include "Switch.h"

#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define PF0       (*((volatile unsigned long *)0x40025004))
#define PF1       (*((volatile unsigned long *)0x40025008))
#define PF2       (*((volatile unsigned long *)0x40025010))
#define PF3       (*((volatile unsigned long *)0x40025020))
#define PF4       (*((volatile unsigned long *)0x40025040))
#define LEDS      (*((volatile unsigned long *)0x40025038))
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08
#define SWITCHES  (*((volatile unsigned long *)0x40025044))
#define SW1       0x10                      // on the left side of the Launchpad board
#define SW2       0x01                      // on the right side of the Launchpad board
int main(void){ unsigned long status;
  Switch_Init();           // PA5 is input
  status = Switch_Input(); // 0x00 or 0x20
  status = Switch_Input(); // 0x00 or 0x20
  
  Board_Init();             // initialize PF0 and PF4 and make them inputs
                            // make PF3-1 out (PF3-1 built-in LEDs)
  GPIO_PORTF_DIR_R |= (RED|BLUE|GREEN);
                              // disable alt funct on PF3-1
  GPIO_PORTF_AFSEL_R &= ~(RED|BLUE|GREEN);
                              // enable digital I/O on PF3-1
  GPIO_PORTF_DEN_R |= (RED|BLUE|GREEN);
                              // configure PF3-1 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFF000F)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;     // disable analog functionality on PF
  while(1){
    status = Board_Input();
    switch(status){                    // switches are negative logic on PF0 and PF4
      case 0x01: LEDS = BLUE; break;   // SW1 pressed
      case 0x10: LEDS = RED; break;    // SW2 pressed
      case 0x00: LEDS = GREEN; break;  // both switches pressed
      case 0x11: LEDS = 0; break;      // neither switch pressed
      default: LEDS = (RED|GREEN|BLUE);// unexpected return value
    }
  }
}
