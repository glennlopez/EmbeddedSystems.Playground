#include "SysTick.h"			// systick
#include "tm4c123gh6pm.h" // has all the device register declarations

//prototypes
void PortF_Init(void);

// struct
struct state{
	unsigned char out;
	unsigned long wait;
	unsigned char next[2];
};

//typedef const struct
typedef const struct state sType;


//define shortcuts to refer to the various states in the FSM array
#define EVEN 0
#define ODD 1


//The data structure that captures the FSM state transition graph
sType FSM[2] = {
	{0, 10, {EVEN,ODD}},
	{1, 10, {ODD,EVEN}}
};


//Current state is Even/Odd
int cState = EVEN;

int main(void) {
	
  PortF_Init();
	SysTick_Init();
	
	//Initial State
  while (1) {
		
     //output based on current state

		
		 // wait for time relevant to state

		
     // get input     

		
     // change state based on input and current state


  }
}






/******************
FUNCTIONS
*******************/
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



