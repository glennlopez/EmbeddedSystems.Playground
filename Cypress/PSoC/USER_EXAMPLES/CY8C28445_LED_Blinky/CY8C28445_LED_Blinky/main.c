//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules


void main(void)
{
    while(1)
    {
    	if (PRT0DR & 0x01) //Checks the state of the button. If the button is pressed then it will execute.
    	{
    		PRT1DR &= ~0x01; //Turns the LED On.
    	}
    	else
    	{
    		PRT1DR |=  0x01; //Turns the LED Off.
    	}
    }
}
