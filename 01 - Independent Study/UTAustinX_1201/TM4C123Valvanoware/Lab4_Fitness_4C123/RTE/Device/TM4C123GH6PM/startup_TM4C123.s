;/**************************************************************************//**
; * @file     startup_TM4C123.s
; * @brief    CMSIS Cortex-M4 Core Device Startup File for
; *           TI Tiva TM4C123 Blizzard Class Device
; * @version  V1.00
; * @date     15. May 2013
; *
; * @note
; * Copyright (C) 2011 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/
; Edited to conform with ISR names as described in 
;   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
;   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2016
;   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
;   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016
;   "Embedded Systems: Real-Time Operating Systems for ARM Cortex M Microcontrollers",
;   ISBN: 978-1466468863, Jonathan Valvano, copyright (c) 2016

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts

                DCD     GPIOPortA_Handler         ;   0: GPIO Port A
                DCD     GPIOPortB_Handler         ;   1: GPIO Port B
                DCD     GPIOPortC_Handler         ;   2: GPIO Port C
                DCD     GPIOPortD_Handler         ;   3: GPIO Port D
                DCD     GPIOPortE_Handler         ;   4: GPIO Port E
                DCD     UART0_Handler             ;   5: UART0 Rx and Tx
                DCD     UART1_Handler             ;   6: UART1 Rx and Tx
                DCD     SSI0_Handler              ;   7: SSI0 Rx and Tx
                DCD     I2C0_Handler              ;   8: I2C0 Master and Slave
                DCD     PMW0_FAULT_Handler        ;   9: PWM Fault
                DCD     PWM0Generator0_Handler    ;  10: PWM Generator 0
                DCD     PWM0Generator1_Handler    ;  11: PWM Generator 1
                DCD     PWM0Generator2_Handler    ;  12: PWM Generator 2
                DCD     Quadrature0_Handler       ;  13: Quadrature Encoder 0
                DCD     ADC0Seq0_Handler          ;  14: ADC Sequence 0
                DCD     ADC0Seq1_Handler          ;  15: ADC Sequence 1
                DCD     ADC0Seq2_Handler          ;  16: ADC Sequence 2
                DCD     ADC0Seq3_Handler          ;  17: ADC Sequence 3
                DCD     WDT_Handler               ;  18: Watchdog timer
                DCD     TIMER0A_Handler           ;  19: Timer 0 subtimer A
                DCD     TIMER0B_Handler           ;  20: Timer 0 subtimer B
                DCD     TIMER1A_Handler           ;  21: Timer 1 subtimer A
                DCD     TIMER1B_Handler           ;  22: Timer 1 subtimer B
                DCD     TIMER2A_Handler           ;  23: Timer 2 subtimer A
                DCD     TIMER2B_Handler           ;  24: Timer 2 subtimer B
                DCD     COMP0_Handler             ;  25: Analog Comparator 0
                DCD     COMP1_Handler             ;  26: Analog Comparator 1
                DCD     COMP2_Handler             ;  27: Analog Comparator 2
                DCD     SYSCTL_Handler            ;  28: System Control (PLL, OSC, BO)
                DCD     FlashCtl_Handler          ;  29: FLASH Control
                DCD     GPIOPortF_Handler         ;  30: GPIO Port F
                DCD     GPIOPortG_Handler         ;  31: GPIO Port G
                DCD     GPIOPortH_Handler         ;  32: GPIO Port H
                DCD     UART2_Handler             ;  33: UART2 Rx and Tx
                DCD     SSI1_Handler              ;  34: SSI1 Rx and Tx
                DCD     TIMER3A_Handler           ;  35: Timer 3 subtimer A
                DCD     TIMER3B_Handler           ;  36: Timer 3 subtimer B
                DCD     I2C1_Handler              ;  37: I2C1 Master and Slave
                DCD     Quadrature1_Handler       ;  38: Quadrature Encoder 1
                DCD     CAN0_Handler              ;  39: CAN0
                DCD     CAN1_Handler              ;  40: CAN1
                DCD     CAN2_Handler              ;  41: CAN2
                DCD     0                         ;  42: Reserved
                DCD     Hibernate_Handler         ;  43: Hibernate
                DCD     USB0_Handler              ;  44: USB0
                DCD     PWM0Generator3_Handler    ;  45: PWM Generator 3
                DCD     UDMA_Handler              ;  46: uDMA Software Transfer
                DCD     UDMAERR_Handler           ;  47: uDMA Error
                DCD     ADC1Seq0_Handler          ;  48: ADC1 Sequence 0
                DCD     ADC1Seq1_Handler          ;  49: ADC1 Sequence 1
                DCD     ADC1Seq2_Handler          ;  50: ADC1 Sequence 2
                DCD     ADC1Seq3_Handler          ;  51: ADC1 Sequence 3
                DCD     0                         ;  52: Reserved
                DCD     0                         ;  53: Reserved
                DCD     GPIOPortJ_Handler         ;  54: GPIO Port J
                DCD     GPIOPortK_Handler         ;  55: GPIO Port K
                DCD     GPIOPortL_Handler         ;  56: GPIO Port L
                DCD     SSI2_Handler              ;  57: SSI2 Rx and Tx
                DCD     SSI3_Handler              ;  58: SSI3 Rx and Tx
                DCD     UART3_Handler             ;  59: UART3 Rx and Tx
                DCD     UART4_Handler             ;  60: UART4 Rx and Tx
                DCD     UART5_Handler             ;  61: UART5 Rx and Tx
                DCD     UART6_Handler             ;  62: UART6 Rx and Tx
                DCD     UART7_Handler             ;  63: UART7 Rx and Tx
                DCD     0                         ;  64: Reserved
                DCD     0                         ;  65: Reserved
                DCD     0                         ;  66: Reserved
                DCD     0                         ;  67: Reserved
                DCD     I2C2_Handler              ;  68: I2C2 Master and Slave
                DCD     I2C3_Handler              ;  69: I2C3 Master and Slave
                DCD     TIMER4A_Handler           ;  70: Timer 4 subtimer A
                DCD     TIMER4B_Handler           ;  71: Timer 4 subtimer B
                DCD     0                         ;  72: Reserved
                DCD     0                         ;  73: Reserved
                DCD     0                         ;  74: Reserved
                DCD     0                         ;  75: Reserved
                DCD     0                         ;  76: Reserved
                DCD     0                         ;  77: Reserved
                DCD     0                         ;  78: Reserved
                DCD     0                         ;  79: Reserved
                DCD     0                         ;  80: Reserved
                DCD     0                         ;  81: Reserved
                DCD     0                         ;  82: Reserved
                DCD     0                         ;  83: Reserved
                DCD     0                         ;  84: Reserved
                DCD     0                         ;  85: Reserved
                DCD     0                         ;  86: Reserved
                DCD     0                         ;  87: Reserved
                DCD     0                         ;  88: Reserved
                DCD     0                         ;  89: Reserved
                DCD     0                         ;  90: Reserved
                DCD     0                         ;  91: Reserved
                DCD     TIMER5A_Handler           ;  92: Timer 5 subtimer A
                DCD     TIMER5B_Handler           ;  93: Timer 5 subtimer B
                DCD     WideTimer0A_Handler       ;  94: Wide Timer 0 subtimer A
                DCD     WideTimer0B_Handler       ;  95: Wide Timer 0 subtimer B
                DCD     WideTimer1A_Handler       ;  96: Wide Timer 1 subtimer A
                DCD     WideTimer1B_Handler       ;  97: Wide Timer 1 subtimer B
                DCD     WideTimer2A_Handler       ;  98: Wide Timer 2 subtimer A
                DCD     WideTimer2B_Handler       ;  99: Wide Timer 2 subtimer B
                DCD     WideTimer3A_Handler       ; 100: Wide Timer 3 subtimer A
                DCD     WideTimer3B_Handler       ; 101: Wide Timer 3 subtimer B
                DCD     WideTimer4A_Handler       ; 102: Wide Timer 4 subtimer A
                DCD     WideTimer4B_Handler       ; 103: Wide Timer 4 subtimer B
                DCD     WideTimer5A_Handler       ; 104: Wide Timer 5 subtimer A
                DCD     WideTimer5B_Handler       ; 105: Wide Timer 5 subtimer B
                DCD     FPU_Handler               ; 106: FPU
                DCD     0                         ; 107: Reserved
                DCD     0                         ; 108: Reserved
                DCD     I2C4_Handler              ; 109: I2C4 Master and Slave
                DCD     I2C5_Handler              ; 110: I2C5 Master and Slave
                DCD     GPIOPortM_Handler         ; 111: GPIO Port M
                DCD     GPIOPortN_Handler         ; 112: GPIO Port N
                DCD     QEI2_Handler              ; 113: Quadrature Encoder 2
                DCD     0                         ; 114: Reserved
                DCD     0                         ; 115: Reserved
                DCD     GPIOPortP0_Handler        ; 116: GPIO Port P (Summary or P0)
                DCD     GPIOPortP1_Handler        ; 117: GPIO Port P1
                DCD     GPIOPortP2_Handler        ; 118: GPIO Port P2
                DCD     GPIOPortP3_Handler        ; 119: GPIO Port P3
                DCD     GPIOPortP4_Handler        ; 120: GPIO Port P4
                DCD     GPIOPortP5_Handler        ; 121: GPIO Port P5
                DCD     GPIOPortP6_Handler        ; 122: GPIO Port P6
                DCD     GPIOPortP7_Handler        ; 123: GPIO Port P7
                DCD     GPIOPortQ0_Handler        ; 124: GPIO Port Q (Summary or Q0)
                DCD     GPIOPortQ1_Handler        ; 125: GPIO Port Q1
                DCD     GPIOPortQ2_Handler        ; 126: GPIO Port Q2
                DCD     GPIOPortQ3_Handler        ; 127: GPIO Port Q3
                DCD     GPIOPortQ4_Handler        ; 128: GPIO Port Q4
                DCD     GPIOPortQ5_Handler        ; 129: GPIO Port Q5
                DCD     GPIOPortQ6_Handler        ; 130: GPIO Port Q6
                DCD     GPIOPortQ7_Handler        ; 131: GPIO Port Q7
                DCD     GPIOPortR_Handler         ; 132: GPIO Port R
                DCD     GPIOPortS_Handler         ; 133: GPIO Port S
                DCD     PWM1Generator0_Handler    ; 134: PWM 1 Generator 0
                DCD     PWM1Generator1_Handler    ; 135: PWM 1 Generator 1
                DCD     PWM1Generator2_Handler    ; 136: PWM 1 Generator 2
                DCD     PWM1Generator3_Handler    ; 137: PWM 1 Generator 3
                DCD     PWM1Fault_Handler         ; 138: PWM 1 Fault

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
;                IMPORT  SystemInit
                IMPORT  __main
;                LDR     R0, =SystemInit
;                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

GPIOPortA_Handler\
                PROC
                EXPORT  GPIOPortA_Handler [WEAK]
                B       .
                ENDP

GPIOPortB_Handler\
                PROC
                EXPORT  GPIOPortB_Handler [WEAK]
                B       .
                ENDP

GPIOPortC_Handler\
                PROC
                EXPORT  GPIOPortC_Handler [WEAK]
                B       .
                ENDP

GPIOPortD_Handler\
                PROC
                EXPORT  GPIOPortD_Handler [WEAK]
                B       .
                ENDP

GPIOPortE_Handler\
                PROC
                EXPORT  GPIOPortE_Handler [WEAK]
                B       .
                ENDP

UART0_Handler\
                PROC
                EXPORT  UART0_Handler [WEAK]
                B       .
                ENDP

UART1_Handler\
                PROC
                EXPORT  UART1_Handler [WEAK]
                B       .
                ENDP

SSI0_Handler\
                PROC
                EXPORT  SSI0_Handler [WEAK]
                B       .
                ENDP

I2C0_Handler\
                PROC
                EXPORT  I2C0_Handler [WEAK]
                B       .
                ENDP

PMW0_FAULT_Handler\
                PROC
                EXPORT  PMW0_FAULT_Handler [WEAK]
                B       .
                ENDP

PWM0Generator0_Handler\
                PROC
                EXPORT  PWM0Generator0_Handler [WEAK]
                B       .
                ENDP

PWM0Generator1_Handler\
                PROC
                EXPORT  PWM0Generator1_Handler [WEAK]
                B       .
                ENDP

PWM0Generator2_Handler\
                PROC
                EXPORT  PWM0Generator2_Handler [WEAK]
                B       .
                ENDP

Quadrature0_Handler\
                PROC
                EXPORT  Quadrature0_Handler [WEAK]
                B       .
                ENDP

ADC0Seq0_Handler\
                PROC
                EXPORT  ADC0Seq0_Handler [WEAK]
                B       .
                ENDP

ADC0Seq1_Handler\
                PROC
                EXPORT  ADC0Seq1_Handler [WEAK]
                B       .
                ENDP

ADC0Seq2_Handler\
                PROC
                EXPORT  ADC0Seq2_Handler [WEAK]
                B       .
                ENDP

ADC0Seq3_Handler\
                PROC
                EXPORT  ADC0Seq3_Handler [WEAK]
                B       .
                ENDP

WDT_Handler\
                PROC
                EXPORT  WDT_Handler [WEAK]
                B       .
                ENDP

TIMER0A_Handler\
                PROC
                EXPORT  TIMER0A_Handler [WEAK]
                B       .
                ENDP

TIMER0B_Handler\
                PROC
                EXPORT  TIMER0B_Handler [WEAK]
                B       .
                ENDP

TIMER1A_Handler\
                PROC
                EXPORT  TIMER1A_Handler [WEAK]
                B       .
                ENDP

TIMER1B_Handler\
                PROC
                EXPORT  TIMER1B_Handler [WEAK]
                B       .
                ENDP

TIMER2A_Handler\
                PROC
                EXPORT  TIMER2A_Handler [WEAK]
                B       .
                ENDP

TIMER2B_Handler\
                PROC
                EXPORT  TIMER2B_Handler [WEAK]
                B       .
                ENDP

COMP0_Handler\
                PROC
                EXPORT  COMP0_Handler [WEAK]
                B       .
                ENDP

COMP1_Handler\
                PROC
                EXPORT  COMP1_Handler [WEAK]
                B       .
                ENDP

COMP2_Handler\
                PROC
                EXPORT  COMP2_Handler [WEAK]
                B       .
                ENDP

SYSCTL_Handler\
                PROC
                EXPORT  SYSCTL_Handler [WEAK]
                B       .
                ENDP

FlashCtl_Handler\
                PROC
                EXPORT  FlashCtl_Handler [WEAK]
                B       .
                ENDP

GPIOPortF_Handler\
                PROC
                EXPORT  GPIOPortF_Handler [WEAK]
                B       .
                ENDP

GPIOPortG_Handler\
                PROC
                EXPORT  GPIOPortG_Handler [WEAK]
                B       .
                ENDP

GPIOPortH_Handler\
                PROC
                EXPORT  GPIOPortH_Handler [WEAK]
                B       .
                ENDP

UART2_Handler\
                PROC
                EXPORT  UART2_Handler [WEAK]
                B       .
                ENDP

SSI1_Handler\
                PROC
                EXPORT  SSI1_Handler [WEAK]
                B       .
                ENDP

TIMER3A_Handler\
                PROC
                EXPORT  TIMER3A_Handler [WEAK]
                B       .
                ENDP

TIMER3B_Handler\
                PROC
                EXPORT  TIMER3B_Handler [WEAK]
                B       .
                ENDP

I2C1_Handler\
                PROC
                EXPORT  I2C1_Handler [WEAK]
                B       .
                ENDP

Quadrature1_Handler\
                PROC
                EXPORT  Quadrature1_Handler [WEAK]
                B       .
                ENDP

CAN0_Handler\
                PROC
                EXPORT  CAN0_Handler [WEAK]
                B       .
                ENDP

CAN1_Handler\
                PROC
                EXPORT  CAN1_Handler [WEAK]
                B       .
                ENDP

CAN2_Handler\
                PROC
                EXPORT  CAN2_Handler [WEAK]
                B       .
                ENDP

Hibernate_Handler\
                PROC
                EXPORT  Hibernate_Handler [WEAK]
                B       .
                ENDP

USB0_Handler\
                PROC
                EXPORT  USB0_Handler [WEAK]
                B       .
                ENDP

PWM0Generator3_Handler\
                PROC
                EXPORT  PWM0Generator3_Handler [WEAK]
                B       .
                ENDP

UDMA_Handler\
                PROC
                EXPORT  UDMA_Handler [WEAK]
                B       .
                ENDP

UDMAERR_Handler\
                PROC
                EXPORT  UDMAERR_Handler [WEAK]
                B       .
                ENDP

ADC1Seq0_Handler\
                PROC
                EXPORT  ADC1Seq0_Handler [WEAK]
                B       .
                ENDP

ADC1Seq1_Handler\
                PROC
                EXPORT  ADC1Seq1_Handler [WEAK]
                B       .
                ENDP

ADC1Seq2_Handler\
                PROC
                EXPORT  ADC1Seq2_Handler [WEAK]
                B       .
                ENDP

ADC1Seq3_Handler\
                PROC
                EXPORT  ADC1Seq3_Handler [WEAK]
                B       .
                ENDP

GPIOPortJ_Handler\
                PROC
                EXPORT  GPIOPortJ_Handler [WEAK]
                B       .
                ENDP

GPIOPortK_Handler\
                PROC
                EXPORT  GPIOPortK_Handler [WEAK]
                B       .
                ENDP

GPIOPortL_Handler\
                PROC
                EXPORT  GPIOPortL_Handler [WEAK]
                B       .
                ENDP

SSI2_Handler\
                PROC
                EXPORT  SSI2_Handler [WEAK]
                B       .
                ENDP

SSI3_Handler\
                PROC
                EXPORT  SSI3_Handler [WEAK]
                B       .
                ENDP

UART3_Handler\
                PROC
                EXPORT  UART3_Handler [WEAK]
                B       .
                ENDP

UART4_Handler\
                PROC
                EXPORT  UART4_Handler [WEAK]
                B       .
                ENDP

UART5_Handler\
                PROC
                EXPORT  UART5_Handler [WEAK]
                B       .
                ENDP

UART6_Handler\
                PROC
                EXPORT  UART6_Handler [WEAK]
                B       .
                ENDP

UART7_Handler\
                PROC
                EXPORT  UART7_Handler [WEAK]
                B       .
                ENDP

I2C2_Handler\
                PROC
                EXPORT  I2C2_Handler [WEAK]
                B       .
                ENDP

I2C3_Handler\
                PROC
                EXPORT  I2C3_Handler [WEAK]
                B       .
                ENDP

TIMER4A_Handler\
                PROC
                EXPORT  TIMER4A_Handler [WEAK]
                B       .
                ENDP

TIMER4B_Handler\
                PROC
                EXPORT  TIMER4B_Handler [WEAK]
                B       .
                ENDP

TIMER5A_Handler\
                PROC
                EXPORT  TIMER5A_Handler [WEAK]
                B       .
                ENDP

TIMER5B_Handler\
                PROC
                EXPORT  TIMER5B_Handler [WEAK]
                B       .
                ENDP

WideTimer0A_Handler\
                PROC
                EXPORT  WideTimer0A_Handler [WEAK]
                B       .
                ENDP

WideTimer0B_Handler\
                PROC
                EXPORT  WideTimer0B_Handler [WEAK]
                B       .
                ENDP

WideTimer1A_Handler\
                PROC
                EXPORT  WideTimer1A_Handler [WEAK]
                B       .
                ENDP

WideTimer1B_Handler\
                PROC
                EXPORT  WideTimer1B_Handler [WEAK]
                B       .
                ENDP

WideTimer2A_Handler\
                PROC
                EXPORT  WideTimer2A_Handler [WEAK]
                B       .
                ENDP

WideTimer2B_Handler\
                PROC
                EXPORT  WideTimer2B_Handler [WEAK]
                B       .
                ENDP

WideTimer3A_Handler\
                PROC
                EXPORT  WideTimer3A_Handler [WEAK]
                B       .
                ENDP

WideTimer3B_Handler\
                PROC
                EXPORT  WideTimer3B_Handler [WEAK]
                B       .
                ENDP

WideTimer4A_Handler\
                PROC
                EXPORT  WideTimer4A_Handler [WEAK]
                B       .
                ENDP

WideTimer4B_Handler\
                PROC
                EXPORT  WideTimer4B_Handler [WEAK]
                B       .
                ENDP

WideTimer5A_Handler\
                PROC
                EXPORT  WideTimer5A_Handler [WEAK]
                B       .
                ENDP

WideTimer5B_Handler\
                PROC
                EXPORT  WideTimer5B_Handler [WEAK]
                B       .
                ENDP

FPU_Handler\
                PROC
                EXPORT  FPU_Handler [WEAK]
                B       .
                ENDP

I2C4_Handler\
                PROC
                EXPORT  I2C4_Handler [WEAK]
                B       .
                ENDP

I2C5_Handler\
                PROC
                EXPORT  I2C5_Handler [WEAK]
                B       .
                ENDP

GPIOPortM_Handler\
                PROC
                EXPORT  GPIOPortM_Handler [WEAK]
                B       .
                ENDP

GPIOPortN_Handler\
                PROC
                EXPORT  GPIOPortN_Handler [WEAK]
                B       .
                ENDP

QEI2_Handler\
                PROC
                EXPORT  QEI2_Handler [WEAK]
                B       .
                ENDP

GPIOPortP0_Handler\
                PROC
                EXPORT  GPIOPortP0_Handler [WEAK]
                B       .
                ENDP

GPIOPortP1_Handler\
                PROC
                EXPORT  GPIOPortP1_Handler [WEAK]
                B       .
                ENDP

GPIOPortP2_Handler\
                PROC
                EXPORT  GPIOPortP2_Handler [WEAK]
                B       .
                ENDP

GPIOPortP3_Handler\
                PROC
                EXPORT  GPIOPortP3_Handler [WEAK]
                B       .
                ENDP

GPIOPortP4_Handler\
                PROC
                EXPORT  GPIOPortP4_Handler [WEAK]
                B       .
                ENDP

GPIOPortP5_Handler\
                PROC
                EXPORT  GPIOPortP5_Handler [WEAK]
                B       .
                ENDP

GPIOPortP6_Handler\
                PROC
                EXPORT  GPIOPortP6_Handler [WEAK]
                B       .
                ENDP

GPIOPortP7_Handler\
                PROC
                EXPORT  GPIOPortP7_Handler [WEAK]
                B       .
                ENDP

GPIOPortQ0_Handler\
                PROC
                EXPORT  GPIOPortQ0_Handler [WEAK]
                B       .
                ENDP

GPIOPortQ1_Handler\
                PROC
                EXPORT  GPIOPortQ1_Handler [WEAK]
                B       .
                ENDP

GPIOPortQ2_Handler\
                PROC
                EXPORT  GPIOPortQ2_Handler [WEAK]
                B       .
                ENDP

GPIOPortQ3_Handler\
                PROC
                EXPORT  GPIOPortQ3_Handler [WEAK]
                B       .
                ENDP

GPIOPortQ4_Handler\
                PROC
                EXPORT  GPIOPortQ4_Handler [WEAK]
                B       .
                ENDP

GPIOPortQ5_Handler\
                PROC
                EXPORT  GPIOPortQ5_Handler [WEAK]
                B       .
                ENDP

GPIOPortQ6_Handler\
                PROC
                EXPORT  GPIOPortQ6_Handler [WEAK]
                B       .
                ENDP

GPIOPortQ7_Handler\
                PROC
                EXPORT  GPIOPortQ7_Handler [WEAK]
                B       .
                ENDP

GPIOPortR_Handler\
                PROC
                EXPORT  GPIOPortR_Handler [WEAK]
                B       .
                ENDP

GPIOPortS_Handler\
                PROC
                EXPORT  GPIOPortS_Handler [WEAK]
                B       .
                ENDP

PWM1Generator0_Handler\
                PROC
                EXPORT  PWM1Generator0_Handler [WEAK]
                B       .
                ENDP

PWM1Generator1_Handler\
                PROC
                EXPORT  PWM1Generator1_Handler [WEAK]
                B       .
                ENDP

PWM1Generator2_Handler\
                PROC
                EXPORT  PWM1Generator2_Handler [WEAK]
                B       .
                ENDP

PWM1Generator3_Handler\
                PROC
                EXPORT  PWM1Generator3_Handler [WEAK]
                B       .
                ENDP

PWM1Fault_Handler\
                PROC
                EXPORT  PWM1Fault_Handler [WEAK]
                B       .
                ENDP

                ALIGN

;******************************************************************************
;
; Make sure the end of this section is aligned.
;
;******************************************************************************
        ALIGN

;******************************************************************************
;
; Some code in the normal code section for initializing the heap and stack.
;
;******************************************************************************
        AREA    |.text|, CODE, READONLY

;******************************************************************************
;
; Useful functions.
;
;******************************************************************************
        EXPORT  DisableInterrupts
        EXPORT  EnableInterrupts
        EXPORT  StartCritical
        EXPORT  EndCritical
        EXPORT  WaitForInterrupt

;*********** DisableInterrupts ***************
; disable interrupts
; inputs:  none
; outputs: none
DisableInterrupts
        CPSID  I
        BX     LR

;*********** EnableInterrupts ***************
; enable interrupts
; inputs:  none
; outputs: none
EnableInterrupts
        CPSIE  I
        BX     LR

;*********** StartCritical ************************
; make a copy of previous I bit, disable interrupts
; inputs:  none
; outputs: previous I bit
StartCritical
        MRS    R0, PRIMASK  ; save old status
        CPSID  I            ; mask all (except faults)
        BX     LR

;*********** EndCritical ************************
; using the copy of previous I bit, restore I bit to previous value
; inputs:  previous I bit
; outputs: none
EndCritical
        MSR    PRIMASK, R0
        BX     LR

;*********** WaitForInterrupt ************************
; go to low power mode while waiting for the next interrupt
; inputs:  none
; outputs: none
WaitForInterrupt
        WFI
        BX     LR
; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
