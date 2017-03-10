
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

// Systick & NVIC Registers
#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

// Prototypes
void initPortF(void);
void delay(unsigned int param);
void SysTick_Pulse(unsigned long param);
void EnableInterrupts(void);
void WaitForInterrupt(void);

/************************
 * ISR
 ************************/
void SysTick_Handler(void){
  GPIO_PORTF_DATA_R ^= 0x04;
}


/************************
 * MAIN ROUTINE
 ************************/
void main(void) {
    // Initialization routine
    initPortF();
    SysTick_Pulse(16000);
    EnableInterrupts();

    while(1){
        WaitForInterrupt();
    }

}


/************************
 * SUB ROUTINES
 ************************/

// SysTick Interrupt Routine (pg. 132)
void SysTick_Pulse(unsigned long param){

    NVIC_ST_CTRL_R           =      0;
    NVIC_ST_RELOAD_R         =      param - 1;
    NVIC_ST_CURRENT_R        =      0;
    NVIC_SYS_PRI3_R         |=      0x50000000;
    NVIC_ST_CTRL_R          |=      0x07;


}


// PortF Output Initialization
void initPortF(void){    unsigned long volatile delay;

    // Port Clock Control
    SYSCTL_RCGC2_R          |=      0x00000020;
    delay  /*Wait Ready*/    =      SYSCTL_RCGC2_R;

    // GPIO Digital Control
    GPIO_PORTF_DEN_R        |=      0x0E;
    GPIO_PORTF_DIR_R        |=      0x0E;

    // GPIO Alternate function control
    GPIO_PORTF_AMSEL_R      &=      0;
    GPIO_PORTF_AFSEL_R      &=      ~0x0E;
    GPIO_PORTF_PCTL_R       &=      ~0x0000FFF0;
}

// Busy-wait delay (~1ms per param)
void delay(unsigned int param){ unsigned int i, j;

    for(j = 0; j < param; j++){
        for(i = 0; i < 800; i++){
            // do nothing
        }
    }
}
