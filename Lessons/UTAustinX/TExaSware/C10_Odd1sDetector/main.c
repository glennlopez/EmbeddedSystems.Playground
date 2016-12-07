// main.c
// Runs on LM4F120 or TM4C123
// C10_Odd 1's Detector using a FSM Implementation, 
//   Indicates using PF2 (Blue LED) whether
//   the number of number of button presses on PF4 (Sw1) is odd
// Daniel Valvano, Jonathan Valvano, and Ramesh Yerraballi
// July 21, 2013

// LaunchPad built-in hardware
// SW1 left switch is negative logic PF4 on the Launchpad
// LED connected to PF2 (Blue) on the Launchpad

#include "SysTick.h"
#include "tm4c123gh6pm.h" // has all the device register declarations

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // Activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // Allow time for clock to start
  GPIO_PORTF_AMSEL_R = 0x00;        // Disable analog on PF4 and PF2
  GPIO_PORTF_PCTL_R = 0x00000000;   // PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R &= ~0x10;        //   PF4 input
	GPIO_PORTF_DIR_R |= 0x04;         //   PF2 output
  GPIO_PORTF_AFSEL_R &= ~0x14;      // Disable alt funct on PF4 and PF2
  GPIO_PORTF_PUR_R |= 0x10;         // Enable pull-up on PF4
  GPIO_PORTF_DEN_R |= 0x14;         // Enable digital I/O on PF4 and PF2
}

// represents a State of the FSM 
struct State {
   unsigned char out;   // output for the state
   unsigned short wait;     // Time to wait when in this state
   unsigned char next[2]; // Next state array
};

typedef const struct State StateType;

//Shortcuts to refer to the various states in the FSM array
#define Even 0
#define Odd 1

//The data structure that captures the FSM state transition graph
StateType Fsm[2] = { 
   {0, 100, {Even,Odd}},
   {1, 100, {Odd,Even}}
}; 

unsigned char cState; //Current state is Even/Odd

int main(void) {
  unsigned char input;
	
  PortF_Init();
	SysTick_Init();
	
  cState = Even; //Initial State
  while (1) {
     //output based on current state
     GPIO_PORTF_DATA_R = Fsm[cState].out<<2; //Output to PF2
		 // wait for time relevant to state
     SysTick_Wait10ms(Fsm[cState].wait);   
     // get input     
     input = (~GPIO_PORTF_DATA_R & 0x10)>>4;// Input 0/1: Sw1 NotPressed/Pressed
     // change state based on input and current state
     cState = Fsm[cState].next[input]; 

  }
}

