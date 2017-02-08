// *****************Texas.c**************
// grading engine for PeriodicRTOS
//
// Runs on TM4C123
// Uses the general board support package on the TM4C123.
// Remember to remove R9 and R10 to use the LCD since R10
// connects PD1 (accelerometer Y) to PB7 (LCD SPI data).
// Daniel and Jonathan Valvano
// March 21, 2016

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

//  J1   J3               J4   J2
// [ 1] [21]             [40] [20]
// [ 2] [22]             [39] [19]
// [ 3] [23]             [38] [18]
// [ 4] [24]             [37] [17]
// [ 5] [25]             [36] [16]
// [ 6] [26]             [35] [15]
// [ 7] [27]             [34] [14]
// [ 8] [28]             [33] [13]
// [ 9] [29]             [32] [12]
// [10] [30]             [31] [11]

// +3.3V connected to J1.1 (power)
// joystick horizontal (X) connected to J1.2 (analog)
// UART from BoosterPack to LaunchPad connected to J1.3 (UART)
// UART from LaunchPad to BoosterPack connected to J1.4 (UART)
// joystick Select button connected to J1.5 (digital)
// microphone connected to J1.6 (analog)
// LCD SPI clock connected to J1.7 (SPI)
// ambient light (OPT3001) interrupt connected to J1.8 (digital)
// ambient light (OPT3001) and temperature sensor (TMP006) I2C SCL connected to J1.9 (I2C)
// ambient light (OPT3001) and temperature sensor (TMP006) I2C SDA connected to J1.10 (I2C)

// temperature sensor (TMP006) interrupt connected to J2.11 (digital)
// nothing connected to J2.12 (SPI CS_Other)
// LCD SPI CS connected to J2.13 (SPI)
// nothing connected to J2.14 (SPI MISO)
// LCD SPI data connected to J2.15 (SPI)
// nothing connected to J2.16 (reset)
// LCD !RST connected to J2.17 (digital)
// nothing connected to J2.18 (SPI CS_Wireless)
// servo PWM connected to J2.19 (PWM)
// GND connected to J2.20 (ground)

// +5V connected to J3.21 (power)
// GND connected to J3.22 (ground)
// accelerometer X connected to J3.23 (analog)
// accelerometer Y connected to J3.24 (analog)
// accelerometer Z connected to J3.25 (analog)
// joystick vertical (Y) connected to J3.26 (analog)
// nothing connected to J3.27 (I2S WS)
// nothing connected to J3.28 (I2S SCLK)
// nothing connected to J3.29 (I2S SDout)
// nothing connected to J3.30 (I2S SDin)

// LCD RS connected to J4.31 (digital)
// user Button2 (bottom) connected to J4.32 (digital)
// user Button1 (top) connected to J4.33 (digital)
// gator hole switch connected to J4.34 (digital)
// nothing connected to J4.35
// nothing connected to J4.36
// RGB LED blue connected to J4.37 (PWM)
// RGB LED green connected to J4.38 (PWM)
// RGB LED red (jumper up) or LCD backlight (jumper down) connected to J4.39 (PWM)
// buzzer connected to J4.40 (PWM)

#include <stdint.h>
#include "TExaS.h"
#include "BSP.h"
#include "CortexM.h"
#include "../inc/tm4c123gh6pm.h"
void UART_Init(void);
char UART_InChar(void);
char UART_InCharNonBlocking(void);
void UART_OutChar(char data);
void UART_OutCharNonBlock(char data);
void UART_OutUDec(uint32_t n);
void UART_OutString(char *pt);
void UART_OutUDec4(uint32_t n);
void UART_OutUDec5(uint32_t n);
void UART_OutUDec6(uint32_t n);
void UART_OutUFix1(uint32_t n);
void UART_OutUDec7(uint32_t n);

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F
char volatile LogicData;
uint32_t Id;

//---------------- execution profile of tasks  ----------------
#define TOLERANCE 50     // tasks 2,5 have 5.0%
#define JITTER_ERROR0 6  // task 0 must be less than or equal to 6us of jitter
#define JITTER_ERROR1 18 // task 1 must be less than or equal to 18us of jitter
#define PROFILESIZE0 100
#define PROFILESIZE1 100
#define PROFILESIZE2 100
#define PROFILESIZE3 100
#define PROFILESIZE4 500
#define PROFILESIZE5 1000
uint32_t TimeBuffer0[PROFILESIZE0];  // time started Task0
uint32_t Index0;
uint32_t TimeBuffer1[PROFILESIZE1];  // time started Task1
uint32_t Index1;
uint32_t TimeBuffer2[PROFILESIZE2];  // time started Task2
uint32_t Index2;
uint32_t TimeBuffer3[PROFILESIZE3];  // time started Task3
uint32_t Index3;
uint32_t TimeBuffer4[PROFILESIZE4];  // time started Task4
uint32_t Index4;
uint32_t TimeBuffer5[PROFILESIZE5];  // time started Task5
uint32_t Index5;

#define EXPECTED3 100000
#define EXPECTED4 20000
#define EXPECTED5 10000
void LogicAnalyzer(void){ // called 10k/sec
  UART0_DR_R = LogicData;  // send data to PC
}
void RealTimeResults(uint32_t n, uint32_t expected, uint32_t  min, uint32_t max, uint32_t jitter, uint32_t ave, uint32_t err){
  UART_OutString("\n\rTask");       UART_OutUDec(n);
  UART_OutString(": Expected= ");   UART_OutUDec7(expected);
  UART_OutString(", min= ");        UART_OutUDec7(min);
  UART_OutString(", max= ");        UART_OutUDec7(max);
  UART_OutString(", jitter= ");     UART_OutUDec7(jitter);
  UART_OutString(", ave= ");        UART_OutUDec7(ave);
  UART_OutString(" usec, error= "); UART_OutUFix1(err);
}
void RealTimeResultsNoJitter(uint32_t n, uint32_t expected, uint32_t  min, uint32_t max, uint32_t jitter, uint32_t ave, uint32_t err){
  UART_OutString("\n\rTask");       UART_OutUDec(n);
  UART_OutString(": Expected= ");   UART_OutUDec7(expected);
  UART_OutString(", min= ");        UART_OutUDec7(min);
  UART_OutString(", max= ");        UART_OutUDec7(max);
  UART_OutString(",                  ave= ");
                                    UART_OutUDec7(ave);
  UART_OutString(" usec, error= "); UART_OutUFix1(err);
}
void NonrealTimeResults(uint32_t n, uint32_t expected, uint32_t  min, uint32_t max, uint32_t jitter, uint32_t ave, uint32_t err){
  UART_OutString("\n\rTask");                    UART_OutUDec(n);
  UART_OutString(":                    min= ");  UART_OutUDec7(min);
  UART_OutString(", max= ");                     UART_OutUDec7(max);
  UART_OutString(",                  ave= ");    UART_OutUDec7(ave);
  UART_OutString(" usec");
}
void Grader(void){        // called once a second
  uint32_t sum,dt,i,min,max,ave,err,jitter;
  uint32_t grade=0;
  uint32_t static count=0;
  if((Index3>=PROFILESIZE3)&&(Index4>=PROFILESIZE4)&&(Index5>=PROFILESIZE5)){ // done
    // run scoring
    TExaS_Stop();
    UART_OutString("\n\r**Done**\n\r");
    // Task 3
    sum = 0; min = 0xFFFFFFFF; max = 0;
    for(i=1;i<PROFILESIZE3;i++){
      dt = TimeBuffer3[i]-TimeBuffer3[i-1]; // time between executions
      if(dt>max)max = dt; // maximum
      if(dt<min)min = dt; // minimum
      sum = sum+dt;
    }
    ave = sum/(PROFILESIZE3-1);
    if(ave>=EXPECTED3){
      err = (1000*(ave-EXPECTED3))/EXPECTED3;
    }else{
      err = (1000*(EXPECTED3-ave))/EXPECTED3;
    }
    jitter = max-min;
    if(jitter <= JITTER_ERROR0) grade += 33;
    RealTimeResults(0,EXPECTED3,min,max,jitter,ave,err);

    // Task 4
    sum = 0; min = 0xFFFFFFFF; max = 0;
    for(i=1;i<PROFILESIZE4;i++){
      dt = TimeBuffer4[i]-TimeBuffer4[i-1]; // time between executions
      if(dt>max)max = dt; // maximum
      if(dt<min)min = dt; // minimum
      sum = sum+dt;
    }
    ave = sum/(PROFILESIZE4-1);
    if(ave>=EXPECTED4){
      err = (1000*(ave-EXPECTED4))/EXPECTED4;
    }else{
      err = (1000*(EXPECTED4-ave))/EXPECTED4;
    }
    jitter = max-min;
    if(jitter <= JITTER_ERROR1) grade += 33;
    RealTimeResults(1,EXPECTED4,min,max,jitter,ave,err);

    // Task 5
    sum = 0; min = 0xFFFFFFFF; max = 0;
    for(i=1;i<PROFILESIZE5;i++){
      dt = TimeBuffer5[i]-TimeBuffer5[i-1]; // time between executions
      if(dt>max)max = dt; // maximum
      if(dt<min)min = dt; // minimum
      sum = sum+dt;
    }
    ave = sum/(PROFILESIZE5-1);
    if(ave>=EXPECTED5){
      err = (1000*(ave-EXPECTED5))/EXPECTED5;
    }else{
      err = (1000*(EXPECTED5-ave))/EXPECTED5;
    }
    jitter = max-min;
    if(jitter <= JITTER_ERROR1) grade += 34;
    RealTimeResults(1,EXPECTED5,min,max,jitter,ave,err);


    UART_OutString("\n\rGrade= "); UART_OutUDec(grade);
  }else{
    UART_OutChar('0'+count%10);
    count++;
  }
}

// ------------PeriodicTask2_Init------------
// Activate an interrupt to run a user task periodically.
// Give it a priority 0 to 6 with lower numbers
// signifying higher priority.  Equal priority is
// handled sequentially.
// Input:  task is a pointer to a user function
//         freq is number of interrupts per second
//           1 Hz to 10 kHz
//         priority is a number 0 to 6
// Output: none
void (*PeriodicTask2)(void);   // user function
void PeriodicTask2_Init(void(*task)(void), uint32_t freq, uint8_t priority){long sr;
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
  TIMER5_TAILR_R = (BSP_Clock_GetFreq()/freq - 1);
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
  TIMER5_ICR_R = TIMER_ICR_TATOCINT;// clear TIMER5A timeout flag
  NVIC_DIS2_R = 1<<28;             // disable IRQ 92 in NVIC
}

// ************TExaS_Init*****************
// Initialize grader, triggered by periodic timer
// This needs to be called once
// Inputs: Grading or Logic analyzer
// Outputs: none
void TExaS_Init(enum TExaSmode mode, uint32_t edXcode){
  // 32 bit free running timer
  // 10 kHz periodic interrupt
  // edge triggered interrupt on Profile bits
  // grade mode will collect 10 seconds of profile (4 arrays)
  // logic analyzer will 10 kHz output to serial port (pack 4 bits): 8 bit bit7 set then LA, but 7 ASCII
  Id = edXcode;
  BSP_Time_Init();  // system timer in usec
  UART_Init();
  Index3 = Index4 = Index5 = 0;
  LogicData |= 0x80; // bit 7 means logic data
  if(mode == LOGICANALYZER){
  // enable 10k periodic interrupt if logic analyzer mode
    PeriodicTask2_Init(&LogicAnalyzer,10000,5); // run grader
  }
  if(mode == GRADER){
    UART_OutString("\n\r**Start PeriodicRTOS Grader**Version 1.00** ");
    PeriodicTask2_Init(&Grader,1,5); // run grader
  }
}

// ************TExaS_Stop*****************
// Stop the transfer
// Inputs:  none
// Outputs: none
void TExaS_Stop(void){
  PeriodicTask2_Stop();
}

#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable


//------------UART_Init------------
// Wait for new serial port input
// Initialize the UART for 115,200 baud rate (assuming 80 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void){
  SYSCTL_RCGCUART_R |= 0x01; // activate UART0
  SYSCTL_RCGCGPIO_R |= 0x01; // activate port A
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
  UART0_FBRD_R = 26;                    // FBRD = round(0.402778 * 64) = 26
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
//------------UART_InCharNonBlocking------------
// look for new serial port input
// Input: none
// Output: ASCII code for key typed
//         0 if no key ready
char UART_InCharNonBlocking(void){
  if((UART0_FR_R&UART_FR_RXFE) == 0){
    return((char)(UART0_DR_R&0xFF));
  }
  return 0;
}
//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}
//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutCharNonBlock(char data){
//  if((UART0_FR_R&UART_FR_TXFF) == 0){
    UART0_DR_R = data;
//  }
}

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(char *pt){
  while(*pt){
    UART_OutChar(*pt);
    pt++;
  }
}

//------------UART_InUDec------------
// InUDec accepts ASCII input in unsigned decimal format
//     and converts to a 32-bit unsigned number
//     valid range is 0 to 4294967295 (2^32-1)
// Input: none
// Output: 32-bit unsigned number
// If you enter a number above 4294967295, it will return an incorrect value
// Backspace will remove last digit typed
uint32_t UART_InUDec(void){
uint32_t number=0, length=0;
char character;
  character = UART_InChar();
  while(character != CR){ // accepts until <enter> is typed
// The next line checks that the input is a digit, 0-9.
// If the character is not 0-9, it is ignored and not echoed
    if((character>='0') && (character<='9')) {
      number = 10*number+(character-'0');   // this line overflows if above 4294967295
      length++;
      UART_OutChar(character);
    }
// If the input is a backspace, then the return number is
// changed and a backspace is outputted to the screen
    else if((character==BS) && length){
      number /= 10;
      length--;
      UART_OutChar(character);
    }
    character = UART_InChar();
  }
  return number;
}

//-----------------------UART_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1-10 digits with no space before or after
void UART_OutUDec(uint32_t n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    UART_OutUDec(n/10);
    n = n%10;
  }
  UART_OutChar(n+'0'); /* n is between 0 and 9 */
}
uint32_t Messageindexb;
char Messageb[8];
void static fillmessageb(uint32_t n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    fillmessageb(n/10);
    n = n%10;
  }
  Messageb[Messageindexb] = (n+'0'); /* n is between 0 and 9 */
  if(Messageindexb<7)Messageindexb++;
}
void static fillmessage4b(uint32_t n){
  if(n>=1000){  // 1000 to 9999
    Messageindexb = 0;
  } else if(n>=100){  // 100 to 999
    Messageb[0] = ' ';
    Messageindexb = 1;
  }else if(n>=10){ //
    Messageb[0] = ' '; /* n is between 10 and 99 */
    Messageb[1] = ' ';
    Messageindexb = 2;
  }else{
    Messageb[0] = ' '; /* n is between 0 and 9 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageindexb = 3;
  }
  fillmessageb(n);
}
void static fillmessage5b(uint32_t n){
  if(n>99999)n=99999;
  if(n>=10000){  // 10000 to 99999
    Messageindexb = 0;
  } else if(n>=1000){  // 1000 to 9999
    Messageb[0] = ' ';
    Messageindexb = 1;
  }else if(n>=100){  // 100 to 999
    Messageb[0] = ' ';
    Messageb[1] = ' ';
    Messageindexb = 2;
  }else if(n>=10){ //
    Messageb[0] = ' '; /* n is between 10 and 99 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageindexb = 3;
  }else{
    Messageb[0] = ' '; /* n is between 0 and 9 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageb[3] = ' ';
    Messageindexb = 4;
  }
  fillmessageb(n);
}
void static fillmessage6b(uint32_t n){
  if(n>999999)n=999999;
  if(n>=100000){  // 100000 to 999999
    Messageindexb = 0;
  } else if(n>=10000){  // 10000 to 99999
    Messageb[0] = ' ';
    Messageindexb = 1;
  }else if(n>=1000){  // 1000 to 9999
    Messageb[0] = ' ';
    Messageb[1] = ' ';
    Messageindexb = 2;
  }else if(n>=100){ //
    Messageb[0] = ' '; /* n is between 100 and 999 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageindexb = 3;
  }else if(n>=10){ //
    Messageb[0] = ' '; /* n is between 10 and 99 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageb[3] = ' ';
    Messageindexb = 4;
  }else {
    Messageb[0] = ' '; /* n is between 0 and 9 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageb[3] = ' ';
    Messageb[4] = ' ';
    Messageindexb = 5;
  }
  fillmessageb(n);
}
void static fillmessage7b(uint32_t n){
  if(n>9999999) n = 9999999;
  if(n>=1000000){  // 1,000,000 to 9,999,999
    Messageindexb = 0;
  }else if(n>=100000){  // 100,000 to 999,999
    Messageb[0] = ' ';
    Messageindexb = 1;
  }else if(n>=10000){  // 10,000 to 99,999
    Messageb[0] = ' ';
    Messageb[1] = ' ';
    Messageindexb = 2;
  }else if(n>=1000){  // 1,000 to 9,999
    Messageb[0] = ' ';
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageindexb = 3;
  }else if(n>=100){ //
    Messageb[0] = ' '; /* n is between 100 and 999 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageb[3] = ' ';
    Messageindexb = 4;
  }else if(n>=10){ //
    Messageb[0] = ' '; /* n is between 10 and 99 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageb[3] = ' ';
    Messageb[4] = ' ';
    Messageindexb = 5;
  }else{
    Messageb[0] = ' '; /* n is between 0 and 9 */
    Messageb[1] = ' ';
    Messageb[2] = ' ';
    Messageb[3] = ' ';
    Messageb[4] = ' ';
    Messageb[5] = ' ';
    Messageindexb = 6;
  }
  fillmessageb(n);
}
//-----------------------UART_OutUDec4-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 4 digits with spaces before
void UART_OutUDec4(uint32_t n){
  if(n>9999){
    UART_OutString("****");
  }else{
    Messageindexb = 0;
    fillmessage4b(n);
    Messageb[Messageindexb] = 0; // terminate
    UART_OutString(Messageb);
  }
}
//-----------------------UART_OutUDec5-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 5 digits with spaces before
void UART_OutUDec5(uint32_t n){
  if(n>99999){
    UART_OutString("*****");
  }else{
    Messageindexb = 0;
    fillmessage5b(n);
    Messageb[Messageindexb] = 0; // terminate
    UART_OutString(Messageb);
  }
}
//-----------------------UART_OutUDec6-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 6 digits with spaces before
void UART_OutUDec6(uint32_t n){
  if(n>999999){
    UART_OutString("******");
  }else{
    Messageindexb = 0;
    fillmessage6b(n);
    Messageb[Messageindexb] = 0; // terminate
    UART_OutString(Messageb);
  }
}
//-----------------------UART_OutUFix1-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 4 digits with no space before or after
void UART_OutUFix1(uint32_t n){
  UART_OutUDec(n/10);
  UART_OutChar('.');
  UART_OutUDec(n%10);
  UART_OutChar('%');
}
//-----------------------UART_OutUDec7-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 7 digits with spaces before
void UART_OutUDec7(uint32_t n){
  if(n>9999999){
    UART_OutString("*******");
  }else{
    Messageindexb = 0;
    fillmessage7b(n);
    Messageb[Messageindexb] = 0; // terminate
    UART_OutString(Messageb);
  }
}
//---------------------UART_InUHex----------------------------------------
// Accepts ASCII input in unsigned hexadecimal (base 16) format
// Input: none
// Output: 32-bit unsigned number
// No '$' or '0x' need be entered, just the 1 to 8 hex digits
// It will convert lower case a-f to uppercase A-F
//     and converts to a 16 bit unsigned number
//     value range is 0 to FFFFFFFF
// If you enter a number above FFFFFFFF, it will return an incorrect value
// Backspace will remove last digit typed
uint32_t UART_InUHex(void){
uint32_t number=0, digit, length=0;
char character;
  character = UART_InChar();
  while(character != CR){
    digit = 0x10; // assume bad
    if((character>='0') && (character<='9')){
      digit = character-'0';
    }
    else if((character>='A') && (character<='F')){
      digit = (character-'A')+0xA;
    }
    else if((character>='a') && (character<='f')){
      digit = (character-'a')+0xA;
    }
// If the character is not 0-9 or A-F, it is ignored and not echoed
    if(digit <= 0xF){
      number = number*0x10+digit;
      length++;
      UART_OutChar(character);
    }
// Backspace outputted and return value changed if a backspace is inputted
    else if((character==BS) && length){
      number /= 0x10;
      length--;
      UART_OutChar(character);
    }
    character = UART_InChar();
  }
  return number;
}

//--------------------------UART_OutUHex----------------------------
// Output a 32-bit number in unsigned hexadecimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1 to 8 digits with no space before or after
void UART_OutUHex(uint32_t number){
// This function uses recursion to convert the number of
//   unspecified length as an ASCII string
  if(number >= 0x10){
    UART_OutUHex(number/0x10);
    UART_OutUHex(number%0x10);
  }
  else{
    if(number < 0xA){
      UART_OutChar(number+'0');
     }
    else{
      UART_OutChar((number-0x0A)+'A');
    }
  }
}

//------------UART_InString------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until <enter> is typed
//    or until max length of the string is reached.
// It echoes each character as it is inputted.
// If a backspace is inputted, the string is modified
//    and the backspace is echoed
// terminates the string with a null character
// uses busy-waiting synchronization on RDRF
// Input: pointer to empty buffer, size of buffer
// Output: Null terminated string
// -- Modified by Agustinus Darmawan + Mingjie Qiu --
void UART_InString(char *bufPt, uint16_t max) {
int length=0;
char character;
  character = UART_InChar();
  while(character != CR){
    if(character == BS){
      if(length){
        bufPt--;
        length--;
        UART_OutChar(BS);
      }
    }
    else if(length < max){
      *bufPt = character;
      bufPt++;
      length++;
      UART_OutChar(character);
    }
    character = UART_InChar();
  }
  *bufPt = 0;
}

// record time Task 0 is started
void TExaS_Task0(void){
  if(Index0<PROFILESIZE0){
    TimeBuffer0[Index0] = BSP_Time_Get(); //usec
  }
  Index0++;
  LogicData ^= 0x01;
}

// record time Task 1 is started
void TExaS_Task1(void){
  if(Index1<PROFILESIZE1){
    TimeBuffer1[Index1] = BSP_Time_Get();
  }
  Index1++;
  LogicData ^= 0x02;
}
// record time Task 2 is started
void TExaS_Task2(void){
  if(Index2<PROFILESIZE2){
    TimeBuffer2[Index2] = BSP_Time_Get();
  }
  Index2++;
  LogicData ^= 0x04;
}
// record time Task 3 is started
void TExaS_Task3(void){
  if(Index3<PROFILESIZE3){
    TimeBuffer3[Index3] = BSP_Time_Get();
  }
  Index3++;
  LogicData ^= 0x08;
}
// record time Task 4 is started
void TExaS_Task4(void){
  if(Index4<PROFILESIZE4){
    TimeBuffer4[Index4] = BSP_Time_Get();
  }
  Index4++;
  LogicData ^= 0x10;
}
// record time Task 5 is started
void TExaS_Task5(void){
  if(Index5<PROFILESIZE5){
    TimeBuffer5[Index5] = BSP_Time_Get();
  }
  Index5++;
  LogicData ^= 0x20;
}
//#define TExaS_Task1()  if(Index1<PROFILESIZE){TimeBuffer1[Index1++] = BSP_Time_Get();}
//#define TExaS_Task2()  if(Index2<PROFILESIZE){TimeBuffer2[Index2++] = BSP_Time_Get();}
//#define TExaS_Task3()  if(Index3<PROFILESIZE){TimeBuffer3[Index3++] = BSP_Time_Get();}
//#define TExaS_Task4()  if(Index4<PROFILESIZE){TimeBuffer4[Index4++] = BSP_Time_Get();}
//#define TExaS_Task5()  if(Index5<PROFILESIZE){TimeBuffer5[Index5++] = BSP_Time_Get();}


