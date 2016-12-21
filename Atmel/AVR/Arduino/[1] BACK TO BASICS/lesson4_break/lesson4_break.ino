/*------------------------------------------------------------------------------
In this BTB (Back to Basics), we'll practice using the 'break;' statement covered in:
	- http://www.programiz.com/c-programming/c-break-continue-statement
	- http://arduino.cc/en/Reference/Break
	- http://arduino.cc/en/Reference/Continue
to exit out of a for and while loop using two buttons

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
 int count = 0;

void setup()												
{	
	//output setup
	pinMode(greenLed, OUTPUT);
	pinMode(redLed, OUTPUT);
	pinMode(yellowLed, OUTPUT);

	//input setup
	pinMode(buttonA, INPUT);		
	pinMode(buttonB, INPUT);
}

void loop() 												
{
	//read the button states first!
	buttonStateA = digitalRead(buttonA);
	buttonStateB = digitalRead(buttonB);

	//cylce the led's in a loop
	for(count=0; count<=3; count++)
	{
		//break loop when buttonA is pressed
	 	if (buttonStateA == HIGH)
	 		break;		//<-- breaks 'for loop'

	 	//if count=1 redLed on
		if (count == 1)
		{
			digitalWrite(redLed, HIGH);
			digitalWrite(yellowLed, LOW);
			digitalWrite(greenLed, LOW);
			delay(200);
		}

	 	//if count=2 yellowLed on
	 	if (count == 2)
	 	{
	 		digitalWrite(redLed, LOW);
			digitalWrite(yellowLed, HIGH);
			digitalWrite(greenLed, LOW);
			delay(200);
	 	}

		//skip the 3rd LED from lighting up when buttonB is pressed
		if (buttonStateB == HIGH)
			continue;	//<-- 'continues' loop, but skips anything below

		//if count=3 redLed on
		if (count == 3)
		{
			digitalWrite(redLed, LOW);
			digitalWrite(yellowLed, LOW);
			digitalWrite(greenLed, HIGH);
			delay(200);
		}
	}
	//all leds are off at this point (when user 'breaks' from the loop)
	digitalWrite(redLed, LOW);
	digitalWrite(yellowLed, LOW);
	digitalWrite(greenLed, LOW);
}
