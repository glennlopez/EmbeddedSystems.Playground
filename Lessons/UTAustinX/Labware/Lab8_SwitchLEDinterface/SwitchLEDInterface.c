// 0.Documentation Section 
// Lab8_SwitchLEDInterface, SwitchLEDInterface.c, glennlopez


// 1. Pre-processor Directives Section
// Includes
#include "TExaS.h"

// Clock gating controls base address: 0x400F.E000
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))			//run mode gating register		- offset 0x108 

// PortE (APB) base address: 0x4002.4000
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x40024000))			//0x3FC means 0011 1111 expressed as 4*2^b (bitspecific addressing)
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))			//gpio direction 							- offset 0x400
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))			//gpio alternte funtion 			- offset 0x420
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))			//gpio pull-up select					- offset 0x510
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))			//gpio digital enable 				- offset 0x51C
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))			//gpio analog mode select			- offset 0x528
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))			//gpio port control						- offset 0x52C
	
// PortE Bit-specific Address definitions (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04) expressed as 4*2^b (bitspecific addressing)
#define SW1											(*((volatile unsigned long *)0x40024004))			//OUT - offset
#define LED											(*((volatile unsigned long *)0x40024008))			//OUT - offset

// Warning: Only use these for bitspecific addresses (do not use for inputs)
#define OFF 										0x00	//not an address, no need to typecast to volatile unsigned long
#define ON											0xFF	//not an address, no need to typecast to volatile unsigned long


// 2. Declarations Section
// Global Variables & prototypes
void DisableInterrupts(void); 			
void EnableInterrupts(void);  			
void initPortE(void);								
void delay1ms(unsigned long msec);	
void blink(int ms);									


// 3. Subroutines Section
int main(void){ 
	
	TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  
  EnableInterrupts();         // enable interrupts for the grader
	initPortE();								// initialize port E
	
	// keep LED on
  while(1){										
		if(SW1 == 0x00){
			LED = ON;
		}
		
		//blink if switch is not 0x00 (off)
		else{
			delay1ms(10);						//debounce
			if(SW1 == 0x01){				//check if switch still on
				blink(100);						//blink the led
			}
		}
		
	}
}






/* _ Subroutine
 * Inputs: None
 * Outputs: None
 * Notes: 
 */
void delay1ms(unsigned long msec){
	int i = 0;
	while(msec > 0){
		for(i = 0; i < 13255; i++);
		msec--;
	}
}

/* _ Subroutine
 * Inputs: None
 * Outputs: None
 * Notes: 
 */
void blink(int ms){
			LED = ON;
			delay1ms(ms);
			LED = OFF;
			delay1ms(ms);
}

/* _ Subroutine
 * Inputs: None
 * Outputs: None
 * Notes: 
 */
void initPortE(void){unsigned long volatile delay;
	
		SYSCTL_RCGC2_R					|=	0x00000010;				// _ _ F E  D C B A (Port selection for clock)
		delay 									= 	SYSCTL_RCGC2_R;		// set delay to wait for RCGC2 before continuing
	
		GPIO_PORTE_AMSEL_R			=		0x00;							// 0 0 0 0  0 0 0 0	(Not using analog mode select)
		GPIO_PORTE_PCTL_R				=		0x00000000;				// 0 0 0 0  0 0 0 0 (Not using alternative functions)
		GPIO_PORTE_DIR_R 			 &= 	~0x01;         		// PE0 (Input)
		GPIO_PORTE_DIR_R 			 |= 	0x02;          		// PE1 (output)
		GPIO_PORTE_AFSEL_R			=		0x00;							// 0 0 0 0  0 0 0 0 (Not using alternative functions)
		GPIO_PORTE_PUR_R				=		0x00;							// 0 0 0 1  0 0 0 1 (Enable pull-up resistors on P0 and P4 switches)
		GPIO_PORTE_DEN_R				=		0x1F; 						// 0 0 0 1  1 1 1 1	(Enable digital signal for all target pins)
	
}
