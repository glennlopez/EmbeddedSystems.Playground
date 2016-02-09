// TExaS.c
// Runs on LM4F120/TM4C123
// Periodic timer interrupt data collection
// PLL must be on for ADC to work (turned on in startup)
// ADC1 PD3 Ain4 continuous sampling (turned on in startup)
//

// Uses Timer5A to trigger the DMA, read from a fixed port address, and then write to a 16-bit buffer
// There is a Timer5A interrupt after the buffer has been transferred.
// This example runs continuously, inputting to the buffer over and over.
// Jonathan Valvano. Daniel Valvano
// January 15, 2016

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015

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

#include "TExaS.h"

// Timer4A implements scope
// Timer5A periodic interrupt implements voltmeter
// ADC1 channel 4 PD3 continuously samples
#define LABNUM 15
void ADC1_Init(void);
unsigned long ADC1_In(void);
void PLL_Init(void);
void copy(char *destPt, char *sourcePt);
void SetCode(char code[]);
void SetCourse(char code[]);
void SetMode(char code[]);
void UART0_Init(void);
unsigned char UART0_InChar(void);
unsigned char UART0_InCharNonBlocking(void);
void UART0_OutChar(unsigned char data);
void UART0_OutCharNonBlock(unsigned char data);

/*
 * Viewer-Data in TExaS Grader 2.1 window
 */
typedef struct TExaS_data  {
  unsigned long Mode;         // 0 means idle, 1 means grading, 2 means done, 4 is error
  unsigned long long Course;  // 8-byte ASCII code "edX" or "EE319K"
  unsigned long Lab;
  unsigned long Grade;        // grade from 0 to 100
  unsigned long NumFromEdX;   // number from edX, set in DLL
  unsigned long long CopyThisToEdX;    // 8 byte ASCII code
  unsigned long ActionMsg;    // Action code
  unsigned long IntroMsg;     // start test message code
  unsigned long OKMsg;        // middle test message code
  unsigned long ErrMsg;       // end test message code
} TEXAS_DATA;
TEXAS_DATA TExaS; // in RAM, communication both directions on DLL
typedef struct portdata  {
  unsigned long InputPort;    // pointer to 40 byte character string
  unsigned long OutputPort;   // pointer to 40 byte character string
} PORT_DATA;
PORT_DATA TExaS_Ports;        // in RAM, set by user in DLL
enum DisplayType Display;// value is not relevant
const unsigned char NoInputMsg[40] = "There is no grader for Lab 15";
const unsigned char OutputPortMsg0[40] = "Simulated Nokia5110 on PA1-0";
const unsigned char OutputPortMsg1[40] = "Real Nokia5110 on PA7-2+Scope on PA1-0";
const unsigned char OutputPortMsg2[40] = "Real Nokia5110 on PA7-2";
const unsigned char OutputPortMsg3[40] = "No Nokia5110, no scope";//NoLCD_NoScope

typedef struct meterdata  {
  unsigned long Voltage;       // in mV
} METER_DATA;
METER_DATA TExaS_Meter; // in RAM, seen on DLL

// ****************messages*******************************
const unsigned char BlankMsg[40] = " ";
const unsigned char InitializedMsg[40] = "TExaS is initialized for Lab 15";
const unsigned char IntroMsg[40]       = "Grading is not implemented for this lab";
const unsigned char DoneMsg[40]        = "Done grading";
#define OUT(PORT,MSG) TExaS. ## PORT = (unsigned long) MSG
#define NONE 0xFFFFFFFF

unsigned long ADCnum;
unsigned long volatile TExaS_Period=80000;       // sampling period in bus cycles
unsigned long LastMode;  // start grading when Mode bit 0 goes from 0 to 1
long     bFlag;          // true at first interrupt of a test
unsigned long volatile Count; // goes from TimeCount to 0, how many interrupts to look
unsigned long volatile DelayBetweenTests;
unsigned long TExaS_Test;     // increments during grading
unsigned long ScopeMode;  // true if implementing scope
unsigned long ScopeCount; // one buffer is 512 points
#define SCOPESIZE 512
#define DELAYTIME 50

//*****************************************************************************
//
// I/O ports so students do not have to include port header file
//
//*****************************************************************************
#define SYSCTL_RCGC0_R          (*((volatile unsigned long *)0x400FE100))
#define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))
#define SYSCTL_RCGC1_SSI0       0x00000010  // SSI0 Clock Gating Control
#define SYSCTL_RCGC1_UART0      0x00000001  // UART0 Clock Gating Control
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // Port F Clock Gating Control
#define SYSCTL_RCGC2_GPIOA      0x00000001  // Port A Clock Gating Control
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_RCGCTIMER_R      (*((volatile unsigned long *)0x400FE604))
#define SYSCTL_RCGCADC_R        (*((volatile unsigned long *)0x400FE638))

#define NVIC_PRI17_R            (*((volatile unsigned long *)0xE000E444))
#define NVIC_PRI23_R            (*((volatile unsigned long *)0xE000E45C))
#define NVIC_EN2_R              (*((volatile unsigned long *)0xE000E108))
#define NVIC_DIS2_R             (*((volatile unsigned long *)0xE000E188))

#define TIMER4_CFG_R            (*((volatile unsigned long *)0x40034000))
#define TIMER4_TAMR_R           (*((volatile unsigned long *)0x40034004))
#define TIMER4_TBMR_R           (*((volatile unsigned long *)0x40034008))
#define TIMER4_CTL_R            (*((volatile unsigned long *)0x4003400C))
#define TIMER4_SYNC_R           (*((volatile unsigned long *)0x40034010))
#define TIMER4_IMR_R            (*((volatile unsigned long *)0x40034018))
#define TIMER4_RIS_R            (*((volatile unsigned long *)0x4003401C))
#define TIMER4_MIS_R            (*((volatile unsigned long *)0x40034020))
#define TIMER4_ICR_R            (*((volatile unsigned long *)0x40034024))
#define TIMER4_TAILR_R          (*((volatile unsigned long *)0x40034028))
#define TIMER4_TBILR_R          (*((volatile unsigned long *)0x4003402C))
#define TIMER4_TAMATCHR_R       (*((volatile unsigned long *)0x40034030))
#define TIMER4_TBMATCHR_R       (*((volatile unsigned long *)0x40034034))
#define TIMER4_TAPR_R           (*((volatile unsigned long *)0x40034038))
#define TIMER4_TBPR_R           (*((volatile unsigned long *)0x4003403C))
#define TIMER4_TAPMR_R          (*((volatile unsigned long *)0x40034040))
#define TIMER4_TBPMR_R          (*((volatile unsigned long *)0x40034044))
#define TIMER4_TAR_R            (*((volatile unsigned long *)0x40034048))
#define TIMER4_TBR_R            (*((volatile unsigned long *)0x4003404C))
#define TIMER4_TAV_R            (*((volatile unsigned long *)0x40034050))
#define TIMER4_TBV_R            (*((volatile unsigned long *)0x40034054))
#define TIMER4_RTCPD_R          (*((volatile unsigned long *)0x40034058))
#define TIMER4_TAPS_R           (*((volatile unsigned long *)0x4003405C))
#define TIMER4_TBPS_R           (*((volatile unsigned long *)0x40034060))
#define TIMER4_TAPV_R           (*((volatile unsigned long *)0x40034064))
#define TIMER4_TBPV_R           (*((volatile unsigned long *)0x40034068))
#define TIMER4_PP_R             (*((volatile unsigned long *)0x40034FC0))

#define TIMER5_CFG_R            (*((volatile unsigned long *)0x40035000))
#define TIMER5_TAMR_R           (*((volatile unsigned long *)0x40035004))
#define TIMER5_TBMR_R           (*((volatile unsigned long *)0x40035008))
#define TIMER5_CTL_R            (*((volatile unsigned long *)0x4003500C))
#define TIMER5_SYNC_R           (*((volatile unsigned long *)0x40035010))
#define TIMER5_IMR_R            (*((volatile unsigned long *)0x40035018))
#define TIMER5_RIS_R            (*((volatile unsigned long *)0x4003501C))
#define TIMER5_MIS_R            (*((volatile unsigned long *)0x40035020))
#define TIMER5_ICR_R            (*((volatile unsigned long *)0x40035024))
#define TIMER5_TAILR_R          (*((volatile unsigned long *)0x40035028))
#define TIMER5_TBILR_R          (*((volatile unsigned long *)0x4003502C))
#define TIMER5_TAMATCHR_R       (*((volatile unsigned long *)0x40035030))
#define TIMER5_TBMATCHR_R       (*((volatile unsigned long *)0x40035034))
#define TIMER5_TAPR_R           (*((volatile unsigned long *)0x40035038))
#define TIMER5_TBPR_R           (*((volatile unsigned long *)0x4003503C))
#define TIMER5_TAPMR_R          (*((volatile unsigned long *)0x40035040))
#define TIMER5_TBPMR_R          (*((volatile unsigned long *)0x40035044))
#define TIMER5_TAR_R            (*((volatile unsigned long *)0x40035048))
#define TIMER5_TBR_R            (*((volatile unsigned long *)0x4003504C))
#define TIMER5_TAV_R            (*((volatile unsigned long *)0x40035050))
#define TIMER5_TBV_R            (*((volatile unsigned long *)0x40035054))
#define TIMER5_RTCPD_R          (*((volatile unsigned long *)0x40035058))
#define TIMER5_TAPS_R           (*((volatile unsigned long *)0x4003505C))
#define TIMER5_TBPS_R           (*((volatile unsigned long *)0x40035060))
#define TIMER5_TAPV_R           (*((volatile unsigned long *)0x40035064))
#define TIMER5_TBPV_R           (*((volatile unsigned long *)0x40035068))
#define TIMER5_PP_R             (*((volatile unsigned long *)0x40035FC0))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define PD2                     (*((volatile unsigned long *)0x40007010))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_IS_R         (*((volatile unsigned long *)0x40007404))
#define GPIO_PORTD_IBE_R        (*((volatile unsigned long *)0x40007408))
#define GPIO_PORTD_IEV_R        (*((volatile unsigned long *)0x4000740C))
#define GPIO_PORTD_IM_R         (*((volatile unsigned long *)0x40007410))
#define GPIO_PORTD_RIS_R        (*((volatile unsigned long *)0x40007414))
#define GPIO_PORTD_MIS_R        (*((volatile unsigned long *)0x40007418))
#define GPIO_PORTD_ICR_R        (*((volatile unsigned long *)0x4000741C))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_DR2R_R       (*((volatile unsigned long *)0x40007500))
#define GPIO_PORTD_DR4R_R       (*((volatile unsigned long *)0x40007504))
#define GPIO_PORTD_DR8R_R       (*((volatile unsigned long *)0x40007508))
#define GPIO_PORTD_ODR_R        (*((volatile unsigned long *)0x4000750C))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_PDR_R        (*((volatile unsigned long *)0x40007514))
#define GPIO_PORTD_SLR_R        (*((volatile unsigned long *)0x40007518))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))
#define GPIO_PORTD_ADCCTL_R     (*((volatile unsigned long *)0x40007530))
#define GPIO_PORTD_DMACTL_R     (*((volatile unsigned long *)0x40007534))
#define GPIO_PORTD_SI_R         (*((volatile unsigned long *)0x40007538))
#define ADC1_ACTSS_R            (*((volatile unsigned long *)0x40039000))
#define ADC1_RIS_R              (*((volatile unsigned long *)0x40039004))
#define ADC1_IM_R               (*((volatile unsigned long *)0x40039008))
#define ADC1_ISC_R              (*((volatile unsigned long *)0x4003900C))
#define ADC1_OSTAT_R            (*((volatile unsigned long *)0x40039010))
#define ADC1_EMUX_R             (*((volatile unsigned long *)0x40039014))
#define ADC1_USTAT_R            (*((volatile unsigned long *)0x40039018))
#define ADC1_SSPRI_R            (*((volatile unsigned long *)0x40039020))
#define ADC1_SPC_R              (*((volatile unsigned long *)0x40039024))
#define ADC1_PSSI_R             (*((volatile unsigned long *)0x40039028))
#define ADC1_SAC_R              (*((volatile unsigned long *)0x40039030))
#define ADC1_DCISC_R            (*((volatile unsigned long *)0x40039034))
#define ADC1_SSMUX0_R           (*((volatile unsigned long *)0x40039040))
#define ADC1_SSCTL0_R           (*((volatile unsigned long *)0x40039044))
#define ADC1_SSFIFO0_R          (*((volatile unsigned long *)0x40039048))
#define ADC1_SSFSTAT0_R         (*((volatile unsigned long *)0x4003904C))
#define ADC1_SSOP0_R            (*((volatile unsigned long *)0x40039050))
#define ADC1_SSDC0_R            (*((volatile unsigned long *)0x40039054))
#define ADC1_SSMUX1_R           (*((volatile unsigned long *)0x40039060))
#define ADC1_SSCTL1_R           (*((volatile unsigned long *)0x40039064))
#define ADC1_SSFIFO1_R          (*((volatile unsigned long *)0x40039068))
#define ADC1_SSFSTAT1_R         (*((volatile unsigned long *)0x4003906C))
#define ADC1_SSOP1_R            (*((volatile unsigned long *)0x40039070))
#define ADC1_SSDC1_R            (*((volatile unsigned long *)0x40039074))
#define ADC1_SSMUX2_R           (*((volatile unsigned long *)0x40039080))
#define ADC1_SSCTL2_R           (*((volatile unsigned long *)0x40039084))
#define ADC1_SSFIFO2_R          (*((volatile unsigned long *)0x40039088))
#define ADC1_SSFSTAT2_R         (*((volatile unsigned long *)0x4003908C))
#define ADC1_SSOP2_R            (*((volatile unsigned long *)0x40039090))
#define ADC1_SSDC2_R            (*((volatile unsigned long *)0x40039094))
#define ADC1_SSMUX3_R           (*((volatile unsigned long *)0x400390A0))
#define ADC1_SSCTL3_R           (*((volatile unsigned long *)0x400390A4))
#define ADC1_SSFIFO3_R          (*((volatile unsigned long *)0x400390A8))
#define ADC1_SSFSTAT3_R         (*((volatile unsigned long *)0x400390AC))
#define ADC_SSFSTAT3_EMPTY      0x00000100  // FIFO Empty
#define ADC1_PP_R               (*((volatile unsigned long *)0x40039FC0))
#define ADC1_PC_R               (*((volatile unsigned long *)0x40039FC4))
#define ADC1_CC_R               (*((volatile unsigned long *)0x40039FC8))

// ************TExaS_Init*****************
// Initialize grader, voltmeter on timer 5A 10 ms, scope on timer4A 100us
// sets PLL to 80 MHz
// This needs to be called once
// Inputs: display system used to output the results
// Outputs: none
void TExaS_Init(enum DisplayType display){volatile unsigned long delay;
  PLL_Init();     // ADC needs PLL on to run, 80 MHz
  SYSCTL_RCGCTIMER_R |= 0x20;      // 0) activate timer5
  SetCourse("UT.6.03x");
  OUT(ActionMsg,IntroMsg);
  OUT(IntroMsg,BlankMsg);
  OUT(OKMsg,BlankMsg);
  OUT(ErrMsg,BlankMsg);
  LastMode = 0;
  TExaS.Mode = 0; // bit 0 set by user in DLL window
  TExaS_Test = 0; // goes from 0 to NUMTESTS-1
  DelayBetweenTests = 0; // 0 means no sleeping
  ADCnum = 0;     // index into oscilloscope buffer
  bFlag = 0;      // true at first interrupt of a test
  TExaS_Period = 800000;  // 10ms
  TExaS.Lab = LABNUM;     // fixed
  TExaS.Grade = 0;
  TExaS_Meter.Voltage = 0;
  Display = display;
  ScopeMode = 0;
  ScopeCount = 0;
  TExaS_Ports.InputPort = (unsigned long) NoInputMsg;  // no grader
  if(Display == UART0_Emulate_Nokia5110_NoScope){
    TExaS_Ports.OutputPort = (unsigned long) OutputPortMsg0;
    UART0_Init();                    // UART0 is connected to TExaSdisplay
  }else if(Display == SSI0_Real_Nokia5110_Scope){
    TExaS_Ports.OutputPort = (unsigned long) OutputPortMsg1;
    ScopeMode = 1;
    SYSCTL_RCGCTIMER_R |= 0x10;      // 0) activate timer4
    UART0_Init();                    // UART0 is connected to TExaSdisplay
    TIMER4_CTL_R = 0x00000000;       // 1) disable timer4A during setup
    TIMER4_CFG_R = 0x00000000;       // 2) configure for 32-bit mode
    TIMER4_TAMR_R = 0x00000002;      // 3) configure for periodic mode, default down-count settings
    TIMER4_TAILR_R = 7999;           // 4) 100us reload value
    TIMER4_TAPR_R = 0;               // 5) bus clock resolution
    TIMER4_ICR_R = 0x00000001;       // 6) clear timer5A timeout flag
    TIMER4_IMR_R = 0x00000001;       // 7) arm timeout interrupt
    NVIC_PRI17_R = (NVIC_PRI17_R&0xFF00FFFF)|0x00E00000; // 8) priority 7
// interrupts enabled in the main program after all devices initialized
// vector number 86, interrupt number 70
    NVIC_EN2_R = 0x00000040;         // 9) enable interrupt 70 in NVIC
    TIMER4_CTL_R = 0x00000001;       // 10) enable timer4A
  }else if(Display == SSI0_Real_Nokia5110_NoScope){
    TExaS_Ports.OutputPort = (unsigned long) OutputPortMsg2;
  }else{
    TExaS_Ports.OutputPort = (unsigned long) OutputPortMsg3;
  }
    
  SetCode("        ");

  TIMER5_CTL_R = 0x00000000;       // 1) disable timer5A during setup
  TIMER5_CFG_R = 0x00000000;       // 2) configure for 32-bit mode
  TIMER5_TAMR_R = 0x00000002;      // 3) configure for periodic mode, default down-count settings
  TIMER5_TAILR_R = TExaS_Period-1; // 4) reload value
  TIMER5_TAPR_R = 0;               // 5) bus clock resolution
  TIMER5_ICR_R = 0x00000001;       // 6) clear timer5A timeout flag
  TIMER5_IMR_R = 0x00000001;       // 7) arm timeout interrupt
  NVIC_PRI23_R = (NVIC_PRI23_R&0xFFFFFF00)|0x00000040; // 8) priority 2
// interrupts enabled in the main program after all devices initialized
// vector number 108, interrupt number 92
  NVIC_EN2_R = 0x10000000;         // 9) enable interrupt 92 in NVIC
  TIMER5_CTL_R = 0x00000001;       // 10) enable timer5A

  ADC1_Init();     // called after PLL on
  OUT(IntroMsg,InitializedMsg);
}

void StopTimer4(void){
  NVIC_DIS2_R = 0x00000040;        // 9) enable interrupt 70 in NVIC
  TIMER4_CTL_R = 0x00000000;       // 10) enable timer4A
}
void StartTimer4(void){
  ScopeCount = SCOPESIZE;
  NVIC_EN2_R = 0x00000040;         // 9) enable interrupt 70 in NVIC
  TIMER4_CTL_R = 0x00000001;       // 10) enable timer4A
}
#define UART0_DR_R              (*((volatile unsigned long *)0x4000C000))
// this ISR implements the scope, 12bit ADC scaled to 8 bits and sent
void Timer4A_Handler(void){
  TIMER4_ICR_R = 0x00000001;        // acknowledge timer4A timeout
  UART0_DR_R = (ADC1_SSFIFO3_R>>4); // send ADC to TExaSdisplay
}

// grading occurs in the background
void Timer5A_Handler(void){
  TIMER5_TAILR_R = TExaS_Period-1;   // allow for variable rate
  TIMER5_ICR_R = 0x00000001;         // acknowledge timer5A timeout
  TExaS_Meter.Voltage = (3300*ADC1_In())>>12; // implements voltmeter
}

// ************TExaS_Stop*****************
// Stop the transfer
// Inputs:  none
// Outputs: none
void TExaS_Stop(void){
  NVIC_DIS2_R = 0x10000000;       // 9) disable interrupt 92 in NVIC
  TIMER5_CTL_R = 0x00000000;      // 10) disable timer5A
}
// start conversions, sample always
// ADC1
// PD3 Ain4
// 16-point averaging 125kHz sampling
void ADC1_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x08;         // 1) activate clock for Port D
//  SYSCTL_RCGCGPIO_R |= 0x08;      // 1) activate clock for Port D
  delay = SYSCTL_RCGC2_R;         //    allow time for clock to stabilize
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTD_DIR_R &= ~0x08;      // 2) make PD3 input
  GPIO_PORTD_AFSEL_R |= 0x08;     // 3) enable alternate function on PD3
  GPIO_PORTD_DEN_R &= ~0x08;      // 4) disable digital I/O on PD3
  GPIO_PORTD_AMSEL_R |= 0x08;     // 5) enable analog functionality on PD3
  SYSCTL_RCGC0_R |= 0x00020000;   // 6) activate ADC1 (legacy code)
//  SYSCTL_RCGCADC_R |= 0x02;
  for(delay = 0; delay<20; delay++){};  // allow time for clock to stabilize
//  SYSCTL_RCGC0_R &= ~0x00000C00;  // 7) configure for 125K (legacy code)
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

//------------ADC1_In------------
// Analog to digital conversion.
// Input: none
// Output: 12-bit result of ADC conversion
unsigned long ADC1_In(void){
  return ADC1_SSFIFO3_R;
}

void copy(char *destPt, char *sourcePt){ unsigned char data;
  do{
    data = *sourcePt; sourcePt++;
    *destPt = data; destPt++;
  }while(data);
}
void SetCode(char code[]){ int i;
  char *pt;
  pt = (char *) &TExaS.CopyThisToEdX;
  for(i=0; i<8; i++){
    pt[i] = code[i];
  }
}
void SetCourse(char code[]){ int i;
  char *pt;
  pt = (char *) &TExaS.Course;
  for(i=0; i<8; i++){
    pt[i] = code[i];
  }
}
void SetMode(char code[]){ int i;
  char *pt;
  pt = (char *) &TExaS.Mode;
  for(i=0; i<8; i++){
    pt[i] = code[i];
  }
}

// The #define statement SYSDIV2 in PLL.h
// initializes the PLL to the desired frequency.

// bus frequency is 400MHz/(SYSDIV2+1) = 400MHz/(4+1) = 80 MHz
// see the table at the end of this file

#define SYSCTL_RIS_R            (*((volatile unsigned long *)0x400FE050))
#define SYSCTL_RIS_PLLLRIS      0x00000040  // PLL Lock Raw Interrupt Status
#define SYSCTL_RCC_R            (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC_XTAL_M       0x000007C0  // Crystal Value
#define SYSCTL_RCC_XTAL_6MHZ    0x000002C0  // 6 MHz Crystal
#define SYSCTL_RCC_XTAL_8MHZ    0x00000380  // 8 MHz Crystal
#define SYSCTL_RCC_XTAL_16MHZ   0x00000540  // 16 MHz Crystal
#define SYSCTL_RCC2_R           (*((volatile unsigned long *)0x400FE070))
#define SYSCTL_RCC2_USERCC2     0x80000000  // Use RCC2
#define SYSCTL_RCC2_DIV400      0x40000000  // Divide PLL as 400 MHz vs. 200
                                            // MHz
#define SYSCTL_RCC2_SYSDIV2_M   0x1F800000  // System Clock Divisor 2
#define SYSCTL_RCC2_SYSDIV2LSB  0x00400000  // Additional LSB for SYSDIV2
#define SYSCTL_RCC2_PWRDN2      0x00002000  // Power-Down PLL 2
#define SYSCTL_RCC2_BYPASS2     0x00000800  // PLL Bypass 2
#define SYSCTL_RCC2_OSCSRC2_M   0x00000070  // Oscillator Source 2
#define SYSCTL_RCC2_OSCSRC2_MO  0x00000000  // MOSC
// The #define statement SYSDIV2 initializes
// the PLL to the desired frequency.
#define SYSDIV2 4
// bus frequency is 400MHz/(SYSDIV2+1) = 400MHz/(4+1) = 80 MHz

// configure the system to get its clock from the PLL
void PLL_Init(void){
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
                  + (SYSDIV2<<22);      // configure for 80 MHz clock
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}

#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define UART0_FR_R              (*((volatile unsigned long *)0x4000C018))
#define UART0_IBRD_R            (*((volatile unsigned long *)0x4000C024))
#define UART0_FBRD_R            (*((volatile unsigned long *)0x4000C028))
#define UART0_LCRH_R            (*((volatile unsigned long *)0x4000C02C))
#define UART0_CTL_R             (*((volatile unsigned long *)0x4000C030))
#define UART0_CC_R              (*((volatile unsigned long *)0x4000CFC8))
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable
#define UART_CC_CS_M            0x0000000F  // UART Baud Clock Source
#define UART_CC_CS_SYSCLK       0x00000000  // The system clock (default)
#define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC1_UART0      0x00000001  // UART0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOA      0x00000001  // port A Clock Gating Control
#define SYSCTL_PRGPIO_R         (*((volatile unsigned long *)0x400FEA08))
#define SYSCTL_PRUART_R         (*((volatile unsigned long *)0x400FEA18))
#define SYSCTL_PRGPIO_R0        0x00000001  // GPIO Port A Peripheral Ready
#define SYSCTL_PRUART_R0        0x00000001  // UART Module 0 Peripheral Ready
//------------UART0_Init------------
// Initialize the UART for 115,200 baud rate (assuming 80 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART0_Init(void){volatile unsigned long delay;
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
                                        // wait for clock to stabilize
//  while((SYSCTL_PRUART_R&SYSCTL_PRUART_R0) == 0){};
  delay =SYSCTL_RCGC2_R;
  delay =SYSCTL_RCGC2_R;
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
  UART0_FBRD_R = 26;                    // FBRD = round(0.402778 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CC_R &= ~UART_CC_CS_M;          // clear baud clock control field
  UART0_CC_R |= UART_CC_CS_SYSCLK;      // configure for system clock
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
//  while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R0) == 0){};
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}

//------------UART0_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
unsigned char UART0_InChar(void){
  while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART0_DR_R&0xFF));
}
//------------UART0_InCharNonBlocking------------
// look for new serial port input
// Input: none
// Output: ASCII code for key typed
//         0 if no key ready
unsigned char UART0_InCharNonBlocking(void){
  if((UART0_FR_R&UART_FR_RXFE) == 0){
    return((unsigned char)(UART0_DR_R&0xFF));
  }
  return 0;
}
//------------UART0_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART0_OutChar(unsigned char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}
//------------UART0_OutCharNonBlock------------
// Output 8-bit to serial port, do not wait
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART0_OutCharNonBlock(unsigned char data){
  UART0_DR_R = data;
}

