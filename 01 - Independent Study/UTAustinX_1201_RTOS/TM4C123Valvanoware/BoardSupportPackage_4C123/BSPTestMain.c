// BSPTestMain.c
// Runs on any computer
// Test the general board support package by calling its
// functions to perform some operation.  To port this program
// to a different processor, re-write BSP.c for that processor.
// This file should contain nothing hardware specific and
// require no significant changes.
// Daniel and Jonathan Valvano
// February 16, 2016

/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
   ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
   ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016

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
#include "BSP.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

uint16_t Red = 0, Green = 0, Blue = 0;
uint16_t JoyX, JoyY;
uint16_t AccX, AccY, AccZ;
void checkbuttons(void){
  static uint8_t prev1 = 0, prev2 = 0, prevS = 0; // previous values
  static uint8_t mode = 0;
  uint8_t current;

  BSP_Buzzer_Set(0);
  BSP_Joystick_Input(&JoyX, &JoyY, &current);
  BSP_Accelerometer_Input(&AccX, &AccY, &AccZ);
  if((current == 0) && (prevS != 0)){
    // Select was pressed since last loop
    mode = (mode + 1)&0x03;
    Red = Green = Blue = 0;
    BSP_Buzzer_Set(512);           // beep until next interrupt (0.1 sec beep)
  }
  prevS = current;
  if(mode == 0){
    // button mode
    current = BSP_Button1_Input();
    if((current == 0) && (prev1 != 0)){
      // Button1 was pressed since last loop
      Green = (Green + 64)&0x3FF;
    }
    prev1 = current;
    current = BSP_Button2_Input();
    if((current == 0) && (prev2 != 0)){
      // Button2 was pressed since last loop
      Blue = (Blue + 64)&0x3FF;
    }
    prev2 = current;
    Red = (Red + 1)&0x3FF;
  } else if(mode == 1){
    // joystick mode
    Green = JoyX;
    Blue = JoyY;
    Red = 0;
  } else if (mode == 2){
    // accelerometer mode
    if((AccX < 325) && (AccY > 325) && (AccY < 675) && (AccZ > 325) && (AccZ < 675)){
      Red = 500; Green = 0; Blue = 0;
    } else if((AccY < 325) && (AccX > 325) && (AccX < 675) && (AccZ > 325) && (AccZ < 675)){
      Red = 350; Green = 350; Blue = 0;
    } else if((AccX > 675) && (AccY > 325) && (AccY < 675) && (AccZ > 325) && (AccZ < 675)){
      Red = 0; Green = 500; Blue = 0;
    } else if((AccY > 675) && (AccX > 325) && (AccX < 675) && (AccZ > 325) && (AccZ < 675)){
      Red = 0; Green = 0; Blue = 500;
    }
  } else{
  }
  BSP_RGB_Set(Red, Green, Blue);
}

// return the number of digits
int numlength(uint32_t n){
  if(n < 10) return 1;
  if(n < 100) return 2;
  if(n < 1000) return 3;
  if(n < 10000) return 4;
  if(n < 100000) return 5;
  if(n < 1000000) return 6;
  if(n < 10000000) return 7;
  if(n < 100000000) return 8;
  if(n < 1000000000) return 9;
  return 10;
}

int main(void){
  int16_t color;
  uint32_t light, i, time;
  int32_t voltage, temperature;
  int count = 0;
  DisableInterrupts();
  BSP_Clock_InitFastest();
  BSP_Button1_Init();
  BSP_Button2_Init();
  BSP_Joystick_Init();
  BSP_RGB_Init(0, 0, 0);
  BSP_Buzzer_Init(0);
  BSP_Accelerometer_Init();
  BSP_PeriodicTask_Init(&checkbuttons, 10, 2);
  BSP_Time_Init();
  BSP_LCD_Init();
  BSP_LCD_FillScreen(BSP_LCD_Color565(0, 0, 0));
  BSP_LightSensor_Init();
  light = BSP_LightSensor_Input();
  BSP_LightSensor_Start();
  BSP_TempSensor_Init();
  BSP_TempSensor_Input(&voltage, &temperature);
  BSP_TempSensor_Start();
  EnableInterrupts();
  while(1){
    WaitForInterrupt();
    count = count + 1;
    if(count == 10){
      count = 0;
      // print LED status
      BSP_LCD_DrawString(0, 0, "Red=    ", BSP_LCD_Color565(255, 0, 0));
      BSP_LCD_SetCursor(4, 0);
      BSP_LCD_OutUDec((uint32_t)Red, BSP_LCD_Color565(255, 0, 0));
      BSP_LCD_DrawString(0, 1, "Green=    ", BSP_LCD_Color565(0, 255, 0));
      BSP_LCD_SetCursor(6, 1);
      BSP_LCD_OutUDec((uint32_t)Green, BSP_LCD_Color565(0, 255, 0));
      BSP_LCD_DrawString(0, 2, "Blue=    ", BSP_LCD_Color565(0, 0, 255));
      BSP_LCD_SetCursor(5, 2);
      BSP_LCD_OutUDec((uint32_t)Blue, BSP_LCD_Color565(0, 0, 255));
      // print joystick status
      BSP_LCD_DrawString(0, 3, "JoyX=    ", BSP_LCD_Color565(255, 255, 255));
      BSP_LCD_SetCursor(5, 3);
      BSP_LCD_OutUDec((uint32_t)JoyX, BSP_LCD_Color565(255, 0, 255));
      BSP_LCD_DrawString(0, 4, "JoyY=    ", BSP_LCD_Color565(255, 255, 255));
      BSP_LCD_SetCursor(5, 4);
      BSP_LCD_OutUDec((uint32_t)JoyY, BSP_LCD_Color565(255, 0, 255));
      // print accelerometer status
      BSP_LCD_DrawString(0, 5, "AccX=    ", BSP_LCD_Color565(255, 255, 255));
      BSP_LCD_SetCursor(5, 5);
      BSP_LCD_OutUDec((uint32_t)AccX, BSP_LCD_Color565(255, 0, 255));
      BSP_LCD_DrawString(0, 6, "AccY=    ", BSP_LCD_Color565(255, 255, 255));
      BSP_LCD_SetCursor(5, 6);
      BSP_LCD_OutUDec((uint32_t)AccY, BSP_LCD_Color565(255, 0, 255));
      BSP_LCD_DrawString(0, 7, "AccZ=    ", BSP_LCD_Color565(255, 255, 255));
      BSP_LCD_SetCursor(5, 7);
      BSP_LCD_OutUDec((uint32_t)AccZ, BSP_LCD_Color565(255, 0, 255));
      // get light sensor status
      if(BSP_LightSensor_End(&light)){
        color = BSP_LCD_Color565(255, 255, 0);
        BSP_LightSensor_Start();
      } else{
        color = BSP_LCD_Color565(255, 255, 255);
      }
      // print light sensor status
      BSP_LCD_DrawString(0, 8, "Light=        ", BSP_LCD_Color565(255, 255, 255));
      BSP_LCD_SetCursor(6, 8);
      BSP_LCD_OutUDec(light/100, color);
      BSP_LCD_DrawString(6+numlength(light/100), 8, ".", color);
      BSP_LCD_SetCursor(7+numlength(light/100), 8);
      if(numlength(light%100) == 1){
        // need to print a leading zero, which BSP_LCD_OutUDec() does not do automatically
        // so 1/100 prints as ".01" instead of ".1 "
        BSP_LCD_OutUDec(0, color);
      }
      BSP_LCD_OutUDec(light%100, color);
      // get temperature sensor status
      if(BSP_TempSensor_End(&voltage, &temperature)){
        color = BSP_LCD_Color565(50, 150, 255);
        BSP_TempSensor_Start();
      } else{
        color = BSP_LCD_Color565(255, 255, 255);
      }
      // print temperature sensor status
      BSP_LCD_DrawString(0, 9, "Volt=           ", BSP_LCD_Color565(255, 255, 255));
      if(voltage < 0){
        // print a leading minus sign ('-') and treat as unsigned
        BSP_LCD_DrawString(5, 9, "-", color);
        BSP_LCD_SetCursor(6, 9);
        BSP_LCD_OutUDec((-1*voltage)/100000000, color);
        BSP_LCD_DrawString(6+numlength((-1*voltage)/100000000), 9, ".", color);
        BSP_LCD_SetCursor(7+numlength((-1*voltage)/100000000), 9);
        for(i=numlength((-1*voltage)%100000000); i<8; i=i+1){
          // print any leading zeroes, which BSP_LCD_OutUDec() does not do automatically
          // so 1/100,000,000 prints as ".00000001" instead of ".1 "
          BSP_LCD_OutUDec(0, color);
        }
        BSP_LCD_OutUDec((-1*voltage)%100000000, color);
      } else{
        BSP_LCD_SetCursor(5, 9);
        BSP_LCD_OutUDec(voltage/100000000, color);
        BSP_LCD_DrawString(5+numlength(voltage/100000000), 9, ".", color);
        BSP_LCD_SetCursor(6+numlength(voltage/100000000), 9);
        for(i=numlength(voltage%100000000); i<8; i=i+1){
          // print any leading zeroes, which BSP_LCD_OutUDec() does not do automatically
          // so 1/100,000,000 prints as ".00000001" instead of ".1 "
          BSP_LCD_OutUDec(0, color);
        }
        BSP_LCD_OutUDec(voltage%100000000, color);
      }
      BSP_LCD_DrawString(0, 10, "Temp=           ", BSP_LCD_Color565(255, 255, 255));
      if(temperature < 0){
        // print a leading minus sign ('-') and treat as unsigned
        BSP_LCD_DrawString(5, 10, "-", color);
        BSP_LCD_SetCursor(6, 10);
        BSP_LCD_OutUDec((-1*temperature)/100000, color);
        BSP_LCD_DrawString(6+numlength((-1*temperature)/100000), 10, ".", color);
        BSP_LCD_SetCursor(7+numlength((-1*temperature)/100000), 10);
        for(i=numlength((-1*temperature)%100000); i<5; i=i+1){
          // print any leading zeroes, which BSP_LCD_OutUDec() does not do automatically
          // so 1/100,000 prints as ".00001" instead of ".1 "
          BSP_LCD_OutUDec(0, color);
        }
        BSP_LCD_OutUDec((-1*temperature)%100000, color);
      } else{
        BSP_LCD_SetCursor(5, 10);
        BSP_LCD_OutUDec(temperature/100000, color);
        BSP_LCD_DrawString(5+numlength(temperature/100000), 10, ".", color);
        BSP_LCD_SetCursor(6+numlength(temperature/100000), 10);
        for(i=numlength(temperature%100000); i<5; i=i+1){
          // print any leading zeroes, which BSP_LCD_OutUDec() does not do automatically
          // so 1/100,000 prints as ".00001" instead of ".1 "
          BSP_LCD_OutUDec(0, color);
        }
        BSP_LCD_OutUDec(temperature%100000, color);
      }
      // print the time
      time = BSP_Time_Get(); // in usec
      color = LCD_LIGHTGREEN;
      BSP_LCD_DrawString(0, 11, "Time=  :  .      ", BSP_LCD_Color565(255, 255, 255));
      BSP_LCD_SetCursor(7-numlength(time/60000000), 11);
      BSP_LCD_OutUDec(time/60000000, color);
      BSP_LCD_SetCursor(8, 11);
      if(numlength((time%60000000)/1000000) == 1){
        // print a leading zero, which BSP_LCD_OutUDec() does not do automatically
        // so 1/60 prints as ":01" instead of ":1 "
        BSP_LCD_OutUDec(0, color);
      }
      BSP_LCD_OutUDec((time%60000000)/1000000, color);
      BSP_LCD_SetCursor(11, 11);
      for(i=numlength(time%1000000); i<6; i=i+1){
        // print any leading zeroes, which BSP_LCD_OutUDec() does not do automatically
        // so 1/1,000,000 prints as ":000001" instead of ".1 "
        BSP_LCD_OutUDec(0, color);
      }
      BSP_LCD_OutUDec(time%1000000, color);
    }
  }
}
