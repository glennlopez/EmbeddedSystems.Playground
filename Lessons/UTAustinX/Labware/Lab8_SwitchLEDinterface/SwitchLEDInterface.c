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


//FIXME: #define ON 0xXX; 
//FIXME: #define OFF 0xXX;


// ***** 2. Global Declarations Section *****
// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts


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


// LED DRIVER(PE1): includes initialization and functions accociated with LED hardware
void LED_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R 				|= 			0x00000010;					// P[E]1: _ _ _ X  _ _ _ _ 	(X X F [E]  D C B A)
  delay 								 = 			SYSCTL_RCGC2_R;			// set delay to RCGC2_R before continuing
	
  GPIO_PORTE_PCTL_R 		&= 			~0x000000F0; 				// PE[1]: _ _ _ _  _ _ X _  (7 6 5 4  3 2 [1] 0) INVERT
  GPIO_PORTE_AMSEL_R 		&= 			~0x02;      				// PE[1]: _ _ _ _  _ _ X _ 	(7 6 5 4  3 2 [1] 0) INVERT
  GPIO_PORTE_DIR_R 			|= 			0x02;         			// PE[1]: _ _ _ _  _ _ X _ 	(7 6 5 4  3 2 [1] 0)
  GPIO_PORTE_AFSEL_R 		&= 			~0x02;      				// PE[1]: _ _ _ _  _ _ X _ 	(7 6 5 4  3 2 [1] 0) INVERT
  GPIO_PORTE_DEN_R 			|= 			0x02;         			// PE[1]: _ _ _ _  _ _ X _ 	(7 6 5 4  3 2 [1] 0)
}



// ***** 3. Subroutines Section *****
int main(void){ 
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz
  EnableInterrupts();           // enable interrupts for the grader
	
  while(1){
    
  }
}

