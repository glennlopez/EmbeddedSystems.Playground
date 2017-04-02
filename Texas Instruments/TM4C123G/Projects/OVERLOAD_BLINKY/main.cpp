
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


/************************
 * Pre-Proccess routines
 ************************/
// Prototypes
void initPortF(void);
void delay(unsigned int param);


/************************
 * MAIN ROUTINE
 ************************/
void main(void) {
    initPortF();                     // Initialize PortF

    while(1){
        GPIO_PORTF_DATA_R ^= 0x04;   // Toggle LED on/off
        delay(100);                  // Up/Down time
    }

}

/************************
 * SUB ROUTINES
 ************************/
void initPortF(void){    unsigned long volatile delay;

    // Port Clock Control
    SYSCTL_RCGC2_R          |=      0x00000020;
    delay  /*Wait Ready*/    =      SYSCTL_RCGC2_R;

    // GPIO Digital Control
    GPIO_PORTF_DEN_R        |=      0x0E;
    GPIO_PORTF_DIR_R        |=      0x0E;

    // GPIO Alternate function control
    GPIO_PORTF_AMSEL_R      &=      ~0x0E;
    GPIO_PORTF_AFSEL_R      &=      ~0x0E;
    GPIO_PORTF_PCTL_R       &=      ~0x0000FFF0;
}

// Busy-wait delay
void delay(unsigned int param){ unsigned int i, j;

    for(j = 0; j < param; j++){
        for(i = 0; i < 15; i++){
            // do nothing
        }
    }
}
