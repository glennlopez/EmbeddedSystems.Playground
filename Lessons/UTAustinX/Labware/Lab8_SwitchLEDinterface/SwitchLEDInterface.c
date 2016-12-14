// ***** 0. Documentation Section *****
//Lab8 - glennlopez@gmail.com

/* H A R D W A R E 
 * 1x switch
 * 1x 10k resistor
 * 1x LED
 * 1x 470 resistor
 */
 
/* S Y S T E M 
 * Input: PE0 (switch)
 * Output: PE1 (LED)
 * Delay: 100ms
 * Start: LED on, Blink when switch is pressed
 * De-bounce: 5ms
 */

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
//#include "tm4c123gh6pm.h" //<-- disabled this so I can define my own stuff

// Common port registers 
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108)) //offset:	0x108		- *Register 136: Clock gating control register


//PortE base address (APB): 0x4002.4000
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400243FC)) //offset: 0x3FC 	- enabled pins for data I/O (4*2^b)
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40024400)) //offset: 0x400		- 1 is output, 0 is input
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40024420)) //offset:	0x420		- 1 enabled, 0 disabled
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40024510)) //offset:	0x510		- 1 pullup enabled, 0 disabled
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002451C)) //offset:	0x51C		- 1 enabled, 0 disabled
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40024520)) //offset:	0x520		- 0x4C4F434B unlocks GPIO commit register
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40024524)) //offset:	0x524		- 1 writeable, 0 cannot be written
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40024528)) //offset:	0x528		- 1 enabled, 0 disabled
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C)) //offset:	0x52C		- 0x00000000 resets 



// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void PortE_Init(void);				// Initialize PortE





// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor

int main(void){ 
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz
  
	
  EnableInterrupts();           // enable interrupts for the grader
  while(1){
    
  }
  
}

/*
 * Subroutine to initialize port E pins for input and output
 * PF4 is input SW1 and PF3-1 is output LEDs
 * Inputs: None
 * Outputs: None
 * Notes: ...
 */
void PortE_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R 							|= 		0x00000010;      			// 1) F clock gate enbale
  delay 											 = 		SYSCTL_RCGC2_R;      	// delay to allow clock to stabilize     
  GPIO_PORTF_AMSEL_R 					&= 		0x00;        					// 2) disable analog function
  GPIO_PORTF_PCTL_R 					&= 		0x00000000;   				// 3) GPIO clear bit PCTL  
  //GPIO_PORTF_DIR_R 						&= 		~0x10;         				// 4.1) PF4 input,
  //GPIO_PORTF_DIR_R 						|= 		0x0E;          				// 4.2) PF3,2,1 output  
  //GPIO_PORTF_AFSEL_R 					&= 		0x00;        					// 5) no alternate function
  //GPIO_PORTF_PUR_R 						|= 		0x10;          				// 6) enable pullup resistor on PF4       
  //GPIO_PORTF_DEN_R 						|= 		0x1E;          				// 7) enable digital pins PF4-PF1
}
