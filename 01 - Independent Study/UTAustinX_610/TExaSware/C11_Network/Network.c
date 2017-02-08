// Network.c
// Runs on LM4F120
// This test file demonstrates the UART.  Download this
// program to two different Launch Pads and connect their
// UART1s and grounds together.  Connect PC4 of the first
// board to PC5 of the second board and PC4 of the second
// board to PC5 of the first board.  Connect the grounds
// together.  When powered, both multi-colored LEDs will
// come on.  Press SW1 to cycle through the color wheel.
// Press SW2 to send the current color to the other board.
// Daniel Valvano
// August 1, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
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

// U1Rx (PC4) connected to U1Tx (PC5) of other microcontroller
// U1Tx (PC5) connected to U1Rx (PC4) of other microcontroller
// Ground connected ground of other microcontroller

// SW2 (send color) connected to PF0
// Red LED connected to PF1
// Blue LED connected to PF2
// Green LED connected to PF3
// SW1 (step color) connected to PF4

#include "PLL.h"
#include "SysTick.h"
#include "UART.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x20;         // 1) activate Port F
  delay = SYSCTL_RCGC2_R;         // allow time for clock to stabilize
  GPIO_PORTF_LOCK_R = 0x4C4F434B; // 2) unlock Port F lock
  GPIO_PORTF_CR_R = 0x1F;         //    enable commit (allow configuration changes) on PF4-0
  GPIO_PORTF_AMSEL_R = 0x00;      // 3) disable analog functionality on PF4-0
  GPIO_PORTF_PCTL_R = 0x00000000; // 4) configure PF4-0 as GPIO
  GPIO_PORTF_DIR_R = 0x0E;        // 5) PF4 and PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;      // 6) disable alt funct on PF4-0
  GPIO_PORTF_DEN_R = 0x1F;        // 7) enable digital I/O on PF4-0
  GPIO_PORTF_PUR_R = 0x11;        //    enable pull-up on PF4 and PF0
}

//  red, yellow, green, light blue, blue, purple,  white,  dark
const long ColorWheel[8] = {0x02,0x0A,0x08,0x0C,0x04,0x06,0x0E,0x00};
int main(void){ unsigned long SW1,SW2;
  long prevSW1 = 0;        // previous value of SW1
  long prevSW2 = 0;        // previous value of SW2
  unsigned char inColor;   // color value from other microcontroller
  unsigned char color = 0; // this microcontroller's color value
  PLL_Init();              // set system clock to 80 MHz
  SysTick_Init();          // initialize SysTick
  UART_Init();             // initialize UART
  PortF_Init();            // initialize buttons and LEDs on Port F
  while(1){
    SW1 = GPIO_PORTF_DATA_R&0x10; // Read SW1
    if((SW1 == 0) && prevSW1){    // falling of SW1?
      color = (color+1)&0x07;     // step to next color 
    }
    prevSW1 = SW1; // current value of SW1 
    SW2 = GPIO_PORTF_DATA_R&0x01; // Read SW2
    if((SW2 == 0) && prevSW2){    // falling of SW2?
      UART_OutChar(color+0x30);   // send color as '0' - '7'
    }
    prevSW2 = SW2; // current value of SW2 
    inColor = UART_InCharNonBlocking();
    if(inColor){ // new data have come in from the UART??
      color = inColor&0x07;     // update this computer's color
    }
    GPIO_PORTF_DATA_R = ColorWheel[color];  // update LEDs
    SysTick_Wait10ms(2);        // debounce switch
  }
}

