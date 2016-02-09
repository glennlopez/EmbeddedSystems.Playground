// TExaS.h
// Runs on LM4F120/TM4C123
// Periodic timer Timer5A which will interact with debugger and grade the lab 
// It initializes on reset and runs whenever interrupts are enabled
// Jonathan Valvano. Daniel Valvano
// January 15, 2016

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// You have three options for display drivers/hardware:
// 1) Emulate the Nokia5110 LCD using UART0 and PA1-0 to send data to a PC
//    running TExaSdisplay in Nokia mode. (Note: this mode is not finished yet)
// 2) Interface a real Nokia5110 LCD and use SSI0 and PA7-2 to send data and
//    commands to it.  Allow TExaS to use UART0 and a PC running TExaSdisplay
//    to implement a low-cost oscilloscope.
// 3) Interface a real Nokia5110 LCD and use SSI0 and PA7-2 to send data and
//    commands to it.  Do not enable the oscilloscope.
// 4) There is no LCD. Do not enable the oscilloscope. You may use this mode to
//    have no display or to use the UART ASCII output like Labs 5 and 11
enum DisplayType{
  UART0_Emulate_Nokia5110_NoScope,
  SSI0_Real_Nokia5110_Scope,
  SSI0_Real_Nokia5110_NoScope,
  NoLCD_NoScope
};

// ************TExaS_Init*****************
// Initialize grader, voltmeter on timer 5A, scope on timer4A
// sets PLL to 80 MHz
// This needs to be called once 
// Inputs: display system used to output the results
// Outputs: none
void TExaS_Init(enum DisplayType display);

// ************TExaS_Stop*****************
// Stop the transfer 
// Inputs:  none
// Outputs: none
void TExaS_Stop(void);
