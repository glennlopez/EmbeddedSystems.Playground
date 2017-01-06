/* 
Runs on TM4C123, Jonathan Valvano 6/17/2013

Module Number: C8  
Module Title:  Switch controls light 

Module Statement: Design two systems that include a switch and LED. The analog system includes 
just the switch and LED, and the digital system includes a microcontroller. The switch controls 
whether an LED is turned on/off using negative logic. In particular, if the switch is pressed 
the LED is off, and if the switch is not pressed the LED is on.

Learning Objectives: 
•  Understanding basic circuit elements like source, ground, switch, LED and resistors.
•  Application of Ohm’s Law
•  Analog circuit design and construction
•  Interfacing circuit elements to a microcontroller
•  Programming simple logic. 
*/

// PD3 is an output to LED output, positive logic
// PD0 is an input from switch, positive logic
// to set the switch in the simulator type this into command window
// PORTD = 1 
// to release the switch in the simulator type this into command window
// PORTD = 0 
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))
unsigned long in,out;
int main(void){ unsigned long volatile delay;
  SYSCTL_RCGC2_R |= 0x08;           // Port D clock
  delay = SYSCTL_RCGC2_R;           // wait 3-5 bus cycles
  GPIO_PORTD_DIR_R |= 0x08;         // PD3 output
  GPIO_PORTD_DIR_R &= ~0x01;        // PD0 input 
  GPIO_PORTD_AFSEL_R &= ~0x09;      // not alternative
  GPIO_PORTD_AMSEL_R &= ~0x09;      // no analog
  GPIO_PORTD_PCTL_R &= ~0x0000F00F; // bits for PD3, PD0
  GPIO_PORTD_DEN_R |= 0x09;         // enable PD3, PD0
  while(1){
    in = (GPIO_PORTD_DATA_R&0x01); // in 0 if not pressed, 1 if pressed
    out = (in^0x01)<<3;   // out 8 if not pressed, 0 if switch pressed
    GPIO_PORTD_DATA_R = out;
  }
}

