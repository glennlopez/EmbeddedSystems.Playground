/************************
 * ADDRESS DEFINITIONS
 ************************/
// System Control Legacy base address: 0x400F.E000 (Datasheet pg. 234)
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// PortF(APB) base address: 0x40025000 (Datasheet pg. 657)
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))

// PortF Interrupt Registers
#define GPIO_PORTF_IS_R         (*((volatile unsigned long *)0x40025404))
#define GPIO_PORTF_IBE_R        (*((volatile unsigned long *)0x40025408))
#define GPIO_PORTF_IEV_R        (*((volatile unsigned long *)0x4002540C))
#define GPIO_PORTF_IM_R         (*((volatile unsigned long *)0x40025410))
#define GPIO_PORTF_RIS_R        (*((volatile unsigned long *)0x40025414))
#define GPIO_PORTF_ICR_R        (*((volatile unsigned long *)0x4002541C))

// PortF GPIO Lock
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))

// PortF Bit-specific Address
#define SW1                     (*((volatile unsigned long *)0x40025040))
#define SW2                     (*((volatile unsigned long *)0x40025004))

/************************
 * ISR HANDLERS
 ************************/
// GPIO PF4
void GPIOPortF_Handler(void){

}

/************************
 * MAIN ROUTINE
 ************************/

// Prototypes
void initPortF_in(void);
void initPortF_out(void);
void delay(unsigned int param);
void initNVIC(void);
void EnableInterrupts(void);

void main(void) {
    // Initialization routine
    SYSCTL_RCGC2_R |= 0x00000020;
    initPortF_in();
    initPortF_out();
    initNVIC();
    EnableInterrupts();

    // Program routine
    while(1){
        if(SW1 == 0x00){
            GPIO_PORTF_DATA_R ^= 0x08;
            delay(200);
        }
    }
}


/************************
 * SUB ROUTINES
 ************************/

// PortF Output Initialization
void initPortF_out(void){

    // GPIO Digital Control
    GPIO_PORTF_DEN_R        |=      0x0E;
    GPIO_PORTF_DIR_R        |=      0x0E;

    // GPIO Alternate function control
    GPIO_PORTF_AMSEL_R      &=      0;
    GPIO_PORTF_AFSEL_R      &=      ~0x0E;
    GPIO_PORTF_PCTL_R       &=      ~0x0000FFF0;
}

// PortF Input Initialization
void initPortF_in(void){

    // UNLOCK PF0
    GPIO_PORTF_LOCK_R        =      0x4C4F434B;
    GPIO_PORTF_CR_R         |=      0x01;

    // GPIO Digital Control
    GPIO_PORTF_DEN_R        |=      0x11;
    GPIO_PORTF_DIR_R        &=      ~0x11;
    GPIO_PORTF_PUR_R        |=       0x11;

    // GPIO Alternate function control
    GPIO_PORTF_AMSEL_R       =      0;
    GPIO_PORTF_AFSEL_R      &=      ~0x11;
    GPIO_PORTF_PCTL_R       &=      ~0x000F000F;
}

// Edge Triggered Interrupt (pg. 657)
void initNVIC(void){

    GPIO_PORTF_IS_R         &=      ~0x10;
    GPIO_PORTF_IBE_R        &=      ~0x10;
    GPIO_PORTF_IEV_R        &=      ~0x10;
    //GPIO_PORTF_IM_R         &=      ~0x00;
    //GPIO_PORTF_RIS_R        &=      ~0x00;
    //GPIO_PORTF_ICR_R        &=      ~0x00;

}

// Busy-wait delay (~1ms per param)
void delay(unsigned int param){ unsigned int i, j;

    for(j = 0; j < param; j++){
        for(i = 0; i < 800; i++){
            // do nothing
        }
    }
}
