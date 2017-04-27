// Piano.c
// Runs on LM4F120 or TM4C123,
// edX lab 13
// There are four keys in the piano

// Port E bits 3-0 have 4 piano keys

#include "Piano.h"

// INPUT PortE(APB) base address: 0x40024000 (Datasheet pg. 657)
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x40024514))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){  unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000010;
    delay = SYSCTL_RCGC2_R;

    // GPIO Digital Control
    GPIO_PORTE_DEN_R        |=       0x0F;
    GPIO_PORTE_DIR_R        &=      ~0x0F;
    GPIO_PORTE_PDR_R        |=       0x0F;

    // GPIO Alternate function control
    GPIO_PORTE_AMSEL_R       =      0;
    GPIO_PORTE_AFSEL_R      &=      ~0x0F;
    GPIO_PORTE_PCTL_R       &=      ~0x0000FFFF;
}

// **************Piano_In*********************
// Input from piano key inputs
// Input: none
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){ unsigned long frq;

    /* NOTE: This returns the reload value for systic
     * ([(1/f)/(1/system clock)]/total pulse) = Wave Reload value
     */

    if(PIANO_KEY == 0x00){
        frq = CUT_OFF;
    }

    if(PIANO_KEY == 0x01){
        frq = (C_NOTE);
    }

    if(PIANO_KEY == 0x02){
        frq = (D_NOTE);
    }

    if(PIANO_KEY == 0x04){
        frq = (E_NOTE);
    }

    if(PIANO_KEY == 0x08){
        frq = (G_NOTE);
    }

    return ((frq * 48)/32) - 1;
}
