/*
	gcc -o test trafficLight_fsm.c -lpigpio -lrt -lpthread

	3 inputs: 	2 car sensors, 1 pedestrian
	8 outputs:	3 west, 3 south, 2 pedestrian

	pedestrian sensor is push and hold - presense sense
	car sensors are also push and hold - presense sense

	west & south lights must both be red before walk light can be green
	walk light should be red while cars have green or yellow light

	PORT B: 6 Traffic lights (output)
	PORT F: 2 Pedestrian lights (output)
	PORT E: 3 Sensors (input)

	~ uC OUTPUTS ~
	South/North: 	PB0 - PB2
	West/East: 		PB3 - PB5

	Walk Light:		PF1
	Dont Walk:		PF3


	~ uC INPUTS ~
	Pedestrian Detector:		PE2
	South/North Detector:	PE1
	West/East Detector:		PE0

*/
#include <stdio.h>		//standard libs
#include <pigpio.h>		//raspi gpio libs

struct DataSet{
	void (*out)(void);			//function pointer used to reduce integration friction
	unsigned int delay;			//delay filler (change as per uC)
	unsigned int next[8];		//calculated by 2^(num of input bits)
}; typedef const struct DataSet FSM;

//state machine data definitions
#define GoW 0
#define WaW 1
#define GoS 2
#define WaS	3
#define GoP	4
#define FN1	5
#define FF1	6
#define FN2	7
#define FF2	8

//function prototype
void delay(unsigned int num);
void initPortRaspi(void);

//function (*pointer) prototype
void goW(); void waitW(); void goS(); void waitS();
void goP(); void fN1(); void fF1(); void fN2(); void fF2();

//state machine lookup table
FSM Lights[9] = {
//	output 	 delay	000	001	010	011	100	101	110	111
	{&goW, 		1, 	{GoW,	GoW, 	WaW, 	WaW, 	WaW, 	WaW, 	WaW, 	WaW	}},
	{&waitW, 	1, 	{GoS, GoS, 	GoS, 	GoS, 	GoP, 	GoP, 	GoP, 	GoS	}},
	{&goS, 		1, 	{GoS, WaS, 	GoS, 	WaS, 	WaS, 	WaS, 	WaS, 	WaS	}},
	{&waitS, 	1, 	{GoW,	GoW, 	GoW, 	GoW, 	GoP, 	GoP, 	GoP, 	GoP	}},
	{&goP, 		1, 	{GoP, FN1, 	FN1, 	FN1, 	GoP, 	FN1, 	FN1, 	FN1	}},
	{&fN1, 		1, 	{FF1,	FF1, 	FF1, 	FF1, 	FF1, 	FF1, 	FF1, 	FF1	}},
	{&fF1, 		1, 	{FN2, FN2, 	FN2, 	FN2, 	FN2, 	FN2, 	FN2, 	FN2	}},
	{&fN2, 		1, 	{FF2, FF2, 	FF2, 	FF2, 	FF2, 	FF2, 	FF2,	FF2	}},
	{&fF2, 		1, 	{GoP,	GoW, 	GoS, 	GoW, 	GoP, 	GoW, 	GoS, 	GoW	}}
};


/************
	MAIN
************/
int main(){ unsigned int cState, input;

	//raspi SETUP
	if (gpioInitialise() < 0){
		fprintf(stderr, "pigpio initialisation failed\n");
		return 1;
	}
	initPortRaspi();

	//fsm SETUP
	cState = 0;

	//fsm loop
	while(1){

		//output
		Lights[cState].out();

		//input
		printf("Input: ");
		scanf("%i", &input);

		//change state based on input and current state
		cState = Lights[cState].next[input];
	}




	//raspi cleanup routine
   gpioTerminate();
	printf("\n");
	return 0;
}




/*******************
	FUNCTIONS
********************/
void delay(unsigned int num){unsigned int i;
	for(i = 0; i < num; i++){
		gpioDelay(1000);	//raspi delay in 1000 = 1ms
	}
}

//Raspbery pi port initialization
void initPortRaspi(void){

	gpioSetMode(16, 				PI_INPUT);		// 0 - West Sensor
	gpioSetMode(20, 				PI_INPUT);		// 1 - South Sensor
	gpioSetMode(21, 				PI_INPUT);		// 2 - Pedestrian Sensor

	gpioSetMode(9, 	/*MISO*/	PI_OUTPUT);		// 0 - South GREEN
	gpioSetMode(11, 	/*SCLK*/	PI_OUTPUT);		// 1 - South YELLOW
	gpioSetMode(0, 	/*ID_SD*/PI_OUTPUT);		// 2 - South RED

	gpioSetMode(5, 				PI_OUTPUT);		// 3 - West GREEN
	gpioSetMode(6, 				PI_OUTPUT);		// 4 - West YELLOW
	gpioSetMode(13, 				PI_OUTPUT);		// 5 - West RED

	gpioSetMode(19, 				PI_OUTPUT);		// 6 - Pedestrian RED
	gpioSetMode(26, 				PI_OUTPUT);		// 7 - Pedestrian GREEN
}


/*******************
	FSM FUNCTIONS
********************/
void goW(){	//PortB: 0x0C PortF:0x01
	printf("goW\n");

	//raspi gpio 001 100
	gpioWrite(9, 	0);		// 0 - South GREEN
	gpioWrite(11, 	0);		// 1 - South YELLOW
	gpioWrite(0, 	1);		// 2 - South RED

	gpioWrite(5, 	1);		// 3 - West GREEN
	gpioWrite(6, 	0);		// 4 - West YELLOW
	gpioWrite(13, 	0);		// 5 - West RED

	gpioWrite(19, 	1);		// 6 - Pedestrian RED
	gpioWrite(26, 	0);		// 7 - Pedestrian GREEN
}
void waitW(){	//PortB: 0x14 PortF:0x01
	printf("waitW\n");

	//raspi gpio 010 100
	gpioWrite(9, 	0);		// 0 - South GREEN
	gpioWrite(11, 	0);		// 1 - South YELLOW
	gpioWrite(0, 	1);		// 2 - South RED

	gpioWrite(5, 	0);		// 3 - West GREEN
	gpioWrite(6, 	1);		// 4 - West YELLOW
	gpioWrite(13, 	0);		// 5 - West RED

	gpioWrite(19, 	1);		// 6 - Pedestrian RED
	gpioWrite(26, 	0);		// 7 - Pedestrian GREEN
}
void goS(){	//PortB: 0x21 PortF:0x01
	printf("goS\n");

	//raspi gpio 100 001
	gpioWrite(9, 	1);		// 0 - South GREEN
	gpioWrite(11, 	0);		// 1 - South YELLOW
	gpioWrite(0, 	0);		// 2 - South RED

	gpioWrite(5, 	0);		// 3 - West GREEN
	gpioWrite(6, 	0);		// 4 - West YELLOW
	gpioWrite(13, 	1);		// 5 - West RED

	gpioWrite(19, 	1);		// 6 - Pedestrian RED
	gpioWrite(26, 	0);		// 7 - Pedestrian GREEN
}
void waitS(){	//PortB: 0x22 PortF:0x01
	printf("waitS\n");

	//raspi gpio 100 010
	gpioWrite(9, 	0);		// 0 - South GREEN
	gpioWrite(11, 	1);		// 1 - South YELLOW
	gpioWrite(0, 	0);		// 2 - South RED

	gpioWrite(5, 	0);		// 3 - West GREEN
	gpioWrite(6, 	0);		// 4 - West YELLOW
	gpioWrite(13, 	1);		// 5 - West RED

	gpioWrite(19, 	1);		// 6 - Pedestrian RED
	gpioWrite(26, 	0);		// 7 - Pedestrian GREEN
}
void goP(){	//PortB: 0x24	PortF:0x08
	printf("goP\n");

	//raspi gpio 100 100
	gpioWrite(9, 	0);		// 0 - South GREEN
	gpioWrite(11, 	0);		// 1 - South YELLOW
	gpioWrite(0, 	1);		// 2 - South RED

	gpioWrite(5, 	0);		// 3 - West GREEN
	gpioWrite(6, 	0);		// 4 - West YELLOW
	gpioWrite(13, 	1);		// 5 - West RED

	gpioWrite(19, 	0);		// 6 - Pedestrian RED
	gpioWrite(26, 	1);		// 7 - Pedestrian GREEN
}
void fN1(){	//PortB: 0x24	PortF:0x02
	printf("fN1\n");

	//raspi gpio 100 100
	gpioWrite(9, 	0);		// 0 - South GREEN
	gpioWrite(11, 	0);		// 1 - South YELLOW
	gpioWrite(0, 	1);		// 2 - South RED

	gpioWrite(5, 	0);		// 3 - West GREEN
	gpioWrite(6, 	0);		// 4 - West YELLOW
	gpioWrite(13, 	1);		// 5 - West RED

	gpioWrite(19, 	1);		// 6 - Pedestrian RED
	gpioWrite(26, 	0);		// 7 - Pedestrian GREEN
}
void fF1(){	//PortB: 0x24	PortF:0x00
	printf("fF1\n");

	//raspi gpio 100 100
	gpioWrite(9, 	0);		// 0 - South GREEN
	gpioWrite(11, 	0);		// 1 - South YELLOW
	gpioWrite(0, 	1);		// 2 - South RED

	gpioWrite(5, 	0);		// 3 - West GREEN
	gpioWrite(6, 	0);		// 4 - West YELLOW
	gpioWrite(13, 	1);		// 5 - West RED

	gpioWrite(19, 	0);		// 6 - Pedestrian RED
	gpioWrite(26, 	0);		// 7 - Pedestrian GREEN
}
void fN2(){	//PortB: 0x24	PortF:0x02
	printf("fN2\n");

	//raspi gpio 100 100
	gpioWrite(9, 	0);		// 0 - South GREEN
	gpioWrite(11, 	0);		// 1 - South YELLOW
	gpioWrite(0, 	1);		// 2 - South RED

	gpioWrite(5, 	0);		// 3 - West GREEN
	gpioWrite(6, 	0);		// 4 - West YELLOW
	gpioWrite(13, 	1);		// 5 - West RED

	gpioWrite(19, 	1);		// 6 - Pedestrian RED
	gpioWrite(26, 	0);		// 7 - Pedestrian GREEN
}
void fF2(){	//PortB: 0x24	PortF:0x00
	printf("fF2\n");

	//raspi gpio 100 100
	gpioWrite(9, 	0);		// 0 - South GREEN
	gpioWrite(11, 	0);		// 1 - South YELLOW
	gpioWrite(0, 	1);		// 2 - South RED

	gpioWrite(5, 	0);		// 3 - West GREEN
	gpioWrite(6, 	0);		// 4 - West YELLOW
	gpioWrite(13, 	1);		// 5 - West RED

	gpioWrite(19, 	0);		// 6 - Pedestrian RED
	gpioWrite(26, 	0);		// 7 - Pedestrian GREEN
}
