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
#include "tm4c123gh6pm.h" //contains defines for register memory


// ***** 2. Global Declarations Section *****
// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

/*
//FIXME: edit this stuff
void PortE_Init(void){ volatile unsigned long delay;
  //SYSCTL_RCGC2_R 							|= 		0x00000010;      			// 1) F clock gate enbale
  //delay 											 = 		SYSCTL_RCGC2_R;      	// delay to allow clock to stabilize     
  //GPIO_PORTF_AMSEL_R 					&= 		0x00;        					// 2) disable analog function
  //GPIO_PORTF_PCTL_R 					&= 		0x00000000;   				// 3) GPIO clear bit PCTL  
  //GPIO_PORTF_DIR_R 						&= 		~0x10;         				// 4.1) PF4 input,
  //GPIO_PORTF_DIR_R 						|= 		0x0E;          				// 4.2) PF3,2,1 output  
  //GPIO_PORTF_AFSEL_R 					&= 		0x00;        					// 5) no alternate function
  //GPIO_PORTF_PUR_R 						|= 		0x10;          				// 6) enable pullup resistor on PF4       
  //GPIO_PORTF_DEN_R 						|= 		0x1E;          				// 7) enable digital pins PF4-PF1
}

*/


// SWITCH DRIVER(PE0): includes initialization and functions accociated with switch hardware
#define PE0	(*((volatile unsigned long *)0x40024004))		//Bit specific addressing - base(port a): 0x40024000 / offset(pin 5):0x004
void Switch_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R 					|= 		0x00000010;							// activate clock for Port E
  delay										 = 		SYSCTL_RCGC2_R;     		// set delay to RCGC2_R before continuing
	
  GPIO_PORTE_AMSEL_R 			&= 		~0x01;      						// disable analog on PE0
  GPIO_PORTE_PCTL_R 			&= 		~0x0000000F; 						// PCTL GPIO on PE0
  GPIO_PORTE_DIR_R 				&= 		~0x01;        					// direction PE0 input
  GPIO_PORTE_AFSEL_R 			&= 		~0x01;      						// PE0 regular port function
  GPIO_PORTE_DEN_R 				|= 		0x01;         					// enable PE0 digital port
}
unsigned long Switch_Input(void){
  return PE0; // return 0x20(pressed) or 0(not pressed)
}
unsigned long Switch_Input2(void){
  return (GPIO_PORTA_DATA_R&0x01); // 0x20(pressed) or 0(not pressed)
}

// LED DRIVER(PE1): includes initialization and functions accociated with LED hardware
#define PE1	(*((volatile unsigned long *)0x40024008))		//Bit specific addressing - base(port a): 0x40024000 / offset(pin 5):0x004
void LED_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R 				|= 			0x00000010;					// P[E]1: _ _ _ X  _ _ _ _ 	(X X F [E]  D C B A)
  delay 								 = 			SYSCTL_RCGC2_R;			// set delay to RCGC2_R before continuing
	
  GPIO_PORTE_PCTL_R 		&= 			~0x000000F0; 				// PE[1]: _ _ _ _  _ _ X _  (7 6 5 4  3 2 [1] 0) INVERT
  GPIO_PORTE_AMSEL_R 		&= 			~0x02;      				// PE[1]: _ _ _ _  _ _ X _ 	(7 6 5 4  3 2 [1] 0) INVERT
  GPIO_PORTE_DIR_R 			|= 			0x02;         			// PE[1]: _ _ _ _  _ _ X _ 	(7 6 5 4  3 2 [1] 0)
  GPIO_PORTE_AFSEL_R 		&= 			~0x02;      				// PE[1]: _ _ _ _  _ _ X _ 	(7 6 5 4  3 2 [1] 0) INVERT
  GPIO_PORTE_DEN_R 			|= 			0x02;         			// PE[1]: _ _ _ _  _ _ X _ 	(7 6 5 4  3 2 [1] 0)
}
// Make PA2 high
 void LED_On(void){
   GPIO_PORTA_DATA_R |= 0x02;
 }
// Make PA2 low
void LED_Off(void){
  GPIO_PORTE_DATA_R &= ~0x02;
}
#define ON 0xFF; 
#define OFF 0x00;

// ***** 3. Subroutines Section *****
int main(void){ 
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOff);  // activate grader and set system clock to 80 MHz
  EnableInterrupts();           // enable interrupts for the grader
	
  while(1){
		PE1 = 0x01;
  }
}

