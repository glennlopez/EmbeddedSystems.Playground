/************************
 * ADDRESS DEFINITIONS
 ************************/
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))           //0x3FC means 0011 1111 expressed as 4*2^b (bitspecific addressing)
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))           //gpio direction            - offset 0x400
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))           //gpio alt function         - offset 0x420
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))           //gpio pull-up select       - offset 0x510
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))           //gpio digital enable       - offset 0x51C
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))           //gpio analog mode select   - offset 0x528
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))           //gpio port control         - offset 0x52C
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))           //gpio portf lock register  - offset 0x520
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))           //gpio portf comit register - offset 0x524

#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))           //gpio clock gating (RCGC2) -   offset 0x108
#define SYSCTL_RCGC2_GPIOF      0x00000020                                          //Port F Clock Gating Control | _ _ _ F E D C B A (ports)


/************************
 * MAIN ROUTINE
 ************************/
int main(void) {
	
	return 0;
}

/************************
 * SUB ROUTINES
 ************************/
