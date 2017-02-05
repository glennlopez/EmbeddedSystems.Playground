/*------------------------------------------------------------------------------
In this BTB (Back to Basics), we'll practice using the 'while' loop covered in:
	- http://www.programiz.com/c-programming/c-do-while-loops
	- http://arduino.cc/en/Reference/While
to create an LED "train" (led lights on 1 by 1 in sequence using a for loop).

Please use the "layout1_led.fzz" breadboard layout for this lesson!
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

	/*---------------------------------------------
	while (test expression) 
	{
    	statement/s to be executed.  
	}
	----------------------------------------------*/

	//pressing buttonA counts counter UP if its lower than 3
	while(count <= 3 && buttonStateA == HIGH)
	{
		count++;
		break;  //<-- break out of while loop (more info in the nextlesson)
	}

	//pressing buttonB counts counter DOWN if its higher than 0
	while(count >= 0 && buttonStateB == HIGH)
	{
		count--;
		break;
	}

	//actions to take depending on what 'count' is
	if(count == 3)
	{
	    digitalWrite(redLed, HIGH); 		//<-- red led turns on
	    digitalWrite(yellowLed, LOW);
	    digitalWrite(greenLed, LOW);
	    delay(200);
	}
	if(count == 2)
	{
	    digitalWrite(redLed, LOW);
	    digitalWrite(yellowLed, HIGH);		//<-- yellow led turns on
	    digitalWrite(greenLed, LOW);	
	    delay(200);	
	}
	if(count == 1)
	{
	    digitalWrite(redLed, LOW);
	    digitalWrite(yellowLed, LOW);
	    digitalWrite(greenLed, HIGH);		//<-- green led turns on
	    delay(200);
	}
}

