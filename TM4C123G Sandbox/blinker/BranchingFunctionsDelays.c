//Blinker - uC hello World: by glennlopez

//TM4C123G REGISTRY DEFINITIONS
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

// Pin Offset = 	200	100	80		40		20		10		8		4
//	Pin Number =	P7		P6		P5		P4		P3		P2		P1		P0


//MACRO DEFINITIONS
#define SW1		(*((volatile unsigned long*)0x40025040)) 	//PF4 input
#define SW2		(*((volatile unsigned long*)0x40025004))	//PF0 input

#define RED		(*((volatile unsigned long*)0x40025008))	//PF1 red 0x02
#define BLUE	(*((volatile unsigned long*)0x40025010))	//PF2 blue 0x04
#define GREEN	(*((volatile unsigned long*)0x40025020))	//PF3	greed 0x08

#define DATA_DIRECTION 		0x0D;		//Output: PF1, PF2, PF3 | Input: PF4, PF0
#define PULL_UP_RESISTORS 	0x11;		//Pull-up resistors for PF4, PF0 (siwtches)
#define INITIAL_PIN_STATE 	0x04;		//Set the initial output pins states



// prototypes
void PortF_Init();									//Init portF prototype
void second_delay(unsigned short second);		//delay


int main(void){

	//pre-loop function initializations
	PortF_Init();	//Initialize Port F

	while(1){
		GREEN = 0x08;	//onboard green LED ON
	}



}




//** FUNCTIONS **//
void PortF_Init(){
	volatile unsigned long dumy_delay;

	SYSCTL_RCGC2_R = SYSCTL_RCGC2_R | 0x00000020;	//Enable PortF Clock
	dumy_delay = SYSCTL_RCGC2_R;							//Catch up to clock before doing aything
	GPIO_PORTF_AMSEL_R 	= 0x00;							//Analog Mode select register
	GPIO_PORTF_AFSEL_R 	= 0x00;							//Alternative function
	GPIO_PORTF_PCTL_R 	= 0x00000000;					//Alternative fucntion control
	GPIO_PORTF_DEN_R		= 0x1F;							//PortF Digital Enable register
	GPIO_PORTF_DIR_R		= DATA_DIRECTION;				//PortF pin directions
	GPIO_PORTF_PUR_R		= PULL_UP_RESISTORS;			//PortF pull up resistors
	GPIO_PORTF_DATA_R		= INITIAL_PIN_STATE;			//PORTF INITIAL STATE
}

void second_delay(unsigned short second){
	unsigned long i, j, x;

	for(x = second; x > 0; x--){
		for(i = 1600; i > 0; i--){
			for(j = 1000; j > 0; j--);
		}
	}

}
