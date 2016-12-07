/* 
Runs on TM4C123, Jonathan Valvano 11/3/2014

Module Number: C8  
Module Title:  Security System 

Design a security system using contact switches for the sensors and flashing LED as the alarm.  
We will first prototype it on a breadboard using a LaunchPad. 
There are two contact switches that measure the status of your home. 
Each contact switch is positioned on a window. 
If the switch is closed or pressed the window is secure, but 
if either switch is open it means the window is open and the home is unsecure. 
There is also a toggle switch with which the user can use to activate or deactivate the alarm. 
If the alarm is activated, the LED will flash at 5 Hz if either switch is not pressed.

Learning Objectives: 
•  Understanding basic circuit elements like source, ground, switch, LED and resistors.
•  Application of Ohm’s Law
•  Analog circuit design and construction
•  Interfacing circuit elements to a microcontroller
•  Programming simple logic. 
*/

// PE4 is an output to LED output, 5 Hz flashing means alarm
// PE2 is an input from toggle switch, 1 means activate, 0 means deactivate
// PE1 is an input from contact switch, 1 means secure, 1 means unsecure
// PE0 is an input from contact switch, 1 means secure, 1 means unsecure
#include "TExaS.h"
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
unsigned long arm,sensor;
void delayms(unsigned long ms);
void EnableInterrupts(void);
int main(void){ unsigned long volatile delay;
  TExaS_Init();  // activate multimeter, 80 MHz
  SYSCTL_RCGC2_R |= 0x10;           // Port E clock
  delay = SYSCTL_RCGC2_R;           // wait 3-5 bus cycles
  GPIO_PORTE_DIR_R |= 0x10;         // PE4 output
  GPIO_PORTE_DIR_R &= ~0x07;        // PE2,1,0 input 
  GPIO_PORTE_AFSEL_R &= ~0x17;      // not alternative
  GPIO_PORTE_AMSEL_R &= ~0x17;      // no analog
  GPIO_PORTE_PCTL_R &= ~0x000F0FFF; // bits for PE4,PE2,PE1,PE0
  GPIO_PORTE_DEN_R |= 0x17;         // enable PE4,PE2,PE1,PE0
  EnableInterrupts();
  while(1){
    arm = GPIO_PORTE_DATA_R&0x04;    // arm 0 if deactivated, 1 if activated
    sensor = GPIO_PORTE_DATA_R&0x03; // 1 means ok, 0 means break in
    if((arm==0x04)&&(sensor != 0x03)){
      GPIO_PORTE_DATA_R ^= 0x10;   // toggle output for alarm
      delayms(100);  // 100ms delay makes a 5Hz period
    }else{
      GPIO_PORTE_DATA_R &= ~0x10;   // LED off if deactivated
    }
  }
}
// Subroutine to delay in units of 1 msec
// Inputs: Number of ms to delay
// Outputs: None
void delayms(unsigned long ms){
  unsigned long count;
  while(ms > 0 ) { // repeat while there are still ms to delay
    count = 16000; // number of counts to delay 1ms at 80MHz
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    ms--;
  }
}
