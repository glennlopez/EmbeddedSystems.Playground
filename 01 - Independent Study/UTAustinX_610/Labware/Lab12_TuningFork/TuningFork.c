/*
    TuningFork.c Lab 12
		By: Glenn Lopez
		
    Runs on LM4F120/TM4C123
    Use SysTick interrupts to create a squarewave at 440Hz.
    There is a positive logic switch connected to PA3.
    There is an output on PA2. The output is
    connected to headphones through a 1k resistor.
    The volume-limiting resistor can be any value from 680 to 2000 ohms
    The tone is initially off, when the switch goes from
    not touched to touched, the tone toggles on/off.

                   |---------|               |---------|
 Switch   ---------|         |---------------|         |------

                    |-| |-| |-| |-| |-| |-| |-|
 Tone     ----------| |-| |-| |-| |-| |-| |-| |---------------

 System Specifications:
 [x] 440Hz Square Wave
 [x] Positive Logic Switch
 [x] PA3 acts as toggle switch
 [x] No edge triggering is possible (System Limitation)
 [x] Bus Clock is set to 80MHz
 [x] Use FSM to emulate edge detection

*/

#include "TExaS.h"
#include "..//tm4c123gh6pm.h"
#include "PLL.h"

/************************
 * DEFINITIONS
 ************************/

// System Control Legacy base address
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// PortA (APB) base address: 0x40004000
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTA_PDR_R        (*((volatile unsigned long *)0x40004514))

// SysTick Registers
#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

// PortA Bit-specific Address: (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
#define PA2   /* OUTPUT */      (*((volatile unsigned long *)0x40004010))
#define PA3   /* INPUT */       (*((volatile unsigned long *)0x40004020))
	
// Lab Specific definitions
#define ON                      0xFF
#define OFF                     0x00
#define TOGGLE_OFF 							0
#define TOGGLE_ON 							1


/************************
 * Pre-Proccess routines
 ************************/
void DisableInterrupts(void);           // Disable interrupts
void EnableInterrupts(void);            // Enable interrupts
void initSysTick(unsigned long param);
void initPortA_out(void);
void initPortA_in(void);
void delay(unsigned int param);
void edgeDetect(char param);

// Button Toggle FSM
struct state{
  unsigned int out;         // state output
  unsigned int next[2];     // possible state transition triggers
};typedef const struct state FSM;

FSM toggle[2] = {
// output | next possible states
  {0, {TOGGLE_OFF, TOGGLE_ON}},
  {1, {TOGGLE_ON, TOGGLE_OFF}}
};

// Global Variables
unsigned int output = 0;
unsigned int cState = TOGGLE_OFF;


/************************
 * ISR HANDLERS
 ************************/

void SysTick_Handler(void){

	// Toggle PA2 on rising-edge (uses FSM for edge detect)
	if(output == 1){
		PA2 ^= ON;
	}
	// Make sure tone is off when toggled off
	else if((output == 0) && (PA3 == 0x00)){
		PA2 = OFF;
	}
	
	else{
		PA2 = OFF;
	}
	

}


/************************
 * MAIN ROUTINE
 ************************/
int main(void){TExaS_Init(SW_PIN_PA3, HEADPHONE_PIN_PA2,ScopeOn);

  // Initialization routine
  SYSCTL_RCGC2_R |= 0x00000001;     // (a) Activate PortA Clock
  initPortA_out();                  // Initialize output driver
  initPortA_in();                   // Initialize input driver
  initSysTick(90909);               // Initialize systick
  PLL_Init();                       // 80 MHz
  EnableInterrupts();               // enable after all initialization are done

  // Program routine
  while(1){	unsigned int input = 0;
		edgeDetect('r');	// 'r' rising, 'f' falling
  }
	
}


/************************
 * SUB ROUTINES
 ************************/

// SysTick Initialization Routine (pg. 132)
void initSysTick(unsigned long param){

    NVIC_ST_CTRL_R           =      0;              //     Disable systick on setup
    NVIC_ST_RELOAD_R         =      param - 1;
    NVIC_ST_CURRENT_R        =      0;
    NVIC_SYS_PRI3_R         |=      0x50000000;     //     Interrupt Priority 2
    NVIC_ST_CTRL_R          |=      0x07;           //     Enable interrupts with systick
}

// PortA Output Initialization Routine
void initPortA_out(void){

    // GPIO Digital Control                         //     ************OUTPUT*************
    GPIO_PORTA_DEN_R        |=      0x04;           //     Make PA2 Digital Pins
    GPIO_PORTA_DIR_R        |=      0x04;           //     Make PA2 OUTPUT Pins

    // GPIO Alternate function control
    GPIO_PORTA_AMSEL_R      &=      0;              //     Disable Analog Mode
    GPIO_PORTA_AFSEL_R      &=      ~0x04;          //     Disable Alternate Function on PA2
    GPIO_PORTA_PCTL_R       &=      ~0x00000F00;    //     Keep PA2 as GPIO
}

// PortA Input Initialization
void initPortA_in(void){

    // GPIO Digital Control                         //     ************INPUT*************
    GPIO_PORTA_DEN_R        |=       0x08;          // 	   Make PA3 Digital Pins
    GPIO_PORTA_DIR_R        &=      ~0x08;          //     Make PA3 INPUT Pins
    GPIO_PORTA_PDR_R        |=       0x08;          //     Set Pull Down resistor for PA3

    // GPIO Alternate function control
    GPIO_PORTA_AFSEL_R      &=      ~0x08;          //     Disable Alternate Function on PA3
    GPIO_PORTA_PCTL_R       &=      ~0x0000F000;    //     Keep PA3 as GPIO
}

// Busy-wait delay 
void delay(unsigned int param){ unsigned int i, j;

    for(j = 0; j < param; j++){
        for(i = 0; i < 15; i++){
            // do nothing
        }
    }
}

// EdgeDetect: 'f' for falling, 'r' for rising
void edgeDetect(char param){
	if(param == 'r'){
		
		unsigned int input = 0;
    output = toggle[cState].out;
		
		// rising-edge detect using FSM
		if(PA3 == 0x00){
			delay(1);	// increase the delay if failing to detect changes
			if(PA3 == 0x08){
				input = 1;
			}
		}
		else{
			input = 0;
		}
		
    cState = toggle[cState].next[input];
		
}
	else if(param == 'f'){
		
		unsigned int input = 0;
    output = toggle[cState].out;
		
		// rising-edge detect using FSM
		if(PA3 == 0x08){
			delay(1);	// increase the delay if failing to detect changes
			if(PA3 == 0x00){
				input = 1;
			}
		}
		else{
			input = 0;
		}
		
    cState = toggle[cState].next[input];
		
	}
}

