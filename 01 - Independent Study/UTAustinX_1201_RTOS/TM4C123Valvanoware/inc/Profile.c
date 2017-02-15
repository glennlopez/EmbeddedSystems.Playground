// Profile.c
// Runs on TM4C123
// Implement the Profile pin initialization and Profile pin
// packaged read on the TM4C123.
// Daniel and Jonathan Valvano
// June 8, 2016

/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
   ISBN: 978-1466468863, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Introduction to the MSP432 Microcontroller",
   ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2015

   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
   ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2015

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

// The following pins were selected to be Profile pins:
// J3.27/PE1 Profile 0
// J3.28/PE2 Profile 1
// J3.29/PE3 Profile 2
// J3.30/PF1 Profile 3
// J2.18/PE0 Profile 4
// J4.36/PC5 Profile 5
// J4.34/PC7 Profile 6
// If it turns out that these pins are needed by another
// BoosterPack, such as the Bluetooth one, then the
// Profile initialization and get functions will need to
// be modified.

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// ------------Profile_Init------------
// Initialize all Profile pins for GPIO output,
// which correspond with unused BoosterPack pins.
// The Profile pins can be set, cleared, or toggled at
// strategic times and observed with a logic analyzer.
// This function should be called once at the beginning.
// Input: none
// Output: none
void Profile_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x00000004; // 1) activate clock for Port C
  while((SYSCTL_PRGPIO_R&0x04) == 0){};// allow time for clock to stabilize
                                   // 2) no need to unlock PC7,5
  GPIO_PORTC_AMSEL_R &= ~0xA0;     // 3) disable analog on PC7,5
                                   // 4) configure PC7,5 as GPIO
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0x0F0FFFFF)+0x00000000;
  GPIO_PORTC_DIR_R |= 0xA0;        // 5) make PC7,5 output
  GPIO_PORTC_AFSEL_R &= ~0xA0;     // 6) disable alt funct on PC7,5
  GPIO_PORTC_PUR_R &= ~0xA0;       // disable pull-up on PC7,5
  GPIO_PORTC_PDR_R &= ~0xA0;       // disable pull-down on PC7,5
  GPIO_PORTC_DEN_R |= 0xA0;        // 7) enable digital I/O on PC7,5
  GPIO_PORTC_DATA_R &= ~0xA0;      // 8) initialize PC7,5 low
  SYSCTL_RCGCGPIO_R |= 0x00000010; // 1) activate clock for Port E
  while((SYSCTL_PRGPIO_R&0x10) == 0){};// allow time for clock to stabilize
                                   // 2) no need to unlock PE3-0
  GPIO_PORTE_AMSEL_R &= ~0x0F;     // 3) disable analog on PE3-0
                                   // 4) configure PE3-0 as GPIO
  GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFF0000)+0x00000000;
  GPIO_PORTE_DIR_R |= 0x0F;        // 5) make PE3-0 output
  GPIO_PORTE_AFSEL_R &= ~0x0F;     // 6) disable alt funct on PE3-0
  GPIO_PORTE_PUR_R &= ~0x0F;       // disable pull-up on PE3-0
  GPIO_PORTE_PDR_R &= ~0x0F;       // disable pull-down on PE3-0
  GPIO_PORTE_DEN_R |= 0x0F;        // 7) enable digital I/O on PE3-0
  GPIO_PORTE_DATA_R &= ~0x0F;      // 8) initialize PE3-0 low
  SYSCTL_RCGCGPIO_R |= 0x00000020; // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20) == 0){};// allow time for clock to stabilize
                                   // 2) no need to unlock PF1
  GPIO_PORTF_AMSEL_R &= ~0x02;     // 3) disable analog on PF1
                                   // 4) configure PF1 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFFF0F)+0x00000000;
  GPIO_PORTF_DIR_R |= 0x02;        // 5) make PF1 output
  GPIO_PORTF_AFSEL_R &= ~0x02;     // 6) disable alt funct on PF1
  GPIO_PORTF_PUR_R &= ~0x02;       // disable pull-up on PF1
  GPIO_PORTF_PDR_R &= ~0x02;       // disable pull-down on PF1
  GPIO_PORTF_DEN_R |= 0x02;        // 7) enable digital I/O on PF1
  GPIO_PORTF_DATA_R &= ~0x02;      // 8) initialize PF1 low
}

// ------------Profile_Get------------
// Return the current status of all Profile pins.
// Profile 0 is in bit 0. Profile 1 is in bit 1, and
// so on.
// The most significant bit is set to tell the PC
// that these values are data and not standard ASCII
// characters.
// Input: none
// Output: 7-bit status of all Profile pins
// Assumes: Profile_Init() has been called
uint8_t Profile_Get(void){
  return (((GPIO_PORTE_DATA_R)&0x0E)>>1) | // Profiles 2, 1, 0
         (((GPIO_PORTF_DATA_R)&0x02)<<2) | // Profile 3
         (((GPIO_PORTE_DATA_R)&0x01)<<4) | // Profile 4
         (((GPIO_PORTC_DATA_R)&0x20))    | // Profile 5
         (((GPIO_PORTC_DATA_R)&0x80)>>1) | // Profile 6
         0x80;                             // set most significant bit
}
