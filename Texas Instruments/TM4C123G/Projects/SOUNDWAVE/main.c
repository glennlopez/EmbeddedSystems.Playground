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
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))

// PortA Interrupt Registers
//#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))
//#define NVIC_PRI7_R             (*((volatile unsigned long *)0xE000E41C))
#define GPIO_PORTA_IS_R         (*((volatile unsigned long *)0x40004404))
#define GPIO_PORTA_IBE_R        (*((volatile unsigned long *)0x40004408))
#define GPIO_PORTA_IEV_R        (*((volatile unsigned long *)0x4000440C))
#define GPIO_PORTA_IM_R         (*((volatile unsigned long *)0x40004410))
#define GPIO_PORTA_ICR_R        (*((volatile unsigned long *)0x4000441C))

// Systick & NVIC Registers
//#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

// PortA Bit-specific Address: (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
#define PF2                     (*((volatile unsigned long *)0x40004010))
#define PF3                     (*((volatile unsigned long *)0x40004020))



// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
void initPortA_out(void);

/************************
 * ISR HANDLERS
 ************************/


// called at 880 Hz
void SysTick_Handler(void){

}



/************************
 * MAIN ROUTINE
 ************************/

int main(void){//TExaS_Init(SW_PIN_PA3, HEADPHONE_PIN_PA2,ScopeOn);

  // Initialization routine
  initPortA_out();      // Initialize output
  EnableInterrupts();   // enable after all initialization are done

  // Program routine
  while(1){

  }
}


/************************
 * SUB ROUTINES
 ************************/

// PortA Output Initialization
void initPortA_out(void){

    // GPIO Digital Control                           //************OUTPUT*************
    //GPIO_PORTA_DEN_R        |=      0x0E;           // (b) Make PA Digital Pins
    //GPIO_PORTA_DIR_R        |=      0x0E;           //     Make PA OUTPUT Pins

    // GPIO Alternate function control
    //GPIO_PORTA_AMSEL_R      &=      0;              //     Disable Analog Mode
    //GPIO_PORTA_AFSEL_R      &=      ~0x0E;          //     Disable Alternate Function on PA
    //GPIO_PORTA_PCTL_R       &=      ~0x0000FFF0;    //     Keep PA as GPIO
}



// input from PA3, output from PA2, SysTick interrupts
void Sound_Init(void){

}
