// EngineControl.c
// Runs on LM4F120/TM4C123
// Use a pointer implementation of a Mealy finite state machine to operate
// an engine with a control input, gas and brake outputs, and two states.
// Daniel Valvano
// September 11, 2013

//  This example accompanies the book
//  "Embedded Systems: Introduction to Arm Cortex M Microcontrollers"
//  ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013
//  Program 6.9
//
//Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
//   You may use, edit, run or distribute this file
//   as long as the above copyright notice remains
//THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
//OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
//MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
//VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
//OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
//For more information about my classes, my research, and my books, see
//http://users.ece.utexas.edu/~valvano/

// control input connected to PA0 (1=go)
// gas output connected to PA1
// brake output connected to PA2

#include "PLL.h"
#include "SysTick.h"

#define INPUT                   (*((volatile unsigned long *)0x40004004))   // port A bit 0
#define OUTPUT                  (*((volatile unsigned long *)0x40004018))   // port A bits 2-1
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOA      0x00000001  // port A Clock Gating Control

// Linked data structure
struct State {
  unsigned long Out[2];
  unsigned long Delay;
  const struct State *Next[2];};
typedef const struct State STyp;
#define Stop  &FSM[0]
#define Go    &FSM[1]
STyp FSM[2]={
 {{2,0},10,{Stop,Go}},
 {{0,1},10,{Stop,Go}}};

int main(void){ volatile unsigned long delay;
  STyp *Pt;  // state pointer
  unsigned long Input;
  PLL_Init();                  // configure for 50 MHz clock
  SysTick_Init();              // initialize SysTick timer
  // activate port A
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
  delay = SYSCTL_RCGC2_R;      // allow time to finish activating
  GPIO_PORTA_DIR_R &= ~0x01;   // make PA0 in
  GPIO_PORTA_DIR_R |= 0x06;    // make PA2-1 out
  GPIO_PORTA_AFSEL_R &= ~0x07; // disable alt func on PA2-0
  GPIO_PORTA_DEN_R |= 0x07;    // enable digital I/O on PA2-0
                               // configure PA2-0 as GPIO
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFF000)+0x00000000;
  GPIO_PORTA_AMSEL_R = 0;      // disable analog functionality on PA
  Pt = Stop;                   // initial state: stopped
  while(1){
    Input = INPUT;             // get new input from Control
    OUTPUT = Pt->Out[Input]<<1;// output to Brake and Gas
    SysTick_Wait10ms(Pt->Delay);// wait 10 ms * current state's Delay value
    Pt = Pt->Next[Input];      // transition to next state
  }
}
