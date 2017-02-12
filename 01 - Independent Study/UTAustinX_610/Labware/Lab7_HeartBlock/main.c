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
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))			//gpio digital enable 				- offset 0x51C
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))			//gpio analog mode select			- offset 0x528
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))			//gpio port control						- offset 0x52C
	
// Warning: Only use these for bitspecific addresses (do not use for inputs)
#define OFF 										0x00	//not an address, no need to typecast to volatile unsigned long
#define ON											0xFF	//not an address, no need to typecast to volatile unsigned long


// 2. Declarations Section
// Global Variables & prototypes
void DisableInterrupts(void); 			
void EnableInterrupts(void);  			
void initPortE(void);								
void delay(unsigned long msec);
void blink(int ms);

/* NOTES: Code-friendly drivers
 * If the desired bit is 0, then mask using 	&= ~0xNUM
 * If the desired bit is 1, then use 					|= 0xNUM
 */

#define SW1											(*((volatile unsigned long *)0x40024004))
void driverSwitch(void){unsigned long volatile delay;	
		SYSCTL_RCGC2_R					|=	0x00000010;				// _ _ F E  D C B A (Port selection for clock)
		delay 									= 	SYSCTL_RCGC2_R;		// set delay to wait for RCGC2 before continuing
	
		GPIO_PORTE_AMSEL_R		 &=		~0x01;						// 1 1 1 1  1 1 1 0 &	AMSEL		(Not using analog mode select)
		GPIO_PORTE_PCTL_R			 &=		~0x01;						// 1 1 1 1  1 1 1 0 & PCTL		(Not using alternative functions)
		GPIO_PORTE_DIR_R 			 &= 	~0x01;         		// 1 1 1 1  1 1 1 0 & DIR			(Input: PE0) INVERT
		GPIO_PORTE_AFSEL_R		 &=		~0x01;						// 1 1 1 1  1 1 1 0 &	AFSEL		(Not using alternative functions)
		GPIO_PORTE_DEN_R			 |=		0x01; 						// 0 0 0 0  0 0 0 1	=	DEN			(Enable digital signal for pin 0)	
}

#define LED											(*((volatile unsigned long *)0x40024008))
void driverLED(void){unsigned long volatile delay;
		SYSCTL_RCGC2_R					|=	0x00000010;				// _ _ F E  D C B A (Port selection for clock)
		delay 									= 	SYSCTL_RCGC2_R;		// set delay to wait for RCGC2 before continuing
	
		GPIO_PORTE_AMSEL_R		 &=		~0x02;						// 1 1 1 1  1 1 0 1 &	AMSEL		(Not using analog mode select)
		GPIO_PORTE_PCTL_R			 &=		~0x02;						// 1 1 1 1  1 1 0 1 & PCTL		(Not using alternative functions)
		GPIO_PORTE_DIR_R 			 |= 	0x02;          		// 0 0 0 0  0 0 1 0 | DIR			(Output: PE1)
		GPIO_PORTE_AFSEL_R		 &=		~0x02;						// 1 1 1 1  1 1 0 1 &	AFSEL		(Not using alternative functions)
		GPIO_PORTE_DEN_R			 |=		0x02; 						// 0 0 0 0  0 0 1 0	=	DEN			(Enable digital signal for pin 1)
}


// 3. Subroutines Section
// main subroutine
int main(void){ 
	TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  
  EnableInterrupts();
	
	driverSwitch();			// initiate switch driver
	driverLED();				// initiate LED driver
	
	while(1){
		LED = ON;
		delay(10);		// debounce delay
		blink(100);		// blink led in ms
	}
}



// delay subroutine
void delay(unsigned long msec){
	int i = 0;
	while(msec > 0){
		for(i = 0; i < 13255; i++);
		msec--;
	}
}

// blink subroutine
void blink(int ms){
	while(SW1 == 0x01){
				LED = ON;
			if(SW1 == 0x00){
				break;
			}
			delay(ms);
			if(SW1 == 0x00){
				break;
			}
			LED = OFF;
			if(SW1 == 0x00){
				break;
			}
			delay(ms);
				if(SW1 == 0x00){
				break;
			}
		}
}