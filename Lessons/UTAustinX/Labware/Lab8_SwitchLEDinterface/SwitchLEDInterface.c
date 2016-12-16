// Includes
#include "TExaS.h"

// Clock gating controls base address: 0x400F.E000
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))			//run mode gating register		- offset 0x108 

	
// PortE(APB) base address: 0x4002.4000
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x40024000))			//0x3FC means 0011 1111 expressed as 4*2^b (bitspecific addressing)
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))			//gpio direction 							- offset 0x400
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))			//gpio alternte funtion 			- offset 0x420
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))			//gpio pull-up select					- offset 0x510
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))			//gpio digital enable 				- offset 0x51C
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))			//gpio analog mode select			- offset 0x528
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))			//gpio port control						- offset 0x52C
#define GPIO_PORTE_LOCK_R				(*((volatile unsigned long *)0x40024520))			//gpio portf lock register 		- offset 0x520
#define GPIO_PORTE_CR_R					(*((volatile unsigned long *)0x40024524))			//gpio portf comit register		- offset 0x524
	
// PortE Bit-specific Address definitions (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04) expressed as 4*2^b (bitspecific addressing)
#define SW1											(*((volatile unsigned long *)0x40024004))			//OUT - offset
#define LED											(*((volatile unsigned long *)0x40024008))			//OUT - offset

// Warning: Only use these for bitspecific addresses
#define OFF 										0x00	//not an address, no need to typecast to volatile unsigned long
#define ON											0xFF	//not an address, no need to typecast to volatile unsigned long



// Basic functions defined at end of startup.s
void DisableInterrupts(void); 				// Disable interrupts
void EnableInterrupts(void);  				// Enable interrupts
int initPortE(void);									// PortA prototype
void blink(int ms);										// Blink LED in miliseconds
void delay1ms(unsigned long msec);		// Delay subroutine req for blink



int main(void){ 
	
	TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOff);  
  EnableInterrupts();         // enable interrupts for the grader
	initPortE();								// configure portA - for debugging
	
  while(1){										

		if(SW1 == OFF){
			LED = ON;
		}
		else{
			delay1ms(10);						//debounce
			if(SW1 == 0x01){				//check if switch still on
				blink(100);						//blink the led
			}
		}

	}
}






void delay1ms(unsigned long msec){
	int i = 0;
	while(msec > 0){
		for(i = 0; i < 13255; i++);
		msec--;
	}
}


void blink(int ms){
			LED = ON;
			delay1ms(ms);
			LED = OFF;
			delay1ms(ms);
}


int initPortE(void){unsigned long volatile delay;

		SYSCTL_RCGC2_R					|=	0x00000010;				// _ _ F E  D C B A (Port selection)
		delay 									= 	SYSCTL_RCGC2_R;
	
		GPIO_PORTE_LOCK_R				=		0x4C4F434B;				// _ _ _ 1  1 1 1 1	(enable write access to GPIOCR register) 
		GPIO_PORTE_CR_R					=		0x1F;							// _ _ _ 1  1 1 1 1	(Change Commit registers)
		GPIO_PORTE_AMSEL_R			=		0x00;							// _ _ _ 0  0 0 0 0	(Not using analog mode select)
		GPIO_PORTE_PCTL_R				=		0x00000000;				// _ _ _ 0  0 0 0 0 (Not using alternative functions)
		GPIO_PORTE_DIR_R 			 &= 	~0x01;         		// PE0 (Input)
		GPIO_PORTE_DIR_R 			 |= 	0x02;          		// PE1 (output)
		GPIO_PORTE_AFSEL_R			=		0x00;							// 0 0 0 0  0 0 0 0 (Not using alternative functions)
		GPIO_PORTE_PUR_R				=		0x00;							// 0 0 0 1  0 0 0 1 (Enable pull-up resistors on P0 and P4 switches)
		GPIO_PORTE_DEN_R				=		0x1F; 						// 0 0 0 1  1 1 1 1	(Enable digital signal for all target pins)
	
	return 0;
}
