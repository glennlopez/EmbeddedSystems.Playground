/*------------------------------------------------------------------------------
In this BTB (Back to Basics), we'll practice using the 'switch case' statement 
	- http://www.programiz.com/c-programming/c-switch-case-statement
	- http://arduino.cc/en/Reference/SwitchCase 

Use the "layout1_led.fzz" breadboard layout for this refresher!
-------------------------------------------------------------------------------*/

//outputs													
 const int greenLed = 13;
 const int redLed = 12;
 const int yellowLed = 11;

//inputs
 const int buttonA = 2;
 int buttonStateA = 0;
 
 const int buttonB = 3;
 int buttonStateB = 0;

//global variables
int numericState = 0;

void setup(){	
	//output setup
	pinMode(greenLed, OUTPUT);
	pinMode(redLed, OUTPUT);
	pinMode(yellowLed, OUTPUT);

	//input setup
	pinMode(buttonA, INPUT);		
	pinMode(buttonB, INPUT);
}

void loop(){
	//read the button states first!
	buttonStateA = digitalRead(buttonA);
	buttonStateB = digitalRead(buttonB);

	//assign intiger values to button states (numericState)
	if(buttonStateA && buttonStateB == LOW){
		numericState = 0;
	}
	if(buttonStateA == HIGH){
		numericState = 1;	    
	}
	if(buttonStateB == HIGH){
	    numericState = 2;
	}
	if(buttonStateA && buttonStateB == HIGH){
	    numericState = 3;
	}

	//assign tasks to diffrent cases
	switch(numericState){
		case 1:
			digitalWrite(redLed, HIGH);
			digitalWrite(yellowLed, LOW);
			digitalWrite(greenLed, LOW);
			numericState = 0; // sets it back to 0 - HOLD BTN TO LIGHT
			break;

		case 2:
			digitalWrite(redLed, LOW);
			digitalWrite(yellowLed, HIGH);
			digitalWrite(greenLed, LOW);
			numericState = 0; // sets it back to 0 - HOLD BTN TO LIGHT
			break;

		case 3:
			digitalWrite(redLed, LOW);
			digitalWrite(yellowLed, LOW);
			digitalWrite(greenLed, HIGH);
			numericState = 0; // sets it back to 0 - HOLD BTN TO LIGHT
			break;

		default: //if condition is not met, do this
			digitalWrite(redLed, LOW);
			digitalWrite(yellowLed, LOW);
			digitalWrite(greenLed, LOW);
	}
}

