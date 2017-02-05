/*
	UTAustinX Lab 10
	Glenn Lopez

	3 inputs: 	2 car sensors, 1 pedestrian
	8 outputs:	3 west, 3 south, 2 pedestrian

	pedestrian sensor is push and hold - presense sense
	car sensors are also push and hold - presense sense

	west & south lights must both be red before walk light can be green
	walk light should be red while cars have green or yellow light

	PORT B: 6 Traffic lights (output)
	PORT F: 2 Pedestrian lights (output)
	PORT E: 3 Sensors (input)

	~ uC OUTPUTS ~
	South/North: 	PB0 - PB2
	West/East: 		PB3 - PB5

	Walk Light:		PF1
	Dont Walk:		PF3


	~ uC INPUTS ~
	Pedestrian Detector:		PE2
	South/North Detector:		PE1
	West/East Detector:			PE0
	
	Bit-specific Addressing: (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
*/

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"						//UTAustinX Grader
//#include "tm4c123gh6pm.h"		//Microcontroller pre-defines

// Systick: 0xE000.E000
#define NVIC_ST_CTRL_R      		(*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R    		(*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R   		(*((volatile unsigned long *)0xE000E018))
	
// Clock Gating: 0x400FE000
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
	
// Port B (APB): 0x4000.5000		OUTPUT (6 traffic lights)
#define GPIO_PORTB_DATA					(*((volatile unsigned long *)0x400050FC))	//bitspecific: 0-5
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
	
// Port E (APB): 0x4002.4000		INPUT (3 sensors)
#define GPIO_PORTE_DATA					(*((volatile unsigned long *)0x4002401C)) //bitspecific: 0-2
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))

// Port F (APB): 0x4002.5000		OUTPUT (2 lights for peds)
#define GPIO_PORTF_DATA					(*((volatile unsigned long *)0x40025028)) //bitspecific: 1+3
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))

// FSM State LUT
#define GoW 0 
#define WaW 1
#define GoS 2
#define WaS	3
#define GoP	4
#define FN1	5
#define FF1	6
#define FN2	7
#define FF2	8

// FSM Delay parameters (in ms)
#define BLI 500 //blink
#define YEL 500	//wait light (yellow)
#define GSL	800	//Go/Stop light (green and red)

// ***** 2. Global Declarations Section *****
struct DataSet{
	void (*out)(void);			//function pointer used to reduce integration friction
	unsigned int delay;			//delay filler (change as per uC)
	unsigned int next[8];		//calculated by 2^(num of input bits)
}; typedef const struct DataSet FSM;

//function (*pointer) prototype
void goW(void); void waitW(void); void goS(void); void waitS(void);
void goP(void); void fN1(void); void fF1(void); void fN2(void); void fF2(void);

//state machine lookup table
FSM Lights[9] = {
// output	 delay	 000	001		010		011		100		101		110		111
	{&goW, 		GSL, 	{GoW,	GoW, 	WaW, 	WaW, 	WaW, 	WaW, 	WaW, 	WaW	}},
	{&waitW, 	YEL, 	{GoS, GoS, 	GoS, 	GoS, 	GoP, 	GoP, 	GoP, 	GoS	}},
	{&goS, 		GSL, 	{GoS, WaS, 	GoS, 	WaS, 	WaS, 	WaS, 	WaS, 	WaS	}},
	{&waitS, 	YEL, 	{GoW,	GoW, 	GoW, 	GoW, 	GoP, 	GoP, 	GoP, 	GoP	}},
	{&goP, 		GSL, 	{GoP, FN1, 	FN1, 	FN1, 	GoP, 	FN1, 	FN1, 	FN1	}},
	{&fN1, 		BLI, 	{FF1,	FF1, 	FF1, 	FF1, 	FF1, 	FF1, 	FF1, 	FF1	}},
	{&fF1, 		BLI, 	{FN2, FN2, 	FN2, 	FN2, 	FN2, 	FN2, 	FN2, 	FN2	}},
	{&fN2, 		BLI, 	{FF2, FF2, 	FF2, 	FF2, 	FF2, 	FF2, 	FF2,	FF2	}},
	{&fF2, 		BLI, 	{GoP,	GoW, 	GoS, 	GoW, 	GoP, 	GoW, 	GoS, 	GoW	}}
};

// FUNCTION PROTOTYPES: Each subroutine defined
void portB_int(void);	void portE_int(void);	void portF_int(void);		
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void SysTick_Init(void);			// Systick 			

void delay(unsigned int num); // Delay routine
void SysTick_Wait(unsigned long delay);
void SysTick_Wait10ms(unsigned long delay);




/************
	MAIN
************/
int main(void){ unsigned int cState, input;
	// Grader system routine
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210,ScopeOff); 
  EnableInterrupts();
	
	// System routine
	portB_int(); portE_int(); portF_int();	//initialize ports
	SysTick_Init(); 
	
	// FSM routine
	cState = 0;
  while(1){

		//display state output
		Lights[cState].out();
		delay(Lights[cState].delay);
		
		//get GPIO input
		input = GPIO_PORTE_DATA;
		
		//change state based on input and cState
		cState = Lights[cState].next[input];
		
  }
}




// ***** 3. Subroutines Section *****

/*******************
	SYSTEM FUNCTIONS
********************/
void delay(unsigned int num){unsigned long i;
	for(i = 0; i < num; i++){
		//systic delay
		for(i=0; i<num; i++){
			SysTick_Wait(80000);  // wait 1ms
		}
	}
}

void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock
}
// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)
void SysTick_Wait(unsigned long delay){
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}
void portB_int(void){ volatile unsigned long delay;	//OUTPUT (6 traffic lights)
	SYSCTL_RCGC2_R |= 0x02;								//enable clock gating for port B
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTB_AMSEL_R 	&= ~0x3F; 				//disable analog function on PB5-0
  GPIO_PORTB_PCTL_R 	&= ~0x00FFFFFF; 	//enable regular GPIO
  GPIO_PORTB_DIR_R 		|= 0x3F;    			//outputs on PB5-0
  GPIO_PORTB_AFSEL_R 	&= ~0x3F; 				//regular function on PB5-0
  GPIO_PORTB_DEN_R 		|= 0x3F;    			//enable digital on PB5-0
}
void portE_int(void){ volatile unsigned long delay;	//INPUT (3 sensors)
	SYSCTL_RCGC2_R |= 0x10;								//enable clock gating for port E
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTE_AMSEL_R 	&= ~0x07; 				//disable analog function on PE2-0
  GPIO_PORTE_PCTL_R 	&= ~0x00000FFF; 	//enable regular GPIO
  GPIO_PORTE_DIR_R 		&= ~0x07;    			//input on PE2-0
  GPIO_PORTE_AFSEL_R 	&= ~0x07; 				//regular function on PE2-0
  GPIO_PORTE_DEN_R 		|= 0x07;    			//enable digital on PE2-0
	//GPIO_PORTE_PUR_R
}
void portF_int(void){ volatile unsigned long delay;	//OUTPUT (2 lights for peds)
	SYSCTL_RCGC2_R |= 0x20;								//enable clock gating for port F
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_AMSEL_R 	&= ~0x0A; 				//disable analog function on PF1 PF3
  GPIO_PORTF_PCTL_R 	&= ~0x0000F0F0; 	//enable regular GPIO
  GPIO_PORTF_DIR_R 		|= 0x0A;    			//outputs on  PF1 PF3
  GPIO_PORTF_AFSEL_R 	&= ~0x0A; 				//regular function on  PF1 PF3
  GPIO_PORTF_DEN_R 		|= 0x0A;    			//enable digital on  PF1 PF3
}

/*******************
	FSM FUNCTIONS
********************/
void goW(){			//PortB: 0x0C | PortF:0x01
	GPIO_PORTB_DATA = 0x0C;
	GPIO_PORTF_DATA = 0x02;
}
void waitW(){		//PortB: 0x14 | PortF:0x02
	GPIO_PORTB_DATA = 0x14;
	GPIO_PORTF_DATA = 0x02;
}
void goS(){			//PortB: 0x21 | PortF:0x02
	GPIO_PORTB_DATA = 0x21;
	GPIO_PORTF_DATA = 0x02;
}
void waitS(){		//PortB: 0x22 | PortF:0x02
	GPIO_PORTB_DATA = 0x22;
	GPIO_PORTF_DATA = 0x02;
}
void goP(){			//PortB: 0x24 |	PortF:0x08
	GPIO_PORTB_DATA = 0x24;
	GPIO_PORTF_DATA = 0x08;
}
void fN1(){			//PortB: 0x24 |	PortF:0x02
	GPIO_PORTB_DATA = 0x24;
	GPIO_PORTF_DATA = 0x02;
}
void fF1(){			//PortB: 0x24 |	PortF:0x00
	GPIO_PORTB_DATA = 0x24;
	GPIO_PORTF_DATA = 0x00;
}
void fN2(){			//PortB: 0x24 |	PortF:0x02
	GPIO_PORTB_DATA = 0x24;
	GPIO_PORTF_DATA = 0x02;
}
void fF2(){			//PortB: 0x24 |	PortF:0x00
	GPIO_PORTB_DATA = 0x24;
	GPIO_PORTF_DATA = 0x00;
}
