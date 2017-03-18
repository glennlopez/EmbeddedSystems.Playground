/*
    TuningFork.c Lab 12
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

*/

//#include "TExaS.h"
//#include "..//tm4c123gh6pm.h"


/************************
 * ADDRESS DEFINITIONS
 ************************/

// System Control Legacy base address
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// PortA (APB) base address: 0x40004000
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)3FC))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)51C))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)400))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)528))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)420))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)52C))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)510))

// PortA Interrupt Registers
//#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))
//#define NVIC_PRI7_R             (*((volatile unsigned long *)0xE000E41C))
#define GPIO_PORTA_IS_R         (*((volatile unsigned long *)404))
#define GPIO_PORTA_IBE_R        (*((volatile unsigned long *)408))
#define GPIO_PORTA_IEV_R        (*((volatile unsigned long *)40C))
#define GPIO_PORTA_IM_R         (*((volatile unsigned long *)410))
#define GPIO_PORTA_ICR_R        (*((volatile unsigned long *)41C))

// Systick & NVIC Registers
//#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

// PortA Bit-specific Address
#define PF2                     (*((volatile unsigned long *)0x40004000))
#define PF3                     (*((volatile unsigned long *)0x40004000))



// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode

/************************
 * ISR HANDLERS
 ************************/


// called at 880 Hz
void SysTick_Handler(void){

}



/************************
 * MAIN ROUTINE
 ************************/

int main(void){// activate grader and set system clock to 80 MHz

  // Initialization routine
  //TExaS_Init(SW_PIN_PA3, HEADPHONE_PIN_PA2,ScopeOn);
  Sound_Init();
  EnableInterrupts();   // enable after all initialization are done

  // Program routine
  while(1){

  }
}


/************************
 * SUB ROUTINES
 ************************/

// input from PA3, output from PA2, SysTick interrupts
void Sound_Init(void){

}
