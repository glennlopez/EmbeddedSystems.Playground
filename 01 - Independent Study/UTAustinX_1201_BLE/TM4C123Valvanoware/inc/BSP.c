// BSP.c
// Runs on TM4C123 with an Educational BoosterPack MKII (BOOSTXL-EDUMKII)
// This file contains the software interface to the MKII BoosterPack.
// This board support package (BSP) is an abstraction layer,
//   forming a bridge between the low-level hardware and the high-level software.

// Remember to remove R9 and R10 to use the LCD since R10
// connects PD1 (accelerometer Y) to PB7 (LCD SPI data).
// Daniel and Jonathan Valvano
// June 8, 2016

/* This example accompanies the books
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
      ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2016
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
      ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016
   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
      ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2016

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

// Connected pins in physical order
// J1.1 +3.3V (power)
// J1.2 joystick horizontal (X) (analog) {TM4C123 PB5/AIN11, MSP432 P6.0}
// J1.3 UART from Bluetooth to LaunchPad (UART) {TM4C123 PB0, MSP432 P3.2} 
// J1.4 UART from LaunchPad to Bluetooth (UART) {TM4C123 PB1, MSP432 P3.3} 
// J1.5 joystick Select button (digital) {TM4C123 PE4, MSP432 P4.1}
// J1.6 microphone (analog)              {TM4C123 PE5/AIN8, MSP432 P4.3}
// J1.7 LCD SPI clock (SPI)              {TM4C123 PB4, MSP432 P1.5}
// J1.8 ambient light (OPT3001) interrupt (digital) {TM4C123 PA5, MSP432 P4.6}
// J1.9 ambient light (OPT3001) and temperature sensor (TMP006) I2C SCL (I2C)  {TM4C123 PA6, MSP432 P6.5}
// J1.10 ambient light (OPT3001) and temperature sensor (TMP006) I2C SDA (I2C) {TM4C123 PA7, MSP432 P6.4}
//--------------------------------------------------
// J2.11 temperature sensor (TMP006) interrupt (digital) {TM4C123 PA2, MSP432 P3.6}
// J2.12 nothing                         {TM4C123 PA3, MSP432 P5.2}
// J2.13 LCD SPI CS (SPI)                {TM4C123 PA4, MSP432 P5.0} 
// J2.14 nothing                         {TM4C123 PB6, MSP432 P1.7}
// J2.15 LCD SPI data (SPI)              {TM4C123 PB7, MSP432 P1.6}
// J2.16 nothing (reset)  
// J2.17 LCD !RST (digital)              {TM4C123 PF0, MSP432 P5.7}
// J2.18 Profile 4                       {TM4C123 PE0, MSP432 P3.0}
// J2.19 servo PWM                       {TM4C123 PB2, MSP432 P2.5}
// J2.20 GND (ground)
//--------------------------------------------------
// J3.21 +5V (power)
// J3.22 GND (ground)
// J3.23 accelerometer X (analog)        {TM4C123 PD0/AIN7, MSP432 P6.1}
// J3.24 accelerometer Y (analog)        {TM4C123 PD1/AIN6, MSP432 P4.0}
// J3.25 accelerometer Z (analog)        {TM4C123 PD2/AIN5, MSP432 P4.2}
// J3.26 joystick vertical (Y) (analog)  {TM4C123 PD3/AIN4, MSP432 P4.4}
// J3.27 Profile 0                       {TM4C123 PE1, MSP432 P4.5}
// J3.28 Profile 1                       {TM4C123 PE2, MSP432 P4.7}
// J3.29 Profile 2                       {TM4C123 PE3, MSP432 P5.4}
// J3.30 Profile 3                       {TM4C123 PF1, MSP432 P5.5}
//--------------------------------------------------
// J4.31 LCD RS (digital)                {TM4C123 PF4, MSP432 P3.7}
// J4.32 user Button2 (bottom) (digital) {TM4C123 PD7, MSP432 P3.5}
// J4.33 user Button1 (top) (digital)    {TM4C123 PD6, MSP432 P5,1}
// J4.34 Profile 6/gator hole switch     {TM4C123 PC7, MSP432 P2.3}
// J4.35 nothing                         {TM4C123 PC6, MSP432 P6.7}
// J4.36 Profile 5                       {TM4C123 PC5, MSP432 P6.6}
// J4.37 RGB LED blue (PWM)              {TM4C123 PC4, MSP432 P5.6}
// J4.38 RGB LED green (PWM)             {TM4C123 PB3, MSP432 P2.4}
// J4.39 RGB LED red (jumper up) or LCD backlight (jumper down) (PWM) {TM4C123 PF3, MSP432 P2.6}
// J4.40 buzzer (PWM)                    {TM4C123 PF2, MSP432 P2.7}
//--------------------------------------------------
// Connected pins in logic order
// power and reset
// J1.1 +3.3V (power)
// J3.21 +5V (power)
// J3.22 GND (ground)
// J2.20 GND (ground)
// J2.16 nothing (reset)  
//--------------------------------------------------
// LCD graphics
// J1.7 LCD SPI clock (SPI)              {TM4C123 PB4, MSP432 P1.5}
// J2.13 LCD SPI CS (SPI)                {TM4C123 PA4, MSP432 P5.0} 
// J2.15 LCD SPI data (SPI)              {TM4C123 PB7, MSP432 P1.6}
// J2.17 LCD !RST (digital)              {TM4C123 PF0, MSP432 P5.7}
// J4.31 LCD RS (digital)                {TM4C123 PF4, MSP432 P3.7}
//--------------------------------------------------
// 3-color LED
// J4.37 RGB LED blue (PWM)              {TM4C123 PC4, MSP432 P5.6}
// J4.38 RGB LED green (PWM)             {TM4C123 PB3, MSP432 P2.4}
// J4.39 RGB LED red (jumper up) or LCD backlight (jumper down) (PWM) {TM4C123 PF3, MSP432 P2.6}
//--------------------------------------------------
// user buttons
// J4.32 user Button2 (bottom) (digital) {TM4C123 PD7, MSP432 P3.5}
// J4.33 user Button1 (top) (digital)    {TM4C123 PD6, MSP432 P5.1}
//--------------------------------------------------
// buzzer output
// J4.40 buzzer (PWM)                    {TM4C123 PF2, MSP432 P2.7}
//--------------------------------------------------
// Joystick
// J1.5 joystick Select button (digital) {TM4C123 PE4, MSP432 P4.1}
// J1.2 joystick horizontal (X) (analog) {TM4C123 PB5/AIN11, MSP432 P6.0}
// J3.26 joystick vertical (Y) (analog)  {TM4C123 PD3/AIN4, MSP432 P4.4}
//--------------------------------------------------
// accelerometer
// J3.23 accelerometer X (analog)        {TM4C123 PD0/AIN7, MSP432 P6.1}
// J3.24 accelerometer Y (analog)        {TM4C123 PD1/AIN6, MSP432 P4.0}
// J3.25 accelerometer Z (analog)        {TM4C123 PD2/AIN5, MSP432 P4.2}
//--------------------------------------------------
// microphone
// J1.6 microphone (analog)              {TM4C123 PE5/AIN8, MSP432 P4.3}
//--------------------------------------------------
// light and temperature sensors (I2C)
// J1.8 ambient light (OPT3001) interrupt (digital) {TM4C123 PA5, MSP432 P4.6}
// J1.9 ambient light (OPT3001) and temperature sensor (TMP006) I2C SCL (I2C)  {TM4C123 PA6, MSP432 P6.5}
// J1.10 ambient light (OPT3001) and temperature sensor (TMP006) I2C SDA (I2C) {TM4C123 PA7, MSP432 P6.4}
// J2.11 temperature sensor (TMP006) interrupt (digital) {TM4C123 PA2, MSP432 P3.6}
//--------------------------------------------------
// Bluetooth booster
// J1.3 UART from Bluetooth to LaunchPad (UART) {TM4C123 PB0, MSP432 P3.2} 
// J1.4 UART from LaunchPad to Bluetooth (UART) {TM4C123 PB1, MSP432 P3.3} 
//--------------------------------------------------
// profile pins
// J3.27 Profile 0                       {TM4C123 PE1, MSP432 P4.5}
// J3.28 Profile 1                       {TM4C123 PE2, MSP432 P4.7}
// J3.29 Profile 2                       {TM4C123 PE3, MSP432 P5.4}
// J3.30 Profile 3                       {TM4C123 PF1, MSP432 P5.5}
// J2.18 Profile 4                       {TM4C123 PE0, MSP432 P3.0}
// J4.36 Profile 5                       {TM4C123 PC5, MSP432 P6.6}
// J4.34 Profile 6                       {TM4C123 PC7, MSP432 P2.3}
//--------------------------------------------------
// unconnected pins
// J2.12 nothing                         {TM4C123 PA3, MSP432 P5.2}
// J2.14 nothing                         {TM4C123 PB6, MSP432 P1.7}
// J2.19 servo PWM                       {TM4C123 PB2, MSP432 P2.5}
// J4.35 nothing                         {TM4C123 PC6, MSP432 P6.7}

#include <stdint.h>
#include "BSP.h"
#include "../inc/tm4c123gh6pm.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

static uint32_t ClockFrequency = 16000000; // cycles/second

// ------------BSP_Button1_Init------------
// Initialize a GPIO pin for input, which corresponds
// with BoosterPack pin J4.33.
// Input: none
// Output: none
void BSP_Button1_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x00000008; // 1) activate clock for Port D
  while((SYSCTL_PRGPIO_R&0x08) == 0){};// allow time for clock to stabilize
                                   // 2) no need to unlock PD6
  GPIO_PORTD_AMSEL_R &= ~0x40;     // 3) disable analog on PD6
                                   // 4) configure PD6 as GPIO
  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xF0FFFFFF)+0x00000000;
  GPIO_PORTD_DIR_R &= ~0x40;       // 5) make PD6 input
  GPIO_PORTD_AFSEL_R &= ~0x40;     // 6) disable alt funct on PD6
  GPIO_PORTD_PUR_R &= ~0x40;       // disable pull-up on PD6
  GPIO_PORTD_DEN_R |= 0x40;        // 7) enable digital I/O on PD6
}

// ------------BSP_Button1_Input------------
// Read and return the immediate status of Button1.
// Button de-bouncing is not considered.
// Input: none
// Output: non-zero if Button1 unpressed
//         zero if Button1 pressed
// Assumes: BSP_Button1_Init() has been called
#define BUTTON1   (*((volatile uint32_t *)0x40007100))  /* PD6 */
uint8_t BSP_Button1_Input(void){
  return BUTTON1;                  // return 0(pressed) or 0x40(not pressed)
}

// ------------BSP_Button2_Init------------
// Initialize a GPIO pin for input, which corresponds
// with BoosterPack pin J4.32.
// Input: none
// Output: none
void BSP_Button2_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x00000008; // 1) activate clock for Port D
  while((SYSCTL_PRGPIO_R&0x08) == 0){};// allow time for clock to stabilize
  GPIO_PORTD_LOCK_R = 0x4C4F434B;  // 2) unlock GPIO Port D
  GPIO_PORTD_CR_R = 0xFF;          // allow changes to PD7-0
  GPIO_PORTD_AMSEL_R &= ~0x80;     // 3) disable analog on PD7
                                   // 4) configure PD7 as GPIO
  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x0FFFFFFF)+0x00000000;
  GPIO_PORTD_DIR_R &= ~0x80;       // 5) make PD7 input
  GPIO_PORTD_AFSEL_R &= ~0x80;     // 6) disable alt funct on PD7
  GPIO_PORTD_PUR_R &= ~0x80;       // disable pull-up on PD7
  GPIO_PORTD_DEN_R |= 0x80;        // 7) enable digital I/O on PD7
}

// ------------BSP_Button2_Input------------
// Read and return the immediate status of Button2.
// Button de-bouncing is not considered.
// Input: none
// Output: non-zero if Button2 unpressed
//         zero if Button2 pressed
// Assumes: BSP_Button2_Init() has been called
#define BUTTON2   (*((volatile uint32_t *)0x40007200))  /* PD7 */
uint8_t BSP_Button2_Input(void){
  return BUTTON2;                  // return 0(pressed) or 0x80(not pressed)
}

// There are six analog inputs on the Educational BoosterPack MKII:
// microphone (J1.6/PE5/AIN8)
// joystick X (J1.2/PB5/AIN11) and Y (J3.26/PD3/AIN4)
// accelerometer X (J3.23/PD0/AIN7), Y (J3.24/PD1/AIN6), and Z (J3.25/PD2/AIN5)
// All six initialization functions can use this general ADC
// initialization.  The joystick uses sample sequencer 1,
// the accelerometer sample sequencer 2, and the microphone
// uses sample sequencer 3.
void static adcinit(void){
  SYSCTL_RCGCADC_R |= 0x00000001;  // 1) activate ADC0
  while((SYSCTL_PRADC_R&0x01) == 0){};// 2) allow time for clock to stabilize
                                   // 3-7) GPIO initialization in more specific functions
  ADC0_PC_R &= ~0xF;               // 8) clear max sample rate field
  ADC0_PC_R |= 0x1;                //    configure for 125K samples/sec
  ADC0_SSPRI_R = 0x3210;           // 9) Sequencer 3 is lowest priority
                                   // 10-15) sample sequencer initialization in more specific functions
}

// ------------BSP_Joystick_Init------------
// Initialize a GPIO pin for input, which corresponds
// with BoosterPack pin J1.5 (Select button).
// Initialize two ADC pins, which correspond with
// BoosterPack pins J1.2 (X) and J3.26 (Y).
// Input: none
// Output: none
void BSP_Joystick_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x0000001A; // 1) activate clock for Ports E, D, and B
  while((SYSCTL_PRGPIO_R&0x1A) != 0x1A){};// allow time for clocks to stabilize
                                   // 2) no need to unlock PE4, PD3, or PB5
  GPIO_PORTE_AMSEL_R &= ~0x10;     // 3a) disable analog on PE4
  GPIO_PORTD_AMSEL_R |= 0x08;      // 3b) enable analog on PD3
  GPIO_PORTB_AMSEL_R |= 0x20;      // 3c) enable analog on PB5
                                   // 4) configure PE4 as GPIO
  GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFF0FFFF)+0x00000000;
  GPIO_PORTE_DIR_R &= ~0x10;       // 5a) make PE4 input
  GPIO_PORTD_DIR_R &= ~0x08;       // 5b) make PD3 input
  GPIO_PORTB_DIR_R &= ~0x20;       // 5c) make PB5 input
  GPIO_PORTE_AFSEL_R &= ~0x10;     // 6a) disable alt funct on PE4
  GPIO_PORTD_AFSEL_R |= 0x08;      // 6b) enable alt funct on PD3
  GPIO_PORTB_AFSEL_R |= 0x20;      // 6c) enable alt funct on PB5
  GPIO_PORTE_DEN_R |= 0x10;        // 7a) enable digital I/O on PE4
  GPIO_PORTD_DEN_R &= ~0x08;       // 7b) enable analog functionality on PD3
  GPIO_PORTB_DEN_R &= ~0x20;       // 7c) enable analog functionality on PB5
  adcinit();                       // 8-9) general ADC initialization
  ADC0_ACTSS_R &= ~0x0002;         // 10) disable sample sequencer 1
  ADC0_EMUX_R &= ~0x00F0;          // 11) seq1 is software trigger
  ADC0_SSMUX1_R = 0x004B;          // 12) set channels for SS1
  ADC0_SSCTL1_R = 0x0060;          // 13) no TS0 D0 IE0 END0 TS1 D1, yes IE1 END1
  ADC0_IM_R &= ~0x0002;            // 14) disable SS1 interrupts
  ADC0_ACTSS_R |= 0x0002;          // 15) enable sample sequencer 1
}

// ------------BSP_Joystick_Input------------
// Read and return the immediate status of the
// joystick.  Button de-bouncing for the Select
// button is not considered.  The joystick X- and
// Y-positions are returned as 10-bit numbers,
// even if the ADC on the LaunchPad is more precise.
// Input: x is pointer to store X-position (0 to 1023)
//        y is pointer to store Y-position (0 to 1023)
//        select is pointer to store Select status (0 if pressed)
// Output: none
// Assumes: BSP_Joystick_Init() has been called
#define SELECT    (*((volatile uint32_t *)0x40024040))  /* PE4 */
void BSP_Joystick_Input(uint16_t *x, uint16_t *y, uint8_t *select){
  ADC0_PSSI_R = 0x0002;            // 1) initiate SS1
  while((ADC0_RIS_R&0x02)==0){};   // 2) wait for conversion done
  *x = ADC0_SSFIFO1_R>>2;          // 3a) read first result
  *y = ADC0_SSFIFO1_R>>2;          // 3b) read second result
  *select = SELECT;                // return 0(pressed) or 0x10(not pressed)
  ADC0_ISC_R = 0x0002;             // 4) acknowledge completion
}

// ------------BSP_RGB_Init------------
// Initialize the GPIO and PWM or timer modules which
// correspond with BoosterPack pins J4.39 (red),
// J4.38 (green), and J4.37 (blue).  The frequency
// must be fast enough to not appear to flicker, and
// the duty cycle is represented as a 10-bit number.
// 1023 is fully (or nearly fully) on.
// 0 is fully (or nearly fully) off.
// Input: red is 10-bit duty cycle for red
//        green is 10-bit duty cycle for green
//        blue is 10-bit duty cycle for blue
// Output: none
static uint16_t PWMCycles;         // number of PWM cycles per period
void BSP_RGB_Init(uint16_t red, uint16_t green, uint16_t blue){
  if((red > 1023) || (green > 1023) || (blue > 1023)){
    return;                        // invalid input
  }
  // ***************** Timer1B initialization *****************
  SYSCTL_RCGCTIMER_R |= 0x02;      // activate clock for Timer1
  SYSCTL_RCGCGPIO_R |= 0x0020;     // activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20) == 0){};// allow time for clock to stabilize
  GPIO_PORTF_AFSEL_R |= 0x08;      // enable alt funct on PF3
  GPIO_PORTF_DEN_R |= 0x08;        // enable digital I/O on PF3
                                   // configure PF3 as T1CCP1
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFF0FFF)+0x00007000;
  GPIO_PORTF_AMSEL_R &= ~0x08;     // disable analog functionality on PF3
  while((SYSCTL_PRTIMER_R&0x02) == 0){};// allow time for clock to stabilize
  TIMER1_CTL_R &= ~TIMER_CTL_TBEN; // disable Timer1B during setup
  TIMER1_CFG_R = TIMER_CFG_16_BIT; // configure for 16-bit timer mode
                                   // configure for alternate (PWM) mode
  TIMER1_TBMR_R = (TIMER_TBMR_TBAMS|TIMER_TBMR_TBMR_PERIOD);
  PWMCycles = ClockFrequency/2048;
  TIMER1_TBILR_R = PWMCycles - 1;  // defines when output signal is set
  TIMER1_TBMATCHR_R = (red*PWMCycles)>>10;// defines when output signal is cleared
                                   // enable Timer1B 16-b, PWM, inverted to match comments
  TIMER1_CTL_R |= (TIMER_CTL_TBPWML|TIMER_CTL_TBEN);
  // ***************** Timer3B initialization *****************
  SYSCTL_RCGCTIMER_R |= 0x08;      // activate clock for Timer3
  SYSCTL_RCGCGPIO_R |= 0x0002;     // activate clock for Port B
  while((SYSCTL_PRGPIO_R&0x02) == 0){};// wait for clock to stabilize
  GPIO_PORTB_AFSEL_R |= 0x08;      // enable alt funct on PB3
  GPIO_PORTB_DEN_R |= 0x08;        // enable digital I/O on PB3
                                   // configure PB3 as T3CCP1
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFF0FFF)+0x00007000;
  GPIO_PORTB_AMSEL_R &= ~0x08;     // disable analog functionality on PB3
  while((SYSCTL_PRTIMER_R&0x08) == 0){};// allow time for clock to stabilize
  TIMER3_CTL_R &= ~TIMER_CTL_TBEN; // disable Timer3B during setup
  TIMER3_CFG_R = TIMER_CFG_16_BIT; // configure for 16-bit timer mode
                                   // configure for alternate (PWM) mode
  TIMER3_TBMR_R = (TIMER_TBMR_TBAMS|TIMER_TBMR_TBMR_PERIOD);
  TIMER3_TBILR_R = PWMCycles - 1;  // defines when output signal is set
  TIMER3_TBMATCHR_R = (green*PWMCycles)>>10;// defines when output signal is cleared
                                   // enable Timer3B 16-b, PWM, inverted to match comments
  TIMER3_CTL_R |= (TIMER_CTL_TBPWML|TIMER_CTL_TBEN);
  // ***************** Wide Timer0A initialization *****************
  SYSCTL_RCGCWTIMER_R |= 0x01;     // activate clock for Wide Timer0
  SYSCTL_RCGCGPIO_R |= 0x0004;     // activate clock for Port C
  while((SYSCTL_PRGPIO_R&0x04) == 0){};// allow time for clock to stabilize
  GPIO_PORTC_AFSEL_R |= 0x10;      // enable alt funct on PC4
  GPIO_PORTC_DEN_R |= 0x10;        // enable digital I/O on PC4
                                   // configure PC4 as WT0CCP0
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFFF0FFFF)+0x00070000;
  GPIO_PORTC_AMSEL_R &= ~0x10;     // disable analog functionality on PC4
  while((SYSCTL_PRWTIMER_R&0x01) == 0){};// allow time for clock to stabilize
  WTIMER0_CTL_R &= ~TIMER_CTL_TAEN;// disable Wide Timer0A during setup
  WTIMER0_CFG_R = TIMER_CFG_16_BIT;// configure for 32-bit timer mode
                                   // configure for alternate (PWM) mode
  WTIMER0_TAMR_R = (TIMER_TAMR_TAAMS|TIMER_TAMR_TAMR_PERIOD);
  WTIMER0_TAILR_R = PWMCycles - 1; // defines when output signal is set
  WTIMER0_TAMATCHR_R = (blue*PWMCycles)>>10;// defines when output signal is cleared
                                   // enable Wide Timer0A 32-b, PWM, inverted to match comments
  WTIMER0_CTL_R |= (TIMER_CTL_TAPWML|TIMER_CTL_TAEN);
}

// ------------BSP_RGB_Set------------
// Set new duty cycles for the RGB LEDs.
// 1023 is fully (or nearly fully) on.
// 0 is fully (or nearly fully) off.
// Input: red is 10-bit duty cycle for red
//        green is 10-bit duty cycle for green
//        blue is 10-bit duty cycle for blue
// Output: none
// Assumes: BSP_RGB_Init() has been called
void BSP_RGB_Set(uint16_t red, uint16_t green, uint16_t blue){
  if((red > 1023) || (green > 1023) || (blue > 1023)){
    return;                        // invalid input
  }
  TIMER1_TBMATCHR_R = (red*PWMCycles)>>10;// defines when output signal is cleared
  TIMER3_TBMATCHR_R = (green*PWMCycles)>>10;// defines when output signal is cleared
  WTIMER0_TAMATCHR_R = (blue*PWMCycles)>>10;// defines when output signal is cleared
}

// ------------BSP_RGB_D_Init------------
// Initialize the GPIO pins for output which
// correspond with BoosterPack pins J4.39 (red),
// J4.38 (green), and J4.37 (blue).  Instead of using
// PWM or timer modules, this configuration uses just
// digital fully on or fully off.
// non-zero is fully on.
// 0 is fully off.
// Input: red is initial status for red
//        green is initial status for green
//        blue is initial status for blue
// Output: none
#define RED       (*((volatile uint32_t *)0x40025020))  /* PF3 */
#define GREEN     (*((volatile uint32_t *)0x40005020))  /* PB3 */
#define BLUE      (*((volatile uint32_t *)0x40006040))  /* PC4 */
void BSP_RGB_D_Init(int red, int green, int blue){
  SYSCTL_RCGCGPIO_R |= 0x00000026; // 1) activate clock for Ports F, C, and B
  while((SYSCTL_PRGPIO_R&0x26) != 0x26){};// allow time for clocks to stabilize
                                   // 2) no need to unlock PF3, PC4, or PB3
  GPIO_PORTF_AMSEL_R &= ~0x08;     // 3a) disable analog on PF3
  GPIO_PORTC_AMSEL_R &= ~0x10;     // 3b) disable analog on PC4
  GPIO_PORTB_AMSEL_R &= ~0x08;     // 3c) disable analog on PB3
                                   // 4a) configure PF3 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFF0FFF)+0x00000000;
                                   // 4b) configure PC4 as GPIO
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFFF0FFFF)+0x00000000;
                                   // 4c) configure PB3 as GPIO
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFF0FFF)+0x00000000;
  GPIO_PORTF_DIR_R |= 0x08;        // 5a) make PF3 output
  GPIO_PORTC_DIR_R |= 0x10;        // 5b) make PC4 output
  GPIO_PORTB_DIR_R |= 0x08;        // 5c) make PB3 output
  GPIO_PORTF_AFSEL_R &= ~0x08;     // 6a) disable alt funct on PF3
  GPIO_PORTC_AFSEL_R &= ~0x10;     // 6b) disable alt funct on PC4
  GPIO_PORTB_AFSEL_R &= ~0x08;     // 6c) disable alt funct on PB3
  GPIO_PORTF_PUR_R &= ~0x08;       // disable pull-up on PF3
  GPIO_PORTC_PUR_R &= ~0x10;       // disable pull-up on PC4
  GPIO_PORTB_PUR_R &= ~0x08;       // disable pull-up on PB3
  GPIO_PORTF_DEN_R |= 0x08;        // 7a) enable digital I/O on PF3
  GPIO_PORTC_DEN_R |= 0x10;        // 7b) enable digital I/O on PC4
  GPIO_PORTB_DEN_R |= 0x08;        // 7c) enable digital I/O on PB3
  BSP_RGB_D_Set(red, green, blue);
}

// ------------BSP_RGB_D_Set------------
// Set new statuses for the RGB LEDs.
// non-zero is fully on.
// 0 is fully off.
// Input: red is status for red
//        green is status for green
//        blue is status for blue
// Output: none
// Assumes: BSP_RGB_D_Init() has been called
void BSP_RGB_D_Set(int red, int green, int blue){
  if(red){
    RED = 0x08;
  } else{
    RED = 0x00;
  }
  if(green){
    GREEN = 0x08;
  } else{
    GREEN = 0x00;
  }
  if(blue){
    BLUE = 0x10;
  } else{
    BLUE = 0x00;
  }
}

// ------------BSP_RGB_D_Toggle------------
// Toggle the statuses of the RGB LEDs.
// non-zero is toggle.
// 0 is do not toggle.
// Input: red is toggle for red
//        green is toggle for green
//        blue is toggle for blue
// Output: none
// Assumes: BSP_RGB_D_Init() has been called
void BSP_RGB_D_Toggle(int red, int green, int blue){
  if(red){
    RED = RED^0x08;
  }
  if(green){
    GREEN = GREEN^0x08;
  }
  if(blue){
    BLUE = BLUE^0x10;
  }
}

// ------------BSP_Buzzer_Init------------
// Initialize the GPIO and PWM or timer modules which
// correspond with BoosterPack pin J4.40.  The
// frequency is 2048 Hz, and the duty cycle is
// represented as a 10-bit number.
// Input: duty is 10-bit duty cycle for the buzzer
// Output: none
void BSP_Buzzer_Init(uint16_t duty){
  if(duty > 1023){
    return;                        // invalid input
  }
  // ***************** Timer1A initialization *****************
  SYSCTL_RCGCTIMER_R |= 0x02;      // activate clock for Timer1
  SYSCTL_RCGCGPIO_R |= 0x0020;     // activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20) == 0){};// allow time for clock to stabilize
  GPIO_PORTF_AFSEL_R |= 0x04;      // enable alt funct on PF2
  GPIO_PORTF_DEN_R |= 0x04;        // enable digital I/O on PF2
                                   // configure PF2 as T1CCP0
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000700;
  GPIO_PORTF_AMSEL_R &= ~0x04;     // disable analog functionality on PF2
  while((SYSCTL_PRTIMER_R&0x02) == 0){};// allow time for clock to stabilize
  TIMER1_CTL_R &= ~TIMER_CTL_TAEN; // disable Timer1A during setup
  TIMER1_CFG_R = TIMER_CFG_16_BIT; // configure for 16-bit timer mode
                                   // configure for alternate (PWM) mode
  TIMER1_TAMR_R = (TIMER_TAMR_TAAMS|TIMER_TAMR_TAMR_PERIOD);
  PWMCycles = ClockFrequency/2048;
  TIMER1_TAILR_R = PWMCycles - 1;  // defines when output signal is set
  TIMER1_TAMATCHR_R = (duty*PWMCycles)>>10;// defines when output signal is cleared
                                   // enable Timer1A 16-b, PWM, inverted to match comments
  TIMER1_CTL_R |= (TIMER_CTL_TAPWML|TIMER_CTL_TAEN);
}

// ------------BSP_Buzzer_Set------------
// Set new duty cycle for the buzzer.
// 512 is typical for sound (50% duty cycle).
// 0 is typical for silent (0% duty cycle).
// Input: duty is 10-bit duty cycle for the buzzer
// Output: none
// Assumes: BSP_Buzzer_Init() has been called
void BSP_Buzzer_Set(uint16_t duty){
  if(duty > 1023){
    return;                        // invalid input
  }
  TIMER1_TAMATCHR_R = (duty*PWMCycles)>>10;// defines when output signal is cleared
}

// ------------BSP_Accelerometer_Init------------
// Initialize three ADC pins, which correspond with
// BoosterPack pins J3.23 (X), J3.24 (Y), and
// J3.25 (Y).
// Input: none
// Output: none
void BSP_Accelerometer_Init(void){
  adcinit();
  SYSCTL_RCGCGPIO_R |= 0x00000008; // 1) activate clock for Port D
  while((SYSCTL_PRGPIO_R&0x08) == 0){};// allow time for clock to stabilize
                                   // 2) no need to unlock PD2-0
  GPIO_PORTD_AMSEL_R |= 0x07;      // 3) enable analog on PD2-0
                                   // 4) configure PD2-0 as ?? (skip this line because PCTL is for digital only)
  GPIO_PORTD_DIR_R &= ~0x07;       // 5) make PD2-0 input
  GPIO_PORTD_AFSEL_R |= 0x07;      // 6) enable alt funct on PD2-0
  GPIO_PORTD_DEN_R &= ~0x07;       // 7) enable analog functionality on PD2-0
  adcinit();                       // 8-9) general ADC initialization
  ADC0_ACTSS_R &= ~0x0004;         // 10) disable sample sequencer 2
  ADC0_EMUX_R &= ~0x0F00;          // 11) seq2 is software trigger
  ADC0_SSMUX2_R = 0x0567;          // 12) set channels for SS2
  ADC0_SSCTL2_R = 0x0600;          // 13) no D0 END0 IE0 TS0 D1 END1 IE1 TS1 D2 TS2, yes IE2 END2
  ADC0_IM_R &= ~0x0004;            // 14) disable SS2 interrupts
  ADC0_ACTSS_R |= 0x0004;          // 15) enable sample sequencer 2
}

// ------------BSP_Accelerometer_Input------------
// Read and return the immediate status of the
// accelerometer.  The accelerometer X-, Y-, and
// Z-measurements are returned as 10-bit numbers,
// even if the ADC on the LaunchPad is more precise.
// Input: x is pointer to store X-measurement (0 to 1023)
//        y is pointer to store Y-measurement (0 to 1023)
//        z is pointer to store Z-measurement (0 to 1023)
// Output: none
// Assumes: BSP_Accelerometer_Init() has been called
void BSP_Accelerometer_Input(uint16_t *x, uint16_t *y, uint16_t *z){
  ADC0_PSSI_R = 0x0004;            // 1) initiate SS2
  while((ADC0_RIS_R&0x04)==0){};   // 2) wait for conversion done
  *x = ADC0_SSFIFO2_R>>2;          // 3a) read first result
  *y = ADC0_SSFIFO2_R>>2;          // 3b) read second result
  *z = ADC0_SSFIFO2_R>>2;          // 3c) read third result
  ADC0_ISC_R = 0x0004;             // 4) acknowledge completion
}

// ------------BSP_Microphone_Init------------
// Initialize one ADC pin, which corresponds with
// BoosterPack pin J1.6.
// Input: none
// Output: none
void BSP_Microphone_Init(void){
  adcinit();
  SYSCTL_RCGCGPIO_R |= 0x00000010; // 1) activate clock for Port E
  while((SYSCTL_PRGPIO_R&0x10) == 0){};// allow time for clock to stabilize
                                   // 2) no need to unlock PE5
  GPIO_PORTE_AMSEL_R |= 0x20;      // 3) enable analog on PE5
                                   // 4) configure PE5 as ?? (skip this line because PCTL is for digital only)
  GPIO_PORTE_DIR_R &= ~0x20;       // 5) make PE5 input
  GPIO_PORTE_AFSEL_R |= 0x20;      // 6) enable alt funct on PE5
  GPIO_PORTE_DEN_R &= ~0x20;       // 7) enable analog functionality on PE5
  adcinit();                       // 8-9) general ADC initialization
  ADC0_ACTSS_R &= ~0x0008;         // 10) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;          // 11) seq3 is software trigger
  ADC0_SSMUX3_R = 0x0008;          // 12) set channels for SS3
  ADC0_SSCTL3_R = 0x0006;          // 13) no D0 TS0, yes IE0 END0
  ADC0_IM_R &= ~0x0008;            // 14) disable SS3 interrupts
  ADC0_ACTSS_R |= 0x0008;          // 15) enable sample sequencer 3
}

// ------------BSP_Microphone_Input------------
// Read and return the immediate status of the
// microphone.  The sound measurement is returned
// as a 10-bit number, even if the ADC on the
// LaunchPad is more precise.
// Input: mic is pointer to store sound measurement (0 to 1023)
// Output: none
// Assumes: BSP_Microphone_Init() has been called
void BSP_Microphone_Input(uint16_t *mic){
  ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
  *mic = ADC0_SSFIFO3_R>>2;        // 3) read result
  ADC0_ISC_R = 0x0008;             // 4) acknowledge completion
}

/* ********************** */
/*      LCD Section       */
/* ********************** */
// This section is based on ST7735.c, which itself is based
// on example code originally from Adafruit.  Some sections
// such as the font table and initialization functions were
// copied verbatim from Adafruit's example and are subject
// to the following disclosure.
/***************************************************
  This is a library for the Adafruit 1.8" SPI display.
  This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
  as well as Adafruit raw 1.8" TFT displayun
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
// some flags for ST7735_InitR()
enum initRFlags{
  none,
  INITR_GREENTAB,
  INITR_REDTAB,
  INITR_BLACKTAB
};

#define ST7735_TFTWIDTH  128
#define ST7735_TFTHEIGHT 128


// Color definitions
#define ST7735_BLACK   0x0000
#define ST7735_BLUE    0x001F
#define ST7735_RED     0xF800
#define ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF


// 12 rows (0 to 11) and 21 characters (0 to 20)
// Requires (11 + size*size*6*8) bytes of transmission for each character
uint32_t StX=0; // position along the horizonal axis 0 to 20
uint32_t StY=0; // position along the vertical axis 0 to 11
uint16_t StTextColor = ST7735_YELLOW;

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

#define TFT_CS                  (*((volatile uint32_t *)0x40004040))  /* PA4 */
#define TFT_CS_LOW              0x00
#define TFT_CS_HIGH             0x10
#define DC                      (*((volatile uint32_t *)0x40025040))  /* PF4 */
#define DC_COMMAND              0x00
#define DC_DATA                 0x10
#define RESET                   (*((volatile uint32_t *)0x40025004))  /* PF0 */
#define RESET_LOW               0x00
#define RESET_HIGH              0x01

// standard ascii 5x7 font
// originally from glcdfont.c from Adafruit project
static const uint8_t Font[] = {
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
  0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
  0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
  0x18, 0x3C, 0x7E, 0x3C, 0x18,
  0x1C, 0x57, 0x7D, 0x57, 0x1C,
  0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
  0x00, 0x18, 0x3C, 0x18, 0x00,
  0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
  0x00, 0x18, 0x24, 0x18, 0x00,
  0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
  0x30, 0x48, 0x3A, 0x06, 0x0E,
  0x26, 0x29, 0x79, 0x29, 0x26,
  0x40, 0x7F, 0x05, 0x05, 0x07,
  0x40, 0x7F, 0x05, 0x25, 0x3F,
  0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
  0x7F, 0x3E, 0x1C, 0x1C, 0x08,
  0x08, 0x1C, 0x1C, 0x3E, 0x7F,
  0x14, 0x22, 0x7F, 0x22, 0x14,
  0x5F, 0x5F, 0x00, 0x5F, 0x5F,
  0x06, 0x09, 0x7F, 0x01, 0x7F,
  0x00, 0x66, 0x89, 0x95, 0x6A,
  0x60, 0x60, 0x60, 0x60, 0x60,
  0x94, 0xA2, 0xFF, 0xA2, 0x94,
  0x08, 0x04, 0x7E, 0x04, 0x08,
  0x10, 0x20, 0x7E, 0x20, 0x10,
  0x08, 0x08, 0x2A, 0x1C, 0x08,
  0x08, 0x1C, 0x2A, 0x08, 0x08,
  0x1E, 0x10, 0x10, 0x10, 0x10,
  0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
  0x30, 0x38, 0x3E, 0x38, 0x30,
  0x06, 0x0E, 0x3E, 0x0E, 0x06,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x5F, 0x00, 0x00,
  0x00, 0x07, 0x00, 0x07, 0x00,
  0x14, 0x7F, 0x14, 0x7F, 0x14,
  0x24, 0x2A, 0x7F, 0x2A, 0x12,
  0x23, 0x13, 0x08, 0x64, 0x62,
  0x36, 0x49, 0x56, 0x20, 0x50,
  0x00, 0x08, 0x07, 0x03, 0x00,
  0x00, 0x1C, 0x22, 0x41, 0x00,
  0x00, 0x41, 0x22, 0x1C, 0x00,
  0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
  0x08, 0x08, 0x3E, 0x08, 0x08,
  0x00, 0x80, 0x70, 0x30, 0x00,
  0x08, 0x08, 0x08, 0x08, 0x08,
  0x00, 0x00, 0x60, 0x60, 0x00,
  0x20, 0x10, 0x08, 0x04, 0x02,
  0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
  0x00, 0x42, 0x7F, 0x40, 0x00, // 1
  0x72, 0x49, 0x49, 0x49, 0x46, // 2
  0x21, 0x41, 0x49, 0x4D, 0x33, // 3
  0x18, 0x14, 0x12, 0x7F, 0x10, // 4
  0x27, 0x45, 0x45, 0x45, 0x39, // 5
  0x3C, 0x4A, 0x49, 0x49, 0x31, // 6
  0x41, 0x21, 0x11, 0x09, 0x07, // 7
  0x36, 0x49, 0x49, 0x49, 0x36, // 8
  0x46, 0x49, 0x49, 0x29, 0x1E, // 9
  0x00, 0x00, 0x14, 0x00, 0x00,
  0x00, 0x40, 0x34, 0x00, 0x00,
  0x00, 0x08, 0x14, 0x22, 0x41,
  0x14, 0x14, 0x14, 0x14, 0x14,
  0x00, 0x41, 0x22, 0x14, 0x08,
  0x02, 0x01, 0x59, 0x09, 0x06,
  0x3E, 0x41, 0x5D, 0x59, 0x4E,
  0x7C, 0x12, 0x11, 0x12, 0x7C, // A
  0x7F, 0x49, 0x49, 0x49, 0x36, // B
  0x3E, 0x41, 0x41, 0x41, 0x22, // C
  0x7F, 0x41, 0x41, 0x41, 0x3E, // D
  0x7F, 0x49, 0x49, 0x49, 0x41, // E
  0x7F, 0x09, 0x09, 0x09, 0x01, // F
  0x3E, 0x41, 0x41, 0x51, 0x73, // G
  0x7F, 0x08, 0x08, 0x08, 0x7F, // H
  0x00, 0x41, 0x7F, 0x41, 0x00, // I
  0x20, 0x40, 0x41, 0x3F, 0x01, // J
  0x7F, 0x08, 0x14, 0x22, 0x41, // K
  0x7F, 0x40, 0x40, 0x40, 0x40, // L
  0x7F, 0x02, 0x1C, 0x02, 0x7F, // M
  0x7F, 0x04, 0x08, 0x10, 0x7F, // N
  0x3E, 0x41, 0x41, 0x41, 0x3E, // O
  0x7F, 0x09, 0x09, 0x09, 0x06, // P
  0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
  0x7F, 0x09, 0x19, 0x29, 0x46, // R
  0x26, 0x49, 0x49, 0x49, 0x32, // S
  0x03, 0x01, 0x7F, 0x01, 0x03, // T
  0x3F, 0x40, 0x40, 0x40, 0x3F, // U
  0x1F, 0x20, 0x40, 0x20, 0x1F, // V
  0x3F, 0x40, 0x38, 0x40, 0x3F, // W
  0x63, 0x14, 0x08, 0x14, 0x63, // X
  0x03, 0x04, 0x78, 0x04, 0x03, // Y
  0x61, 0x59, 0x49, 0x4D, 0x43, // Z
  0x00, 0x7F, 0x41, 0x41, 0x41,
  0x02, 0x04, 0x08, 0x10, 0x20,
  0x00, 0x41, 0x41, 0x41, 0x7F,
  0x04, 0x02, 0x01, 0x02, 0x04,
  0x40, 0x40, 0x40, 0x40, 0x40,
  0x00, 0x03, 0x07, 0x08, 0x00,
  0x20, 0x54, 0x54, 0x78, 0x40, // a
  0x7F, 0x28, 0x44, 0x44, 0x38, // b
  0x38, 0x44, 0x44, 0x44, 0x28, // c
  0x38, 0x44, 0x44, 0x28, 0x7F, // d
  0x38, 0x54, 0x54, 0x54, 0x18, // e
  0x00, 0x08, 0x7E, 0x09, 0x02, // f
  0x18, 0xA4, 0xA4, 0x9C, 0x78, // g
  0x7F, 0x08, 0x04, 0x04, 0x78, // h
  0x00, 0x44, 0x7D, 0x40, 0x00, // i
  0x20, 0x40, 0x40, 0x3D, 0x00, // j
  0x7F, 0x10, 0x28, 0x44, 0x00, // k
  0x00, 0x41, 0x7F, 0x40, 0x00, // l
  0x7C, 0x04, 0x78, 0x04, 0x78, // m
  0x7C, 0x08, 0x04, 0x04, 0x78, // n
  0x38, 0x44, 0x44, 0x44, 0x38, // o
  0xFC, 0x18, 0x24, 0x24, 0x18, // p
  0x18, 0x24, 0x24, 0x18, 0xFC, // q
  0x7C, 0x08, 0x04, 0x04, 0x08, // r
  0x48, 0x54, 0x54, 0x54, 0x24, // s
  0x04, 0x04, 0x3F, 0x44, 0x24, // t
  0x3C, 0x40, 0x40, 0x20, 0x7C, // u
  0x1C, 0x20, 0x40, 0x20, 0x1C, // v
  0x3C, 0x40, 0x30, 0x40, 0x3C, // w
  0x44, 0x28, 0x10, 0x28, 0x44, // x
  0x4C, 0x90, 0x90, 0x90, 0x7C, // y
  0x44, 0x64, 0x54, 0x4C, 0x44, // z
  0x00, 0x08, 0x36, 0x41, 0x00,
  0x00, 0x00, 0x77, 0x00, 0x00,
  0x00, 0x41, 0x36, 0x08, 0x00,
  0x02, 0x01, 0x02, 0x04, 0x02,
  0x3C, 0x26, 0x23, 0x26, 0x3C,
  0x1E, 0xA1, 0xA1, 0x61, 0x12,
  0x3A, 0x40, 0x40, 0x20, 0x7A,
  0x38, 0x54, 0x54, 0x55, 0x59,
  0x21, 0x55, 0x55, 0x79, 0x41,
  0x21, 0x54, 0x54, 0x78, 0x41,
  0x21, 0x55, 0x54, 0x78, 0x40,
  0x20, 0x54, 0x55, 0x79, 0x40,
  0x0C, 0x1E, 0x52, 0x72, 0x12,
  0x39, 0x55, 0x55, 0x55, 0x59,
  0x39, 0x54, 0x54, 0x54, 0x59,
  0x39, 0x55, 0x54, 0x54, 0x58,
  0x00, 0x00, 0x45, 0x7C, 0x41,
  0x00, 0x02, 0x45, 0x7D, 0x42,
  0x00, 0x01, 0x45, 0x7C, 0x40,
  0xF0, 0x29, 0x24, 0x29, 0xF0,
  0xF0, 0x28, 0x25, 0x28, 0xF0,
  0x7C, 0x54, 0x55, 0x45, 0x00,
  0x20, 0x54, 0x54, 0x7C, 0x54,
  0x7C, 0x0A, 0x09, 0x7F, 0x49,
  0x32, 0x49, 0x49, 0x49, 0x32,
  0x32, 0x48, 0x48, 0x48, 0x32,
  0x32, 0x4A, 0x48, 0x48, 0x30,
  0x3A, 0x41, 0x41, 0x21, 0x7A,
  0x3A, 0x42, 0x40, 0x20, 0x78,
  0x00, 0x9D, 0xA0, 0xA0, 0x7D,
  0x39, 0x44, 0x44, 0x44, 0x39,
  0x3D, 0x40, 0x40, 0x40, 0x3D,
  0x3C, 0x24, 0xFF, 0x24, 0x24,
  0x48, 0x7E, 0x49, 0x43, 0x66,
  0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
  0xFF, 0x09, 0x29, 0xF6, 0x20,
  0xC0, 0x88, 0x7E, 0x09, 0x03,
  0x20, 0x54, 0x54, 0x79, 0x41,
  0x00, 0x00, 0x44, 0x7D, 0x41,
  0x30, 0x48, 0x48, 0x4A, 0x32,
  0x38, 0x40, 0x40, 0x22, 0x7A,
  0x00, 0x7A, 0x0A, 0x0A, 0x72,
  0x7D, 0x0D, 0x19, 0x31, 0x7D,
  0x26, 0x29, 0x29, 0x2F, 0x28,
  0x26, 0x29, 0x29, 0x29, 0x26,
  0x30, 0x48, 0x4D, 0x40, 0x20,
  0x38, 0x08, 0x08, 0x08, 0x08,
  0x08, 0x08, 0x08, 0x08, 0x38,
  0x2F, 0x10, 0xC8, 0xAC, 0xBA,
  0x2F, 0x10, 0x28, 0x34, 0xFA,
  0x00, 0x00, 0x7B, 0x00, 0x00,
  0x08, 0x14, 0x2A, 0x14, 0x22,
  0x22, 0x14, 0x2A, 0x14, 0x08,
  0xAA, 0x00, 0x55, 0x00, 0xAA,
  0xAA, 0x55, 0xAA, 0x55, 0xAA,
  0x00, 0x00, 0x00, 0xFF, 0x00,
  0x10, 0x10, 0x10, 0xFF, 0x00,
  0x14, 0x14, 0x14, 0xFF, 0x00,
  0x10, 0x10, 0xFF, 0x00, 0xFF,
  0x10, 0x10, 0xF0, 0x10, 0xF0,
  0x14, 0x14, 0x14, 0xFC, 0x00,
  0x14, 0x14, 0xF7, 0x00, 0xFF,
  0x00, 0x00, 0xFF, 0x00, 0xFF,
  0x14, 0x14, 0xF4, 0x04, 0xFC,
  0x14, 0x14, 0x17, 0x10, 0x1F,
  0x10, 0x10, 0x1F, 0x10, 0x1F,
  0x14, 0x14, 0x14, 0x1F, 0x00,
  0x10, 0x10, 0x10, 0xF0, 0x00,
  0x00, 0x00, 0x00, 0x1F, 0x10,
  0x10, 0x10, 0x10, 0x1F, 0x10,
  0x10, 0x10, 0x10, 0xF0, 0x10,
  0x00, 0x00, 0x00, 0xFF, 0x10,
  0x10, 0x10, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x10, 0xFF, 0x10,
  0x00, 0x00, 0x00, 0xFF, 0x14,
  0x00, 0x00, 0xFF, 0x00, 0xFF,
  0x00, 0x00, 0x1F, 0x10, 0x17,
  0x00, 0x00, 0xFC, 0x04, 0xF4,
  0x14, 0x14, 0x17, 0x10, 0x17,
  0x14, 0x14, 0xF4, 0x04, 0xF4,
  0x00, 0x00, 0xFF, 0x00, 0xF7,
  0x14, 0x14, 0x14, 0x14, 0x14,
  0x14, 0x14, 0xF7, 0x00, 0xF7,
  0x14, 0x14, 0x14, 0x17, 0x14,
  0x10, 0x10, 0x1F, 0x10, 0x1F,
  0x14, 0x14, 0x14, 0xF4, 0x14,
  0x10, 0x10, 0xF0, 0x10, 0xF0,
  0x00, 0x00, 0x1F, 0x10, 0x1F,
  0x00, 0x00, 0x00, 0x1F, 0x14,
  0x00, 0x00, 0x00, 0xFC, 0x14,
  0x00, 0x00, 0xF0, 0x10, 0xF0,
  0x10, 0x10, 0xFF, 0x10, 0xFF,
  0x14, 0x14, 0x14, 0xFF, 0x14,
  0x10, 0x10, 0x10, 0x1F, 0x00,
  0x00, 0x00, 0x00, 0xF0, 0x10,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
  0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF,
  0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
  0x38, 0x44, 0x44, 0x38, 0x44,
  0x7C, 0x2A, 0x2A, 0x3E, 0x14,
  0x7E, 0x02, 0x02, 0x06, 0x06,
  0x02, 0x7E, 0x02, 0x7E, 0x02,
  0x63, 0x55, 0x49, 0x41, 0x63,
  0x38, 0x44, 0x44, 0x3C, 0x04,
  0x40, 0x7E, 0x20, 0x1E, 0x20,
  0x06, 0x02, 0x7E, 0x02, 0x02,
  0x99, 0xA5, 0xE7, 0xA5, 0x99,
  0x1C, 0x2A, 0x49, 0x2A, 0x1C,
  0x4C, 0x72, 0x01, 0x72, 0x4C,
  0x30, 0x4A, 0x4D, 0x4D, 0x30,
  0x30, 0x48, 0x78, 0x48, 0x30,
  0xBC, 0x62, 0x5A, 0x46, 0x3D,
  0x3E, 0x49, 0x49, 0x49, 0x00,
  0x7E, 0x01, 0x01, 0x01, 0x7E,
  0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
  0x44, 0x44, 0x5F, 0x44, 0x44,
  0x40, 0x51, 0x4A, 0x44, 0x40,
  0x40, 0x44, 0x4A, 0x51, 0x40,
  0x00, 0x00, 0xFF, 0x01, 0x03,
  0xE0, 0x80, 0xFF, 0x00, 0x00,
  0x08, 0x08, 0x6B, 0x6B, 0x08,
  0x36, 0x12, 0x36, 0x24, 0x36,
  0x06, 0x0F, 0x09, 0x0F, 0x06,
  0x00, 0x00, 0x18, 0x18, 0x00,
  0x00, 0x00, 0x10, 0x10, 0x00,
  0x30, 0x40, 0xFF, 0x01, 0x01,
  0x00, 0x1F, 0x01, 0x01, 0x1E,
  0x00, 0x19, 0x1D, 0x17, 0x12,
  0x00, 0x3C, 0x3C, 0x3C, 0x3C,
  0x00, 0x00, 0x00, 0x00, 0x00,
};


static uint8_t ColStart, RowStart; // some displays need this changed
//static uint8_t Rotation;           // 0 to 3
//static enum initRFlags TabColor;
static int16_t _width = ST7735_TFTWIDTH;   // this could probably be a constant, except it is used in Adafruit_GFX and depends on image rotation
static int16_t _height = ST7735_TFTHEIGHT;


// The Data/Command pin must be valid when the eighth bit is
// sent.  The SSI module has hardware input and output FIFOs
// that are 8 locations deep; however, they are not used in
// this implementation.  Each function first stalls while
// waiting for any pending SSI2 transfers to complete.  Once
// the SSI2 module is idle, it then prepares the Chip Select
// pin for the LCD and the Data/Command pin.  Next it starts
// transmitting the data or command.  Finally once the
// hardware is idle again, it sets the chip select pin high
// as required by the serial protocol.  This is a
// significant change from previous implementations of this
// function.  It is less efficient without the FIFOs, but it
// should ensure that the Chip Select and Data/Command pin
// statuses all match the byte that is actually being
// transmitted.
// NOTE: These functions will crash or stall indefinitely if
// the SSI2 module is not initialized and enabled.

// This is a helper function that sends an 8-bit command to the LCD.
// Inputs: c  8-bit code to transmit
// Outputs: 8-bit reply
// Assumes: SSI2 and ports have already been initialized and enabled
uint8_t static writecommand(uint8_t c) {
                                        // wait until SSI2 not busy/transmit FIFO empty
  while((SSI2_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};
  TFT_CS = TFT_CS_LOW;
  DC = DC_COMMAND;
  SSI2_DR_R = c;                        // data out
  while((SSI2_SR_R&SSI_SR_RNE)==0){};   // wait until response
  TFT_CS = TFT_CS_HIGH;
  return (uint8_t)SSI2_DR_R;            // return the response
}


// This is a helper function that sends a piece of 8-bit data to the LCD.
// Inputs: c  8-bit data to transmit
// Outputs: 8-bit reply
// Assumes: SSI2 and ports have already been initialized and enabled
uint8_t static writedata(uint8_t c) {
                                        // wait until SSI2 not busy/transmit FIFO empty
  while((SSI2_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};
  TFT_CS = TFT_CS_LOW;
  DC = DC_DATA;
  SSI2_DR_R = c;                        // data out
  while((SSI2_SR_R&SSI_SR_RNE)==0){};   // wait until response
  TFT_CS = TFT_CS_HIGH;
  return (uint8_t)SSI2_DR_R;            // return the response
}


// delay function from sysctl.c
// which delays 3.3*ulCount cycles
// ulCount=23746 => 1ms = 23746*3.3cycle/loop/80,000
#ifdef __TI_COMPILER_VERSION__
  //Code Composer Studio Code
  void parrotdelay(uint32_t ulCount){
  __asm (  "    subs    r0, #1\n"
      "    bne     Delay\n"
      "    bx      lr\n");
}

#else
  //Keil uVision Code
  __asm void
  parrotdelay(uint32_t ulCount)
  {
    subs    r0, #1
    bne     parrotdelay
    bx      lr
  }

#endif


// Rather than a bazillion writecommand() and writedata() calls, screen
// initialization commands and arguments are organized in these tables
// stored in ROM.  The table may look bulky, but that's mostly the
// formatting -- storage-wise this is hundreds of bytes more compact
// than the equivalent code.  Companion function follows.
#define DELAY 0x80
//static const uint8_t
//  Bcmd[] = {                  // Initialization commands for 7735B screens
//    18,                       // 18 commands in list:
//    ST7735_SWRESET,   DELAY,  //  1: Software reset, no args, w/delay
//      50,                     //     50 ms delay
//    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, no args, w/delay
//      255,                    //     255 = 500 ms delay
//    ST7735_COLMOD , 1+DELAY,  //  3: Set color mode, 1 arg + delay:
//      0x05,                   //     16-bit color
//      10,                     //     10 ms delay
//    ST7735_FRMCTR1, 3+DELAY,  //  4: Frame rate control, 3 args + delay:
//      0x00,                   //     fastest refresh
//      0x06,                   //     6 lines front porch
//      0x03,                   //     3 lines back porch
//      10,                     //     10 ms delay
//    ST7735_MADCTL , 1      ,  //  5: Memory access ctrl (directions), 1 arg:
//      0x08,                   //     Row addr/col addr, bottom to top refresh
//    ST7735_DISSET5, 2      ,  //  6: Display settings #5, 2 args, no delay:
//      0x15,                   //     1 clk cycle nonoverlap, 2 cycle gate
//                              //     rise, 3 cycle osc equalize
//      0x02,                   //     Fix on VTL
//    ST7735_INVCTR , 1      ,  //  7: Display inversion control, 1 arg:
//      0x0,                    //     Line inversion
//    ST7735_PWCTR1 , 2+DELAY,  //  8: Power control, 2 args + delay:
//      0x02,                   //     GVDD = 4.7V
//      0x70,                   //     1.0uA
//      10,                     //     10 ms delay
//    ST7735_PWCTR2 , 1      ,  //  9: Power control, 1 arg, no delay:
//      0x05,                   //     VGH = 14.7V, VGL = -7.35V
//    ST7735_PWCTR3 , 2      ,  // 10: Power control, 2 args, no delay:
//      0x01,                   //     Opamp current small
//      0x02,                   //     Boost frequency
//    ST7735_VMCTR1 , 2+DELAY,  // 11: Power control, 2 args + delay:
//      0x3C,                   //     VCOMH = 4V
//      0x38,                   //     VCOML = -1.1V
//      10,                     //     10 ms delay
//    ST7735_PWCTR6 , 2      ,  // 12: Power control, 2 args, no delay:
//      0x11, 0x15,
//    ST7735_GMCTRP1,16      ,  // 13: Magical unicorn dust, 16 args, no delay:
//      0x09, 0x16, 0x09, 0x20, //     (seriously though, not sure what
//      0x21, 0x1B, 0x13, 0x19, //      these config values represent)
//      0x17, 0x15, 0x1E, 0x2B,
//      0x04, 0x05, 0x02, 0x0E,
//    ST7735_GMCTRN1,16+DELAY,  // 14: Sparkles and rainbows, 16 args + delay:
//      0x0B, 0x14, 0x08, 0x1E, //     (ditto)
//      0x22, 0x1D, 0x18, 0x1E,
//      0x1B, 0x1A, 0x24, 0x2B,
//      0x06, 0x06, 0x02, 0x0F,
//      10,                     //     10 ms delay
//    ST7735_CASET  , 4      ,  // 15: Column addr set, 4 args, no delay:
//      0x00, 0x02,             //     XSTART = 2
//      0x00, 0x81,             //     XEND = 129
//    ST7735_RASET  , 4      ,  // 16: Row addr set, 4 args, no delay:
//      0x00, 0x02,             //     XSTART = 1
//      0x00, 0x81,             //     XEND = 160
//    ST7735_NORON  ,   DELAY,  // 17: Normal display on, no args, w/delay
//      10,                     //     10 ms delay
//    ST7735_DISPON ,   DELAY,  // 18: Main screen turn on, no args, w/delay
//      255 };                  //     255 = 500 ms delay
static const uint8_t
  Rcmd1[] = {                 // Init for 7735R, part 1 (red or green tab)
    15,                       // 15 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
      150,                    //     150 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
      255,                    //     500 ms delay
    ST7735_FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
      0x01, 0x2C, 0x2D,       //     Dot inversion mode
      0x01, 0x2C, 0x2D,       //     Line inversion mode
    ST7735_INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
      0x07,                   //     No inversion
    ST7735_PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                   //     -4.6V
      0x84,                   //     AUTO mode
    ST7735_PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
      0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    ST7735_PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
      0x0A,                   //     Opamp current small
      0x00,                   //     Boost frequency
    ST7735_PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
      0x8A,                   //     BCLK/2, Opamp current small & Medium low
      0x2A,
    ST7735_PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    ST7735_VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
      0x0E,
    ST7735_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    ST7735_MADCTL , 1      ,  // 14: Memory access control (directions), 1 arg:
      0xC8,                   //     row addr/col addr, bottom to top refresh
    ST7735_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05 };                 //     16-bit color
static const uint8_t
  Rcmd2green[] = {            // Init for 7735R, part 2 (green tab only)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x02,             //     XSTART = 0
      0x00, 0x7F+0x02,        //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x01,             //     XSTART = 0
      0x00, 0x7F+0x01 };      //     XEND = 127
static const uint8_t
  Rcmd2red[] = {              // Init for 7735R, part 2 (red tab only)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F,             //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F };           //     XEND = 127
static const uint8_t
  Rcmd3[] = {                 // Init for 7735R, part 3 (red or green tab)
    4,                        //  4 commands in list:
    ST7735_GMCTRP1, 16      , //  1: Magical unicorn dust, 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735_GMCTRN1, 16      , //  2: Sparkles and rainbows, 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST7735_NORON  ,    DELAY, //  3: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,    DELAY, //  4: Main screen turn on, no args w/delay
      100 };                  //     100 ms delay


// Companion code to the above tables.  Reads and issues
// a series of LCD commands stored in ROM byte array.
void static commandList(const uint8_t *addr) {

  uint8_t numCommands, numArgs;
  uint16_t ms;

  numCommands = *(addr++);               // Number of commands to follow
  while(numCommands--) {                 // For each command...
    writecommand(*(addr++));             //   Read, issue command
    numArgs  = *(addr++);                //   Number of args to follow
    ms       = numArgs & DELAY;          //   If hibit set, delay follows args
    numArgs &= ~DELAY;                   //   Mask out delay bit
    while(numArgs--) {                   //   For each argument...
      writedata(*(addr++));              //     Read, issue argument
    }

    if(ms) {
      ms = *(addr++);             // Read post-command delay time (ms)
      if(ms == 255) ms = 500;     // If 255, delay for 500 ms
      BSP_Delay1ms(ms);
    }
  }
}


// Initialization code common to both 'B' and 'R' type displays
void static commonInit(const uint8_t *cmdList) {
  ColStart  = RowStart = 0; // May be overridden in init func

  // toggle RST low to reset; CS low so it'll listen to us
  // SSI2Fss is not available, so use GPIO on PA4
  SYSCTL_RCGCGPIO_R |= 0x00000023; // 1) activate clock for Ports F, B, and A
  while((SYSCTL_PRGPIO_R&0x23) != 0x23){};// allow time for clocks to stabilize
  GPIO_PORTF_LOCK_R = 0x4C4F434B;  // 2a) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;          // allow changes to PF4-0
                                   // 2b) no need to unlock PF4, PB7, PB4, or PA4
  GPIO_PORTF_AMSEL_R &= ~0x11;     // 3a) disable analog on PF4,0
  GPIO_PORTB_AMSEL_R &= ~0x90;     // 3b) disable analog on PB7,4
  GPIO_PORTA_AMSEL_R &= ~0x10;     // 3c) disable analog on PA4
                                   // 4a) configure PF4,0 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFF0FFF0)+0x00000000;
                                   // 4b) configure PB7,4 as SSI
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0x0FF0FFFF)+0x20020000;
                                   // 4c) configure PA4 as GPIO
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFF0FFFF)+0x00000000;
  GPIO_PORTF_DIR_R |= 0x11;        // 5a) make PF4,0 output
  GPIO_PORTA_DIR_R |= 0x10;        // 5b) make PA4 output
  GPIO_PORTF_AFSEL_R &= ~0x11;     // 6a) disable alt funct on PF4,0
  GPIO_PORTB_AFSEL_R |= 0x90;      // 6b) enable alt funct on PB7,4
  GPIO_PORTA_AFSEL_R &= ~0x10;     // 6c) disable alt funct on PA4
  GPIO_PORTF_DEN_R |= 0x11;        // 7a) enable digital I/O on PF4,0
  GPIO_PORTB_DEN_R |= 0x90;        // 7b) enable digital I/O on PB7,4
  GPIO_PORTA_DEN_R |= 0x10;        // 7c) enable digital I/O on PA4
  TFT_CS = TFT_CS_LOW;
  RESET = RESET_HIGH;
  BSP_Delay1ms(500);
  RESET = RESET_LOW;
  BSP_Delay1ms(500);
  RESET = RESET_HIGH;
  BSP_Delay1ms(500);
  TFT_CS = TFT_CS_HIGH;

  // initialize SSI2
                                        // activate clock for SSI2
  SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R2;
                                        // allow time for clock to stabilize
  while((SYSCTL_PRSSI_R&SYSCTL_PRSSI_R2) == 0){};
  SSI2_CR1_R &= ~SSI_CR1_SSE;           // disable SSI
  SSI2_CR1_R &= ~SSI_CR1_MS;            // master mode
                                        // configure for clock from source PIOSC for baud clock source
  SSI2_CC_R = (SSI2_CC_R&~SSI_CC_CS_M)+SSI_CC_CS_PIOSC;
                                        // clock divider for 4 MHz SSIClk (16 MHz PIOSC/4)
                                        // PIOSC/(CPSDVSR*(1+SCR))
                                        // 16/(4*(1+0)) = 4 MHz
  SSI2_CPSR_R = (SSI2_CPSR_R&~SSI_CPSR_CPSDVSR_M)+4; // must be even number
  SSI2_CR0_R &= ~(SSI_CR0_SCR_M |       // SCR = 0 (4 Mbps data rate)
                  SSI_CR0_SPH |         // SPH = 0
                  SSI_CR0_SPO);         // SPO = 0
                                        // FRF = Freescale format
  SSI2_CR0_R = (SSI2_CR0_R&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO;
                                        // DSS = 8-bit data
  SSI2_CR0_R = (SSI2_CR0_R&~SSI_CR0_DSS_M)+SSI_CR0_DSS_8;
  SSI2_CR1_R |= SSI_CR1_SSE;            // enable SSI

  if(cmdList) commandList(cmdList);
}


////------------ST7735_InitB------------
//// Initialization for ST7735B screens.
//// Input: none
//// Output: none
//void static ST7735_InitB(void) {
//  commonInit(Bcmd);
//  BSP_LCD_SetCursor(0,0);
//  StTextColor = ST7735_YELLOW;
//  BSP_LCD_FillScreen(0);                // set screen to black
//}


//------------ST7735_InitR------------
// Initialization for ST7735R screens (green or red tabs).
// Input: option one of the enumerated options depending on tabs
// Output: none
void static ST7735_InitR(enum initRFlags option) {
  commonInit(Rcmd1);
  if(option == INITR_GREENTAB) {
    commandList(Rcmd2green);
    ColStart = 2;
    RowStart = 3;
  } else {
    // colstart, rowstart left at default '0' values
    commandList(Rcmd2red);
  }
  commandList(Rcmd3);

  // if black, change MADCTL color filter
  if (option == INITR_BLACKTAB) {
    writecommand(ST7735_MADCTL);
    writedata(0xC0);
  }
//  TabColor = option;
  BSP_LCD_SetCursor(0,0);
  StTextColor = ST7735_YELLOW;
  BSP_LCD_FillScreen(0);                // set screen to black
}


// ------------BSP_LCD_Init------------
// Initialize the SPI and GPIO, which correspond with
// BoosterPack pins J1.7 (SPI CLK), J2.13 (SPI CS), J2.15
// (SPI MOSI), J2.17 (LCD ~RST), and J4.31 (LCD DC).
// Input: none
// Output: none
void BSP_LCD_Init(void){
  ST7735_InitR(INITR_GREENTAB);
}


// Set the region of the screen RAM to be modified
// Pixel colors are sent left to right, top to bottom
// (same as Font table is encoded; different from regular bitmap)
// Requires 11 bytes of transmission
void static setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {

  writecommand(ST7735_CASET); // Column addr set
  writedata(0x00);
  writedata(x0+ColStart);     // XSTART
  writedata(0x00);
  writedata(x1+ColStart);     // XEND

  writecommand(ST7735_RASET); // Row addr set
  writedata(0x00);
  writedata(y0+RowStart);     // YSTART
  writedata(0x00);
  writedata(y1+RowStart);     // YEND

  writecommand(ST7735_RAMWR); // write to RAM
}


// Send two bytes of data, most significant byte first
// Requires 2 bytes of transmission
void static pushColor(uint16_t color) {
  writedata((uint8_t)(color >> 8));
  writedata((uint8_t)color);
}


//------------BSP_LCD_DrawPixel------------
// Color the pixel at the given coordinates with the given color.
// Requires 13 bytes of transmission
// Input: x     horizontal position of the pixel, columns from the left edge
//               must be less than 128
//               0 is on the left, 126 is near the right
//        y     vertical position of the pixel, rows from the top edge
//               must be less than 128
//               126 is near the wires, 0 is the side opposite the wires
//        color 16-bit color, which can be produced by BSP_LCD_Color565()
// Output: none
void BSP_LCD_DrawPixel(int16_t x, int16_t y, uint16_t color) {

  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;

//  setAddrWindow(x,y,x+1,y+1); // original code, bug???
  setAddrWindow(x,y,x,y);

  pushColor(color);
}


//------------BSP_LCD_DrawFastVLine------------
// Draw a vertical line at the given coordinates with the given height and color.
// A vertical line is parallel to the longer side of the rectangular display
// Requires (11 + 2*h) bytes of transmission (assuming image fully on screen)
// Input: x     horizontal position of the start of the line, columns from the left edge
//        y     vertical position of the start of the line, rows from the top edge
//        h     vertical height of the line
//        color 16-bit color, which can be produced by BSP_LCD_Color565()
// Output: none
void BSP_LCD_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;

  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
  if((y+h-1) >= _height) h = _height-y;
  setAddrWindow(x, y, x, y+h-1);

  while (h--) {
    writedata(hi);
    writedata(lo);
  }
}


//------------BSP_LCD_DrawFastHLine------------
// Draw a horizontal line at the given coordinates with the given width and color.
// A horizontal line is parallel to the shorter side of the rectangular display
// Requires (11 + 2*w) bytes of transmission (assuming image fully on screen)
// Input: x     horizontal position of the start of the line, columns from the left edge
//        y     vertical position of the start of the line, rows from the top edge
//        w     horizontal width of the line
//        color 16-bit color, which can be produced by BSP_LCD_Color565()
// Output: none
void BSP_LCD_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;

  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;
  setAddrWindow(x, y, x+w-1, y);

  while (w--) {
    writedata(hi);
    writedata(lo);
  }
}


//------------BSP_LCD_FillScreen------------
// Fill the screen with the given color.
// Requires 33,293 bytes of transmission
// Input: color 16-bit color, which can be produced by BSP_LCD_Color565()
// Output: none
void BSP_LCD_FillScreen(uint16_t color) {
  BSP_LCD_FillRect(0, 0, _width, _height, color);  // original
//  screen is actually 129 by 129 pixels, x 0 to 128, y goes from 0 to 128
}


//------------BSP_LCD_FillRect------------
// Draw a filled rectangle at the given coordinates with the given width, height, and color.
// Requires (11 + 2*w*h) bytes of transmission (assuming image fully on screen)
// Input: x     horizontal position of the top left corner of the rectangle, columns from the left edge
//        y     vertical position of the top left corner of the rectangle, rows from the top edge
//        w     horizontal width of the rectangle
//        h     vertical height of the rectangle
//        color 16-bit color, which can be produced by BSP_LCD_Color565()
// Output: none
void BSP_LCD_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;

  // rudimentary clipping (drawChar w/big text requires this)
  if((x >= _width) || (y >= _height)) return;
  if((x + w - 1) >= _width)  w = _width  - x;
  if((y + h - 1) >= _height) h = _height - y;

  setAddrWindow(x, y, x+w-1, y+h-1);

  for(y=h; y>0; y--) {
    for(x=w; x>0; x--) {
      writedata(hi);
      writedata(lo);
    }
  }
}


//------------BSP_LCD_Color565------------
// Pass 8-bit (each) R,G,B and get back 16-bit packed color.
// Input: r red value
//        g green value
//        b blue value
// Output: 16-bit color
uint16_t BSP_LCD_Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


//------------BSP_LCD_SwapColor------------
// Swaps the red and blue values of the given 16-bit packed color;
// green is unchanged.
// Input: x 16-bit color in format B, G, R
// Output: 16-bit color in format R, G, B
uint16_t BSP_LCD_SwapColor(uint16_t x) {
  return (x << 11) | (x & 0x07E0) | (x >> 11);
}


//------------BSP_LCD_DrawBitmap------------
// Displays a 16-bit color BMP image.  A bitmap file that is created
// by a PC image processing program has a header and may be padded
// with dummy columns so the data have four byte alignment.  This
// function assumes that all of that has been stripped out, and the
// array image[] has one 16-bit halfword for each pixel to be
// displayed on the screen (encoded in reverse order, which is
// standard for bitmap files).  An array can be created in this
// format from a 24-bit-per-pixel .bmp file using the associated
// converter program.
// (x,y) is the screen location of the lower left corner of BMP image
// Requires (11 + 2*w*h) bytes of transmission (assuming image fully on screen)
// Input: x     horizontal position of the bottom left corner of the image, columns from the left edge
//        y     vertical position of the bottom left corner of the image, rows from the top edge
//        image pointer to a 16-bit color BMP image
//        w     number of pixels wide
//        h     number of pixels tall
// Output: none
// Must be less than or equal to 128 pixels wide by 128 pixels high
void BSP_LCD_DrawBitmap(int16_t x, int16_t y, const uint16_t *image, int16_t w, int16_t h){
  int16_t skipC = 0;                      // non-zero if columns need to be skipped due to clipping
  int16_t originalWidth = w;              // save this value; even if not all columns fit on the screen, the image is still this width in ROM
  int i = w*(h - 1);

  if((x >= _width) || ((y - h + 1) >= _height) || ((x + w) <= 0) || (y < 0)){
    return;                             // image is totally off the screen, do nothing
  }
  if((w > _width) || (h > _height)){    // image is too wide for the screen, do nothing
    //***This isn't necessarily a fatal error, but it makes the
    //following logic much more complicated, since you can have
    //an image that exceeds multiple boundaries and needs to be
    //clipped on more than one side.
    return;
  }
  if((x + w - 1) >= _width){            // image exceeds right of screen
    skipC = (x + w) - _width;           // skip cut off columns
    w = _width - x;
  }
  if((y - h + 1) < 0){                  // image exceeds top of screen
    i = i - (h - y - 1)*originalWidth;  // skip the last cut off rows
    h = y + 1;
  }
  if(x < 0){                            // image exceeds left of screen
    w = w + x;
    skipC = -1*x;                       // skip cut off columns
    i = i - x;                          // skip the first cut off columns
    x = 0;
  }
  if(y >= _height){                     // image exceeds bottom of screen
    h = h - (y - _height + 1);
    y = _height - 1;
  }

  setAddrWindow(x, y-h+1, x+w-1, y);

  for(y=0; y<h; y=y+1){
    for(x=0; x<w; x=x+1){
                                        // send the top 8 bits
      writedata((uint8_t)(image[i] >> 8));
                                        // send the bottom 8 bits
      writedata((uint8_t)image[i]);
      i = i + 1;                        // go to the next pixel
    }
    i = i + skipC;
    i = i - 2*originalWidth;
  }
}


//------------BSP_LCD_DrawCharS------------
// Simple character draw function.  This is the same function from
// Adafruit_GFX.c but adapted for this processor.  However, each call
// to BSP_LCD_DrawPixel() calls setAddrWindow(), which needs to send
// many extra data and commands.  If the background color is the same
// as the text color, no background will be printed, and text can be
// drawn right over existing images without covering them with a box.
// Requires (11 + 2*size*size)*6*8 bytes of transmission (image fully on screen; textcolor != bgColor)
// Input: x         horizontal position of the top left corner of the character, columns from the left edge
//        y         vertical position of the top left corner of the character, rows from the top edge
//        c         character to be printed
//        textColor 16-bit color of the character
//        bgColor   16-bit color of the background
//        size      number of pixels per character pixel (e.g. size==2 prints each pixel of font as 2x2 square)
// Output: none
void BSP_LCD_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size){
  uint8_t line; // vertical column of pixels of character in font
  int32_t i, j;
  if((x >= _width)            || // Clip right
     (y >= _height)           || // Clip bottom
     ((x + 6 * size - 1) < 0) || // Clip left
     ((y + 8 * size - 1) < 0))   // Clip top
    return;

  for (i=0; i<6; i++ ) {
    if (i == 5)
      line = 0x0;
    else
      line = Font[(c*5)+i];
    for (j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) // default size
          BSP_LCD_DrawPixel(x+i, y+j, textColor);
        else {  // big size
          BSP_LCD_FillRect(x+(i*size), y+(j*size), size, size, textColor);
        }
      } else if (bgColor != textColor) {
        if (size == 1) // default size
          BSP_LCD_DrawPixel(x+i, y+j, bgColor);
        else {  // big size
          BSP_LCD_FillRect(x+i*size, y+j*size, size, size, bgColor);
        }
      }
      line >>= 1;
    }
  }
}


//------------BSP_LCD_DrawChar------------
// Advanced character draw function.  This is similar to the function
// from Adafruit_GFX.c but adapted for this processor.  However, this
// function only uses one call to setAddrWindow(), which allows it to
// run at least twice as fast.
// Requires (11 + size*size*6*8) bytes of transmission (assuming image fully on screen)
// Input: x         horizontal position of the top left corner of the character, columns from the left edge
//        y         vertical position of the top left corner of the character, rows from the top edge
//        c         character to be printed
//        textColor 16-bit color of the character
//        bgColor   16-bit color of the background
//        size      number of pixels per character pixel (e.g. size==2 prints each pixel of font as 2x2 square)
// Output: none
void BSP_LCD_DrawChar(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size){
  uint8_t line; // horizontal row of pixels of character
  int32_t col, row, i, j;// loop indices
  if(((x + 6*size - 1) >= _width)  || // Clip right
     ((y + 8*size - 1) >= _height) || // Clip bottom
     ((x + 6*size - 1) < 0)        || // Clip left
     ((y + 8*size - 1) < 0)){         // Clip top
    return;
  }

  setAddrWindow(x, y, x+6*size-1, y+8*size-1);

  line = 0x01;        // print the top row first
  // print the rows, starting at the top
  for(row=0; row<8; row=row+1){
    for(i=0; i<size; i=i+1){
      // print the columns, starting on the left
      for(col=0; col<5; col=col+1){
        if(Font[(c*5)+col]&line){
          // bit is set in Font, print pixel(s) in text color
          for(j=0; j<size; j=j+1){
            pushColor(textColor);
          }
        } else{
          // bit is cleared in Font, print pixel(s) in background color
          for(j=0; j<size; j=j+1){
            pushColor(bgColor);
          }
        }
      }
      // print blank column(s) to the right of character
      for(j=0; j<size; j=j+1){
        pushColor(bgColor);
      }
    }
    line = line<<1;   // move up to the next row
  }
}


//------------BSP_LCD_DrawString------------
// String draw function.
// 13 rows (0 to 12) and 21 characters (0 to 20)
// Requires (11 + size*size*6*8) bytes of transmission for each character
// Input: x         columns from the left edge (0 to 20)
//        y         rows from the top edge (0 to 12)
//        pt        pointer to a null terminated string to be printed
//        textColor 16-bit color of the characters
// bgColor is Black and size is 1
// Output: number of characters printed
uint32_t BSP_LCD_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor){
  uint32_t count = 0;
  if(y>12) return 0;
  while(*pt){
    BSP_LCD_DrawChar(x*6, y*10, *pt, textColor, ST7735_BLACK, 1);
    pt++;
    x = x+1;
    if(x>20) return count;  // number of characters printed
    count++;
  }
  return count;  // number of characters printed
}


//-----------------------fillmessage-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1-10 digits with no space before or after
char Message[12];
uint32_t Messageindex;

void static fillmessage(uint32_t n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    fillmessage(n/10);
    n = n%10;
  }
  Message[Messageindex] = (n+'0'); /* n is between 0 and 9 */
  if(Messageindex<11)Messageindex++;
}
void static fillmessage4(uint32_t n){
  if(n>9999)n=9999;
  if(n>=1000){  // 1000 to 9999
    Messageindex = 0;
  } else if(n>=100){  // 100 to 999
    Message[0] = ' ';
    Messageindex = 1;
  }else if(n>=10){ //
    Message[0] = ' '; /* n is between 10 and 99 */
    Message[1] = ' ';
    Messageindex = 2;
  }else{
    Message[0] = ' '; /* n is between 0 and 9 */
    Message[1] = ' ';
    Message[2] = ' ';
    Messageindex = 3;
  }
  fillmessage(n);
}
void static fillmessage5(uint32_t n){
  if(n>99999)n=99999;
  if(n>=10000){  // 10000 to 99999
    Messageindex = 0;
  } else if(n>=1000){  // 1000 to 9999
    Message[0] = ' ';
    Messageindex = 1;
  }else if(n>=100){  // 100 to 999
    Message[0] = ' ';
    Message[1] = ' ';
    Messageindex = 2;
  }else if(n>=10){ //
    Message[0] = ' '; /* n is between 10 and 99 */
    Message[1] = ' ';
    Message[2] = ' ';
    Messageindex = 3;
  }else{
    Message[0] = ' '; /* n is between 0 and 9 */
    Message[1] = ' ';
    Message[2] = ' ';
    Message[3] = ' ';
    Messageindex = 4;
  }
  fillmessage(n);
}
void static fillmessage2_1(uint32_t n){
  if(n>999)n=999;
  if(n>=100){  // 100 to 999
    Message[0] = (n/100+'0'); /* tens digit */
    n = n%100; //the rest
  }else { // 0 to 99
    Message[0] = ' '; /* n is between 0.0 and 9.9 */
  }
  Message[1] = (n/10+'0'); /* ones digit */
  n = n%10; //the rest
  Message[2] = '.';
  Message[3] = (n+'0'); /* tenths digit */
  Message[4] = 0;
}
void static fillmessage2_Hex(uint32_t n){ char digit;
  if(n>255){
    Message[0] = '*';
    Message[1] = '*';
  }else{
    digit = n/16;
    if(digit<10){
      digit = digit+'0';
    }else{
      digit = digit+'A'-10;
    }
    Message[0] = digit; /* 16's digit */
    digit = n%16;
    if(digit<10){
      digit = digit+'0';
    }else{
      digit = digit+'A'-10;
    }
    Message[1] = digit; /* ones digit */
  }
  Message[2] = ',';
  Message[3] = 0;
}
//********BSP_LCD_SetCursor*****************
// Move the cursor to the desired X- and Y-position.  The
// next character of the next unsigned decimal will be
// printed here.  X=0 is the leftmost column.  Y=0 is the top
// row.
// inputs: newX  new X-position of the cursor (0<=newX<=20)
//         newY  new Y-position of the cursor (0<=newY<=12)
// outputs: none
void BSP_LCD_SetCursor(uint32_t newX, uint32_t newY){
  if((newX > 20) || (newY > 12)){       // bad input
    return;                             // do nothing
  }
  StX = newX;
  StY = newY;
}


//-----------------------BSP_LCD_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Position determined by BSP_LCD_SetCursor command
// Input: n         32-bit number to be transferred
//        textColor 16-bit color of the numbers
// Output: none
// Variable format 1-10 digits with no space before or after
void BSP_LCD_OutUDec(uint32_t n, int16_t textColor){
  StTextColor = textColor;
  Messageindex = 0;
  fillmessage(n);
  Message[Messageindex] = 0; // terminate
  BSP_LCD_DrawString(StX,StY,Message,textColor);
  StX = StX+Messageindex;
  if(StX>20){
    StX = 20;
    BSP_LCD_DrawChar(StX*6,StY*10,'*',ST7735_RED,ST7735_BLACK, 1);
  }
}


//-----------------------BSP_LCD_OutUDec4-----------------------
// Output a 32-bit number in unsigned 4-digit decimal format
// Position determined by BSP_LCD_SetCursor command
// Input: 32-bit number to be transferred
//        textColor 16-bit color of the numbers
// Output: none
// Fixed format 4 digits with no space before or after
void BSP_LCD_OutUDec4(uint32_t n, int16_t textColor){
  Messageindex = 0;
  fillmessage4(n);
  Message[Messageindex] = 0; // terminate
  BSP_LCD_DrawString(StX,StY,Message,textColor);
  StX = StX+Messageindex;
  if(StX>20){
    StX = 20;
    BSP_LCD_DrawChar(StX*6,StY*10,'*',ST7735_RED,ST7735_BLACK, 1);
  }
}


//-----------------------BSP_LCD_OutUDec5-----------------------
// Output a 32-bit number in unsigned 5-digit decimal format
// Position determined by BSP_LCD_SetCursor command
// Input: 32-bit number to be transferred
//        textColor 16-bit color of the numbers
// Output: none
// Fixed format 5 digits with no space before or after
void BSP_LCD_OutUDec5(uint32_t n, int16_t textColor){
  Messageindex = 0;
  fillmessage5(n);
  Message[Messageindex] = 0; // terminate
  BSP_LCD_DrawString(StX,StY,Message,textColor);
  StX = StX+Messageindex;
  if(StX>20){
    StX = 20;
    BSP_LCD_DrawChar(StX*6,StY*10,'*',ST7735_RED,ST7735_BLACK, 1);
  }
}


//-----------------------BSP_LCD_OutUFix2_1-----------------------
// Output a 32-bit number in unsigned 3-digit fixed point, 0.1 resolution
// numbers 0 to 999 printed as " 0.0" to "99.9"
// Position determined by BSP_LCD_SetCursor command
// Input: 32-bit number to be transferred
//        textColor 16-bit color of the numbers
// Output: none
// Fixed format 4 characters with no space before or after
void BSP_LCD_OutUFix2_1(uint32_t n, int16_t textColor){
  fillmessage2_1(n);
  BSP_LCD_DrawString(StX,StY,Message,textColor);
  StX = StX+4;
  if(StX>20){
    StX = 20;
    BSP_LCD_DrawChar(StX*6,StY*10,'*',ST7735_RED,ST7735_BLACK, 1);
  }
}
//-----------------------BSP_LCD_OutUHex2-----------------------
// Output a 32-bit number in unsigned 2-digit hexadecimal format
// numbers 0 to 255 printed as "00," to "FF,"
// Position determined by BSP_LCD_SetCursor command
// Input: 32-bit number to be transferred
//        textColor 16-bit color of the numbers
// Output: none
// Fixed format 3 characters with comma after
void BSP_LCD_OutUHex2(uint32_t n, int16_t textColor){
  fillmessage2_Hex(n);
  BSP_LCD_DrawString(StX,StY,Message,textColor);
  StX = StX+3;
  if(StX>20){
    StX = 20;
    BSP_LCD_DrawChar(StX*6,StY*10,'*',ST7735_RED,ST7735_BLACK, 1);
  }
}

int TimeIndex;               // horizontal position of next point to plot on graph (0 to 99)
int32_t Ymax, Ymin, Yrange;  // vertical axis max, min, and range (units not specified)
uint16_t PlotBGColor;        // background color of the plot used whenever clearing plot area

// ------------BSP_LCD_Drawaxes------------
// Set up the axes, labels, and other variables to
// allow data to be plotted in a chart using the
// functions BSP_LCD_PlotPoint() and
// BSP_LCD_PlotIncrement().
// Input: axisColor   16-bit color for axes, which can be produced by BSP_LCD_Color565()
//        bgColor     16-bit color for plot background, which can be produced by BSP_LCD_Color565()
//        xLabel      pointer to a null terminated string for x-axis (~4 character space)
//        yLabel1     pointer to a null terminated string for top of y-axis (~3-5 character space)
//        label1Color 16-bit color for y-axis label1, which can be produced by BSP_LCD_Color565()
//        yLabel2     pointer to a null terminated string for bottom of y-axis (~3 character space)
//                      if yLabel2 is empty string, no yLabel2 is printed, and yLabel1 is centered
//        label2Color 16-bit color for y-axis label2, which can be produced by BSP_LCD_Color565()
//        ymax        maximum value to be printed
//        ymin        minimum value to be printed
// Output: none
// Assumes: BSP_LCD_Init() has been called
void BSP_LCD_Drawaxes(uint16_t axisColor, uint16_t bgColor, char *xLabel,
  char *yLabel1, uint16_t label1Color, char *yLabel2, uint16_t label2Color,
  int32_t ymax, int32_t ymin){
  int i;
  // assume that ymax > ymin
  Ymax = ymax;
  Ymin = ymin;
  Yrange = Ymax - Ymin;
  TimeIndex = 0;
  PlotBGColor = bgColor;
  BSP_LCD_FillRect(0, 17, 111, 111, bgColor);
  BSP_LCD_DrawFastHLine(10, 117, 101, axisColor);
  BSP_LCD_DrawFastVLine(10, 17, 101, axisColor);
  for(i=20; i<=110; i=i+10){
    BSP_LCD_DrawPixel(i, 118, axisColor);
  }
  for(i=17; i<117; i=i+10){
    BSP_LCD_DrawPixel(9, i, axisColor);
  }
  i = 50;
  while((*xLabel) && (i < 100)){
    BSP_LCD_DrawChar(i, 120, *xLabel, axisColor, bgColor, 1);
    i = i + 6;
    xLabel++;
  }
  if(*yLabel2){ // two labels
    i = 26;
    while((*yLabel2) && (i < 50)){
      BSP_LCD_DrawChar(0, i, *yLabel2, label2Color, bgColor, 1);
      i = i + 8;
      yLabel2++;
    }
    i = 82;
  }else{ // one label
    i = 42;
  }
  while((*yLabel1) && (i < 120)){
    BSP_LCD_DrawChar(0, i, *yLabel1, label1Color, bgColor, 1);
    i = i + 8;
    yLabel1++;
  }
}


// ------------BSP_LCD_PlotPoint------------
// Plot a point on the chart.  To plot several points in the
// same column, call this function repeatedly before calling
// BSP_LCD_PlotIncrement().  The units of the data are the
// same as the ymax and ymin values specified in the
// initialization function.
// Input: data1  value to be plotted (units not specified)
//        color1 16-bit color for the point, which can be produced by BSP_LCD_Color565()
// Output: none
// Assumes: BSP_LCD_Init() and BSP_LCD_Drawaxes() have been called
void BSP_LCD_PlotPoint(int32_t data1, uint16_t color1){
  data1 = ((data1 - Ymin)*100)/Yrange;
  if(data1 > 98){
    data1 = 98;
    color1 = LCD_RED;
  }
  if(data1 < 0){
    data1 = 0;
    color1 = LCD_RED;
  }
  BSP_LCD_DrawPixel(TimeIndex + 11, 116 - data1, color1);
  BSP_LCD_DrawPixel(TimeIndex + 11, 115 - data1, color1);
}


// ------------BSP_LCD_PlotIncrement------------
// Increment the plot between subsequent calls to
// BSP_LCD_PlotPoint().  Automatically wrap and clear the
// column to be printed to.
// Input: none
// Output: none
// Assumes: BSP_LCD_Init() and BSP_LCD_Drawaxes() have been called
void BSP_LCD_PlotIncrement(void){
  TimeIndex = TimeIndex + 1;
  if(TimeIndex > 99){
    TimeIndex = 0;
  }
  BSP_LCD_DrawFastVLine(TimeIndex + 11, 17, 100, PlotBGColor);
}
/* ********************** */
/*   End of LCD Section   */
/* ********************** */

// ------------BSP_Clock_InitFastest------------
// Configure the system clock to run at the fastest
// and most accurate settings.  For example, if the
// LaunchPad has a crystal, it should be used here.
// Call BSP_Clock_GetFreq() to get the current system
// clock frequency for the LaunchPad.
// Input: none
// Output: none
void BSP_Clock_InitFastest(void){
  // 0) configure the system to use RCC2 for advanced features
  //    such as 400 MHz PLL and non-integer System Clock Divisor
  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
  // 1) bypass PLL while initializing
  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
  // 2) select the crystal value and oscillator source
  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // clear XTAL field
  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;// configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear oscillator source field
  SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;// configure for main oscillator source
  // 3) activate PLL by clearing PWRDN
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
  // 4) set the desired system divider and the system divider least significant bit
  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) // clear system clock divider field
                  + (4<<22);      // configure for 80 MHz clock
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
  ClockFrequency = 80000000;
}

// ------------BSP_Clock_GetFreq------------
// Return the current system clock frequency for the
// LaunchPad.
// Input: none
// Output: system clock frequency in cycles/second
uint32_t BSP_Clock_GetFreq(void){
  return ClockFrequency;
}

// ------------BSP_PeriodicTask_Init------------
// Activate an interrupt to run a user task periodically.
// Give it a priority 0 to 6 with lower numbers
// signifying higher priority.  Equal priority is
// handled sequentially.
// Input:  task is a pointer to a user function
//         freq is number of interrupts per second
//           1 Hz to 10 kHz
//         priority is a number 0 to 6
// Output: none
void (*PeriodicTask)(void);   // user function
void BSP_PeriodicTask_Init(void(*task)(void), uint32_t freq, uint8_t priority){long sr;
  if((freq == 0) || (freq > 10000)){
    return;                        // invalid input
  }
  if(priority > 6){
    priority = 6;
  }
  sr = StartCritical();
  PeriodicTask = task;             // user function
  // ***************** Wide Timer5A initialization *****************
  SYSCTL_RCGCWTIMER_R |= 0x20;     // activate clock for Wide Timer5
  while((SYSCTL_PRWTIMER_R&0x20) == 0){};// allow time for clock to stabilize
  WTIMER5_CTL_R &= ~TIMER_CTL_TAEN;// disable Wide Timer5A during setup
  WTIMER5_CFG_R = TIMER_CFG_16_BIT;// configure for 32-bit timer mode
                                   // configure for periodic mode, default down-count settings
  WTIMER5_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  WTIMER5_TAILR_R = (ClockFrequency/freq - 1); // reload value
  WTIMER5_TAPR_R = 0;              // bus clock resolution
  WTIMER5_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER5A timeout flag
  WTIMER5_IMR_R |= TIMER_IMR_TATOIM;// arm timeout interrupt
//PRIn Bit   Interrupt
//Bits 31:29 Interrupt [4n+3]
//Bits 23:21 Interrupt [4n+2], 
//Bits 15:13 Interrupt [4n+1]
//Bits 7:5   Interrupt [4n]   n=26 => (4n)=104
  NVIC_PRI26_R = (NVIC_PRI26_R&0xFFFFFF00)|(priority<<5); // priority
// interrupts enabled in the main program after all devices initialized
// vector number 120, interrupt number 104
// 32 bits in each NVIC_ENx_R register, 104/32 = 3 remainder 8
  NVIC_EN3_R = 1<<8;               // enable IRQ 104 in NVIC
  WTIMER5_CTL_R |= TIMER_CTL_TAEN; // enable Wide Timer0A 32-b
  EndCritical(sr);
}

void WideTimer5A_Handler(void){
  WTIMER5_ICR_R = TIMER_ICR_TATOCINT;// acknowledge Wide Timer5A timeout
  (*PeriodicTask)();               // execute user task
}

// ------------BSP_PeriodicTask_Stop------------
// Deactivate the interrupt running a user task
// periodically.
// Input: none
// Output: none
void BSP_PeriodicTask_Stop(void){
  WTIMER5_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER5A timeout flag
  NVIC_DIS3_R = 1<<8;              // disable IRQ 104 in NVIC
}
// ------------BSP_PeriodicTask_Restart------------
// Reactivate the interrupt running a user task periodically.
// Input: none
// Output: none
void BSP_PeriodicTask_Restart(void){
  WTIMER5_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER5A timeout flag
  NVIC_EN3_R = 1<<8;              // enable IRQ 104 in NVIC
}

// ------------BSP_PeriodicTask_InitB------------
// Activate an interrupt to run a user task periodically.
// Give it a priority 0 to 6 with lower numbers
// signifying higher priority.  Equal priority is
// handled sequentially.
// Input:  task is a pointer to a user function
//         freq is number of interrupts per second
//           1 Hz to 10 kHz
//         priority is a number 0 to 6
// Output: none
void (*PeriodicTaskB)(void);   // user function
void BSP_PeriodicTask_InitB(void(*task)(void), uint32_t freq, uint8_t priority){long sr;
  if((freq == 0) || (freq > 10000)){
    return;                        // invalid input
  }
  if(priority > 6){
    priority = 6;
  }
  sr = StartCritical();
  PeriodicTaskB = task;             // user function
  // ***************** Wide Timer4A initialization *****************
  SYSCTL_RCGCWTIMER_R |= 0x10;     // activate clock for Wide Timer4
  while((SYSCTL_PRWTIMER_R&0x10) == 0){};// allow time for clock to stabilize
  WTIMER4_CTL_R &= ~TIMER_CTL_TAEN;// disable Wide Timer4A during setup
  WTIMER4_CFG_R = TIMER_CFG_16_BIT;// configure for 32-bit timer mode
                                   // configure for periodic mode, default down-count settings
  WTIMER4_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  WTIMER4_TAILR_R = (ClockFrequency/freq - 1); // reload value
  WTIMER4_TAPR_R = 0;              // bus clock resolution
  WTIMER4_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER4A timeout flag
  WTIMER4_IMR_R |= TIMER_IMR_TATOIM;// arm timeout interrupt
//PRIn Bit   Interrupt
//Bits 31:29 Interrupt [4n+3]
//Bits 23:21 Interrupt [4n+2], n=25 => (4n+2)=102
//Bits 15:13 Interrupt [4n+1]
//Bits 7:5 Interrupt [4n]
  NVIC_PRI25_R = (NVIC_PRI25_R&0xFF00FFFF)|(priority<<21); // priority
// interrupts enabled in the main program after all devices initialized
// vector number 118, interrupt number 102
// 32 bits in each NVIC_ENx_R register, 102/32 = 3 remainder 6
  NVIC_EN3_R = 1<<6;               // enable IRQ 102 in NVIC
  WTIMER4_CTL_R |= TIMER_CTL_TAEN; // enable Wide Timer4A 32-b
  EndCritical(sr);
}

void WideTimer4A_Handler(void){
  WTIMER4_ICR_R = TIMER_ICR_TATOCINT;// acknowledge Wide Timer4A timeout
  (*PeriodicTaskB)();               // execute user task
}

// ------------BSP_PeriodicTask_StopB------------
// Deactivate the interrupt running a user task
// periodically.
// Input: none
// Output: none
void BSP_PeriodicTask_StopB(void){
  WTIMER4_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER4A timeout flag
  NVIC_DIS3_R = 1<<6;              // disable IRQ 102 in NVIC
}


// ------------BSP_PeriodicTask_InitC------------
// Activate an interrupt to run a user task periodically.
// Give it a priority 0 to 6 with lower numbers
// signifying higher priority.  Equal priority is
// handled sequentially.
// Input:  task is a pointer to a user function
//         freq is number of interrupts per second
//           1 Hz to 10 kHz
//         priority is a number 0 to 6
// Output: none
void (*PeriodicTaskC)(void);   // user function
void BSP_PeriodicTask_InitC(void(*task)(void), uint32_t freq, uint8_t priority){long sr;
  if((freq == 0) || (freq > 10000)){
    return;                        // invalid input
  }
  if(priority > 6){
    priority = 6;
  }
  sr = StartCritical();
  PeriodicTaskC = task;             // user function
  // ***************** Wide Timer3A initialization *****************
  SYSCTL_RCGCWTIMER_R |= 0x08;     // activate clock for Wide Timer3
  while((SYSCTL_PRWTIMER_R&0x08) == 0){};// allow time for clock to stabilize
  WTIMER3_CTL_R &= ~TIMER_CTL_TAEN;// disable Wide Timer3A during setup
  WTIMER3_CFG_R = TIMER_CFG_16_BIT;// configure for 32-bit timer mode
                                   // configure for periodic mode, default down-count settings
  WTIMER3_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  WTIMER3_TAILR_R = (ClockFrequency/freq - 1); // reload value
  WTIMER3_TAPR_R = 0;              // bus clock resolution
  WTIMER3_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER3A timeout flag
  WTIMER3_IMR_R |= TIMER_IMR_TATOIM;// arm timeout interrupt
//PRIn Bit   Interrupt
//Bits 31:29 Interrupt [4n+3]
//Bits 23:21 Interrupt [4n+2]
//Bits 15:13 Interrupt [4n+1]
//Bits 7:5   Interrupt [4n]  , n=25 => (4n+0)=100
  NVIC_PRI25_R = (NVIC_PRI25_R&0xFFFFFF00)|(priority<<5); // priority
// interrupts enabled in the main program after all devices initialized
// vector number 116, interrupt number 100
// 32 bits in each NVIC_ENx_R register, 100/32 = 3 remainder 4
  NVIC_EN3_R = 1<<4;               // enable IRQ 100 in NVIC
  WTIMER3_CTL_R |= TIMER_CTL_TAEN; // enable Wide Timer3A 32-b
  EndCritical(sr);
}

void WideTimer3A_Handler(void){
  WTIMER3_ICR_R = TIMER_ICR_TATOCINT;// acknowledge Wide Timer3A timeout
  (*PeriodicTaskC)();               // execute user task
}

// ------------BSP_PeriodicTask_StopC------------
// Deactivate the interrupt running a user task
// periodically.
// Input: none
// Output: none
void BSP_PeriodicTask_StopC(void){
  WTIMER3_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER3A timeout flag
  NVIC_DIS3_R = 1<<4;              // disable IRQ 100 in NVIC
}

// ------------BSP_Time_Init------------
// Activate a 32-bit timer to count the number of
// microseconds since the timer was initialized.
// Input: none
// Output: none
// Assumes: BSP_Clock_InitFastest() has been called
//          so clock = 80/80 = 1 MHz
void BSP_Time_Init(void){long sr;
  sr = StartCritical();
  // ***************** Wide Timer5B initialization *****************
  SYSCTL_RCGCWTIMER_R |= 0x20;     // activate clock for Wide Timer5
  while((SYSCTL_PRWTIMER_R&0x20) == 0){};// allow time for clock to stabilize
  WTIMER5_CTL_R &= ~TIMER_CTL_TBEN;// disable Wide Timer5B during setup
  WTIMER5_CFG_R = TIMER_CFG_16_BIT;// configure for 32-bit timer mode
                                   // configure for periodic mode, default down-count settings
  WTIMER5_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
  WTIMER5_TBILR_R = 0xFFFFFFFF;    // reload value
  WTIMER5_TBPR_R = 79;             // 1 MHz resolution
  WTIMER5_ICR_R = TIMER_ICR_TBTOCINT;// clear WTIMER5B timeout flag
  WTIMER5_IMR_R &= ~TIMER_IMR_TBTOIM;// disarm timeout interrupt
  WTIMER5_CTL_R |= TIMER_CTL_TBEN; // enable Wide Timer0B 32-b
  EndCritical(sr);
}

// ------------BSP_Time_Get------------
// Return the system time in microseconds, which is the
// number of 32-bit timer counts since the timer was
// initialized.  This will work properly for at least 71
// minutes after which it could roll over.
// Input: none
// Output: system time in microseconds
// Assumes: BSP_Time_Init() has been called
uint32_t BSP_Time_Get(void){
  // 2*32/1,000,000 = 4,294 seconds, about 71 minutes
  return (0xFFFFFFFF - WTIMER5_TBV_R);
}

// ------------BSP_Delay1ms------------
// Simple delay function which delays about n
// milliseconds.
// Inputs: n  number of 1 msec to wait
// Outputs: none
void BSP_Delay1ms(uint32_t n){
  while(n){
    parrotdelay(23746);    // 1 msec, tuned at 80 MHz, originally part of LCD module
    n--;
  }
}

// There are two I2C devices on the Educational BoosterPack MKII:
// OPT3001 Light Sensor
// TMP006 Temperature sensor
// Both initialization functions can use this general I2C
// initialization.
#define MAXRETRIES              5  // number of receive attempts before giving up
void static i2cinit(void){
  SYSCTL_RCGCI2C_R |= 0x0002;      // 1a) activate clock for I2C1
  SYSCTL_RCGCGPIO_R |= 0x0001;     // 1b) activate clock for Port A
  while((SYSCTL_PRGPIO_R&0x01) == 0){};// allow time for clock to stabilize
                                   // 2) no need to unlock PA7-6
  GPIO_PORTA_AMSEL_R &= ~0xC0;     // 3) disable analog functionality on PA7-6
                                   // 4) configure PA7-6 as I2C1
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0x00FFFFFF)+0x33000000;
  GPIO_PORTA_ODR_R |= 0x80;        // 5) enable open drain on PA7 only
  GPIO_PORTA_AFSEL_R |= 0xC0;      // 6) enable alt funct on PA7-6
  GPIO_PORTA_DEN_R |= 0xC0;        // 7) enable digital I/O on PA7-6
  I2C1_MCR_R = I2C_MCR_MFE;        // 8) master function enable
  I2C1_MTPR_R = 39;                // 9) configure for 100 kbps clock
  // 20*(TPR+1)*12.5ns = 10us, with TPR=39
}

// receives one byte from specified slave
// Note for HMC6352 compass only:
// Used with 'r' and 'g' commands
// Note for TMP102 thermometer only:
// Used to read the top byte of the contents of the pointer register
//  This will work but is probably not what you want to do.
//uint8_t static I2C_Recv(int8_t slave){
//  int retryCounter = 1;
//  do{
//    while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
//    I2C1_MSA_R = (slave<<1)&0xFE;    // MSA[7:1] is slave address
//    I2C1_MSA_R |= 0x01;              // MSA[0] is 1 for receive
//    I2C1_MCS_R = (0
////                         & ~I2C_MCS_ACK     // negative data ack (last byte)
//                         | I2C_MCS_STOP     // generate stop
//                         | I2C_MCS_START    // generate start/restart
//                         | I2C_MCS_RUN);    // master enable
//    while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
//    retryCounter = retryCounter + 1;        // increment retry counter
//  }                                         // repeat if error
//  while(((I2C1_MCS_R&(I2C_MCS_ADRACK|I2C_MCS_ERROR)) != 0) && (retryCounter <= MAXRETRIES));
//  return (I2C1_MDR_R&0xFF);          // usually returns 0xFF on error
//}

// receives two bytes from specified slave
// Note for HMC6352 compass only:
// Used with 'A' commands
// Note for TMP102 thermometer only:
// Used to read the contents of the pointer register
uint16_t static I2C_Recv2(int8_t slave){
  uint8_t data1,data2;
  int retryCounter = 1;
  do{
    while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
    I2C1_MSA_R = (slave<<1)&0xFE;    // MSA[7:1] is slave address
    I2C1_MSA_R |= 0x01;              // MSA[0] is 1 for receive
    I2C1_MCS_R = (0
                         | I2C_MCS_ACK      // positive data ack
//                         & ~I2C_MCS_STOP    // no stop
                         | I2C_MCS_START    // generate start/restart
                         | I2C_MCS_RUN);    // master enable
    while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
    data1 = (I2C1_MDR_R&0xFF);       // MSB data sent first
    I2C1_MCS_R = (0
//                         & ~I2C_MCS_ACK     // negative data ack (last byte)
                         | I2C_MCS_STOP     // generate stop
//                         & ~I2C_MCS_START   // no start/restart
                         | I2C_MCS_RUN);    // master enable
    while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
    data2 = (I2C1_MDR_R&0xFF);       // LSB data sent last
    retryCounter = retryCounter + 1;        // increment retry counter
  }                                         // repeat if error
  while(((I2C1_MCS_R&(I2C_MCS_ADRACK|I2C_MCS_ERROR)) != 0) && (retryCounter <= MAXRETRIES));
  return (data1<<8)+data2;                  // usually returns 0xFFFF on error
}

// sends one byte to specified slave
// Note for HMC6352 compass only:
// Used with 'S', 'W', 'O', 'C', 'E', 'L', and 'A' commands
//  For 'A' commands, I2C_Recv2() should also be called
// Note for TMP102 thermometer only:
// Used to change the pointer register
// Returns 0 if successful, nonzero if error
uint16_t static I2C_Send1(int8_t slave, uint8_t data1){
  while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
  I2C1_MSA_R = (slave<<1)&0xFE;    // MSA[7:1] is slave address
  I2C1_MSA_R &= ~0x01;             // MSA[0] is 0 for send
  I2C1_MDR_R = data1&0xFF;         // prepare first byte
  I2C1_MCS_R = (0
//                       & ~I2C_MCS_ACK     // no data ack (no data on send)
                       | I2C_MCS_STOP     // generate stop
                       | I2C_MCS_START    // generate start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
                                          // return error bits
  return (I2C1_MCS_R&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR));
}

// sends two bytes to specified slave
// Note for HMC6352 compass only:
// Used with 'r' and 'g' commands
//  For 'r' and 'g' commands, I2C_Recv() should also be called
// Note for TMP102 thermometer only:
// Used to change the top byte of the contents of the pointer register
//  This will work but is probably not what you want to do.
// Returns 0 if successful, nonzero if error
//uint16_t static I2C_Send2(int8_t slave, uint8_t data1, uint8_t data2){
//  while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
//  I2C1_MSA_R = (slave<<1)&0xFE;    // MSA[7:1] is slave address
//  I2C1_MSA_R &= ~0x01;             // MSA[0] is 0 for send
//  I2C1_MDR_R = data1&0xFF;         // prepare first byte
//  I2C1_MCS_R = (0
////                       & ~I2C_MCS_ACK     // no data ack (no data on send)
////                       & ~I2C_MCS_STOP    // no stop
//                       | I2C_MCS_START    // generate start/restart
//                       | I2C_MCS_RUN);    // master enable
//  while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
//                                          // check error bits
//  if((I2C1_MCS_R&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR)) != 0){
//    I2C1_MCS_R = (0                // send stop if nonzero
////                       & ~I2C_MCS_ACK     // no data ack (no data on send)
//                       | I2C_MCS_STOP     // stop
////                       & ~I2C_MCS_START   // no start/restart
////                       & ~I2C_MCS_RUN     // master disable
//                        );
//                                          // return error bits if nonzero
//    return (I2C1_MCS_R&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR));
//  }
//  I2C1_MDR_R = data2&0xFF;         // prepare second byte
//  I2C1_MCS_R = (0
////                       & ~I2C_MCS_ACK     // no data ack (no data on send)
//                       | I2C_MCS_STOP     // generate stop
////                       & ~I2C_MCS_START   // no start/restart
//                       | I2C_MCS_RUN);    // master enable
//  while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
//                                          // return error bits
//  return (I2C1_MCS_R&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR));
//}

// sends three bytes to specified slave
// Note for HMC6352 compass only:
// Used with 'w' and 'G' commands
// Note for TMP102 thermometer only:
// Used to change the contents of the pointer register
// Returns 0 if successful, nonzero if error
uint16_t static I2C_Send3(int8_t slave, uint8_t data1, uint8_t data2, uint8_t data3){
  while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for I2C ready
  I2C1_MSA_R = (slave<<1)&0xFE;    // MSA[7:1] is slave address
  I2C1_MSA_R &= ~0x01;             // MSA[0] is 0 for send
  I2C1_MDR_R = data1&0xFF;         // prepare first byte
  I2C1_MCS_R = (0
//                       & ~I2C_MCS_ACK     // no data ack (no data on send)
//                       & ~I2C_MCS_STOP    // no stop
                       | I2C_MCS_START    // generate start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
                                          // check error bits
  if((I2C1_MCS_R&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR)) != 0){
    I2C1_MCS_R = (0                // send stop if nonzero
//                       & ~I2C_MCS_ACK     // no data ack (no data on send)
                       | I2C_MCS_STOP     // stop
//                       & ~I2C_MCS_START   // no start/restart
//                       & ~I2C_MCS_RUN     // master disable
                       );
                                          // return error bits if nonzero
    return (I2C1_MCS_R&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR));
  }
  I2C1_MDR_R = data2&0xFF;         // prepare second byte
  I2C1_MCS_R = (0
//                       & ~I2C_MCS_ACK     // no data ack (no data on send)
//                       & ~I2C_MCS_STOP    // no stop
//                       & ~I2C_MCS_START   // no start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
                                          // check error bits
  if((I2C1_MCS_R&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR)) != 0){
    I2C1_MCS_R = (0                // send stop if nonzero
//                       & ~I2C_MCS_ACK     // no data ack (no data on send)
                       | I2C_MCS_STOP     // stop
//                       & ~I2C_MCS_START   // no start/restart
//                       & ~I2C_MCS_RUN   // master disable
                        );
                                          // return error bits if nonzero
    return (I2C1_MCS_R&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR));
  }
  I2C1_MDR_R = data3&0xFF;         // prepare third byte
  I2C1_MCS_R = (0
//                       & ~I2C_MCS_ACK     // no data ack (no data on send)
                       | I2C_MCS_STOP     // generate stop
//                       & ~I2C_MCS_START   // no start/restart
                       | I2C_MCS_RUN);    // master enable
  while(I2C1_MCS_R&I2C_MCS_BUSY){};// wait for transmission done
                                          // return error bits
  return (I2C1_MCS_R&(I2C_MCS_DATACK|I2C_MCS_ADRACK|I2C_MCS_ERROR));
}

// ------------BSP_LightSensor_Init------------
// Initialize a GPIO pin for input, which corresponds
// with BoosterPack pins J1.8 (Light Sensor interrupt).
// Initialize two I2C pins, which correspond with
// BoosterPack pins J1.9 (SCL) and J1.10 (SDA).
// Input: none
// Output: none
void BSP_LightSensor_Init(void){
  i2cinit();
                                   // 1) activate clock for Port A (done in i2cinit())
                                   // allow time for clock to stabilize (done in i2cinit())
                                   // 2) no need to unlock PA5
  GPIO_PORTA_AMSEL_R &= ~0x20;     // 3) disable analog on PA5
                                   // 4) configure PA5 as GPIO
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFF0FFFFF)+0x00000000;
  GPIO_PORTA_DIR_R &= ~0x20;       // 5) make PA5 input
  GPIO_PORTA_AFSEL_R &= ~0x20;     // 6) disable alt funct on PA5
  GPIO_PORTA_DEN_R |= 0x20;        // 7) enable digital I/O on PA5
}

// Send the appropriate codes to initiate a
// measurement with an OPT3001 light sensor at I2C
// slave address 'slaveAddress'.
// Assumes: BSP_LightSensor_Init() has been called
void static lightsensorstart(uint8_t slaveAddress){
  // configure Low Limit Register (0x02) for:
  // INT pin active after each conversion completes
  I2C_Send3(slaveAddress, 0x02, 0xC0, 0x00);
  // configure Configuration Register (0x01) for:
  // 15-12 RN         range number         1100b = automatic full-scale setting mode
  // 11    CT         conversion time         1b = 800 ms
  // 10-9  M          mode of conversion     01b = single-shot
  // 8     OVF        overflow flag field     0b (read only)
  // 7     CRF        conversion ready field  0b (read only)
  // 6     FH         flag high field         0b (read only)
  // 5     FL         flag low field          0b (read only)
  // 4     L          latch                   1b = latch interrupt if measurement exceeds programmed ranges
  // 3     POL        polarity                0b = INT pin reports active low
  // 2     ME         mask exponent           0b = do not mask exponent (more math later)
  // 1-0   FC         fault count            00b = 1 fault triggers interrupt
  I2C_Send3(slaveAddress, 0x01, 0xCA, 0x10);
  I2C_Recv2(slaveAddress);         // read Configuration Register to reset conversion ready
}

// Send the appropriate codes to end a measurement
// with an OPT3001 light sensor at I2C slave address
// 'slaveAddress'.  Return results (units 100*lux).
// Assumes: BSP_LightSensor_Init() has been called and measurement is ready
int32_t static lightsensorend(uint8_t slaveAddress){
  uint16_t raw, config;
  I2C_Send1(slaveAddress, 0x00);   // pointer register 0x00 = Result Register
  raw = I2C_Recv2(slaveAddress);
  // force the INT pin to clear by clearing and resetting the latch bit of the Configuration Register (0x01)
  I2C_Send1(slaveAddress, 0x01);   // pointer register 0x01 = Configuration Register
  config = I2C_Recv2(slaveAddress);// current Configuration Register
  I2C_Send3(slaveAddress, 0x01, (config&0xFF00)>>8, (config&0x00FF)&~0x0010);
  I2C_Send3(slaveAddress, 0x01, (config&0xFF00)>>8, (config&0x00FF)|0x0010);
  return (1<<(raw>>12))*(raw&0x0FFF);
}

// ------------BSP_LightSensor_Input------------
// Query the OPT3001 light sensor for a measurement.
// Wait until the measurement is ready, which may
// take 800 ms.
// Input: none
// Output: light intensity (units 100*lux)
// Assumes: BSP_LightSensor_Init() has been called
#define LIGHTINT  (*((volatile uint32_t *)0x40004080))  /* PA5 */
int LightBusy = 0;                 // 0 = idle; 1 = measuring
uint32_t BSP_LightSensor_Input(void){
  uint32_t light;
  LightBusy = 1;
  lightsensorstart(0x44);
  while(LIGHTINT == 0x20){};       // wait for conversion to complete
  light = lightsensorend(0x44);
  LightBusy = 0;
  return light;
}

// ------------BSP_LightSensor_Start------------
// Start a measurement using the OPT3001.
// If a measurement is currently in progress, return
// immediately.
// Input: none
// Output: none
// Assumes: BSP_LightSensor_Init() has been called
void BSP_LightSensor_Start(void){
  if(LightBusy == 0){
    // no measurement is in progress, so start one
    LightBusy = 1;
    lightsensorstart(0x44);
  }
}

// ------------BSP_LightSensor_End------------
// Query the OPT3001 light sensor for a measurement.
// If no measurement is currently in progress, start
// one and return zero immediately.  If the measurement
// is not yet complete, return zero immediately.  If
// the measurement is complete, store the result in the
// pointer provided and return one.
// Input: light is pointer to store light intensity (units 100*lux)
// Output: one if measurement is ready and pointer is valid
//         zero if measurement is not ready and pointer unchanged
// Assumes: BSP_LightSensor_Init() has been called
int BSP_LightSensor_End(uint32_t *light){
  uint32_t lightLocal;
  if(LightBusy == 0){
    // no measurement is in progress, so start one
    LightBusy = 1;
    lightsensorstart(0x44);
    return 0;                      // measurement needs more time to complete
  } else{
    // measurement is in progress
    if(LIGHTINT == 0x20){
      return 0;                    // measurement needs more time to complete
    } else{
      lightLocal = lightsensorend(0x44);
      *light = lightLocal;
      LightBusy = 0;
      return 1;                    // measurement is complete; pointer valid
    }
  }
}

// ------------BSP_TempSensor_Init------------
// Initialize a GPIO pin for input, which corresponds
// with BoosterPack pins J2.11 (Temperature Sensor
// interrupt).  Initialize two I2C pins, which
// correspond with BoosterPack pins J1.9 (SCL) and
// J1.10 (SDA).
// Input: none
// Output: none
void BSP_TempSensor_Init(void){
  i2cinit();
                                   // 1) activate clock for Port A (done in i2cinit())
                                   // allow time for clock to stabilize (done in i2cinit())
                                   // 2) no need to unlock PA2
  GPIO_PORTA_AMSEL_R &= ~0x04;     // 3) disable analog on PA2
                                   // 4) configure PA2 as GPIO
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFF0FF)+0x00000000;
  GPIO_PORTA_DIR_R &= ~0x04;       // 5) make PA5 input
  GPIO_PORTA_AFSEL_R &= ~0x04;     // 6) disable alt funct on PA2
  GPIO_PORTA_DEN_R |= 0x04;        // 7) enable digital I/O on PA2
}

// Send the appropriate codes to initiate a
// measurement with a TMP006 temperature sensor at
// I2C slave address 'slaveAddress'.
// Assumes: BSP_TempSensor_Init() has been called
void static tempsensorstart(uint8_t slaveAddress){
  // configure Configuration Register (0x02) for:
  // 15    RST        software reset bit      0b = normal operation
  // 14-12 MOD        mode of operation     111b = sensor and die continuous conversion
  // 11-9  CR         ADC conversion rate   010b = 1 sample/sec
  // 8     EN         interrupt pin enable    1b = ~DRDY pin enabled (J2.11/P3.6)
  // 7     ~DRDY      data ready bit          0b (read only, automatic clear)
  // 6-0   reserved                      000000b (reserved)
  I2C_Send3(slaveAddress, 0x02, 0x75, 0x00);
}

// Send the appropriate codes to end a measurement
// with a TMP006 temperature sensor at I2C slave
// address 'slaveAddress'.  Store the results at the
// provided pointers.
// Assumes: BSP_TempSensor_Init() has been called and measurement is ready
void static tempsensorend(uint8_t slaveAddress, int32_t *sensorV, int32_t *localT){
  int16_t raw;
  I2C_Send1(slaveAddress, 0x00);   // pointer register 0x00 = Sensor Voltage Register
  raw = I2C_Recv2(slaveAddress);
  *sensorV = raw*15625;            // 156.25 nV per LSB
  I2C_Send1(slaveAddress, 0x01);   // pointer register 0x01 = Local Temperature Register
  raw = I2C_Recv2(slaveAddress);
  *localT = (raw>>2)*3125;         // 0.03125 C per LSB
}

// ------------BSP_TempSensor_Input------------
// Query the TMP006 temperature sensor for a
// measurement.  Wait until the measurement is ready,
// which may take 4 seconds.
// Input: sensorV is signed pointer to store sensor voltage (units 100*nV)
//        localT is signed pointer to store local temperature (units 100,000*C)
// Output: none
// Assumes: BSP_TempSensor_Init() has been called
#define TEMPINT   (*((volatile uint32_t *)0x40004010))  /* PA2 */
int TempBusy = 0;                  // 0 = idle; 1 = measuring
void BSP_TempSensor_Input(int32_t *sensorV, int32_t *localT){
  int32_t volt, temp;
  TempBusy = 1;
  tempsensorstart(0x40);
  while(TEMPINT == 0x04){};        // wait for conversion to complete
  tempsensorend(0x40, &volt, &temp);
  *sensorV = volt;
  *localT = temp;
  TempBusy = 0;
}

// ------------BSP_TempSensor_Start------------
// Start a measurement using the TMP006.
// If a measurement is currently in progress, return
// immediately.
// Input: none
// Output: none
// Assumes: BSP_TempSensor_Init() has been called
void BSP_TempSensor_Start(void){
  if(TempBusy == 0){
    // no measurement is in progress, so start one
    TempBusy = 1;
    tempsensorstart(0x40);
  }
}

// ------------BSP_TempSensor_End------------
// Query the TMP006 temperature sensor for a
// measurement.  If no measurement is currently in
// progress, start one and return zero immediately.
// If the measurement is not yet complete, return
// zero immediately.  If the measurement is complete,
// store the result in the pointers provided and
// return one.
// Input: sensorV is signed pointer to store sensor voltage (units 100*nV)
//        localT is signed pointer to store local temperature (units 100,000*C)
// Output: one if measurement is ready and pointers are valid
//         zero if measurement is not ready and pointers unchanged
// Assumes: BSP_TempSensor_Init() has been called
int BSP_TempSensor_End(int32_t *sensorV, int32_t *localT){
  int32_t volt, temp;
  if(TempBusy == 0){
    // no measurement is in progress, so start one
    TempBusy = 1;
    tempsensorstart(0x40);
    return 0;                      // measurement needs more time to complete
  } else{
    // measurement is in progress
    if(TEMPINT == 0x04){
      return 0;                    // measurement needs more time to complete
    } else{
      tempsensorend(0x40, &volt, &temp);
      *sensorV = volt;
      *localT = temp;
      TempBusy = 0;
      return 1;                    // measurement is complete; pointers valid
    }
  }
}
