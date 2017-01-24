#include "PLL.h"
#include "SysTick.h"

//OUTPUT
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC)) // bits 7-0
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_DR8R_R       (*((volatile unsigned long *)0x40005508))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

//INPUT
#define GPIO_PORTE10            (*((volatile unsigned long *)0x4002400C)) // bits 1-0
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC)) // bits 7-0
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
	
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

//prototypes
void PortB_Init(void);
void PortE_Init(void);

// represents a State of the FSM
struct State{
  unsigned char out;     // PB7-4 to right motor, PB3-0 to left          
  unsigned short wait;   // in 10ms units       
  unsigned char next[4]; // input 0x00 means ok,
                         //       0x01 means right side bumped something,
                         //       0x02 means left side bumped something,
                         //       0x03 means head-on collision (both sides bumped something)
};typedef const struct State StateType;


StateType Fsm[10] = {
  {0x55, 1, {1, 4, 7, 3} }, // S0) initial state and state where bumpers are checked
	
  {0x66, 1, {2, 2, 2, 0} }, // S1) both forward [1]
  {0xAA, 1, {3, 3, 3, 1} }, // S2) both forward [2]
  {0x99, 1, {0, 0, 0, 2} }, // S3) both forward [3]
	
  {0x69, 2, {5, 5, 5, 5} }, // S4) turn left, left reverse; right forward[1] left
  {0xAA, 2, {6, 6, 6, 6} }, // S5) turn left, left reverse; right forward[2] left
  {0x96, 2, {0, 0, 0, 0} }, // S6) turn left, left reverse; right forward[3] left
	
  {0x96, 2, {8, 8, 8, 8} }, // S7) turn right, left forward; right reverse[1] right
  {0xAA, 2, {9, 9, 9, 9} }, // S8) turn right, left forward; right reverse[2] right
  {0x69, 2, {0, 0, 0, 0} }  // S9) turn right, left forward; right reverse[3] right
};







/**********
	MAIN
***********/
unsigned char cState;      // current State (0 to 9)
int main(void){
	
	//setup
  unsigned char input;
  PLL_Init();                      
  SysTick_Init();                  
  PortB_Init();                    // initialize motor outputs on Port B
  PortE_Init();                    // initialize sensor inputs on Port E
  cState = 0;                      // initial state = 0
	
	//main loop routine
  while(1){
    // OUTPUT based on current state
    GPIO_PORTB_DATA_R = Fsm[cState].out; 	// step motor
    // wait for time according to state
    SysTick_Wait10ms(Fsm[cState].wait);
		
		
    // get INPUT     
    input = GPIO_PORTE_DATA_R&0x03; 			// Input 0,1,2,3
    // change the state based on input and current state
    cState = Fsm[cState].next[input];
  }
	
}








/***********
	FUNCTION
***********/
void PortB_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x02;          			// 1) activate Port B
  delay = SYSCTL_RCGC2_R;          			// allow time for clock to stabilize
																				// 2) no need to unlock PB7-0
  GPIO_PORTB_AMSEL_R 		&= ~0xFF;     	// 3) disable analog functionality on PB7-0
  GPIO_PORTB_PCTL_R 		 = 0x00000000;  // 4) configure PB7-0 as GPIO
  GPIO_PORTB_DIR_R 			|= 0xFF;        // 5) make PB7-0 out
  GPIO_PORTB_AFSEL_R 		&= ~0xFF;     	// 6) disable alt funct on PB7-0
  GPIO_PORTB_DR8R_R 		|= 0xFF;      	// enable 8 mA drive on PB7-0
  GPIO_PORTB_DEN_R 			|= 0xFF;        // 7) enable digital I/O on PB7-0
}

void PortE_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x10;          			// 1) activate Port E
  delay = SYSCTL_RCGC2_R;          			// allow time for clock to stabilize
																				// 2) no need to unlock PE1-0
  GPIO_PORTE_AMSEL_R 		&= ~0x03;     	// 3) disable analog function on PE1-0
  GPIO_PORTE_PCTL_R 		&= ~0x000000FF;	// 4) configure PE1-0 as GPIO
  GPIO_PORTE_DIR_R 			&= ~0x03;       // 5) make PE1-0 in
  GPIO_PORTE_AFSEL_R 		&= ~0x03;     	// 6) disable alt funct on PE1-0
  GPIO_PORTE_DEN_R 			|= 0x03;        // 7) enable digital I/O on PE1-0
}







/*
// option 2: this FSM should turn more sharply, but of course it uses more states
StateType FSM[18] = {
  {0x55, 2, {1, 4, 11, 3} },       // S0)  initial state and state where bumpers are checked
  {0x66, 2, {2, 2, 2, 0} },        // S1)  both forward [1]
  {0xAA, 2, {3, 3, 3, 1} },        // S2)  both forward [2]
  {0x99, 2, {0, 0, 0, 2} },        // S3)  both forward [3]
  {0x59, 5, {5, 5, 5, 5} },        // S4)  left forward half; right reverse full [1]
  {0x6A, 5, {6, 6, 6, 6} },        // S5)  left forward half; right reverse full [2]
  {0x66, 5, {7, 7, 7, 7} },        // S6)  left forward half; right reverse full [3]
  {0xA5, 5, {8, 8, 8, 8} },        // S7)  left forward half; right reverse full [4]
  {0xA9, 5, {9, 9, 9, 9} },        // S8)  left forward half; right reverse full [5]
  {0x9A, 5, {10, 10, 10, 10} },    // S9)  left forward half; right reverse full [6]
  {0x96, 5, {0, 0, 0, 0} },        // S10) left forward half; right reverse full [7]
  {0x95, 6, {12, 12, 12, 12} },    // S11) left reverse full; right forward half [1]
  {0xA6, 5, {13, 13, 13, 13} },    // S12) left reverse full; right forward half [2]
  {0x96, 5, {14, 14, 14, 14} },    // S13) left reverse full; right forward half [3]
  {0x5A, 5, {15, 15, 15, 15} },    // S14) left reverse full; right forward half [4]
  {0x9A, 5, {16, 16, 16, 16} },    // S15) left reverse full; right forward half [5]
  {0xA9, 5, {17, 17, 17, 17} },    // S16) left reverse full; right forward half [6]
  {0x69, 5, {0, 0, 0, 0} }         // S17) left reverse full; right forward half [7]
};
*/
