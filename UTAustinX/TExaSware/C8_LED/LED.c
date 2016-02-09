// LED.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize a GPIO pin and turn it on and off.
// Daniel Valvano
// September 12, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2014
   Volume 1 Program 4.3, Figure 4.14

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

// positive logic LED connected to PA2

#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define PA2                     (*((volatile unsigned long *)0x40004010))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

// Make PA2 an output, enable digital I/O, ensure alt. functions off
void LED_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x01;           // 1) activate clock for Port A
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
                                    // 2) no need to unlock PA2
  GPIO_PORTA_PCTL_R &= ~0x00000F00; // 3) regular GPIO
  GPIO_PORTA_AMSEL_R &= ~0x04;      // 4) disable analog function on PA2
  GPIO_PORTA_DIR_R |= 0x04;         // 5) set direction to output
  GPIO_PORTA_AFSEL_R &= ~0x04;      // 6) regular port function
  GPIO_PORTA_DEN_R |= 0x04;         // 7) enable digital port
}

// Make PA2 high
void LED_On(void){
  GPIO_PORTA_DATA_R |= 0x04;
}
// Make PA2 low
void LED_Off(void){
  GPIO_PORTA_DATA_R &= ~0x04;
}

//debug code

int main(void){
  LED_Init();               // initialize PA2 and make it output
  while(1){
    LED_On();
    LED_Off();
  }
}
