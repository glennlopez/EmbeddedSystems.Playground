// BranchingFunctionsDelays.c Lab 6
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to 
// toggle an LED while a button is pressed and 
// turn the LED on when the button is released.  
// This lab will use the hardware already built into the LaunchPad.
// Daniel Valvano, Jonathan Valvano
// January 15, 2016

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

#include "TExaS.h"

// GPIO Address definitions																										PortF(APB): 0x40025000
//APB: Advanced Peripheral Bus (has backwards compatability)
//AHB: Advanced High-performance Bus (is faster)
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))			//0x3FC means 0011 1111 expressed as 4*2^b (bitspecific addressing)
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))			//gpio direction 					- offset 0x400
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))			//gpio alternte funtion 	- offset 0x420
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))			//gpio pull-up select			- offset 0x510
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))			//gpio digital enable 		- offset 0x51C
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))			//gpio analog mode select	- offset 0x528
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))			//gpio port control				- offset 0x52C
	
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))			
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

// PortF Bit-specific Address definitions (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
#define LED_BLUE								(*((volatile unsigned long *)0x40025010))			//PF2
#define LED_RED									(*((volatile unsigned long *)0x40025008))			//PF1
#define LED_GREEN								(*((volatile unsigned long *)0x40025020))			//PF3
#define SW1											(*((volatile unsigned long *)0x40025040))			//PF4
#define SW2											(*((volatile unsigned long *)0x40025004))			//PF0

// WARNING: to be used only with single bit-specific address
#define OFF 										0x00
#define ON											0x2F

// basic functions defined at end of startup.s
void DisableInterrupts(void); 	// Disable interrupts
void EnableInterrupts(void);  	// Enable interrupts
int initPortF(void);						// PortF prototype




int main(void){ unsigned long volatile delay;
	
	TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);  
	SYSCTL_RCGC2_R					|=		SYSCTL_RCGC2_GPIOF;
	delay = SYSCTL_RCGC2_R;
	
  EnableInterrupts();         // enable interrupts for the grader
	initPortF();								// configure portf
	
  while(1){										// body goes here
		if(SW1 == (SW1&ON)){
			LED_BLUE = ON;
		}
		else{
			LED_BLUE = OFF;
		}
	}
}





//FUNCTIONS
int initPortF(void){				//GPIO PortF(APB): 0x 4002.5000
	
		// Configure PortF pins
		GPIO_PORTF_AMSEL_R			=		0x00;		// _ _ _ 0  0 0 0 0	(Not using analog mode select)
		GPIO_PORTF_PCTL_R				=		0x00;		// _ _ _ 0  0 0 0 0 (Not using alternative functions)
		GPIO_PORTF_DATA_R 			= 	0x00;		// _ _ _ _  _ _ _ _ (Initialize to 0x00)
		GPIO_PORTF_DIR_R 				= 	0x0E;		// _ _ _ 0  1 1 1 0 (PF0 and PF4 are input switches)
		GPIO_PORTF_AFSEL_R			=		0x00;		// _ _ _ 0  0 0 0 0 (Not using alternative functions)
		GPIO_PORTF_PUR_R				=		0x11;		// _ _ _ 1  0 0 0 1 (Enable pull-up resistors on P0 and P4 switches)
		GPIO_PORTF_DEN_R				=		0x1F; 	// _ _ _ 1  1 1 1 1	(Enable digital signal for all target pins)
	
	return 0;
	}