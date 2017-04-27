#include "Piano.h"

// INPUT PortE(APB) base address: 0x40024000 (Datasheet pg. 657)
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x40024514))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))

/************************
 * Piano_Init
 ************************/
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
		//GPIO_PORTE_PUR_R        |=       0x0F;

    // GPIO Alternate function control
    GPIO_PORTE_AMSEL_R       =      0;
    GPIO_PORTE_AFSEL_R      &=      ~0x0F;
    GPIO_PORTE_PCTL_R       &=      ~0x0000FFFF;
}

/************************
 * Piano_In
 ************************/
// Input from piano key inputs
// Input: none
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){ unsigned long frq;

    if(BTN_INPUT == 0x00){
        frq = CUT_OFF;			//Lab13: CUT_OFF
    }

    if(BTN_INPUT == 0x01){
				frq = (C_NOTE -1);	//Lab13: C_NOTE
    }

    if(BTN_INPUT == 0x02){
        frq = (D_NOTE -1);	//Lab13: D_NOTE
    }

    if(BTN_INPUT == 0x04){
        frq = (E_NOTE -1);	//Lab13: E_NOTE
    }

    if(BTN_INPUT == 0x08){
        frq = (G_NOTE -1);	//Lab13: G_NOTE
    }

    return frq;
}
