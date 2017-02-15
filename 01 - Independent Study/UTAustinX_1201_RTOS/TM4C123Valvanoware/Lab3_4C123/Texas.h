// *****************Texas.h**************
// grading engine for Lab 3
//
// Runs on TM4C123
// Daniel and Jonathan Valvano
// March 23, 2016

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

enum TExaSmode{
  GRADER,
  GRADESTEP2,
  GRADESTEP3,
  GRADESTEP4,
  GRADESTEP5,
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
