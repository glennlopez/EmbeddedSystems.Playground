// GPIO.c
// Runs on TM4C123
// Digital input/output from TM4C123 LaunchPad to CC2650
// Jonathan Valvano
// September 23, 2016

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

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "GPIO.h"
// Legend    TI part number
// CC2650BP  BOOSTXL-CC2650MA
// CC2650LP  LAUNCHXL-CC2650
// MSP432    MSP-EXP432P401R
// TM4C123   EK-TM4C123GXL
// MKII      BOOSTXL-EDUMKII

#ifdef DEFAULT
// Option 4) Use this option with CC2650BP without an MKII 
// Two board stack: CC2650BP+TM4C123 
// Acceptable projects:
//     VerySimpleApplicationProcessor_4C123
//     ApplicationProcessor_4C123
// This runs with the default version of SNP that ships on the BOOSTXL-CC2650MA
// signal  TM4C123                          CC2650BP       comment
//  3V3    J1.1  3.3V                       J1.1  3.3V     Power from TM4C123 to CC2650BP 
//  GND    J2.20 ground                     J2.20 ground   Connect ground together
//  NRESET J4.35 TM4C123 PC6, MSP432 P6.7   J4.35          Reset from TM4C123 to CC2650BP  
//  TX     J1.3  TM4C123 PB0, MSP432 P3.2   J1.3  DIO0_TXD UART from CC2650BP to TM4C123  
//  RX     J1.4  TM4C123 PB1, MSP432 P3.3   J1.4  DIO1_RXD UART from TM4C123 to CC2650BP
//  MRDY   J1.2  TM4C123 PB5, MSP432 P6.0   J1.2  IOID_7   Master ready from TM4C123 to CC2650BP 
//  SRDY   J2.19 TM4C123 PB2, MSP432 P2.5   J2.19 IOID_8   Slave ready from CC2650BP to TM4C123 

//------------GPIO_Init------------
// Initialize MRDY (out), SRDY (in), RESET (out) GPIO pins
// Input: none
// Output: none
void GPIO_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x0006;     // activate clock for Ports B and C
  while((SYSCTL_PRGPIO_R&0x06) != 0x06){};// wait for clocks to stabilize

  GPIO_PORTB_AFSEL_R &= ~0x04;     // SRDY is PB2, J2.19
  GPIO_PORTB_AMSEL_R &= ~0x04;     // disable analog functionality on PB2
  GPIO_PORTB_DEN_R |= 0x04;        // enable digital I/O on PB2
  GPIO_PORTB_PUR_R |= 0x04;        // enable pullup on PB2
  GPIO_PORTB_DIR_R &= ~0x04;       // input on PB2
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFF0FF);

  GPIO_PORTC_AFSEL_R &= ~0x40;     // J4.35 Reset to CC2650 {TM4C123 PC6, MSP432 P6.7}
  GPIO_PORTC_AMSEL_R &= ~0x40;     // disable analog functionality on PC6
  GPIO_PORTC_DEN_R |= 0x40;        // enable digital I/O on PC6
  GPIO_PORTC_DIR_R |= 0x40;        // output on PC6
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xF0FFFFFF);

  GPIO_PORTB_AFSEL_R &= ~0x20;     // J1.2 MRDY {TM4C123 PB5, MSP432 P6.0}
  GPIO_PORTB_AMSEL_R &= ~0x20;     // disable analog functionality on PB5
  GPIO_PORTB_DEN_R |= 0x20;        // enable digital I/O on PB5
  GPIO_PORTB_DIR_R |= 0x20;        // output on PB5
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFF0FFFFF);
    
  SetMRDY();        //   MRDY=1  
  
  ClearReset();     // RESET=0    
}
#else
// These three options require either reprogramming the CC2650LP/CC2650BP or using a 7-wire tether
// These three options allow the use of the MKII I/O boosterpack
// Option 1) The CC2650BP is tethered to the TM4C123 using 7 wires (no reprogramming CC2650 needed)
// Two board stack: TM4C123+MKII  <---7 wires--->  CC2650BP
// signal  TM4C123                          CC2650BP       comment
//  3V3    J1.1  3.3V                       J1.1  3.3V     Power from TM4C123 to CC2650BP 
//  GND    J2.20 ground                     J2.20 ground   Connect ground together
//  NRESET J4.35 TM4C123 PC6, MSP432 P6.7   J4.35          Reset from TM4C123 to CC2650BP  
//  TX     J1.3  TM4C123 PB0, MSP432 P3.2   J1.3  DIO0_TXD UART from CC2650BP to TM4C123 
//  RX     J1.4  TM4C123 PB1, MSP432 P3.3   J1.4  DIO1_RXD UART from TM4C123 to CC2650BP
//  MRDY   J2.14 TM4C123 PB6, MSP432 P1.7   J1.2  IOID_7   Master ready from TM4C123 to CC2650BP 
//  SRDY   J2.12 TM4C123 PA3, MSP432 P5.2   J2.19 IOID_8   Slave ready from CC2650BP to TM4C123  

// Option 2) This version also works with a custom version of the SNP loaded onto the CC2650BP
// Program into CC2650BP: simple_np_cc2650bp_uart_pm_xsbl_mooc_custom.hex
// Three board stack: CC2650BP+TM4C123+MKII (BOOSTXL-CC2650MA, EK-TM4C123GXL, and BOOSTXL-EDUMKII)
// signal  TM4C123                          CC2650LP       comment
//  3V3    J1.1  3.3V                       J1.1  3.3V     Power from MSP432 to CC2650BP 
//  GND    J2.20 ground                     J2.20 ground   Connect ground together
//  NRESET J4.35 TM4C123 PC6, MSP432 P6.7   J4.35          Reset from TM4C123 to CC2650BP  
//  TX     J1.3  TM4C123 PB0, MSP432 P3.2   J1.3  DIO0_TXD UART from CC2650BP to TM4C123 
//  RX     J1.4  TM4C123 PB1, MSP432 P3.3   J1.4  DIO1_RXD UART from TM4C123 to CC2650BP
//  MRDY   J2.14 TM4C123 PB6, MSP432 P1.7   J1.14 DIO8     Master ready from TM4C123 to CC2650BP 
//  SRDY   J2.12 TM4C123 PA3, MSP432 P5.2   J2.12 DIO14    Slave ready from CC2650BP to TM4C123 

// Option 3) This version also works with a custom version of the SNP loaded onto the CC2650LP
// Program into CC2650LP: simple_np_cc2650lp_uart_pm_xsbl_mooc_custom.hex
// Remove Rx and Tx jumpers on CC2650LP
// Optional: remove two LED jumpers on Red, Green LEDs on CC2650 LaunchPad
// Place insulting tape over the set of 11 jumpers in middle, before stacking
// Three board stack: CC2650LP+TM4C123+MKII (LAUNCHXL-CC2650, EK-TM4C123GXL, and BOOSTXL-EDUMKII)
// signal  TM4C123                          CC2650LP       comment
//  3V3    J1.1  3.3V                       J1.1  3.3V     Power from TM4C123 to CC2650LP 
//  GND    J2.20 ground                     J2.20 ground   Connect ground together
//  NRESET J4.35 TM4C123 PC6, MSP432 P6.7   J4.35          Reset from TM4C123 to CC2650LP  
//  TX     J1.3  TM4C123 PB0, MSP432 P3.2   J1.3  DIO3_TXD UART from CC2650LP to TM4C123 
//  RX     J1.4  TM4C123 PB1, MSP432 P3.3   J1.4  DIO2_RXD UART from TM4C123 to CC2650LP
//  MRDY   J2.14 TM4C123 PB6, MSP432 P1.7   J1.14 DIO12    Master ready from TM4C123 to CC2650LP 
//  SRDY   J2.12 TM4C123 PA3, MSP432 P5.2   J2.12 DIO14    Slave ready from CC2650LP to TM4C123 

//------------GPIO_Init------------
// Initialize MRDY (out), SRDY (in), RESET (out) GPIO pins
// Input: none
// Output: none
void GPIO_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x0007;     // activate clock for Ports A B and C
  while((SYSCTL_PRGPIO_R&0x07) != 0x07){};// wait for clocks to stabilize

  GPIO_PORTA_AFSEL_R &= ~0x08;     // SRDY   J2.12 TM4C123 PA3, MSP432 P5.2}
  GPIO_PORTA_AMSEL_R &= ~0x08;     // disable analog functionality on PA3
  GPIO_PORTA_DEN_R |= 0x08;        // enable digital I/O on PA3
  GPIO_PORTA_PUR_R |= 0x08;        // enable pullup on PA3
  GPIO_PORTA_DIR_R &= ~0x08;       // input on PA3
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFF0FFF);

  GPIO_PORTC_AFSEL_R &= ~0x40;     // J4.35 Reset to CC2650 {TM4C123 PC6, MSP432 P6.7}
  GPIO_PORTC_AMSEL_R &= ~0x40;     // disable analog functionality on PC6
  GPIO_PORTC_DEN_R |= 0x40;        // enable digital I/O on PC6
  GPIO_PORTC_DIR_R |= 0x40;        // output on PC6
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xF0FFFFFF);

  GPIO_PORTB_AFSEL_R &= ~0x40;     // MRDY {J2.14 TM4C123 PB6, MSP432 P1.7}
  GPIO_PORTB_AMSEL_R &= ~0x40;     // disable analog functionality on PB6
  GPIO_PORTB_DEN_R |= 0x40;        // enable digital I/O on PB6
  GPIO_PORTB_DIR_R |= 0x40;        // output on PB6
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xF0FFFFFF);
    
  SetMRDY();        //   MRDY=1  
  
  ClearReset();     // RESET=0    
  
}
#endif
