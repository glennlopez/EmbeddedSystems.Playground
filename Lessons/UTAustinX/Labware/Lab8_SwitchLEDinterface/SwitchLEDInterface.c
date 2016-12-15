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

//bit-specific addressing
#define PE0	(*((volatile unsigned long *)0x40024004))	//PE0(Switch) | base(port a): 0x40024000 / offset(pin 5):0x004  


// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// SWITCH DRIVER: includes initialization and functions accociated with switch hardware
void Switch_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R 					|= 		0x00000010;					// 1) activate clock for Port E
  delay										 = 		SYSCTL_RCGC2_R;     // wait for SYSCTL_RCGC2_R before continuing
																										// 2) no need to unlock GPIO Port A
  GPIO_PORTE_AMSEL_R 			&= 		~0x01;      				// 3) disable analog on PE0
  GPIO_PORTE_PCTL_R 			&= 		~0x0000000F; 				// 4) PCTL GPIO on PE0
  GPIO_PORTE_DIR_R 				&= 		~0x01;        			// 5) direction PE0 input
  GPIO_PORTE_AFSEL_R 			&= 		~0x01;      				// 6) PE0 regular port function
  GPIO_PORTE_DEN_R 				|= 		0x01;         			// 7) enable PE0 digital port
}
unsigned long Switch_Input(void){
	return PE0; 																			// return 0x01(pressed) or 0(not pressed)
}
unsigned long Switch_Input2(void){
	return (GPIO_PORTE_DATA_R&0x01); 									// 0x01(pressed) or 0(not pressed)
}




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

