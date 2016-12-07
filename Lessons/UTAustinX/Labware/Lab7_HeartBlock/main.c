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
// Common port registers 
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108)) //offset:	0x108		- *Register 136: Clock gating control register
	
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


	/* D E B U G   P O R T   P A R A M E T E R S
	* PA3: 		Output 	(GREEN LED) - Ready signal
	* PA2: 		Output 	(RED LED)		- Venticular trigger
	* PA5:		Output	( ??? )			-	Unknown
	* PA4: 		Input 	(SWITCH)		- Atrial sensor
	*/


// PortA Base Address (APB): 0x4000.4000 (for debug)
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC)) //offset: 0x3FC 	- enabled pins for data I/O (4*2^b)
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400)) //offset: 0x400		- 1 is output, 0 is input
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420)) //offset:	0x420		- 1 enabled, 0 disabled
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510)) //offset:	0x510		- 1 pullup enabled, 0 disabled
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C)) //offset:	0x51C		- 1 enabled, 0 disabled
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520)) //offset:	0x520		- 0x4C4F434B unlocks GPIO commit register
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524)) //offset:	0x524		- 1 writeable, 0 cannot be written
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528)) //offset:	0x528		- 1 enabled, 0 disabled
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C)) //offset:	0x52C		- 0x00000000 resets 



// PortF Bit-specific Address definitions (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04) expressed as 4*2^b (bitspecific addressing)
#define LED_BLUE								(*((volatile unsigned long *)0x40025010))			//PF2 - offset 0x010 
#define LED_RED									(*((volatile unsigned long *)0x40025008))			//PF1 - offset 0x008 
#define LED_GREEN								(*((volatile unsigned long *)0x40025020))			//PF3 - offset 0x020 
#define SW1											(*((volatile unsigned long *)0x40025040))			//PF4 - offset 0x040 
#define SW2											(*((volatile unsigned long *)0x40025004))			//PF0 - offset 0x004
	
	
// PortA Bit-specific Address definitions (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04) expressed as 4*2^b (bitspecific addressing)
#define PA2											(*((volatile unsigned long *)0x40004010))			//OUTPUT	VT
#define PA3											(*((volatile unsigned long *)0x40004020))			//OUTPUT	READY
#define PA4											(*((volatile unsigned long *)0x40004040))			//INPUT		AS
#define PA5											(*((volatile unsigned long *)0x40004080))			//OUTPUT	??



// Warning: Only use these for bitspecific addresses
#define OFF 										0x00	//not an address, no need to typecast to volatile unsigned long
#define ON											0xFF	//not an address, no need to typecast to volatile unsigned long




// 2. Declarations Section
//   Global Variables

//   Function Prototypes
void PortF_Init(void);
void PortA_Init(void);
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
  PortF_Init();                            						// Init port F    
	PortA_Init();																				// Init port A
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
		
		
		LED_GREEN = ON;
		PA3 = ON;
		
		
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
  SYSCTL_RCGC2_R 							|= 		0x00000020;      			// 1) F clock gate enbale
  delay 											 = 		SYSCTL_RCGC2_R;      	// delay to allow clock to stabilize     
  GPIO_PORTF_AMSEL_R 					&= 		0x00;        					// 2) disable analog function
  GPIO_PORTF_PCTL_R 					&= 		0x00000000;   				// 3) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R 						&= 		~0x10;         				// 4.1) PF4 input,
  GPIO_PORTF_DIR_R 						|= 		0x0E;          				// 4.2) PF3,2,1 output  
  GPIO_PORTF_AFSEL_R 					&= 		0x00;        					// 5) no alternate function
  GPIO_PORTF_PUR_R 						|= 		0x10;          				// 6) enable pullup resistor on PF4       
  GPIO_PORTF_DEN_R 						|= 		0x1E;          				// 7) enable digital pins PF4-PF1
}

void PortA_Init(void){ volatile unsigned long delay;
	SYSCTL_RCGC2_R 							|= 		0x00000001;      			// 1) A clock gate enable
  delay 											 = 		SYSCTL_RCGC2_R;      	// delay to allow clock to stabilize  
	GPIO_PORTA_LOCK_R						 =		0x4C4F434B;						// Check 0x4C4F.434B in datasheet
	GPIO_PORTA_CR_R					 		 =		0x2F;									// _ _ 1 1  1 1 1 1	(Change Commit registers)
  GPIO_PORTA_AMSEL_R 					&= 		0x00;        					// 2) disable analog function
  GPIO_PORTA_PCTL_R 					&= 		0x00000000;   				// 3) GPIO clear bit PCTL  
  GPIO_PORTA_DIR_R 						&= 		~0x10;         				// 4.1) PA4 input
  GPIO_PORTA_DIR_R 						|= 		0x2C;          				// 4.2) PA3, PA2, PA5 output  
  GPIO_PORTA_AFSEL_R 					&= 		0x00;        					// 5) no alternate function
  GPIO_PORTA_PUR_R 						|= 		0x10;          				// 6) enable pullup resistor on PA4       
  GPIO_PORTA_DEN_R 						|= 		0x3C;          				// 7) enable digital pins PA5 PA4 PA3 PA2
	
}



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

