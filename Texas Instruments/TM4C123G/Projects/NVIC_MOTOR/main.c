/************************
 * ADDRESS DEFINITIONS
 ************************/
// System Control Legacy base address
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// PortF(APB) base address: 0x40025000
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))

// PortF Interrupt Registers
#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))
#define NVIC_PRI7_R             (*((volatile unsigned long *)0xE000E41C))
#define GPIO_PORTF_IS_R         (*((volatile unsigned long *)0x40025404))
#define GPIO_PORTF_IBE_R        (*((volatile unsigned long *)0x40025408))
#define GPIO_PORTF_IEV_R        (*((volatile unsigned long *)0x4002540C))
#define GPIO_PORTF_IM_R         (*((volatile unsigned long *)0x40025410))
#define GPIO_PORTF_ICR_R        (*((volatile unsigned long *)0x4002541C))

// PortF GPIO Lock
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))

// Systick & NVIC Registers
#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

// PortF Bit-specific Address
#define SW1                     (*((volatile unsigned long *)0x40025040))
#define SW2                     (*((volatile unsigned long *)0x40025004))
#define LED_B                   (*((volatile unsigned long *)0x40025010))
#define LED_R                   (*((volatile unsigned long *)0x40025008))
#define LED_G                   (*((volatile unsigned long *)0x40025020))
#define PF2                     (*((volatile unsigned long *)0x40025010))

// Switch Definitions
#define ON                      0xFF
#define OFF                     0x00

void initPortF_in(void);
void initPortF_out(void);
void delay(unsigned int param);
void initNVIC(void);
void SysTick_Pulse(unsigned long param);
void EnableInterrupts(void);
void WaitForInterrupt(void);

// Parametric Settings (Global Variables)
unsigned long SysTickPeriod = 80000;     //(1ms/62.5us) - 1ms period @ 16MHz clock
unsigned long H = 40000;                 // SysTickPeriod/2 - initial HIGH wave state
unsigned long L = 40000;                 // SysTickPeriod/2 - initial LOW wave state
unsigned long AdjParam = 10000;          // PWM Adjustment Parameter (12.5% of SysTickPeriod)

/************************
 * ISR HANDLERS
 ************************/
// Edge Trigger (Background Thread)
void GPIOPortF_Handler(void){
    GPIO_PORTF_ICR_R = 0x11;    //clear PF4 and PF0 flags

    // Slow down
    if(SW2 == 0){
        if(H > (AdjParam*2)){   // <-- lower boundary limit
            H -= AdjParam;
            L += AdjParam;
        }
    }

    // Speed up
    if(SW1 == 0){
        if(L > (AdjParam*2)){   // <-- upper boundary limit
            H += AdjParam;
            L -= AdjParam;
        }
    }
}

// Periodic Handler (Background Thread)
void SysTick_Handler(void){

    /*
     * This will toggle PF2 on and off
     * at SysTickPeriod rate
     */

    if(PF2 == OFF){
        PF2 = ON;
        NVIC_ST_RELOAD_R = L - 1;
    }

    else{
        PF2 = OFF;
        NVIC_ST_RELOAD_R = H - 1;
    }
}


/************************
 * MAIN ROUTINE
 ************************/
void main(void) {
    // Initialization routine
    SYSCTL_RCGC2_R |= 0x00000020;                 // (a) Activate PortF Clock
    initPortF_in();
    initPortF_out();
    SysTick_Pulse(SysTickPeriod);
    initNVIC();
    EnableInterrupts();

    // Program routine
    while(1){
        // Blink Red LED (Foreground Thread)
        LED_G ^= ON;
        delay(500);
        //WaitForInterrupt();   //enter low power mode while doing nothing
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
    NVIC_SYS_PRI3_R         |=      0x50000000;     //     Interrupt Priority 2
    NVIC_ST_CTRL_R          |=      0x07;
}

// PortF Output Initialization
void initPortF_out(void){

    // GPIO Digital Control                         //     ************OUTPUT*************
    GPIO_PORTF_DEN_R        |=      0x0E;           // (b) Make PF1,2,3 Digital Pins
    GPIO_PORTF_DIR_R        |=      0x0E;           //     Make PF1,2,3 OUTPUT Pins

    // GPIO Alternate function control
    GPIO_PORTF_AMSEL_R      &=      0;              //     Disable Analog Mode
    GPIO_PORTF_AFSEL_R      &=      ~0x0E;          //     Disable Alternate Function on PF1,2,3
    GPIO_PORTF_PCTL_R       &=      ~0x0000FFF0;    //     Keep PF1,2,3 as GPIO
}

// PortF Input Initialization
void initPortF_in(void){

    // UNLOCK PF0                                   //     ************INPUT*************
    GPIO_PORTF_LOCK_R        =      0x4C4F434B;     //     Unlock PF0
    GPIO_PORTF_CR_R         |=      0x01;           //     Commit LOCK_R changes

    // GPIO Digital Control
    GPIO_PORTF_DEN_R        |=       0x11;          // (b) Make PF4 & PF0 Digital Pins
    GPIO_PORTF_DIR_R        &=      ~0x11;          //     Make PF4 & PF0 INPUT Pins
    GPIO_PORTF_PUR_R        |=       0x11;          //     Set a PULL-UP resister internal for PF4 & PF1

    // GPIO Alternate function control
    GPIO_PORTF_AMSEL_R       =      0;              //     Disable Analog Mode
    GPIO_PORTF_AFSEL_R      &=      ~0x11;          //     Disable Alternate Function on PF
    GPIO_PORTF_PCTL_R       &=      ~0x000F000F;    //     Keep PF4 & PF0 as GPIO
}

// Edge Triggered Interrupt (pg. 657)
void initNVIC(void){

    /* EDGE TRIGGER NOTE:
     * We Trigger on the falling
     * edge because SW1 & SW2 are set
     * to be a negative-logic switch
     */
                                                    //     ************INTERRUPT*************
    GPIO_PORTF_IS_R         &=      ~0x11;          // (c) Edge-sensitive
    GPIO_PORTF_IBE_R        &=      ~0x11;          //     Does not trigger on falling or rising
//  GPIO_PORTF_IBE_R        |=      0x11;           //     Does triggers on BOTH
    GPIO_PORTF_IEV_R        &=      ~0x11;          //     Triggers on FALLING edge
//  GPIO_PORTF_IEV_R        |=      0x11;           //     Triggers on RISING edge
    GPIO_PORTF_ICR_R        |=       0x0F;          // (d) CLEAR All Interrupt FLAGS
    GPIO_PORTF_IM_R         |=       0x11;          // (e) Enable interrupt mask (allows designated pins for ISR)

    //NVIC Configuration (pg. 132)
    NVIC_PRI7_R            |=        0x00A00000;    // (f) Interrupt Priority to 5
    NVIC_EN0_R             |=        0X40000000;    // (g) Enable Interrupt # 30 - PORTF
}

// Busy-wait delay (~1ms per param)
void delay(unsigned int param){ unsigned int i, j;

    for(j = 0; j < param; j++){
        for(i = 0; i < 800; i++){
            // do nothing
        }
    }
}
