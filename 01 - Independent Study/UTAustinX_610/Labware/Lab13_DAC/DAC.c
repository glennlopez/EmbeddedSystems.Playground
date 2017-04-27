#include "DAC.h"

// OUTPUT PortB(APB) base address: 0x40005000 (Datasheet pg. 657)
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
#define GPIO_PORTB_DR8R_R       (*((volatile unsigned long *)0x40005508))

/************************
 * DAC_Init
 ************************/
// Initialize 4-bit DAC
// Input: none
// Output: none
void DAC_Init(void){unsigned int delay;
    SYSCTL_RCGC2_R |= 0x00000002;
    delay = SYSCTL_RCGC2_R;

    // GPIO Digital Control
    GPIO_PORTB_DEN_R        |=      0x0F;
    GPIO_PORTB_DIR_R        |=      0x0F;
		GPIO_PORTB_DR8R_R 			|= 			0x0F;  

    // GPIO Alternate function control
    GPIO_PORTB_AMSEL_R      &=      ~0x0F;
    GPIO_PORTB_AFSEL_R      &=      ~0x0F;
    GPIO_PORTB_PCTL_R       &=      ~0x0000FFFF;
}

/************************
 * DAC_Out
 ************************/
// output to DAC
// Input: 4-bit data, 0 to 15
// Output: none
void DAC_Out(unsigned long data){
    DACOUT = data;
}
