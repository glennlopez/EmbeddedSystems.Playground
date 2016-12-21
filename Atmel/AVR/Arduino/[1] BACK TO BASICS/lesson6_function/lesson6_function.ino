/*------------------------------------------------------------------------------
In this BTB (Back to Basics), we'll practice using functions 
	- http://www.programiz.com/c-programming/c-functions
	- http://playground.arduino.cc/Code/Function 

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

	//pressing buttonA will cycle led then blink all after cycle
	if(buttonStateA == HIGH){
		delay(500);
		redGreen();
		blinkAll();
		blinkAll();
	}

	//pressing buttonB will
	if(buttonStateB == HIGH){
		digitalWrite(yellowLed, HIGH);
		delay(500);
		blinkAll();
		blinkAll();
	}

	//no buttons pressed
	if(buttonStateA && buttonStateB == LOW){
		ledOff();
		delay(500);
	}
}





/*
 * FUNCTIONS HELP REDUCE REDUNDUNCY IN CODE IF A PIECE 
 * OF CODE IS TO BE EXCECUTED MORE THAN ONCE. IT ALSO HELPS
 * DE-BUGGING - IF ONE FUNCTION IS NOT "FUNCTIONING" PROPERLY
 * YOU ONLY NEED TO EDIT THE CODE ONCE 
 */

//function that turns on all LEDs
void ledOn(){
	digitalWrite(redLed, HIGH);
	digitalWrite(yellowLed, HIGH);
	digitalWrite(greenLed, HIGH);
}

//function that turns off all LEDs
void ledOff(){
	digitalWrite(redLed, LOW);
	digitalWrite(yellowLed, LOW);
	digitalWrite(greenLed, LOW);
}

//function for blinking all LEDs
void blinkAll(){
	ledOn();
	delay(300);
	ledOff();
	delay(300);
}

//function for red and gree on
void redGreen(){
	digitalWrite(redLed, HIGH);
	digitalWrite(greenLed, HIGH);
	digitalWrite(yellowLed, LOW);
	delay(500);
}