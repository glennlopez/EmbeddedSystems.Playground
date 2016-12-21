/*------------------------------------------------------------------------------
In this BTB (Back to Basics), we'll practice using the 'for' loop covered in:
	- http://www.programiz.com/c-programming/c-for-loop
	- http://arduino.cc/en/Reference/For
to create an LED "train" (led lights on 1 by 1 in sequence using a for loop).

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

	//condition if buttonA is pressed
	if (buttonStateA == HIGH)
	{
		/*---------------------------------------------
		for(initialization statement; test expression; update statement) 
		{
   			code to be executed; 
		}
		----------------------------------------------*/
		for(int count=0; count<13; count++)
		{
			if (count >=0 && count <=3)
			{
				digitalWrite(redLed, HIGH);
				digitalWrite(yellowLed, LOW);
				digitalWrite(greenLed, LOW);
				delay(100);
			}
			if (count >= 4	&& count <= 7)
			{
				digitalWrite(redLed, LOW);
				digitalWrite(yellowLed, HIGH);
				digitalWrite(greenLed, LOW);
				delay(100);
			}
			if (count >= 10 && count <=13)
			{
				digitalWrite(redLed, LOW);
				digitalWrite(yellowLed, LOW);
				digitalWrite(greenLed, HIGH);
				delay(100);
			}
		}
	}

	//condition if buttonB is pressed
	if (buttonStateB == HIGH)
	{
		for(int count=13; count>0; count--)
		{
			if (count >=0 && count <=3)
			{
				digitalWrite(redLed, HIGH);
				digitalWrite(yellowLed, LOW);
				digitalWrite(greenLed, LOW);
				delay(100);
			}
			if (count >= 4 && count <= 7)
			{
				digitalWrite(redLed, LOW);
				digitalWrite(yellowLed, HIGH);
				digitalWrite(greenLed, LOW);
				delay(100);
			}
			if (count >= 10 && count <=13)
			{
				digitalWrite(redLed, LOW);
				digitalWrite(yellowLed, LOW);
				digitalWrite(greenLed, HIGH);
				delay(100);
			}
		}
	}
	
	else
	{
		digitalWrite(redLed, LOW);
		digitalWrite(yellowLed, LOW);
		digitalWrite(greenLed, LOW);	
	}

}
