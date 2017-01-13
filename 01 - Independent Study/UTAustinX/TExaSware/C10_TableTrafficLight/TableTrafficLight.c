#include "PLL.h"
#include "SysTick.h"

//GPIO Port B (APB) base: 0x4000.5000
//Bit-specific Address definitions (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
/*
		Bits 5 - 080
		Bits 4 - 040
		Bits 3 - 020
		Bits 2 - 010
		Bits 1 - 008
		Bits 0 - 004
	----------------
	Total:		 0FC >> 0x400050FC

*/
#define LIGHT                   (*((volatile unsigned long *)0x400050FC)) // bits 5-0
#define GPIO_PORTB_OUT          (*((volatile unsigned long *)0x400050FC)) // bits 5-0
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
	




//GPIO Port E (APB) base: 0x4002.4000
//Bit-specific Address definitions (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
/*
		Bits 1 - 008
		Bits 0 - 004
	----------------
	Total:		 00C >> 0x4002400C

*/
#define SENSOR                  (*((volatile unsigned long *)0x4002400C)) // bits 1-0
#define GPIO_PORTE_IN           (*((volatile unsigned long *)0x4002400C)) // bits 1-0
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))


//Run Mode Clock Gating Control Register 2
//Base 0x400FE000 w/ Offset 0x108
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOE      0x00000010  // port E Clock Gating Control
#define SYSCTL_RCGC2_GPIOB      0x00000002  // port B Clock Gating Control

//prototypes
void portClock_init(void);
void portE_int(void);
void portB_int(void);

// Linked data structure
struct State {
  unsigned long Out; 
  unsigned long Time;  
  unsigned long Next[4];
}; 

typedef const struct State STyp;
#define goN   0
#define waitN 1
#define goE   2
#define waitE 3
	
STyp FSM[4] = {
 {0x21,	3000,	{goN,waitN,goN,waitN}	}, 
 {0x22,	500,	{goE,goE,goE,goE}			},
 {0x0C,	3000,	{goE,goE,waitE,waitE}	},
 {0x14,	500,	{goN,goN,goN,goN}			}
};

unsigned long S;
unsigned long Input;
 


/*************
	MAIN
*************/
int main(void){
  PLL_Init();       // 80 MHz, Program 10.1
  SysTick_Init();   // Program 10.2

	portClock_init();	// init port register clocks
	portE_int();			// init INPUT port E 
	portB_int();			// init port B
	
  S = goN; 					// set initial state to goN
	
	
  while(1){
    LIGHT = FSM[S].Out;  // set lights
    SysTick_Wait10ms(FSM[S].Time);
		
    Input = SENSOR;     // read sensors
    S = FSM[S].Next[Input];  
  }
		
	//return 0;
}





/*************
	FUNCTIONS
*************/
void portClock_init(void){ volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x12;      					// 1) B E
  delay = SYSCTL_RCGC2_R;      					// 2) no need to unlock
}

void portE_int(void){
	GPIO_PORTE_AMSEL_R 	&= ~0x03; 				// 3) disable analog function on PE1-0
  GPIO_PORTE_PCTL_R 	&= ~0x000000FF; 	// 4) enable regular GPIO
  GPIO_PORTE_DIR_R 		&= ~0x03;   			// 5) inputs on PE1-0
  GPIO_PORTE_AFSEL_R 	&= ~0x03; 				// 6) regular function on PE1-0
  GPIO_PORTE_DEN_R 		|= 0x03;    			// 7) enable digital on PE1-0
}

void portB_int(void){
	GPIO_PORTB_AMSEL_R 	&= ~0x3F; 				// 3) disable analog function on PB5-0
  GPIO_PORTB_PCTL_R 	&= ~0x00FFFFFF; 	// 4) enable regular GPIO
  GPIO_PORTB_DIR_R 		|= 0x3F;    			// 5) outputs on PB5-0
  GPIO_PORTB_AFSEL_R 	&= ~0x3F; 				// 6) regular function on PB5-0
  GPIO_PORTB_DEN_R 		|= 0x3F;    			// 7) enable digital on PB5-0
}

