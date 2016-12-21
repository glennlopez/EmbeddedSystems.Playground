/*------------------------------------------------------------------------------
In this BTB (Back to Basics), we'll practice using the 'else if' statement covered in:
	- http://www.programiz.com/c-programming/c-if-else-statement
to control a set of LED's. 

Please use the "layout1_led.fzz" breadboard layout for this refresher!
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
	
	//then decide what to do
	//if (buttonStateA == HIGH && buttonStateB == HIGH) 	/*alternate (also works)*/
	if (buttonStateA && buttonStateB == HIGH)
		/*---------------------------------------------
		[DEBUG NOTE]
		Make sure to check if both buttons are pressed 
		first otherwise if buttonA or B is logic HIGH
		the uC will never get a chance to check if both 
		A & B are pressed.
		----------------------------------------------*/
	{
		digitalWrite(yellowLed, HIGH);
		digitalWrite(redLed, LOW);
		digitalWrite(greenLed, LOW);
	} 

	else if (buttonStateA == HIGH)
	{
		digitalWrite(greenLed, HIGH);
		digitalWrite(redLed, LOW);
		digitalWrite(yellowLed, LOW);
	}

	else if (buttonStateB == HIGH)
	{
		digitalWrite(greenLed, LOW);
		digitalWrite(redLed, HIGH);
		digitalWrite(yellowLed, LOW);
	}

	//lights off if nothing is pressed
	else
	{
		digitalWrite(redLed, LOW);
		digitalWrite(greenLed, LOW);
		digitalWrite(yellowLed, LOW);
	}
}

/*---------------------------------------------
[NOTES]

	-if statement:
	-if statement: 
If the first statement is true, its code will execute. 
Also, if the second statement is true, its code will execute.

	-if statement:
	-else if statment:
The second block will only execute here if the first one did not, 
and the second check is true.

	-if statement:
	-else:
The first statement will execute if it is true, 
while the second will execute if the first is false.
---------------------------------------------*/
