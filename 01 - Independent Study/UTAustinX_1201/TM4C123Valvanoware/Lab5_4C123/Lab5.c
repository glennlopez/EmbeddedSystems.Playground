// Lab5.c
// Runs on either MSP432 or TM4C123
// Start project to Lab 5.  High level test of the file
// system will initialize variables, store files, and access
// files.
// Daniel and Jonathan Valvano
// August 29, 2016

/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
   ISBN: 978-1466468863, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Introduction to the MSP432 Microcontroller",
   ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
   ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2016

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
#include "../inc/BSP.h"
#include "../inc/CortexM.h"
#include "eDisk.h"
#include "../inc/Profile.h"
#include "Texas.h"
#include "eFile.h"

// normally this access would be poor style,
// but the access to internal data is used here for debugging
extern uint8_t Buff[512];
extern uint8_t Directory[256], FAT[256];

// Test function: Copy a NULL-terminated 'inString' into the
// 'Buff' global variable with a maximum of 512 characters.
// Uninitialized characters are set to 0xFF.
// Inputs:  inString  pointer to NULL-terminated character string
// Outputs: none
void testbuildbuff(char *inString){
  uint32_t i = 0;
  while((i < 512) && (inString[i] != 0)){
    Buff[i] = inString[i];
    i = i + 1;
  }
  while(i < 512){
    Buff[i] = 0xFF;             // fill the remainder of the buffer with 0xFF
    i = i + 1;
  }
}

// Test function: Draw a visual representation of the file
// system to the screen.  It should resemble Figure 5.13.
// This function reads the contents of the flash memory, so
// first call OS_File_Flush() to synchronize.
// Inputs:  index  starting index of directory and FAT
// Outputs: none
#define COLORSIZE 9
#define LCD_GRAY      0xCE59    // 200, 200, 200
const uint16_t ColorArray[COLORSIZE] = {LCD_YELLOW, LCD_BLUE, LCD_GREEN, LCD_RED, LCD_CYAN, LCD_LIGHTGREEN, LCD_ORANGE, LCD_MAGENTA, LCD_WHITE};
// display 12 lines of the directory and FAT
// used for debugging
// Input:  index is starting line number
// Output: none
void DisplayDirectory(uint8_t index){
  uint16_t dirclr[256], fatclr[256];
  volatile uint8_t *diraddr = (volatile uint8_t *)(EDISK_ADDR_MAX - 511); /* address of directory */
  volatile uint8_t *fataddr = (volatile uint8_t *)(EDISK_ADDR_MAX - 255); /* address of FAT */
  int i, j;
  // set default color to gray
  for(i=0; i<256; i=i+1){
    dirclr[i] = LCD_GRAY;
    fatclr[i] = LCD_GRAY;
  }
  // set color for each active file
  for(i=0; i<255; i=i+1){
    j = diraddr[i];
    if(j != 255){
      dirclr[i] = ColorArray[i%COLORSIZE];
    }
    while(j != 255){
      fatclr[j] = ColorArray[i%COLORSIZE];
      j = fataddr[j];
    }
  }
  // clear the screen if necessary (very slow but helps with button bounce)
  if((index + 11) > 255){
    BSP_LCD_FillScreen(LCD_BLACK);
  }
  // print the column headers
  BSP_LCD_DrawString(5, 0, "DIR", LCD_GRAY);
  BSP_LCD_DrawString(15, 0, "FAT", LCD_GRAY);
  // print the cloumns
  i = 0;
  while((i <= 11) && ((index + i) <= 255)){
    BSP_LCD_SetCursor(0, i+1);
    BSP_LCD_OutUDec4((uint32_t)(index + i), LCD_GRAY);
    BSP_LCD_SetCursor(4, i+1);
    BSP_LCD_OutUDec4((uint32_t)diraddr[index+i], dirclr[index+i]);
    BSP_LCD_SetCursor(10, i+1);
    BSP_LCD_OutUDec4((uint32_t)(index + i), LCD_GRAY);
    BSP_LCD_SetCursor(14, i+1);
    BSP_LCD_OutUDec4((uint32_t)fataddr[index+i], fatclr[index+i]);
    i = i + 1;
  }
}

int main(void){
  uint8_t m, n, p;              // file numbers
  uint8_t index = 0;            // row index
  volatile int i;
  DisableInterrupts();
  BSP_Clock_InitFastest();
  Profile_Init();               // initialize the 7 hardware profiling pins
  eDisk_Init(0);
  BSP_Button1_Init();
  BSP_Button2_Init();
  BSP_LCD_Init();
  BSP_LCD_FillScreen(LCD_BLACK);

  if(BSP_Button1_Input() == 0){ // run TExaS if Button1 is pressed
    BSP_LCD_DrawString(0, 0, "Running TExaS grader", LCD_YELLOW);
    // change 1000 to 4-digit number from edX
    TExaS_Init(GRADER, 1000);   // initialize the Lab 5 grader
//    TExaS_Init(LOGICANALYZER, 1000);  
// Logic analyzer will run, but the Lab 5 doesn't really use the logic analyzer
    while(BSP_Button1_Input() == 0){};
    BSP_LCD_DrawString(0, 0, "                    ", LCD_YELLOW);
  }
  if(BSP_Button2_Input() == 0){ // erase if Button2 is pressed
    BSP_LCD_DrawString(0, 0, "Erasing entire disk", LCD_YELLOW);
    OS_File_Format();
    while(BSP_Button2_Input() == 0){};
    BSP_LCD_DrawString(0, 0, "                   ", LCD_YELLOW);
  }
  EnableInterrupts();
  n = OS_File_New();            // n = 0, 3, 6, 9, ...
  testbuildbuff("buf0");
  OS_File_Append(n, Buff);      // 0x00020000
  testbuildbuff("buf1");
  OS_File_Append(n, Buff);      // 0x00020200
  testbuildbuff("buf2");
  OS_File_Append(n, Buff);      // 0x00020400
  testbuildbuff("buf3");
  OS_File_Append(n, Buff);      // 0x00020600
  testbuildbuff("buf4");
  OS_File_Append(n, Buff);      // 0x00020800
  testbuildbuff("buf5");
  OS_File_Append(n, Buff);      // 0x00020A00
  testbuildbuff("buf6");
  OS_File_Append(n, Buff);      // 0x00020C00
  testbuildbuff("buf7");
  OS_File_Append(n, Buff);      // 0x00020E00
  m = OS_File_New();            // m = 1, 4, 7, 10, ...
  testbuildbuff("dat0");
  OS_File_Append(m, Buff);      // 0x00021000
  testbuildbuff("dat1");
  OS_File_Append(m, Buff);      // 0x00021200
  testbuildbuff("dat2");
  OS_File_Append(m, Buff);      // 0x00021400
  testbuildbuff("dat3");
  OS_File_Append(m, Buff);      // 0x00021600
  p = OS_File_New();            // p = 2, 5, 8, 11, ...
  testbuildbuff("arr0");
  OS_File_Append(p, Buff);      // 0x00021800
  testbuildbuff("arr1");
  OS_File_Append(p, Buff);      // 0x00021A00
  testbuildbuff("buf8");
  OS_File_Append(n, Buff);      // 0x00021C00
  testbuildbuff("buf9");
  OS_File_Append(n, Buff);      // 0x00021E00
  testbuildbuff("arr2");
  OS_File_Append(p, Buff);      // 0x00022000
  testbuildbuff("dat4");
  OS_File_Append(m, Buff);      // 0x00022200
  i = OS_File_Size(n);          // i = 10 
  i = OS_File_Size(m);          // i = 5
  i = OS_File_Size(p);          // i = 3
  i = OS_File_Size(p+1);        // i = 0
  OS_File_Flush();              // 0x0003FE00
  while(1){
    DisplayDirectory(index);
    while((BSP_Button1_Input() != 0) && (BSP_Button2_Input() != 0)){};
    if(BSP_Button1_Input() == 0){
      if(index > 11){
        index = index - 11;
      } else{
        index = 0;
      }
    }
    if(BSP_Button2_Input() == 0){
      if((index + 11) <= 255){
        index = index + 11;
      }
    }
    while((BSP_Button1_Input() == 0) || (BSP_Button2_Input() == 0)){};
  }
}
