// *****************Texas.c**************
// Open version of TExaS
//
// Runs on TM4C123
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


#include <stdint.h>
#include "../inc/CortexM.h"
#include "../inc/tm4c123gh6pm.h"
#include "TExaS.h"

char volatile LogicData;

void LogicAnalyzer(void){  // called 10k/sec
  UART0_DR_R = LogicData;  // send data to PC
}
void Scope(void){  // called 10k/sec
  UART0_DR_R = (ADC1_SSFIFO3_R>>4); // send ADC to TExaSdisplay
}
// ------------PeriodicTask2_Init------------
// Activate an interrupt to run a user task periodically.
// Give it a priority 0 to 6 with lower numbers
// signifying higher priority.  Equal priority is
// handled sequentially.
// Input:  task is a pointer to a user function
//         Bus clock frequency in Hz
//         freq is number of interrupts per second
//           1 Hz to 10 kHz
//         priority is a number 0 to 6
// Output: none
void (*PeriodicTask2)(void);   // user function
void PeriodicTask2_Init(void(*task)(void), 
  uint32_t busfrequency, uint32_t freq, uint8_t priority){long sr;
  if((freq == 0) || (freq > 10000)){
    return;                        // invalid input
  }
  if(priority > 6){
    priority = 6;
  }
  sr = StartCritical();
  PeriodicTask2 = task;            // user function
  // ***************** Timer5 initialization *****************
  SYSCTL_RCGCTIMER_R |= 0x20;      // 0) activate clock for Timer5
  while((SYSCTL_PRTIMER_R&0x20) == 0){};// allow time for clock to stabilize
  TIMER5_CTL_R &= ~TIMER_CTL_TAEN; // 1) disable Timer5A during setup
                                   // 2) configure for 32-bit timer mode
  TIMER5_CFG_R = TIMER_CFG_32_BIT_TIMER;
                                   // 3) configure for periodic mode, default down-count settings
  TIMER5_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
                                   // 4) reload value
  TIMER5_TAILR_R = (busfrequency/freq - 1);
  TIMER5_TAPR_R = 0;               // 5) bus clock resolution
                                   // 6) clear TIMER5A timeout flag
  TIMER5_ICR_R = TIMER_ICR_TATOCINT;
  TIMER5_IMR_R |= TIMER_IMR_TATOIM;// 7) arm timeout interrupt
                                   // 8) priority
  NVIC_PRI23_R = (NVIC_PRI23_R&0xFFFFFF00)|(priority<<5);
// interrupts enabled in the main program after all devices initialized
// vector number 108, interrupt number 92
  NVIC_EN2_R = 1<<28;              // 9) enable IRQ 92 in NVIC
  TIMER5_CTL_R |= TIMER_CTL_TAEN;  // 10) enable Timer5A 32-b
  EndCritical(sr);
}

void TIMER5A_Handler(void){
  TIMER5_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER5A timeout
  (*PeriodicTask2)();              // execute user task
}

// ------------PeriodicTask2_Stop------------
// Deactivate the interrupt running a user task
// periodically.
// Input: none
// Output: none
void PeriodicTask2_Stop(void){
  if(SYSCTL_RCGCTIMER_R&0x20){
    // prevent hardware fault if PeriodicTask2_Init() has not been called
    TIMER5_ICR_R = TIMER_ICR_TATOCINT;// clear TIMER5A timeout flag
    NVIC_DIS2_R = 1<<28;           // disable IRQ 92 in NVIC
  }
}



#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable


//------------UART_Init------------
// Wait for new serial port input
// Initialize the UART for 115,200 baud rate (assuming busfrequency system clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
//        bus clock frequency in Hz
//        baud rate in bps
// Output: none
void UART_Init(uint32_t busfrequency, uint32_t baud){
  SYSCTL_RCGCUART_R |= 0x01; // activate UART0
  SYSCTL_RCGCGPIO_R |= 0x01; // activate port A
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = busfrequency/16/baud;   
  UART0_FBRD_R = ((64*(busfrequency%baud))+baud/2)/baud;      

//  UART0_IBRD_R = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
//  UART0_FBRD_R = 26;                    // FBRD = round(0.402778 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}

//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
char UART_InChar(void){
  while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((char)(UART0_DR_R&0xFF));
}

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

// toggle bit 0 
void TExaS_Task0(void){
  LogicData ^= 0x01;
}
// toggle bit 1 
void TExaS_Task1(void){
  LogicData ^= 0x02;
}
// toggle bit 2 
void TExaS_Task2(void){
  LogicData ^= 0x04;
}
// toggle bit 3 
void TExaS_Task3(void){ 
  LogicData ^= 0x08;
}
// toggle bit 4 
void TExaS_Task4(void){
}
// toggle bit 5 
void TExaS_Task5(void){
  LogicData ^= 0x20;
}
// toggle bit 6 
void TExaS_Task6(void){
  LogicData ^= 0x40;
}
// set bit 0 
void TExaS_Set0(void){
  LogicData |= 0x01;
}
// set bit 1 
void TExaS_Set1(void){
  LogicData |= 0x02;
}
// set bit 2 
void TExaS_Set2(void){
  LogicData |= 0x04;
}
// set bit 3 
void TExaS_Set3(void){ 
  LogicData |= 0x08;
}
// set bit 4 
void TExaS_Set4(void){
}
// set bit 5 
void TExaS_Set5(void){
  LogicData |= 0x20;
}
// set bit 6 
void TExaS_Set6(void){
  LogicData |= 0x40;
}
// clear bit 0 
void TExaS_Clear0(void){
  LogicData |= 0x01;
}
// clear bit 1 
void TExaS_Clear1(void){
  LogicData |= 0x02;
}
// clear bit 2 
void TExaS_Clear2(void){
  LogicData |= 0x04;
}
// clear bit 3 
void TExaS_Clear3(void){ 
  LogicData |= 0x08;
}
// clear bit 4 
void TExaS_Clear4(void){
}
// clear bit 5 
void TExaS_Clear5(void){
  LogicData |= 0x20;
}
// clear bit 6 
void TExaS_Clear6(void){
  LogicData |= 0x40;
}

// start conversions, sample always
// ADC1
// PD3 Ain4
// 16-point averaging 125kHz sampling
void ADC1_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGCADC_R |= 0x02;       // 1) ADC1 clock
  SYSCTL_RCGCGPIO_R |= 0x08;      // 2) activate clock for Port D
  while((SYSCTL_PRGPIO_R&0x08) == 0){};// allow time for clock to stabilize
  GPIO_PORTD_DIR_R &= ~0x08;      // 3) make PD3 input
  GPIO_PORTD_AFSEL_R |= 0x08;     // 4) enable alternate function on PD3
  GPIO_PORTD_DEN_R &= ~0x08;      // 5) disable digital I/O on PD3
  GPIO_PORTD_AMSEL_R |= 0x08;     // 6) enable analog functionality on PD3
  for(delay = 0; delay<20; delay++){};  // allow time for clock to stabilize
  ADC1_PC_R = 0x01;               // 7) 125K rate
  ADC1_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority
  ADC1_ACTSS_R = 0x0000;          // 9) disable sample sequencer 3
  ADC1_EMUX_R |= 0xF000;          // 10) seq3 is always/continuous trigger
  ADC1_SAC_R = 0x03;              //   8-point average 125kHz/8 = 15,625 Hz
  ADC1_SSMUX3_R = 4;              // 11) set channel 4
  ADC1_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
  ADC1_IM_R = 0x0000;             // 13) disable SS3 interrupts
  ADC1_ACTSS_R = 0x0008;          // 14) enable sample sequencer 3
}

// ************TExaS_Init*****************
// Initialize grader, triggered by periodic timer
// This needs to be called once
// Inputs: Scope or Logic analyzer
//         Bus clock frequency in Hz
// Outputs: none
void TExaS_Init(enum TExaSmode mode,uint32_t busfrequency){
  // 10 kHz periodic interrupt
  UART_Init(busfrequency,115200);
  LogicData |= 0x80; // bit 7 means logic data
  if(mode == LOGICANALYZER){
  // enable 10k periodic interrupt if logic analyzer mode
    PeriodicTask2_Init(&LogicAnalyzer,busfrequency,10000,5); // run logic analyzer
  }else if(mode == SCOPE){
    ADC1_Init();  // activate PD3 as analog input
    PeriodicTask2_Init(&Scope,busfrequency,10000,5); // run scope at 10k
  }
}

// ************TExaS_Stop*****************
// Stop the transfer
// Inputs:  none
// Outputs: none
void TExaS_Stop(void){
  PeriodicTask2_Stop();
}
