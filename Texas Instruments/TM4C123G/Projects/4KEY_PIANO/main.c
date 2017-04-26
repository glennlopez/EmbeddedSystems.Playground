

/************************
 * PREPROCESSOR DIRECTIVES
 ************************/

 // Includes
#include "PLL.h"
#include "DAC.h"

// System Control Legacy base address: 0x400F.E000 (Datasheet pg. 234)
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// INPUT PortE(APB) base address: 0x40024000 (Datasheet pg. 657)
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x40024514))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))

// Systick & NVIC Registers (pg 132)
#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

// INPUT Bit-specific Address: (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
#define G_KEY /* E3: (783.991) */ (*((volatile unsigned long *)0x40024020))
#define E_KEY /* E2: (659.255) */ (*((volatile unsigned long *)0x40024010))
#define D_KEY /* E1: (587.330) */ (*((volatile unsigned long *)0x40024008))
#define C_KEY /* E0: (523.251) */ (*((volatile unsigned long *)0x40024004))


/************************
 * PROTOTYPES & GLOBAL
 ************************/

// Prototypes
//void initPortBOut(void);
void initPortEIn(void);
void toneCutOff(void);
void SysTick_Init(unsigned long period);
//void DACOut(unsigned char param);
void EnableInterrupts(void);
void DisableInterrupts(void);

// Globals variables
unsigned char index = 0;
const unsigned char SineWave[48] = {
     0,0,1,1,1,2,2,3,4,5,6,7,8,9,10,11,12,13,13,14,14,14,15,15,
     15,15,14,14,14,13,13,12,11,10,9,8,7,6,5,4,3,2,2,1,1,1,0,0
};


/************************
 * ISR HANDLERS
 ************************/
void SysTick_Handler(void){

    toneCutOff();

    if(index < 49){
        index++;
        if(index == 48){
            index = 0;
        }
    }
    DAC_Out(SineWave[index]);

}


/************************
 * MAIN ROUTINE
 ************************/
void main(void) {

    // Initialization routine
    SYSCTL_RCGC2_R |= 0x00000012;
    DAC_Init();
    initPortEIn();
    SysTick_Init(2126);
    PLL_Init();

    // Loop routine
    while(1){

        /* NOTE:
         * ([(1/f)/(1/system clock)]/total pulse) = Wave Reload value
         */

        if(C_KEY == 0x01){
            EnableInterrupts();
            NVIC_ST_RELOAD_R = (3186 -1);
        }

        if(D_KEY == 0x02){
            EnableInterrupts();
            NVIC_ST_RELOAD_R = (2839 -1);
        }

        if(E_KEY == 0x04){
            EnableInterrupts();
            NVIC_ST_RELOAD_R = (2529 -1);
        }

        if(G_KEY == 0x08){
            EnableInterrupts();
            NVIC_ST_RELOAD_R = (2126 -1);
        }

    }

}



/************************
 * SUB ROUTINES
 ************************/

// SysTick Interrupt Routine (pg. 132)
void SysTick_Init(unsigned long period){

  NVIC_ST_CTRL_R = 0;
  NVIC_ST_RELOAD_R = period-1;
  NVIC_ST_CURRENT_R = 0;

  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000;
  NVIC_ST_CTRL_R = 0x07;
}

void initPortEIn(void){

    // GPIO Digital Control
    GPIO_PORTE_DEN_R        |=       0x0F;
    GPIO_PORTE_DIR_R        &=      ~0x0F;
    GPIO_PORTE_PDR_R        |=       0x0F;

    // GPIO Alternate function control
    GPIO_PORTE_AMSEL_R       =      0;
    GPIO_PORTE_AFSEL_R      &=      ~0x0F;
    GPIO_PORTE_PCTL_R       &=      ~0x0000FFFF;
}

// Tone cutoff
void toneCutOff(void){

    if(GPIO_PORTE_DATA_R == 0x00){
        DisableInterrupts();
    }

}
