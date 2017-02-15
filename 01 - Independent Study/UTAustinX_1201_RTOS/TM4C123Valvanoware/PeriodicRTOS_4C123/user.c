//*****************************************************************************
// user.c
// Runs on LM4F120/TM4C123/MSP432
// An example user program that initializes the simple operating system
//   Schedule three main threads and three periodic threads using preemptive round robin
//   Each thread rapidly toggles a pin on profile pins and increments its counter
//   THREADFREQ is the rate of the scheduler in Hz

// Daniel Valvano
// March 7, 2016

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
   ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2016
   Programs 4.4 through 4.12, section 4.2

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

#include <stdint.h>
#include "os.h"
#include "BSP.h"
#include "profile.h"
#include "TExaS.h"

#define THREADFREQ 1000   // frequency in Hz
// Main threads runs each thread 1 ms
uint32_t Count0;   // number of times MainThread0 loops
uint32_t Count1;   // number of times MainThread1 loops
uint32_t Count2;   // number of times MainThread2 loops
// Event threads run 
uint32_t Count3;   // number of times EventThread0 loops, 10 Hz
uint32_t Count4;   // number of times EventThread1 loops, 50 Hz
uint32_t Count5;   // number of times EventThread2 loops, 100 Hz 


void MainThread0(void){
  Count0 = 0;
  while(1){
    Count0++;
    Profile_Toggle0();    // toggle bit
  }
}
void MainThread1(void){
  Count1 = 0;
  while(1){
    Count1++;
    Profile_Toggle1();    // toggle bit
  }
}
void MainThread2(void){
  Count2 = 0;
  while(1){
    Count2++;
    Profile_Toggle2();   // toggle bit
    OS_Suspend();  // main threads can cooperate
  }
}
void EventThread0(void){ 
  Count3 = 0;
  while(1){             // 10 Hz real time task
    Count3++;
    Profile_Toggle3();  // toggle bit
    TExaS_Task3();
    OS_Suspend();       // execution of event threads must short and bounded
  }
}
void EventThread1(void){ 
  Count4 = 0;
  while(1){             // 50 Hz real time task
    Count4++;
    Profile_Toggle4();  // toggle bit
    TExaS_Task4();
    OS_Suspend();       // execution of event threads must short and bounded
  }
}
void EventThread2(void){
  Count5 = 0;
  while(1){             // 100 Hz real time task
    Count5++;
    Profile_Toggle5();  // toggle bit
    TExaS_Task5();
    OS_Suspend();       // execution of event threads must short and bounded
  }
}
// void realtime(void){
//  OS_Signal(&s0);
//}
//void EventThread0(void){ 
//  Count3 = 0;
//  while(1){             // 10 Hz real time task
//    OS_Wait(&s1);
//    Count3++;
//    Profile_Toggle3();  // toggle bit
//    TExaS_Task3();
//  }
//}
// BSP_PeriodTask_Init(&realtime,12345,0);
int main(void){ 
  OS_Init();            // initialize, disable interrupts
  TExaS_Init(GRADER,1000);
  Profile_Init();       // enable digital I/O on profile pins
  OS_AddThreads(&MainThread0, &MainThread1, &MainThread2);
  OS_AddPeriodicThreads(&EventThread0, 100000, &EventThread1, 20000, &EventThread2, 10000);
  OS_Launch(BSP_Clock_GetFreq()/THREADFREQ); // doesn't return, interrupts enabled in here
  return 0;             // this never executes
}
