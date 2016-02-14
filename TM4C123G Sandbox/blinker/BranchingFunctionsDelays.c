//Blinker - uC hello World: by glennlopez
#include "TExaS.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1


//Pin Access definitions
#define SW1		(*((volatile unsigned long*)0x40025040)) 	//PF4 input 	| Switch
#define LED		(*((volatile unsigned long*)0x40025010))	//PF2 output 	| LED



// basic functions defined at end of startup.s
void DisableInterrupts(void); 				// Disable interrupts
void EnableInterrupts(void);  				// Enable interrupts

void PortF_Init();								//Init portF prototype
void soft_delay(unsigned long second);		//delay

int main(void){

	unsigned long volatile delay;
	TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);  	// activate grader and set system clock to 80 MHz

	EnableInterrupts();           			// enable interrupts for the grader
	PortF_Init();

	while(1){
		soft_delay(1);

	    	// body goes here
			if(SW1 == 0){
				LED = LED^0x04;
			}

			else{
				LED = 0x04;
			}
	  }
	}





/*
 *	PORT F INITIALIZATION:
 *	Make PF2 an output and make PF4 an input (enable PUR for PF4)
 */

//portf initialization
void PortF_Init(){
	volatile unsigned long delay;

	SYSCTL_RCGC2_R = SYSCTL_RCGC2_R | 0x00000020;	//Enable PortF Clock
	delay = SYSCTL_RCGC2_R;									//Catch up to clock before doing aything
	GPIO_PORTF_AMSEL_R 	= 0x00;							//Analog Mode select register
	GPIO_PORTF_AFSEL_R 	= 0x00;							//Alternative function
	GPIO_PORTF_PCTL_R 	= 0x00000000;					//Alternative fucntion control
	GPIO_PORTF_DIR_R		= 0x04;							//PortF pin directions
	GPIO_PORTF_PUR_R		= 0x10;							//PortF pull up resistors
	GPIO_PORTF_DEN_R		= 0x1F;							//PortF Digital Enable register

	GPIO_PORTF_DATA_R		= 0x04;							//PORTF INITIAL STATE
}


//software delay
void soft_delay(unsigned long second){
	unsigned long i;
	unsigned long j;
	unsigned long x;

	for(x = second; x > 0; x--){
		for(i = 1600; i > 0; i--){
			for(j = 1000; j > 0; j--);
		}
	}

}
