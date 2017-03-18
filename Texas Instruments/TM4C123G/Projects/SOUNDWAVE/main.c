/*
    TuningFork.c Lab 12
    Runs on LM4F120/TM4C123
    Use SysTick interrupts to create a squarewave at 440Hz.
    There is a positive logic switch connected to PA3, PB3, or PE3.
    There is an output on PA2, PB2, or PE2. The output is
    connected to headphones through a 1k resistor.
    The volume-limiting resistor can be any value from 680 to 2000 ohms
    The tone is initially off, when the switch goes from
    not touched to touched, the tone toggles on/off.

                   |---------|               |---------|
 Switch   ---------|         |---------------|         |------

                    |-| |-| |-| |-| |-| |-| |-|
 Tone     ----------| |-| |-| |-| |-| |-| |-| |---------------

*/

//#include "TExaS.h"
//#include "..//tm4c123gh6pm.h"


/************************
 * ADDRESS DEFINITIONS
 ************************/




// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode

/************************
 * ISR HANDLERS
 ************************/


// called at 880 Hz
void SysTick_Handler(void){

}



/************************
 * MAIN ROUTINE
 ************************/

int main(void){// activate grader and set system clock to 80 MHz

  // Initialization routine
  //TExaS_Init(SW_PIN_PA3, HEADPHONE_PIN_PA2,ScopeOn);
  Sound_Init();
  EnableInterrupts();   // enable after all initialization are done

  // Program routine
  while(1){

  }
}


/************************
 * SUB ROUTINES
 ************************/

// input from PA3, output from PA2, SysTick interrupts
void Sound_Init(void){

}
