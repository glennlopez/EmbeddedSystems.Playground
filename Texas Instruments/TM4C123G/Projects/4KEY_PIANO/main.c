

/************************
 * PREPROCESSOR DIRECTIVES
 ************************/

 // Includes
#include "PLL.h"
#include "Sound.h"
#include "Piano.h"


/************************
 * MAIN ROUTINE
 ************************/
void main(void) {

    // Initialization routine
    Sound_Init();
    Piano_Init();
    PLL_Init();
    EnableInterrupts();


    // Loop routine
    while(1){

        Sound_Tone(Piano_In());

    }

}
