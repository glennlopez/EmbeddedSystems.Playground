/*
 * board.h - tiva-c launchpad configuration
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef _BOARD_H
#define    _BOARD_H

//#include <stdbool.h>
#include <stdint.h>

//
// global variable to hold the clock value
//
extern uint32_t g_ui32SysClock;

#define PIN_HIGH                              0xFF
#define PIN_LOW                              (!PIN_HIGH)

//*****************************************************************************
//
// Make sure one or other boosterpack header has been selected in the build
// environment.
//
//*****************************************************************************
#if (!(defined CC3100_USE_BOOSTERPACK1) && !(defined CC3100_USE_BOOSTERPACK2))
#error Please define one of CC3100_USE_BOOSTERPACK1 or CC3100_USE_BOOSTERPACK2
#endif


//*****************************************************************************
//
// Pin defines for CC3100 Boost boosterpack on BoosterPack1 Header
//
//*****************************************************************************
#if defined(CC3100_USE_BOOSTERPACK1)

//
// CC3100 Enable / Disable signal
//
#define CC3100_ENABLEBASE   GPIO_PORTC_BASE
#define CC3100_ENABLEPIN    GPIO_PIN_6

//
// CC3100 IRQ pin
//
#define CC3100_IRQBASE      GPIO_PORTM_BASE
#define CC3100_IRQPIN       GPIO_PIN_3

//
// UART Base
//
#define CC3100_UARTBASE     UART7_BASE

#endif // CC3100_USE_BOOSTERPACK1

//*****************************************************************************
//
// Pin defines for CC3100 Boost boosterpack on BoosterPack2 Header
//
//*****************************************************************************
#if defined(CC3100_USE_BOOSTERPACK2)

//
// CC3100 Enable / Disable signal
//
#define CC3100_ENABLEBASE   GPIO_PORTD_BASE
#define CC3100_ENABLEPIN    GPIO_PIN_4

//
// CC3100 IRQ pin
//
#define CC3100_IRQBASE      GPIO_PORTM_BASE
#define CC3100_IRQPIN       GPIO_PIN_7

//
// UART Base
//
#define CC3100_UARTBASE     UART6_BASE

#endif // CC3100_USE_BOOSTERPACK2

typedef void (*P_EVENT_HANDLER)(void* pValue);

/*!
    \brief register an interrupt handler for the host IRQ

    \param[in]      InterruptHdl    -    pointer to interrupt handler function

    \param[in]      pValue          -    pointer to a memory strcuture that is 
                    passed to the interrupt handler.

    \return         upon successful registration, the function shall return 0.
                    Otherwise, -1 shall be returned

    \sa
    \note           If there is already registered interrupt handler, the 
                    function should overwrite the old handler with the new one

    \warning
*/
int registerInterruptHandler(P_EVENT_HANDLER InterruptHdl , void* pValue);

/*!
    \brief          GPIOB interrupt handler

    \param[in]      none

    \return         none

    \note

    \warning
*/
void IRQ_intHandler();

/*!
    \brief             Enables the CC3100

    \param[in]         none

    \return            none

    \note

    \warning
*/
void CC3100_enable();

/*!
    \brief             Disables the CC3100

    \param[in]         none

    \return            none

    \note

    \warning
*/
void CC3100_disable();

/*!
    \brief          Enables the interrupt from the CC3100

    \param[in]      none

    \return         none

    \note

    \warning
*/
void CC3100_InterruptEnable();

/*!
    \brief          Disables the interrupt from the CC3100

    \param[in]      none

    \return         none

    \note

    \warning
*/
void CC3100_InterruptDisable();

/*!
    \brief          Stops the Watch Dog timer

    \param[in]      none

    \return         none

    \note

    \warning
*/
void stopWDT();

/*!
    \brief          Initialize the system clock of MCU

    \param[in]      none

    \return         none

    \note

    \warning
*/
void initClk();

/*!
    \brief      Masks the Host IRQ

	\param[in]      none

    \return         none

    \warning
*/
void MaskIntHdlr();

/*!
    \brief     Unmasks the Host IRQ
	
	\param[in]      none

    \return         none

    \warning
*/
void UnMaskIntHdlr();

/*!
    \brief          GPIOB interrupt handler

    \param[in]      none

    \return         none

    \note

    \warning
*/
void UART1_intHandler();

/*!
    \brief     Produce delay in ms

    \param[in]         interval - Time in ms

    \return            none

    \note

    \warning
*/
void Delay(unsigned long interval);

#endif
