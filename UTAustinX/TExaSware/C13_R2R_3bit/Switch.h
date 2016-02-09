// Switch.h
// This software configures the on-board switches and LEDs.
//
// For use with the LM4F120 or TM4C123
// September 15, 2013
// Port B bits 2-0 have the 3-bit DAC
// Port F is onboard LaunchPad switches and LED
// Port F bit 4 is negative logic switch to play sound, SW1
// SysTick ISR: PF3 ISR heartbeat


//---------------------Switch_Init---------------------
// initialize switch interface
// Input: none
// Output: none 
void Switch_Init(void);

//---------------------Switch_In---------------------
// read the values of the two switches
// Input: none
// Output: 0x00,0x01,0x10,0x11 from the two switches
//         0 if no switch is pressed
// bit4 PF4 SW1 switch
// bit0 PF0 SW2 switch 
unsigned long Switch_In(void); 

//---------------------Delay10ms---------------------
// wait 10ms for switches to stop bouncing
// Input: none
// Output: none
void Delay10ms(void);
