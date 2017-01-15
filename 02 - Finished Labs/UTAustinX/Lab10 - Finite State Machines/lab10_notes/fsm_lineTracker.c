#include <stdio.h>
/*
	This is a simple prototype for a line tracker
	finite state machine to be implemented on a microcontroller
*/

struct dataBank{
	void (*out)(void);		//output a function
	unsigned int delay;		//delay param
	unsigned int next[4];	//4 possible next states
}; typedef const struct dataBank FSM;

//state definitions
unsigned int cState;	//current state
#define CEN 0			//center state
#define LEF 1			//left state
#define RIG 2			//right state

//function prototypes
void Center(void);
void Left(void);
void Right(void);

FSM lineTracker[3] = {	//change state based on current state and input
//(*output)		delay		{next states}
	{&Center,	1,			{RIG,	LEF,	RIG,	CEN}},
	{&Left,		1,			{LEF,	CEN,	RIG,	CEN}},
	{&Right,		1,			{RIG,	LEF,	CEN,	CEN}}
	//	inputs-->			00		01		10		11
	//	in dec-->			0		1		2		3
};


/**************
	MAIN
**************/
int main(){
	cState = CEN;	//set initial state to CENTER
	int input = 0;

	while(1){
		//output
		(lineTracker[cState].out)();

		//get input
		printf("L-Sensor | R-Sensor\n");
		printf("[0]-00 [1]-01 [2]-10 [3]-11: ");
		scanf("%i", &input);

		//change cState to next state based on input and current state
		cState = lineTracker[cState].next[input];
	}

	printf("\n");	//newline
	return 0;
}





/**************
	FUNCTION
**************/
void Center(void){
	printf("Running: Both wheels (go fwd)\n");
}
void Left(void){
	printf("Running: Left wheel only (turn right)\n");
}
void Right(void){
	printf("Running: Right wheel only (turn left)\n");
}
