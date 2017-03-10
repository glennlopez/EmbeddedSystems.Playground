//*****************************************************************************
//
// Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2011-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************
/* Style edited to be consist with the three Valvano books
"Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
  ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015
"Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
"Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
   */
#include <stdint.h>

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);

//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);

//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern uint32_t __STACK_TOP;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
//Weak Function Deffinitions, can be written / declared in other files
extern void SVC_Handler(void) __attribute__((weak));                // SVCall Handler
extern void DebugMon_Handler(void) __attribute__((weak));           // Debug Monitor Handler
extern void PendSV_Handler(void) __attribute__((weak));             // PendSV Handler
extern void SysTick_Handler(void) __attribute__((weak));            // SysTick Handler
extern void GPIOPortA_Handler(void) __attribute__((weak));          // GPIO Port A
extern void GPIOPortB_Handler(void) __attribute__((weak));          // GPIO Port B
extern void GPIOPortC_Handler(void) __attribute__((weak));          // GPIO Port C
extern void GPIOPortD_Handler(void) __attribute__((weak));          // GPIO Port D
extern void GPIOPortE_Handler(void) __attribute__((weak));          // GPIO Port E
extern void UART0_Handler(void) __attribute__((weak));              // UART0 Rx and Tx
extern void UART1_Handler(void) __attribute__((weak));              // UART1 Rx and Tx
extern void SSI0_Handler(void) __attribute__((weak));               // SSI0 Rx and Tx
extern void I2C0_Handler(void) __attribute__((weak));               // I2C0 Master and Slave
extern void PWM0Fault_Handler(void) __attribute__((weak));          // PWM 0 Fault
extern void PWM0Generator0_Handler(void) __attribute__((weak));     // PWM 0 Generator 0
extern void PWM0Generator1_Handler(void) __attribute__((weak));     // PWM 0 Generator 1
extern void PWM0Generator2_Handler(void) __attribute__((weak));     // PWM 0 Generator 2
extern void Quadrature0_Handler(void) __attribute__((weak));        // Quadrature Encoder 0
extern void ADC0Seq0_Handler(void) __attribute__((weak));           // ADC0 Sequence 0
extern void ADC0Seq1_Handler(void) __attribute__((weak));           // ADC0 Sequence 1
extern void ADC0Seq2_Handler(void) __attribute__((weak));           // ADC0 Sequence 2
extern void ADC0Seq3_Handler(void) __attribute__((weak));           // ADC0 Sequence 3
extern void WDT_Handler(void) __attribute__((weak));                // Watchdog
extern void Timer0A_Handler(void) __attribute__((weak));            // Timer 0 subtimer A
extern void Timer0B_Handler(void) __attribute__((weak));            // Timer 0 subtimer B
extern void Timer1A_Handler(void) __attribute__((weak));            // Timer 1 subtimer A
extern void Timer1B_Handler(void) __attribute__((weak));            // Timer 1 subtimer B
extern void Timer2A_Handler(void) __attribute__((weak));            // Timer 2 subtimer A
extern void Timer2B_Handler(void) __attribute__((weak));            // Timer 2 subtimer B
extern void Comp0_Handler(void) __attribute__((weak));              // Analog Comp 0
extern void Comp1_Handler(void) __attribute__((weak));              // Analog Comp 1
extern void Comp2_Handler(void) __attribute__((weak));              // Analog Comp 2
extern void SysCtl_Handler(void) __attribute__((weak));             // System Control
extern void FlashCtl_Handler(void) __attribute__((weak));           // Flash Control
extern void GPIOPortF_Handler(void) __attribute__((weak));          // GPIO Port F
extern void GPIOPortG_Handler(void) __attribute__((weak));          // GPIO Port G
extern void GPIOPortH_Handler(void) __attribute__((weak));          // GPIO Port H
extern void UART2_Handler(void) __attribute__((weak));              // UART2 Rx and Tx
extern void SSI1_Handler(void) __attribute__((weak));               // SSI1 Rx and Tx
extern void Timer3A_Handler(void) __attribute__((weak));            // Timer 3 subtimer A
extern void Timer3B_Handler(void) __attribute__((weak));            // Timer 3 subtimer B
extern void I2C1_Handler(void) __attribute__((weak));               // I2C1 Master and Slave
extern void Quadrature1_Handler(void) __attribute__((weak));        // Quadrature Encoder 1
extern void CAN0_Handler(void) __attribute__((weak));               // CAN0
extern void CAN1_Handler(void) __attribute__((weak));               // CAN1
extern void CAN2_Handler(void) __attribute__((weak));               // CAN2
extern void Ethernet_Handler(void) __attribute__((weak));           // Ethernet
extern void Hibernate_Handler(void) __attribute__((weak));          // Hibernate
extern void USB0_Handler(void) __attribute__((weak));               // USB0
extern void PWM0Generator3_Handler(void) __attribute__((weak));     // PWM 0 Generator 3
extern void uDMA_Handler(void) __attribute__((weak));               // uDMA Software Transfer
extern void uDMA_Error(void) __attribute__((weak));                 // uDMA Error
extern void ADC1Seq0_Handler(void) __attribute__((weak));           // ADC1 Sequence 0
extern void ADC1Seq1_Handler(void) __attribute__((weak));           // ADC1 Sequence 1
extern void ADC1Seq2_Handler(void) __attribute__((weak));           // ADC1 Sequence 2
extern void ADC1Seq3_Handler(void) __attribute__((weak));           // ADC1 Sequence 3
extern void I2S0_Handler(void) __attribute__((weak));               // I2S0
extern void ExtBus_Handler(void) __attribute__((weak));             // External Bus Interface 0
extern void GPIOPortJ_Handler(void) __attribute__((weak));          // GPIO Port J
extern void GPIOPortK_Handler(void) __attribute__((weak));          // GPIO Port K
extern void GPIOPortL_Handler(void) __attribute__((weak));          // GPIO Port L
extern void SSI2_Handler(void) __attribute__((weak));               // SSI2 Rx and Tx
extern void SSI3_Handler(void) __attribute__((weak));               // SSI3 Rx and Tx
extern void UART3_Handler(void) __attribute__((weak));              // UART3 Rx and Tx
extern void UART4_Handler(void) __attribute__((weak));              // UART4 Rx and Tx
extern void UART5_Handler(void) __attribute__((weak));              // UART5 Rx and Tx
extern void UART6_Handler(void) __attribute__((weak));              // UART6 Rx and Tx
extern void UART7_Handler(void) __attribute__((weak));              // UART7 Rx and Tx
extern void I2C2_Handler(void) __attribute__((weak));               // I2C2 Master and Slave
extern void I2C3_Handler(void) __attribute__((weak));               // I2C3 Master and Slave
extern void Timer4A_Handler(void) __attribute__((weak));            // Timer 4 subtimer A
extern void Timer4B_Handler(void) __attribute__((weak));            // Timer 4 subtimer B
extern void Timer5A_Handler(void) __attribute__((weak));            // Timer 5 subtimer A
extern void Timer5B_Handler(void) __attribute__((weak));            // Timer 5 subtimer B
extern void WideTimer0A_Handler(void) __attribute__((weak));        // Wide Timer 0 subtimer A
extern void WideTimer0B_Handler(void) __attribute__((weak));        // Wide Timer 0 subtimer B
extern void WideTimer1A_Handler(void) __attribute__((weak));        // Wide Timer 1 subtimer A
extern void WideTimer1B_Handler(void) __attribute__((weak));        // Wide Timer 1 subtimer B
extern void WideTimer2A_Handler(void) __attribute__((weak));        // Wide Timer 2 subtimer A
extern void WideTimer2B_Handler(void) __attribute__((weak));        // Wide Timer 2 subtimer B
extern void WideTimer3A_Handler(void) __attribute__((weak));        // Wide Timer 3 subtimer A
extern void WideTimer3B_Handler(void) __attribute__((weak));        // Wide Timer 3 subtimer B
extern void WideTimer4A_Handler(void) __attribute__((weak));        // Wide Timer 4 subtimer A
extern void WideTimer4B_Handler(void) __attribute__((weak));        // Wide Timer 4 subtimer B
extern void WideTimer5A_Handler(void) __attribute__((weak));        // Wide Timer 5 subtimer A
extern void WideTimer5B_Handler(void) __attribute__((weak));        // Wide Timer 5 subtimer B
extern void FPU_Handler(void) __attribute__((weak));                // FPU
extern void PECI0_Handler(void) __attribute__((weak));              // PECI 0
extern void LPC0_Handler(void) __attribute__((weak));               // LPC 0
extern void I2C4_Handler(void) __attribute__((weak));               // I2C4 Master and Slave
extern void I2C5_Handler(void) __attribute__((weak));               // I2C5 Master and Slave
extern void GPIOPortM_Handler(void) __attribute__((weak));          // GPIO Port M
extern void GPIOPortN_Handler(void) __attribute__((weak));          // GPIO Port N
extern void Quadrature2_Handler(void) __attribute__((weak));        // Quadrature Encoder 2
extern void Fan0_Handler(void) __attribute__((weak));               // Fan 0
extern void GPIOPortP_Handler(void) __attribute__((weak));          // GPIO Port P (Summary or P0)
extern void GPIOPortP1_Handler(void) __attribute__((weak));         // GPIO Port P1
extern void GPIOPortP2_Handler(void) __attribute__((weak));         // GPIO Port P2
extern void GPIOPortP3_Handler(void) __attribute__((weak));         // GPIO Port P3
extern void GPIOPortP4_Handler(void) __attribute__((weak));         // GPIO Port P4
extern void GPIOPortP5_Handler(void) __attribute__((weak));         // GPIO Port P5
extern void GPIOPortP6_Handler(void) __attribute__((weak));         // GPIO Port P6
extern void GPIOPortP7_Handler(void) __attribute__((weak));         // GPIO Port P7
extern void GPIOPortQ_Handler(void) __attribute__((weak));          // GPIO Port Q (Summary or Q0)
extern void GPIOPortQ1_Handler(void) __attribute__((weak));         // GPIO Port Q1
extern void GPIOPortQ2_Handler(void) __attribute__((weak));         // GPIO Port Q2
extern void GPIOPortQ3_Handler(void) __attribute__((weak));         // GPIO Port Q3
extern void GPIOPortQ4_Handler(void) __attribute__((weak));         // GPIO Port Q4
extern void GPIOPortQ5_Handler(void) __attribute__((weak));         // GPIO Port Q5
extern void GPIOPortQ6_Handler(void) __attribute__((weak));         // GPIO Port Q6
extern void GPIOPortQ7_Handler(void) __attribute__((weak));         // GPIO Port Q7
extern void GPIOPortR_Handler(void) __attribute__((weak));          // GPIO Port R
extern void GPIOPortS_Handler(void) __attribute__((weak));          // GPIO Port S
extern void PWM1Generator0_Handler(void) __attribute__((weak));     // PWM 1 Generator 0
extern void PWM1Generator1_Handler(void) __attribute__((weak));     // PWM 1 Generator 1
extern void PWM1Generator2_Handler(void) __attribute__((weak));     // PWM 1 Generator 2
extern void PWM1Generator3_Handler(void) __attribute__((weak));     // PWM 1 Generator 3
extern void PWM1Fault_Handler(void) __attribute__((weak));          // PWM 1 Fault



//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)&__STACK_TOP),
                                            // The initial stack pointer
    ResetISR,                               // The reset handler
    NmiSR,                                  // The NMI handler
    FaultISR,                               // The hard fault handler
    IntDefaultHandler,                      // The MPU fault handler
    IntDefaultHandler,                      // The bus fault handler
    IntDefaultHandler,                      // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved





    SVC_Handler,                // SVCall Handler
    DebugMon_Handler,           // Debug Monitor Handler
    0,                          // Reserved
    PendSV_Handler,             // PendSV Handler
    SysTick_Handler,            // SysTick Handler
    GPIOPortA_Handler,          // GPIO Port A
    GPIOPortB_Handler,          // GPIO Port B
    GPIOPortC_Handler,          // GPIO Port C
    GPIOPortD_Handler,          // GPIO Port D
    GPIOPortE_Handler,          // GPIO Port E
    UART0_Handler,              // UART0 Rx and Tx
    UART1_Handler,              // UART1 Rx and Tx
    SSI0_Handler,               // SSI0 Rx and Tx
    I2C0_Handler,               // I2C0 Master and Slave
    PWM0Fault_Handler,          // PWM 0 Fault
    PWM0Generator0_Handler,     // PWM 0 Generator 0
    PWM0Generator1_Handler,     // PWM 0 Generator 1
    PWM0Generator2_Handler,     // PWM 0 Generator 2
    Quadrature0_Handler,        // Quadrature Encoder 0
    ADC0Seq0_Handler,           // ADC0 Sequence 0
    ADC0Seq1_Handler,           // ADC0 Sequence 1
    ADC0Seq2_Handler,           // ADC0 Sequence 2
    ADC0Seq3_Handler,           // ADC0 Sequence 3
    WDT_Handler,                // Watchdog
    Timer0A_Handler,            // Timer 0 subtimer A
    Timer0B_Handler,            // Timer 0 subtimer B
    Timer1A_Handler,            // Timer 1 subtimer A
    Timer1B_Handler,            // Timer 1 subtimer B
    Timer2A_Handler,            // Timer 2 subtimer A
    Timer2B_Handler,            // Timer 2 subtimer B
    Comp0_Handler,              // Analog Comp 0
    Comp1_Handler,              // Analog Comp 1
    Comp2_Handler,              // Analog Comp 2
    SysCtl_Handler,             // System Control
    FlashCtl_Handler,           // Flash Control
    GPIOPortF_Handler,          // GPIO Port F
    GPIOPortG_Handler,          // GPIO Port G
    GPIOPortH_Handler,          // GPIO Port H
    UART2_Handler,              // UART2 Rx and Tx
    SSI1_Handler,               // SSI1 Rx and Tx
    Timer3A_Handler,            // Timer 3 subtimer A
    Timer3B_Handler,            // Timer 3 subtimer B
    I2C1_Handler,               // I2C1 Master and Slave
    Quadrature1_Handler,        // Quadrature Encoder 1
    CAN0_Handler,               // CAN0
    CAN1_Handler,               // CAN1
    CAN2_Handler,               // CAN2
    Ethernet_Handler,           // Ethernet
    Hibernate_Handler,          // Hibernate
    USB0_Handler,               // USB0
    PWM0Generator3_Handler,     // PWM 0 Generator 3
    uDMA_Handler,               // uDMA Software Transfer
    uDMA_Error,                 // uDMA Error
    ADC1Seq0_Handler,           // ADC1 Sequence 0
    ADC1Seq1_Handler,           // ADC1 Sequence 1
    ADC1Seq2_Handler,           // ADC1 Sequence 2
    ADC1Seq3_Handler,           // ADC1 Sequence 3
    I2S0_Handler,               // I2S0
    ExtBus_Handler,             // External Bus Interface 0
    GPIOPortJ_Handler,          // GPIO Port J
    GPIOPortK_Handler,          // GPIO Port K
    GPIOPortL_Handler,          // GPIO Port L
    SSI2_Handler,               // SSI2 Rx and Tx
    SSI3_Handler,               // SSI3 Rx and Tx
    UART3_Handler,              // UART3 Rx and Tx
    UART4_Handler,              // UART4 Rx and Tx
    UART5_Handler,              // UART5 Rx and Tx
    UART6_Handler,              // UART6 Rx and Tx
    UART7_Handler,              // UART7 Rx and Tx
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    I2C2_Handler,               // I2C2 Master and Slave
    I2C3_Handler,               // I2C3 Master and Slave
    Timer4A_Handler,            // Timer 4 subtimer A
    Timer4B_Handler,            // Timer 4 subtimer B
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    Timer5A_Handler,            // Timer 5 subtimer A
    Timer5B_Handler,            // Timer 5 subtimer B
    WideTimer0A_Handler,        // Wide Timer 0 subtimer A
    WideTimer0B_Handler,        // Wide Timer 0 subtimer B
    WideTimer1A_Handler,        // Wide Timer 1 subtimer A
    WideTimer1B_Handler,        // Wide Timer 1 subtimer B
    WideTimer2A_Handler,        // Wide Timer 2 subtimer A
    WideTimer2B_Handler,        // Wide Timer 2 subtimer B
    WideTimer3A_Handler,        // Wide Timer 3 subtimer A
    WideTimer3B_Handler,        // Wide Timer 3 subtimer B
    WideTimer4A_Handler,        // Wide Timer 4 subtimer A
    WideTimer4B_Handler,        // Wide Timer 4 subtimer B
    WideTimer5A_Handler,        // Wide Timer 5 subtimer A
    WideTimer5B_Handler,        // Wide Timer 5 subtimer B
    FPU_Handler,                // FPU
    PECI0_Handler,              // PECI 0
    LPC0_Handler,               // LPC 0
    I2C4_Handler,               // I2C4 Master and Slave
    I2C5_Handler,               // I2C5 Master and Slave
    GPIOPortM_Handler,          // GPIO Port M
    GPIOPortN_Handler,          // GPIO Port N
    Quadrature2_Handler,        // Quadrature Encoder 2
    Fan0_Handler,               // Fan 0
    0,                          // Reserved
    GPIOPortP_Handler,          // GPIO Port P (Summary or P0)
    GPIOPortP1_Handler,         // GPIO Port P1
    GPIOPortP2_Handler,         // GPIO Port P2
    GPIOPortP3_Handler,         // GPIO Port P3
    GPIOPortP4_Handler,         // GPIO Port P4
    GPIOPortP5_Handler,         // GPIO Port P5
    GPIOPortP6_Handler,         // GPIO Port P6
    GPIOPortP7_Handler,         // GPIO Port P7
    GPIOPortQ_Handler,          // GPIO Port Q (Summary or Q0)
    GPIOPortQ1_Handler,         // GPIO Port Q1
    GPIOPortQ2_Handler,         // GPIO Port Q2
    GPIOPortQ3_Handler,         // GPIO Port Q3
    GPIOPortQ4_Handler,         // GPIO Port Q4
    GPIOPortQ5_Handler,         // GPIO Port Q5
    GPIOPortQ6_Handler,         // GPIO Port Q6
    GPIOPortQ7_Handler,         // GPIO Port Q7
    GPIOPortR_Handler,          // GPIO Port R
    GPIOPortS_Handler,          // GPIO Port S
    PWM1Generator0_Handler,     // PWM 1 Generator 0
    PWM1Generator1_Handler,     // PWM 1 Generator 1
    PWM1Generator2_Handler,     // PWM 1 Generator 2
    PWM1Generator3_Handler,     // PWM 1 Generator 3
    PWM1Fault_Handler           // PWM 1 Fault

};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void
ResetISR(void)
{
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void
NmiSR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
FaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}





void SVC_Handler(void){ while(1){}}                // SVCall Handler
void DebugMon_Handler(void){ while(1){}}           // Debug Monitor Handler
void PendSV_Handler(void){ while(1){}}             // PendSV Handler
void SysTick_Handler(void){ while(1){}}            // SysTick Handler
void GPIOPortA_Handler(void){ while(1){}}          // GPIO Port A
void GPIOPortB_Handler(void){ while(1){}}          // GPIO Port B
void GPIOPortC_Handler(void){ while(1){}}          // GPIO Port C
void GPIOPortD_Handler(void){ while(1){}}          // GPIO Port D
void GPIOPortE_Handler(void){ while(1){}}          // GPIO Port E
void UART0_Handler(void){ while(1){}}              // UART0 Rx and Tx
void UART1_Handler(void){ while(1){}}              // UART1 Rx and Tx
void SSI0_Handler(void){ while(1){}}               // SSI0 Rx and Tx
void I2C0_Handler(void){ while(1){}}               // I2C0 Master and Slave
void PWM0Fault_Handler(void){ while(1){}}          // PWM 0 Fault
void PWM0Generator0_Handler(void){ while(1){}}     // PWM 0 Generator 0
void PWM0Generator1_Handler(void){ while(1){}}     // PWM 0 Generator 1
void PWM0Generator2_Handler(void){ while(1){}}     // PWM 0 Generator 2
void Quadrature0_Handler(void){ while(1){}}        // Quadrature Encoder 0
void ADC0Seq0_Handler(void){ while(1){}}           // ADC0 Sequence 0
void ADC0Seq1_Handler(void){ while(1){}}           // ADC0 Sequence 1
void ADC0Seq2_Handler(void){ while(1){}}           // ADC0 Sequence 2
void ADC0Seq3_Handler(void){ while(1){}}           // ADC0 Sequence 3
void WDT_Handler(void){ while(1){}}                // Watchdog
void Timer0A_Handler(void){ while(1){}}            // Timer 0 subtimer A
void Timer0B_Handler(void){ while(1){}}            // Timer 0 subtimer B
void Timer1A_Handler(void){ while(1){}}            // Timer 1 subtimer A
void Timer1B_Handler(void){ while(1){}}            // Timer 1 subtimer B
void Timer2A_Handler(void){ while(1){}}            // Timer 2 subtimer A
void Timer2B_Handler(void){ while(1){}}            // Timer 2 subtimer B
void Comp0_Handler(void){ while(1){}}              // Analog Comp 0
void Comp1_Handler(void){ while(1){}}              // Analog Comp 1
void Comp2_Handler(void){ while(1){}}              // Analog Comp 2
void SysCtl_Handler(void){ while(1){}}             // System Control
void FlashCtl_Handler(void){ while(1){}}           // Flash Control
void GPIOPortF_Handler(void){ while(1){}}          // GPIO Port F
void GPIOPortG_Handler(void){ while(1){}}          // GPIO Port G
void GPIOPortH_Handler(void){ while(1){}}          // GPIO Port H
void UART2_Handler(void){ while(1){}}              // UART2 Rx and Tx
void SSI1_Handler(void){ while(1){}}               // SSI1 Rx and Tx
void Timer3A_Handler(void){ while(1){}}            // Timer 3 subtimer A
void Timer3B_Handler(void){ while(1){}}            // Timer 3 subtimer B
void I2C1_Handler(void){ while(1){}}               // I2C1 Master and Slave
void Quadrature1_Handler(void){ while(1){}}        // Quadrature Encoder 1
void CAN0_Handler(void){ while(1){}}               // CAN0
void CAN1_Handler(void){ while(1){}}               // CAN1
void CAN2_Handler(void){ while(1){}}               // CAN2
void Ethernet_Handler(void){ while(1){}}           // Ethernet
void Hibernate_Handler(void){ while(1){}}          // Hibernate
void USB0_Handler(void){ while(1){}}               // USB0
void PWM0Generator3_Handler(void){ while(1){}}     // PWM 0 Generator 3
void uDMA_Handler(void){ while(1){}}               // uDMA Software Transfer
void uDMA_Error(void){ while(1){}}                 // uDMA Error
void ADC1Seq0_Handler(void){ while(1){}}           // ADC1 Sequence 0
void ADC1Seq1_Handler(void){ while(1){}}           // ADC1 Sequence 1
void ADC1Seq2_Handler(void){ while(1){}}           // ADC1 Sequence 2
void ADC1Seq3_Handler(void){ while(1){}}           // ADC1 Sequence 3
void I2S0_Handler(void){ while(1){}}               // I2S0
void ExtBus_Handler(void){ while(1){}}             // External Bus Interface 0
void GPIOPortJ_Handler(void){ while(1){}}          // GPIO Port J
void GPIOPortK_Handler(void){ while(1){}}          // GPIO Port K
void GPIOPortL_Handler(void){ while(1){}}          // GPIO Port L
void SSI2_Handler(void){ while(1){}}               // SSI2 Rx and Tx
void SSI3_Handler(void){ while(1){}}               // SSI3 Rx and Tx
void UART3_Handler(void){ while(1){}}              // UART3 Rx and Tx
void UART4_Handler(void){ while(1){}}              // UART4 Rx and Tx
void UART5_Handler(void){ while(1){}}              // UART5 Rx and Tx
void UART6_Handler(void){ while(1){}}              // UART6 Rx and Tx
void UART7_Handler(void){ while(1){}}              // UART7 Rx and Tx
void I2C2_Handler(void){ while(1){}}               // I2C2 Master and Slave
void I2C3_Handler(void){ while(1){}}               // I2C3 Master and Slave
void Timer4A_Handler(void){ while(1){}}            // Timer 4 subtimer A
void Timer4B_Handler(void){ while(1){}}            // Timer 4 subtimer B
void Timer5A_Handler(void){ while(1){}}            // Timer 5 subtimer A
void Timer5B_Handler(void){ while(1){}}            // Timer 5 subtimer B
void WideTimer0A_Handler(void){ while(1){}}        // Wide Timer 0 subtimer A
void WideTimer0B_Handler(void){ while(1){}}        // Wide Timer 0 subtimer B
void WideTimer1A_Handler(void){ while(1){}}        // Wide Timer 1 subtimer A
void WideTimer1B_Handler(void){ while(1){}}        // Wide Timer 1 subtimer B
void WideTimer2A_Handler(void){ while(1){}}        // Wide Timer 2 subtimer A
void WideTimer2B_Handler(void){ while(1){}}        // Wide Timer 2 subtimer B
void WideTimer3A_Handler(void){ while(1){}}        // Wide Timer 3 subtimer A
void WideTimer3B_Handler(void){ while(1){}}        // Wide Timer 3 subtimer B
void WideTimer4A_Handler(void){ while(1){}}        // Wide Timer 4 subtimer A
void WideTimer4B_Handler(void){ while(1){}}        // Wide Timer 4 subtimer B
void WideTimer5A_Handler(void){ while(1){}}        // Wide Timer 5 subtimer A
void WideTimer5B_Handler(void){ while(1){}}        // Wide Timer 5 subtimer B
void FPU_Handler(void){ while(1){}}                // FPU
void PECI0_Handler(void){ while(1){}}              // PECI 0
void LPC0_Handler(void){ while(1){}}               // LPC 0
void I2C4_Handler(void){ while(1){}}               // I2C4 Master and Slave
void I2C5_Handler(void){ while(1){}}               // I2C5 Master and Slave
void GPIOPortM_Handler(void){ while(1){}}          // GPIO Port M
void GPIOPortN_Handler(void){ while(1){}}          // GPIO Port N
void Quadrature2_Handler(void){ while(1){}}        // Quadrature Encoder 2
void Fan0_Handler(void){ while(1){}}               // Fan 0
void GPIOPortP_Handler(void){ while(1){}}          // GPIO Port P (Summary or P0)
void GPIOPortP1_Handler(void){ while(1){}}         // GPIO Port P1
void GPIOPortP2_Handler(void){ while(1){}}         // GPIO Port P2
void GPIOPortP3_Handler(void){ while(1){}}         // GPIO Port P3
void GPIOPortP4_Handler(void){ while(1){}}         // GPIO Port P4
void GPIOPortP5_Handler(void){ while(1){}}         // GPIO Port P5
void GPIOPortP6_Handler(void){ while(1){}}         // GPIO Port P6
void GPIOPortP7_Handler(void){ while(1){}}         // GPIO Port P7
void GPIOPortQ_Handler(void){ while(1){}}          // GPIO Port Q (Summary or Q0)
void GPIOPortQ1_Handler(void){ while(1){}}         // GPIO Port Q1
void GPIOPortQ2_Handler(void){ while(1){}}         // GPIO Port Q2
void GPIOPortQ3_Handler(void){ while(1){}}         // GPIO Port Q3
void GPIOPortQ4_Handler(void){ while(1){}}         // GPIO Port Q4
void GPIOPortQ5_Handler(void){ while(1){}}         // GPIO Port Q5
void GPIOPortQ6_Handler(void){ while(1){}}         // GPIO Port Q6
void GPIOPortQ7_Handler(void){ while(1){}}         // GPIO Port Q7
void GPIOPortR_Handler(void){ while(1){}}          // GPIO Port R
void GPIOPortS_Handler(void){ while(1){}}          // GPIO Port S
void PWM1Generator0_Handler(void){ while(1){}}     // PWM 1 Generator 0
void PWM1Generator1_Handler(void){ while(1){}}     // PWM 1 Generator 1
void PWM1Generator2_Handler(void){ while(1){}}     // PWM 1 Generator 2
void PWM1Generator3_Handler(void){ while(1){}}     // PWM 1 Generator 3
void PWM1Fault_Handler(void){ while(1){}}          // PWM 1 Fault

//*********** DisableInterrupts ***************
// disable interrupts
// inputs:  none
// outputs: none
void DisableInterrupts(void){
	__asm ("    CPSID  I\n");
}

//*********** EnableInterrupts ***************
// emable interrupts
// inputs:  none
// outputs: none
void EnableInterrupts(void){
	__asm  ("    CPSIE  I\n");
}
//*********** StartCritical ************************
// make a copy of previous I bit, disable interrupts
// inputs:  none
// outputs: previous I bit
void StartCritical(void){
 __asm  ("    MRS    R0, PRIMASK  ; save old status \n"
         "    CPSID  I         	  ; mask all (except faults)\n");
}

//*********** EndCritical ************************
// using the copy of previous I bit, restore I bit to previous value
// inputs:  previous I bit
// outputs: none
void EndCritical(void){
	__asm  ("    MSR    PRIMASK, R0\n");
}

//*********** WaitForInterrupt ************************
// go to low power mode while waiting for the next interrupt
// inputs:  none
// outputs: none
void WaitForInterrupt(void){
	__asm  ("    WFI\n");
}
