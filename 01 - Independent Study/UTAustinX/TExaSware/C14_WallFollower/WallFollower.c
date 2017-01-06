// WallFollower.c
// Runs on LM4F120/TM4C123
// Use SysTick interrupts to implement a software PWM to drive
// two DC motors at variable duty cycles.
// Two GP2Y0A21YK0F analog IR distance sensors are used to allow
// the robot to follow a wall.  The two IR sensors are mounted
// looking forward to the left and forward to the right.
// Basically, the goal is to control power to each wheel so the
// left and right distances to the walls are equal.
// A third IR sensor looks directly forward to attempt to avoid
// a head-on collision.  If an object is detected too close to
// the front of the robot, both wheels are immediately stopped.
/*
    ------------------------------------------wall---------
                      /
                     /
                    / 
                   /
         -----------
         |         |
         | Robot   | ---> direction of motion and third sensor
         |         |
         -----------
                   \
                    \
                     \
                      \
    ------------------------------------------wall---------
*/
// Daniel Valvano, Jonathan Valvano
// September 12, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
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

// PA0 connected to U0Rx (VCP receive)
// PA1 connected to U0Tx (VCP transmit)
// PA5 connected to DC motor interface for left wheel
// PA6 connected to DC motor interface for right wheel
//  Note that the way the wheels are physically mounted requires
//  that one of the motors be wired opposite to the other one.
//  Since the motors are back-to-back, one must spin "backwards"
//  when both wheels are supposed to spin the same direction.
// PE1 connected to forward facing IR distance sensor
// PE4 connected to forward right IR distance sensor
// PE5 connected to forward left IR distance sensor

#include "ADCSWTrigger.h"
#include "PLL.h"
#include "UART2.h"

#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DR8R_R       (*((volatile unsigned long *)0x40004508))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_IS_R         (*((volatile unsigned long *)0x40025404))
#define GPIO_PORTF_IBE_R        (*((volatile unsigned long *)0x40025408))
#define GPIO_PORTF_IEV_R        (*((volatile unsigned long *)0x4002540C))
#define GPIO_PORTF_IM_R         (*((volatile unsigned long *)0x40025410))
#define GPIO_PORTF_RIS_R        (*((volatile unsigned long *)0x40025414))
#define GPIO_PORTF_ICR_R        (*((volatile unsigned long *)0x4002541C))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))
#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))
#define NVIC_PRI7_R             (*((volatile unsigned long *)0xE000E41C))
#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

// High and low cycle counts for left and right wheels
long LeftH, LeftL, RightH, RightL;
// Counter for the stage of PWM output
unsigned long PWMStage = 1;
// Properties of the controller
long Error;                     // difference between right and left distances to the walls
#define GAIN              2     // translates the difference between right and left ADC readings into a PWM duty update
#define CRASH             IR10CM// if there is less than this distance ahead of the robot, it will immediately stop
#define IR10CM            3100  // according to datasheet ~2.3 V with object at 10 cm
#define IR16CM            1704  // according to experiment ~1.25 V with object at 16 cm
#define IR20CM            1417  // according to experiment ~1.038 V with object at 20 cm
#define IR80CM            546   // according to datasheet ~0.4 V with object at 80 cm
                                // with equal power to both motors (LeftH == RightH), the robot still may not drive straight
                                // due to mechanical differences in the motors, so bias the left wheel faster or slower than
                                // the constant right wheel
#define LEFTMINPCT        30    // minimum percent duty cycle of left wheel (10 to 90)
#define LEFTMAXPCT        50    // maximum percent duty cycle of left wheel (10 to 90)
#define RIGHTCONSTPCT     40    // constant percent duty cycle of right wheel (10 to 90)

// Initialize motor pins and configure SysTick interrupts
void Motor_Init(void){
  SYSCTL_RCGC2_R |= 0x00000001; // activate clock for port A
  LeftH = (LEFTMAXPCT + LEFTMINPCT)*400;
  LeftL = 80000 - LeftH;        // value modified my controller
  RightH = RIGHTCONSTPCT*800;   // constant
  RightL = 80000 - RightH;
  GPIO_PORTA_AMSEL_R &= ~0x60;      // disable analog functionality on PA6-5
  GPIO_PORTA_PCTL_R &= ~0x0FF00000; // configure PA6-5 as GPIO
  GPIO_PORTA_DIR_R |= 0x60;     // make PA6-5 out
  GPIO_PORTA_DR8R_R |= 0x60;    // enable 8 mA drive on PA6-5
  GPIO_PORTA_AFSEL_R &= ~0x60;  // disable alt funct on PA6-5
  GPIO_PORTA_DEN_R |= 0x60;     // enable digital I/O on PA6-5
  GPIO_PORTA_DATA_R &= ~0x60;   // make PA6-5 low
  NVIC_ST_CTRL_R = 0;           // disable SysTick during setup
  NVIC_ST_RELOAD_R = LeftL - 1; // reload value for 500us
  NVIC_ST_CURRENT_R = 0;        // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
  NVIC_ST_CTRL_R = 0x00000007;  // enable with core clock and interrupts
}
void SysTick_Handler(void){
  if((PWMStage%3) == 1){        // time for first pin to rise
    if((LeftL + 100) < RightL){
      GPIO_PORTA_DATA_R |= 0x20;// make PA5 high (left wheel on)
                                // reload value for difference between right and left low time
      NVIC_ST_RELOAD_R = RightL - LeftL - 1;
    } else if((RightL + 100) < LeftL){
      GPIO_PORTA_DATA_R |= 0x40;// make PA6 high (right wheel on)
                                // reload value for difference between left and right low time
      NVIC_ST_RELOAD_R = LeftL - RightL - 1;
    } else{                     // LeftL == RightL
      GPIO_PORTA_DATA_R |= 0x60;// make PA6-5 high (both wheels on)
                                // reload value for high phase (LeftH == RightH)
      NVIC_ST_RELOAD_R = LeftH - 1;
      PWMStage = PWMStage + 1;  // next interrupt is skipped
    }
  } else if((PWMStage%3) == 2){ // time for second pin to rise
    if(LeftL < RightL){
      GPIO_PORTA_DATA_R |= 0x40;// make PA6 high (right wheel on)
                                // reload value high phase
      NVIC_ST_RELOAD_R = RightH - 1;
    } else{
      GPIO_PORTA_DATA_R |= 0x20;// make PA5 high (left wheel on)
                                // reload value high phase
      NVIC_ST_RELOAD_R = LeftH - 1;
    }
  } else if((PWMStage%3) == 0){ // time for both pins to fall
    GPIO_PORTA_DATA_R &= ~0x60; // make PA6-5 low
    PWMStage = 0;               // restart the count to prevent error upon rollover
    /*
    if((ForwardDistance + RearDistance) > 40){        // too far away; move toward wall
      if((LeftL + STEP/2) <= 72000){
        LeftL = LeftL + STEP/2; // turn soft left
      }
    } else if((ForwardDistance + RearDistance) < 20){ // too close; move away from wall
      if((LeftL - STEP/2) >= 8000){
        LeftL = LeftL - STEP/2; // turn soft right
      }
    } else if(ForwardDistance > RearDistance){        // run parallel to left wall
      if((LeftL + STEP) <= 72000){
        LeftL = LeftL + STEP;   // turn left
      }
    } else{
      if((LeftL - STEP) >= 8000){
        LeftL = LeftL - STEP;   // turn right
      }
      LeftH = 80000 - LeftL;
    }*/
    // integral control
    if(Error > 0){
      // Error is positive, so the left ADC value is greater
      // than the right ADC value.  This means that the right
      // distance is greater, so the robot must steer right.
      // Increasing power to the left wheel steers right.
      if((LeftH + Error) <= (LEFTMAXPCT*800)){
        LeftH = LeftH + Error;  // turn right
      } else{
        LeftH = (LEFTMAXPCT*800);// left wheel full speed
      }
    } else{
      // Error is negative, so the right ADC value is greater
      // than the left ADC value.  This means that the left
      // distance is greater, so the robot must steer left.
      // Decreasing power to the left wheel steers left.
      if((LeftH + Error) >= (LEFTMINPCT*800)){
        LeftH = LeftH + Error;  // turn left
      } else{
        LeftH = (LEFTMINPCT*800);// left wheel minimum speed
      }
    }
    LeftL = 80000 - LeftH;
    if(LeftL < RightL){         // reload value for low phase is minimum of LeftL and RightL
      NVIC_ST_RELOAD_R = LeftL - 1;
    } else{
      NVIC_ST_RELOAD_R = RightL - 1;
    }
  }
  PWMStage = PWMStage + 1;
  NVIC_ST_CURRENT_R = 0;
}
// Initialize built-in switch pins and configure falling edge interrupts
void Switch_Init(void){  unsigned long volatile delay;
  SYSCTL_RCGC2_R |= 0x00000020; // (a) activate clock for port F
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x11;         // allow changes to PF4,0
  GPIO_PORTF_DIR_R &= ~0x11;    // (c) make PF4,0 in (built-in button)
  GPIO_PORTF_AFSEL_R &= ~0x11;  //     disable alt funct on PF4,0
  GPIO_PORTF_DEN_R |= 0x11;     //     enable digital I/O on PF4,0
  GPIO_PORTF_PCTL_R &= ~0x000F000F; //  configure PF4,0 as GPIO
  GPIO_PORTF_AMSEL_R &= ~0x11;  //     disable analog functionality on PF4,0
  GPIO_PORTF_PUR_R |= 0x11;     //     enable weak pull-up on PF4,0
  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4,PF0 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;    //     PF4,PF0 is not both edges
  GPIO_PORTF_IEV_R &= ~0x11;    //     PF4,PF0 falling edge event
  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flags 4,0
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4,PF0
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00400000; // (g) priority 2
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
}
// L range: 8000,16000,24000,32000,40000,48000,56000,64000,72000
// power:   10%    20%   30%   40%   50%   60%   70%   80%   90%
void GPIOPortF_Handler(void){ // called on touch of either SW1 or SW2
  if(GPIO_PORTF_RIS_R&0x01){  // SW2 touch
    GPIO_PORTF_ICR_R = 0x01;  // acknowledge flag0
/*    if(MinL > 8000){
      MinL = MinL - 8000;     // slow down
      LeftL = LeftL - 8000;
      LeftH = 80000 - LeftL;  // constant period of 1ms, variable duty cycle
      RightL = RightL - 8000;
      RightH = 80000 - RightL;// constant period of 1ms, variable duty cycle
    }*/
  }
  if(GPIO_PORTF_RIS_R&0x10){  // SW1 touch
    GPIO_PORTF_ICR_R = 0x10;  // acknowledge flag4
/*    if(MinL < 72000){
      MinL = MinL + 8000;     // speed up
      LeftL = LeftL + 8000;
      LeftH = 80000 - LeftL;  // constant period of 1ms, variable duty cycle
      RightL = RightL + 8000;
      RightH = 80000 - RightL;// constant period of 1ms, variable duty cycle
    }*/
  }
}
// Initialize RGB LED pins
void LED_Init(void){  unsigned long volatile delay;
  SYSCTL_RCGC2_R |= 0x00000020; // (a) activate clock for port F
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTF_AMSEL_R &= ~0x0E;      // disable analog functionality on PF3-1
  GPIO_PORTF_PCTL_R &= ~0x0000FFF0; // configure PF3-1 as GPIO
  GPIO_PORTF_DIR_R |= 0x0E;     // make PF3-1 out (built-in LEDs)
  GPIO_PORTF_AFSEL_R &= ~0x0E;  // disable alt funct on PF3-1
  GPIO_PORTF_DEN_R |= 0x0E;     // enable digital I/O on PF3-1
  GPIO_PORTF_DATA_R &= ~0x0E;   // make PF3-1 low
}
// This function samples AIN2 (PE1), AIN9 (PE4), AIN8 (PE5) and
// returns the results in the corresponding variables.  Some
// kind of filtering is required because the IR distance sensors
// output occasional erroneous spikes.  This is an FIR filter:
// y(n) = (x(n) + x(n-1))/2
// Assumes: ADC initialized by previously calling ADC_Init298()
void ReadADCFIRFilter(unsigned long *ain2, unsigned long *ain9, unsigned long *ain8){
  //                   x(n-1)
  static unsigned long ain2previous=0;
  static unsigned long ain9previous=0;
  static unsigned long ain8previous=0;
  // save some memory; these do not need to be 'static'
  //            x(n)
  unsigned long ain2newest;
  unsigned long ain9newest;
  unsigned long ain8newest;
  ADC_In298(&ain2newest, &ain9newest, &ain8newest); // sample AIN2(PE1), AIN9 (PE4), AIN8 (PE5)
  *ain2 = (ain2newest + ain2previous)/2;
  *ain9 = (ain9newest + ain9previous)/2;
  *ain8 = (ain8newest + ain8previous)/2;
  ain2previous = ain2newest; ain9previous = ain9newest; ain8previous = ain8newest;
}
// This function samples AIN2 (PE1), AIN9 (PE4), AIN8 (PE5) and
// returns the results in the corresponding variables.  Some
// kind of filtering is required because the IR distance sensors
// output occasional erroneous spikes.  This is an IIR filter:
// y(n) = (x(n) + y(n-1))/2
// Assumes: ADC initialized by previously calling ADC_Init298()
void ReadADCIIRFilter(unsigned long *ain2, unsigned long *ain9, unsigned long *ain8){
  //                   y(n-1)
  static unsigned long filter2previous=0;
  static unsigned long filter9previous=0;
  static unsigned long filter8previous=0;
  // save some memory; these do not need to be 'static'
  //            x(n)
  unsigned long ain2newest;
  unsigned long ain9newest;
  unsigned long ain8newest;
  ADC_In298(&ain2newest, &ain9newest, &ain8newest); // sample AIN2(PE1), AIN9 (PE4), AIN8 (PE5)
  *ain2 = filter2previous = (ain2newest + filter2previous)/2;
  *ain9 = filter9previous = (ain9newest + filter9previous)/2;
  *ain8 = filter8previous = (ain8newest + filter8previous)/2;
}
// Median function from EE345M Lab 7 2011; Program 5.1 from Volume 3
// helper function for ReadADCMedianFilter() but works for general use
unsigned long median(unsigned long u1, unsigned long u2, unsigned long u3){
unsigned long result;
  if(u1>u2)
    if(u2>u3)   result=u2;     // u1>u2,u2>u3       u1>u2>u3
      else
        if(u1>u3) result=u3;   // u1>u2,u3>u2,u1>u3 u1>u3>u2
        else      result=u1;   // u1>u2,u3>u2,u3>u1 u3>u1>u2
  else
    if(u3>u2)   result=u2;     // u2>u1,u3>u2       u3>u2>u1
      else
        if(u1>u3) result=u1;   // u2>u1,u2>u3,u1>u3 u2>u1>u3
        else      result=u3;   // u2>u1,u2>u3,u3>u1 u2>u3>u1
  return(result);
}
// This function samples AIN2 (PE1), AIN9 (PE4), AIN8 (PE5) and
// returns the results in the corresponding variables.  Some
// kind of filtering is required because the IR distance sensors
// output occasional erroneous spikes.  This is a median filter:
// y(n) = median(x(n), x(n-1), x(n-2))
// Assumes: ADC initialized by previously calling ADC_Init298()
void ReadADCMedianFilter(unsigned long *ain2, unsigned long *ain9, unsigned long *ain8){
  //                   x(n-2)        x(n-1)
  static unsigned long ain2oldest=0, ain2middle=0;
  static unsigned long ain9oldest=0, ain9middle=0;
  static unsigned long ain8oldest=0, ain8middle=0;
  // save some memory; these do not need to be 'static'
  //            x(n)
  unsigned long ain2newest;
  unsigned long ain9newest;
  unsigned long ain8newest;
  ADC_In298(&ain2newest, &ain9newest, &ain8newest); // sample AIN2(PE1), AIN9 (PE4), AIN8 (PE5)
  *ain2 = median(ain2newest, ain2middle, ain2oldest);
  *ain9 = median(ain9newest, ain9middle, ain9oldest);
  *ain8 = median(ain8newest, ain8middle, ain8oldest);
  ain2oldest = ain2middle; ain9oldest = ain9middle; ain8oldest = ain8middle;
  ain2middle = ain2newest; ain9middle = ain9newest; ain8middle = ain8newest;
}
// This function returns the number of digits in the input 'n'.
// For example, if n=1234, the output is 4.
// For example, if n=88, the output is 2.
// Assumes: n <= 4095
unsigned long digits(unsigned long n){
  if(n < 10){
    return 1;
  }
  if(n < 100){
    return 2;
  }
  if(n < 1000){
    return 3;
  }
  return 4;             // more is not needed in this context
} 
#define LEDPATTERN        5171  // arbitrary number defines sequence of flashing LED
//#define LEDPATTERN     306783846// arbitrary number defines sequence of flashing LED
int main(void){
  unsigned long frwdleft, frwdright, ahead, i, timeOutput, pattern;
  long e;               // intermediate value of Error
  DisableInterrupts();  // disable interrupts while initializing
  PLL_Init();           // bus clock at 80 MHz
  Motor_Init();         // output to PA6-5, SysTick interrupts
  Switch_Init();        // arm PF4, PF0 for falling edge interrupts
  LED_Init();           // configure PF3-1 as GPIO or LEDs
  ADC_Init298();        // initialize ADC to sample AIN2 (PE1), AIN9 (PE4), AIN8 (PE5)
  UART_Init();          // initialize UART0 for 115,200 baud rate
  EnableInterrupts();   // enable after all initialization are done
  UART_OutString("\r\nL% - R% - Ahead - Frwd R - Frwd L - Error\r\n");
  timeOutput = 0;       // very imprecise counter to output occasionally
  pattern = LEDPATTERN; // used to flash an arbitrary pattern defined above
  while(1){
    // main program samples the ADC to check the sensors
    ReadADCMedianFilter(&ahead, &frwdright, &frwdleft);
    e = (frwdleft - frwdright);       // run parallel to left wall
    e = e*GAIN;
    Error = e;
    if((timeOutput%4096) == 0){
      // print to the UART occasionally
      // "L% - R% - Ahead - Frwd R - Frwd L - Error"  <-line gets printed once
      // "XX%  XX%  XXXX    XXXX     XXXX     -XXXXX" <-writes over previous
      UART_OutChar('\r');
      UART_OutUDec(LeftH/800);
      UART_OutChar('%');
      for(i=1; i<=(4-digits(LeftH/800)); i=i+1){
        UART_OutChar(' ');           // line up the output
      }
      UART_OutUDec(RightH/800);
      UART_OutChar('%');
      for(i=1; i<=(4-digits(RightH/800)); i=i+1){
        UART_OutChar(' ');           // line up the output
      }
      UART_OutUDec(ahead);
      for(i=1; i<=(8-digits(ahead)); i=i+1){
        UART_OutChar(' ');           // line up the output
      }
      UART_OutUDec(frwdright);
      for(i=1; i<=(9-digits(frwdright)); i=i+1){
        UART_OutChar(' ');           // line up the output
      }
      UART_OutUDec(frwdleft);
      for(i=1; i<=(9-digits(frwdleft)); i=i+1){
        UART_OutChar(' ');           // line up the output
      }
      if(Error < 0){
        UART_OutChar('-');
        UART_OutUDec(-1*Error);
      } else{
        UART_OutUDec(Error);
      }
      UART_OutString("       ");     // cover up any previous output
      // flash the LED in an arbitrary, ideally eye-catching pattern
      if(pattern&0x1){
        GPIO_PORTF_DATA_R ^= 0x04;   // toggle blue LED
      }
      pattern = pattern/2;
      if(pattern == 0){
        pattern = LEDPATTERN;
      }
    }
    timeOutput = timeOutput + 1;
    while(ahead > CRASH){
      // impending collision
      NVIC_ST_CTRL_R &= ~0x01;       // disable SysTick timer
      GPIO_PORTA_DATA_R &= ~0x60;    // make PA6-5 low
      GPIO_PORTF_DATA_R &= ~0x04;    // blue LED off
      GPIO_PORTF_DATA_R |= 0x02;     // red LED on
      while(ahead > CRASH){
        for(i=0; i<5000000; i=i+1);  // some amount of delay, doesn't really matter
        GPIO_PORTF_DATA_R &= ~0x02;  // red LED off
        for(i=0; i<5000000; i=i+1);  // some amount of delay, doesn't really matter
        GPIO_PORTF_DATA_R |= 0x02;   // red LED on
        ReadADCMedianFilter(&ahead, &frwdright, &frwdleft);
        UART_OutString("\r0%   0%   ");
        UART_OutUDec(ahead);
        UART_OutString("   PAUSED                            ");
      }
      UART_OutString("\r0%   0%   ");
      UART_OutUDec(ahead);
      UART_OutString(" RESTARTING");
      GPIO_PORTF_DATA_R |= 0x08;     // red and green LEDs on (appears yellow)
      for(i=0; i<25000000; i=i+1);   // several second delay before robot begins moving
      GPIO_PORTF_DATA_R &= ~0x0E;    // all LEDs off
      ReadADCMedianFilter(&ahead, &frwdright, &frwdleft);
      if(ahead < CRASH){
        LeftH = (LEFTMAXPCT + LEFTMINPCT)*400;
        LeftL = 80000 - LeftH;       // value modified my controller
        RightH = RIGHTCONSTPCT*800;  // constant
        RightL = 80000 - RightH;
        PWMStage = 1;                // start over at beginning stage of PWM
        NVIC_ST_CTRL_R |= 0x01;      // enable SysTick timer
        timeOutput = 0;
        pattern = LEDPATTERN;
      }
    }
  }
}
