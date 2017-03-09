/************************
 * ADDRESS DEFINITIONS
 ************************/

// System Control Legacy registers  (Datasheet pg. 234)
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// PortF Unlock registers           (Datasheet pg. 657)
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))

// PortF Configuration registers    (Datasheet pg. 657)
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_PDR_R        (*((volatile unsigned long *)0x40025514))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))

// PortF Bit-specific Address: (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
#define LED_B                   (*((volatile unsigned long *)0x40025010))
#define LED_R                   (*((volatile unsigned long *)0x40025008))
#define LED_G                   (*((volatile unsigned long *)0x40025020))
#define SW1                     (*((volatile unsigned long *)0x40025040))
#define SW2                     (*((volatile unsigned long *)0x40025004))

// Misc defines
#define ON                      0xFF
#define OFF                     0x00

// Prototypes
void initPortF_out(void);
void initPortF_in(void);
void delay(unsigned int param);
void blink_b(unsigned int param);
void blink_g(unsigned int param);
void blink_all(unsigned int param);

/************************
 * MAIN ROUTINE
 ************************/
void main(void) {

    // Initialization routine
    SYSCTL_RCGC2_R |= 0x00000020;       // Enable Port-F clock gate
    initPortF_out();                    // Initialize Port-F output
    initPortF_in();                     // Initialize Port-F input

    while(1){

        // SW1 & SW2
        if((SW1 == 0) && (SW2 == 0)){
            GPIO_PORTF_DATA_R &= ~0x0E;
        }

        // SW2
        else if(SW2 == 0){
            blink_b(300);
        }

        // SW1
        else if(SW1 == 0){
            blink_all(200);
        }

        // No SW
        else{
            GPIO_PORTF_DATA_R &= ~0x0E;
        }
    }

}

/************************
 * SUB ROUTINES
 ************************/

// Initialize PortF outputs
void initPortF_out(void){    unsigned long volatile delay;

    // GPIO Digital Control
    GPIO_PORTF_DEN_R        |=      0x0E;
    GPIO_PORTF_DIR_R        |=      0x0E;

    // GPIO Alternate function control
    GPIO_PORTF_AMSEL_R       =      0;
    GPIO_PORTF_AFSEL_R      &=      ~0x0E;
    GPIO_PORTF_PCTL_R       &=      ~0x0000FFF0;
}

// Initialize PortF inputs
void initPortF_in(void){

    //UNLOCK PF0
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

// Busy-wait delay (~1ms per param)
void delay(unsigned int param){ unsigned int i, j;

    for(j = 0; j < param; j++){
        for(i = 0; i < 800; i++){
            // do nothing
        }
    }
}

// Blink Blue LED
void blink_b(unsigned int param){
    GPIO_PORTF_DATA_R ^= 0x04;
    delay(param);
}

// Blink Green LED
void blink_g(unsigned int param){
    LED_G ^= ON;
    delay(param);
}

// Blink All LED
void blink_all(unsigned int param){
    GPIO_PORTF_DATA_R++;
    delay(param);
}
