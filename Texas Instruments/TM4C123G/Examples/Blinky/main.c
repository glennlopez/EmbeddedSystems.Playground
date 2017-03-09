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

// PortF Bit-specific Address: (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
#define LED_B                   (*((volatile unsigned long *)0x40025010))
#define LED_R                   (*((volatile unsigned long *)0x40025008))
#define LED_G                   (*((volatile unsigned long *)0x40025020))

#define ON                      0xFF
#define OFF                     0x00

// Prototypes
void initPortF(void);
void delay(unsigned int param);
void blink_b(unsigned int param);
void blink_g(unsigned int param);

/************************
 * MAIN ROUTINE
 ************************/
void main(void) {
    initPortF();                     // Initialize PortF

    while(1){
        GPIO_PORTF_DATA_R ^= 0x02;
        delay(100);
    }

}

/************************
 * SUB ROUTINES
 ************************/

// Initialize PortF as Digital
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
    while(1){
          GPIO_PORTF_DATA_R ^= 0x04;   // Toggle LED on/off
          delay(param);                  // Up/Down time
      }
}

//Blink Green LED
void blink_g(unsigned int param){
    while(1){
        LED_G ^= ON;
        delay(param);
    }
}
