// GPIO.h
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

#include "../inc/tm4c123gh6pm.h"

//#define DEFAULT 1
// Legend    TI part number
// CC2650BP  BOOSTXL-CC2650MA
// CC2650LP  LAUNCHXL-CC2650
// MSP432    MSP-EXP432P401R
// TM4C123   EK-TM4C123GXL
// MKII      BOOSTXL-EDUMKII
// TM4C123 bit-specific I/O addressing
//  bit    offset
// Bit 0 = 0x004 
// Bit 1 = 0x008
// Bit 2 = 0x010
// Bit 3 = 0x020
// Bit 4 = 0x040
// Bit 5 = 0x080
// Bit 6 = 0x100
// Bit 7 = 0x200
#define PA3   (*((volatile uint32_t *)0x40004020))
#define PB2   (*((volatile uint32_t *)0x40005010))
#define PB5   (*((volatile uint32_t *)0x40005080))
#define PB6   (*((volatile uint32_t *)0x40005100))
#define PC6   (*((volatile uint32_t *)0x40006100))
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

#define SetMRDY() (PB5 = 0x20)
#define ClearMRDY() (PB5 = 0x00)
#define SetReset() (PC6 = 0x40)
#define ClearReset() (PC6 = 0x00)
#define ReadSRDY() (PC6)
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

#define SetMRDY() (PB6 = 0x40)
#define ClearMRDY() (PB6 = 0x00)
#define SetReset() (PC6 = 0x40)
#define ClearReset() (PC6 = 0x00)
#define ReadSRDY() (PA3)
#endif


//------------GPIO_Init------------
// Initialize MRDY (out), SRDY (in), RESET (out) GPIO pins
// Input: none
// Output: none
void GPIO_Init(void);
