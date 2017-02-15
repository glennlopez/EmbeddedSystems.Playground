// *****************Texas.h**************
// grading engine for Lab 4
//
// Runs on TM4C123/MSP432
// Daniel and Jonathan Valvano
// August 22, 2016

/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
   ISBN: 978-1466468863, Jonathan Valvano, copyright (c) 2016

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


enum TExaSmode{
  GRADER,
  GRADESTEP1,
  GRADESTEP2,
  GRADESTEP3,
  LOGICANALYZER
};

// ************TExaS_Init*****************
// Initialize grader, triggered by periodic timer
// This needs to be called once
// Inputs: Grading or Logic analyzer
//         4-digit number from edX
// Outputs: none
void TExaS_Init(enum TExaSmode mode, uint32_t edXcode);

// ************TExaS_Stop*****************
// Stop the transfer
// Inputs:  none
// Outputs: none
void TExaS_Stop(void);

// record time Task 0 is started
void TExaS_Task0(void);

// record time Task 0 is started
void TExaS_Task1(void);

// record time Task 2 is started
void TExaS_Task2(void);

// record time Task 3 is started
void TExaS_Task3(void);

// record time Task 4 is started
void TExaS_Task4(void);

// record time Task 5 is started
void TExaS_Task5(void);

// record time Task 6 is started
void TExaS_Task6(void);
