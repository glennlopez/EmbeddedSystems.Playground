// 0.Documentation Section 
// Lab7_HeartBlock, main.c

// Runs on LM4F120 or TM4C123 LaunchPad
// Input from PF4(SW1) is AS (atrial sensor), 
// Output to PF3, Green LED, is Ready,
// Output to PF1, Red LED, is VT (ventricular trigger) 
// Make PF4 input, PF3,PF1 output
// Initialize Ready to high and VT to low
// Repeat this sequence of operation over and over
// 1) Wait for AS to fall (touch SW1 switch)
// 2) Clear Ready low
// 3) Wait 10ms (debounces the switch)
// 4) Wait for AS to rise (release SW1)
// 5) Wait 250ms (simulates the time between atrial and ventricular contraction)
// 6) set VT high, which will pulse the ventricles 
// 7) Wait 250ms
// 8) clear VT low 
// 9) set Ready high

// Date: January 15, 2016

// 1. Pre-processor Directives Section
#include "TExaS.h"

// Constant declarations to access port registers using 
// PortF Base Address: 0x4002.5FFF
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC)) //offset: 0x3FC 	- enabled pins for data I/O (4*2^b)
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400)) //offset: 0x400		- 1 is output, 0 is input
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420)) //offset:	0x420		- 1 enabled, 0 disabled
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510)) //offset:	0x510		- 1 pullup enabled, 0 disabled
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C)) //offset:	0x51C		- 1 enabled, 0 disabled
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520)) //offset:	0x520		- 0x4C4F434B unlocks GPIO commit register
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524)) //offset:	0x524		- 1 writeable, 0 cannot be written
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528)) //offset:	0x528		- 1 enabled, 0 disabled
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C)) //offset:	0x52C		- 0x00000000 resets 
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108)) //offset:	0x108		- 
// 2. Declarations Section
//   Global Variables

//   Function Prototypes
void PortF_Init(void);
void Delay1ms(unsigned long msec);
void EnableInterrupts(void);
void WaitForASLow(void);
void WaitForASHigh(void);
void SetVT(void);
void ClearVT(void);
void SetReady(void);
void ClearReady(void);

// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void){
  TExaS_Init(SW_PIN_PF40, LED_PIN_PF31,ScopeOn);  		// activate grader and set system clock to 80 MHz
  PortF_Init();                            						// Init port PF4 PF3 PF1    
  EnableInterrupts();                      						// enable interrupts for the grader  
	
	
  while(1){          
		
		
    // a) Ready signal goes high
    // b) wait for switch to be pressed
    // c) Ready signal goes low
    // d) wait 10ms
    // e) wait for switch to be released
    // f) wait 250ms
    // g) VT signal goes high
    // h) wait 250ms
    // i) VT signal goes low
		
		
		
		
		
  }
}




/*
 * Subroutine to initialize port F pins for input and output
 * PF4 is input SW1 and PF3-1 is output LEDs
 * Inputs: None
 * Outputs: None
 * Notes: ...
 */
void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R 							|= 		0x00000020;      			// 1) F clock
  delay 											 = 		SYSCTL_RCGC2_R;      	// delay to allow clock to stabilize     
  GPIO_PORTF_AMSEL_R 					&= 		0x00;        					// 2) disable analog function
  GPIO_PORTF_PCTL_R 					&= 		0x00000000;   				// 3) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R 						&= 		~0x10;         				// 4.1) PF4 input,
  GPIO_PORTF_DIR_R 						|= 		0x0E;          				// 4.2) PF3,2,1 output  
  GPIO_PORTF_AFSEL_R 					&= 		0x00;        					// 5) no alternate function
  GPIO_PORTF_PUR_R 						|= 		0x10;          				// 6) enable pullup resistor on PF4       
  GPIO_PORTF_DEN_R 						|= 		0x1E;          				// 7) enable digital pins PF4-PF1
}

/*
		// Configure PortF pins
		SYSCTL_RCGC2_R					|=	0x00000020;				// _ _ F E  D C B A (Port selection)
		delay 									= 	SYSCTL_RCGC2_R;
	
		GPIO_PORTF_LOCK_R				=		0x4C4F434B;				// _ _ _ 1  1 1 1 1	(enable write access to GPIOCR register) 
		GPIO_PORTF_CR_R					=		0x1F;							// _ _ _ 1  1 1 1 1	(Change Commit registers)
		GPIO_PORTF_AMSEL_R			=		0x00;							// _ _ _ 0  0 0 0 0	(Not using analog mode select)
		GPIO_PORTF_PCTL_R				=		0x00000000;				// _ _ _ 0  0 0 0 0 (Not using alternative functions)
		GPIO_PORTF_DIR_R 				= 	0x0E;							// _ _ _ 0  1 1 1 0 (PF0 and PF4 are input switches)
		GPIO_PORTF_AFSEL_R			=		0x00;							// _ _ _ 0  0 0 0 0 (Not using alternative functions)
		GPIO_PORTF_PUR_R				=		0x11;							// _ _ _ 1  0 0 0 1 (Enable pull-up resistors on P0 and P4 switches)
		GPIO_PORTF_DEN_R				=		0x1F; 						// _ _ _ 1  1 1 1 1	(Enable digital signal for all target pins)
*/



/*
 * Subroutine reads AS input and waits for signal to be low
 * If AS is already low, it returns right away
 * If AS is currently high, it will wait until it to go low
 * Inputs:  None
 * Outputs: None
 */
void WaitForASLow(void){

	
}



/*
 * Subroutine reads AS input and waits for signal to be high
 * If AS is already high, it returns right away
 * If AS is currently low, it will wait until it to go high
 * Inputs:  None
 * Outputs: None
 */
void WaitForASHigh(void){

	
}




/*
 * Subroutine sets VT high
 * Inputs:  None
 * Outputs: None
 * Notes:   friendly means it does not affect other bits in the port
 */
void SetVT(void){

	
}




/*
 * Subroutine clears VT low
 * Inputs:  None
 * Outputs: None
 * Notes:   friendly means it does not affect other bits in the port
 */
void ClearVT(void){
// write this function
}




/*
 * Subroutine sets Ready high
 * Inputs:  None
 * Outputs: None
 * Notes:   friendly means it does not affect other bits in the port
 */
void SetReady(void){

	
}




/*
 * Subroutine clears Ready low
 * Inputs:  None
 * Outputs: None
 * Notes:   friendly means it does not affect other bits in the port
 */
void ClearReady(void){

	
}



/*
 * Subroutine to delay in units of milliseconds
 * Inputs:  Number of milliseconds to delay
 * Outputs: None
 * Notes:   assumes 80 MHz clock 
 */
void Delay1ms(unsigned long msec){
	

}

