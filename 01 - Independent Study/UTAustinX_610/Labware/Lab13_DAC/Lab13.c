/************************
 * PREPROCESSOR DIRECTIVES
 ************************/

#include "..//tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"

void DisableInterrupts(void);
void EnableInterrupts(void); 


/************************
 * MAIN ROUTINE
 ************************/
int main(void) {
	
		// for the real board grader to work 
		// you must connect PD3 to your DAC output
		TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz


    // Initialization routine
    Sound_Init();
    Piano_Init();
    EnableInterrupts();


    // Loop routine
    while(1){

        Sound_Tone(Piano_In());

    }
		
}



