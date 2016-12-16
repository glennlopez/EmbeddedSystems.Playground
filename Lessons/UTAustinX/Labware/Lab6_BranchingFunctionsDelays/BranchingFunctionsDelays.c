// Includes
#include "TExaS.h"

// Clock gating controls base address: 0x400F.E000
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))			//run mode gating register		- offset 0x108 
#define SYSCTL_RCGC2_GPIOF      0x00000020  																	//clock gating control PortF
#define SYSCTL_RCGC2_GPIOA      0x00000001  																	//clock gating control PortA


// PortA(APB) base address: 0x4000.4000
// APB: Advanced Peripheral Bus (has backwards compatability)
// AHB: Advanced High-performance Bus (is faster)
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))			//0x3FC means 0011 1111 expressed as 4*2^b (bitspecific addressing)
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))			//gpio direction 							- offset 0x400
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))			//gpio alternte funtion 			- offset 0x420
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))			//gpio pull-up select					- offset 0x510
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))			//gpio digital enable 				- offset 0x51C
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))			//gpio analog mode select			- offset 0x528
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))			//gpio port control						- offset 0x52C
#define GPIO_PORTA_LOCK_R				(*((volatile unsigned long *)0x40004520))			//gpio portf lock register 		- offset 0x520
#define GPIO_PORTA_CR_R					(*((volatile unsigned long *)0x40004524))			//gpio portf comit register		- offset 0x524
	
// PortE(APB) base address: 0x4002.4000
// APB: Advanced Peripheral Bus (has backwards compatability)
// AHB: Advanced High-performance Bus (is faster)


// PortF(APB) base address: 0x4002.5000
// APB: Advanced Peripheral Bus (has backwards compatability)
// AHB: Advanced High-performance Bus (is faster)
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))			//0x3FC means 0011 1111 expressed as 4*2^b (bitspecific addressing)
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))			//gpio direction 							- offset 0x400
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))			//gpio alternte funtion 			- offset 0x420
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))			//gpio pull-up select					- offset 0x510
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))			//gpio digital enable 				- offset 0x51C
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))			//gpio analog mode select			- offset 0x528
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))			//gpio port control						- offset 0x52C
#define GPIO_PORTF_LOCK_R				(*((volatile unsigned long *)0x40025520))			//gpio portf lock register 		- offset 0x520
#define GPIO_PORTF_CR_R					(*((volatile unsigned long *)0x40025524))			//gpio portf comit register		- offset 0x524


// PortF Bit-specific Address definitions (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04) expressed as 4*2^b (bitspecific addressing)
#define LED_BLUE								(*((volatile unsigned long *)0x40025010))			//PF2 - offset 0x010 
#define LED_RED									(*((volatile unsigned long *)0x40025008))			//PF1 - offset 0x008 
#define LED_GREEN								(*((volatile unsigned long *)0x40025020))			//PF3 - offset 0x020 
#define SW1											(*((volatile unsigned long *)0x40025040))			//PF4 - offset 0x040 
#define SW2											(*((volatile unsigned long *)0x40025004))			//PF0 - offset 0x004
	
	
// PortA Bit-specific Address definitions (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04) expressed as 4*2^b (bitspecific addressing)
#define PA4											(*((volatile unsigned long *)0x40004040))			//OUT - offset
#define PA3											(*((volatile unsigned long *)0x40004020))			//OUT - offset
#define PA2											(*((volatile unsigned long *)0x40004010))			//IN 	- offset



// Warning: Only use these for bitspecific addresses
#define OFF 										0x00	//not an address, no need to typecast to volatile unsigned long
#define ON											0xFF	//not an address, no need to typecast to volatile unsigned long



// Basic functions defined at end of startup.s
void DisableInterrupts(void); 				// Disable interrupts
void EnableInterrupts(void);  				// Enable interrupts
int initPortF(void);									// PortF prototype
int initPortA(void);									// PortA prototype
void delay();



int main(void){ 
	
	TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);  
	
  EnableInterrupts();         // enable interrupts for the grader
	initPortF();								// configure portF - main program
	initPortA();								// configure portA - for debugging
	
  while(1){										// body goes here
		
		
		/*
			[x] Make PF2 an output and make PF4 an input (enable PUR for PF4). 
			[x] The system starts with the LED ON (make PF2 =1). 
			[x] Delay for about 100 ms
			[x] If the switch is pressed (PF4 is 0), then toggle the LED once, else turn the LED ON. 
			[x] Repeat steps 3 and 4 over and over.
		*/
		
		if(SW1 == 0x10){
			LED_BLUE = ON;
			PA4 = ON;						//debug pin for logic analyser
		}
		else{
			LED_BLUE = ON;
			PA4 = ON;
			delay();
			LED_BLUE = OFF;
			PA4 = OFF;					//debug pin for logic analyser
			delay();
		}

	}
}





//FUNCTIONS
void delay(){								//Software delay
	int long i = 1333333;			//use 1600000 when simulating
	while(i > 0){
		i--;
	}
}


int initPortA(void){				//GPIO PortA(APB): 0x 4000.4000
	
		unsigned long volatile delay;
	
		// Configure PortA pins
		SYSCTL_RCGC2_R					|=	0x00000001;				// _ _ F E  D C B A (Port selection)
		delay 									= 	SYSCTL_RCGC2_R;
	
		GPIO_PORTA_LOCK_R				=		0x4C4F434B;				// _ _ _ 1  1 1 1 1	(Check 0x4C4F.434B in datasheet) 
		GPIO_PORTA_CR_R					=		0x1F;							// _ _ _ 1  1 1 1 1	(Change Commit registers)
		GPIO_PORTA_AMSEL_R			=		0x00;							// _ _ _ 0  0 0 0 0	(Not using analog mode select)
		GPIO_PORTA_PCTL_R				=		0x00000000;				// _ _ _ 0  0 0 0 0 (Not using alternative functions)
		GPIO_PORTA_DIR_R 				= 	0xFB;							// _ _ _ 1  1 0 1 1 (PF0 and PF4 are input switches)
		GPIO_PORTA_AFSEL_R			=		0x00;							// _ _ _ 0  0 0 0 0 (Not using alternative functions)
		GPIO_PORTA_PUR_R				=		0x04;							// _ _ _ 0  0 1 0 0 (Enable pull-up resistors on P0 and P4 switches)
		GPIO_PORTA_DEN_R				=		0x1C; 						// _ _ _ 1  1 1 0 0	(Enable only PA4 PA3 PA2)
	
	return 0;
	}

int initPortF(void){				//GPIO PortF(APB): 0x 4002.5000
	
		unsigned long volatile delay;
	
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
	
	return 0;
	}