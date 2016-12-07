// main.c
// Runs on LM4F120 or TM4C123
// C10_Odd 1's Detector using a FSM Implementation, 
//   Indicates using PF1 (red LED) whether
//   the number of number of button presses on PF4 (Sw1) is odd
// Daniel Valvano, Jonathan Valvano, and Ramesh Yerraballi
// July 21, 2013

// LaunchPad built-in hardware
// SW1 left switch is negative logic PF4 on the Launchpad
// LED connected to PB0 on the Launchpad

#include "SysTick.h"
#include "tm4c123gh6pm.h" // has all the device register declarations

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_AMSEL_R = 0x00;        // 2) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 3) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R &= ~0x10;        // 4) PF4 in
  GPIO_PORTF_AFSEL_R &= ~0x10;      // 5) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R |= 0x10;         // enable pull-up on PF4
  GPIO_PORTF_DEN_R |= 0x10;         // 6) enable digital I/O on PF4
}
void PortB_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000002;     // 1) activate clock for Port B
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog on PB
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PB0
  GPIO_PORTB_DIR_R |= 0x01;         // 5) PB0 is out
  GPIO_PORTB_AFSEL_R &= ~0x01;      // 6) disable alt funct on PB0
  GPIO_PORTB_DEN_R |= 0x01;         // 7) enable digital I/O on PB0
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
	PortB_Init();
	SysTick_Init();
	
  cState = Even; //Initial State
  while (1) {
     //output based on current state
     GPIO_PORTB_DATA_R = Fsm[cState].out; 
		 // wait for time relevant to state
     SysTick_Wait10ms(Fsm[cState].wait);   
     // get input     
     input = (~GPIO_PORTF_DATA_R & 0x10)>>4;  // Input 0/1: Sw1 NotPressed/Pressed
     // change state based on input and current state
     cState = Fsm[cState].next[input]; 

  }
}

