// *****************Texas.h**************
// Open version of TExaS
//
// Runs on either MSP432 or TM4C123
// Daniel and Jonathan Valvano
// September 26, 2016

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
  SCOPE,
  LOGICANALYZER
};

// ************TExaS_Init*****************
// Initialize scope or logic analyzer, triggered by periodic timer
// This needs to be called once
// Inputs: Scope or Logic analyzer
//         Bus clock frequency in Hz
// Outputs: none
void TExaS_Init(enum TExaSmode mode, uint32_t busfrequency);

// ************TExaS_Stop*****************
// Stop the transfer
// Inputs:  none
// Outputs: none
void TExaS_Stop(void);

// toggle bit 0 
void TExaS_Task0(void);
// toggle bit 1 
void TExaS_Task1(void);
// toggle bit 2 
void TExaS_Task2(void);
// toggle bit 3 
void TExaS_Task3(void);
// toggle bit 4 
void TExaS_Task4(void);
// toggle bit 5 
void TExaS_Task5(void);
// toggle bit 6 
void TExaS_Task6(void);
// set bit 0 
void TExaS_Set0(void);
// set bit 1 
void TExaS_Set1(void);
// set bit 2 
void TExaS_Set2(void);
// set bit 3 
void TExaS_Set3(void);
// set bit 4 
void TExaS_Set4(void);
// set bit 5 
void TExaS_Set5(void);
// set bit 6 
void TExaS_Set6(void);
// clear bit 0 
void TExaS_Clear0(void);
// clear bit 1 
void TExaS_Clear1(void);
// clear bit 2 
void TExaS_Clear2(void);
// clear bit 3 
void TExaS_Clear3(void);
// clear bit 4 
void TExaS_Clear4(void);
// clear bit 5 
void TExaS_Clear5(void);
// clear bit 6 
void TExaS_Clear6(void);

