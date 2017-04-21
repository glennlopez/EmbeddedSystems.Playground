

/************************
 * ADDRESS DEFINITIONS
 ************************/
// System Control Legacy base address: 0x400F.E000 (Datasheet pg. 234)
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// PortB(APB) base address: 0x40005000 (Datasheet pg. 657)
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

// NVIC Registers
//#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))  // IRQ 0 to 31 Set Enable Register
//#define NVIC_PRI7_R             (*((volatile unsigned long *)0xE000E41C))  // IRQ 28 to 31 Priority Register


// Systick & NVIC Registers (pg 132)
#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

// GPIO Port Interrupt Registers (pg 657)
//#define GPIO_PORTF_IS_R         (*((volatile unsigned long *)0x40025404))
//#define GPIO_PORTF_IBE_R        (*((volatile unsigned long *)0x40025408))
//#define GPIO_PORTF_IEV_R        (*((volatile unsigned long *)0x4002540C))
//#define GPIO_PORTF_IM_R         (*((volatile unsigned long *)0x40025410))
//#define GPIO_PORTF_RIS_R        (*((volatile unsigned long *)0x40025414))
//#define GPIO_PORTF_ICR_R        (*((volatile unsigned long *)0x4002541C))


// DAC Bit-specific address: (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
#define DACOUT                  (*((volatile unsigned long *)0x4000503C))



/************************
 * Pre-Proccess routines
 ************************/
// Prototypes
void initPortBOut(void);
void delay(unsigned int param);
void SysTick_Init(unsigned long period);

// Global Variables
unsigned int rampDown = 0;
//DACOUT = 0x00;



/************************
 * ISR HANDLERS
 ************************/
void SysTick_Handler(void){

    if(rampDown == 0){
        DACOUT++;
        if(DACOUT == 0x0F){
            rampDown = 1;
        }
    }

    if(rampDown == 1){
       DACOUT--;
       if(DACOUT == 0x00){
           rampDown = 0;
       }
   }


    //DACOUT++;

}


/************************
 * MAIN ROUTINE
 ************************/
void main(void) {
    // Initialization routine
    initPortBOut();
    SysTick_Init(800000);
    EnableInterrupts();


    // Loop routine
    while(1){
        //do nothing
    }

}



/************************
 * SUB ROUTINES
 ************************/

// SysTick Interrupt Routine (pg. 132)
void SysTick_Init(unsigned long period){
  // Setup Routine
  NVIC_ST_CTRL_R = 0;         // (a) disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// (b) reload value
  NVIC_ST_CURRENT_R = 0;      // (c) any write to current clears it

  // (d) priority 2 - PRI < 2 can interrupt this routine
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000;
  NVIC_ST_CTRL_R = 0x07;      // (e) enable SysTick with core clock and interrupts
}

//PortB Output Initiazation Routine
void initPortBOut(void){    unsigned long volatile delay;

    // Port Clock Control
    SYSCTL_RCGC2_R          |=      0x00000002;
    delay  /*Wait Ready*/    =      SYSCTL_RCGC2_R;

    // GPIO Digital Control
    GPIO_PORTB_DEN_R        |=      0x0F;
    GPIO_PORTB_DIR_R        |=      0x0F;

    // GPIO Alternate function control
    GPIO_PORTB_AMSEL_R      &=      ~0x0F;
    GPIO_PORTB_AFSEL_R      &=      ~0x0F;
    GPIO_PORTB_PCTL_R       &=      ~0x0000FFFF;
}

// Busy-wait delay
void delay(unsigned int param){ unsigned int i, j;

    for(j = 0; j < param; j++){
        for(i = 0; i < 15; i++){
            // do nothing
        }
    }
}
