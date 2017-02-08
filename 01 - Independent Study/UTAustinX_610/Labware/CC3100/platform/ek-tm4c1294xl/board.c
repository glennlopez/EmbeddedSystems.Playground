/*
 * board.c - tiva-c launchpad configuration
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
#include <stdint.h>
#include <stdbool.h>
uint32_t g_ui32SysClock;
#include "simplelink.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "driverlib/ssi.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/fpu.h"
#include "driverlib/uart.h"
//#include "board.h"


P_EVENT_HANDLER        pIrqEventHandler = 0;

BOOLEAN IntIsMasked;

//*****************************************************************************
//
// Global to hold the system clock frequency. It is returned during by
// SysCtlClockFreqSet() and is required later to configure SSI, for example.
//
//*****************************************************************************


void initClk()
{
    /*The FPU should be enabled because some compilers will use floating-
    * point registers, even for non-floating-point code.  If the FPU is not
    * enabled this will cause a fault.  This also ensures that floating-
    * point operations could be added to this application and would work
    * correctly and use the hardware floating-point unit.  Finally, lazy
    * stacking is enabled for interrupt handlers.  This allows floating-
    * point instructions to be used within interrupt handlers, but at the
    * expense of extra stack usage. */
    FPUEnable();
    FPULazyStackingEnable();


    //
    // Set the system clock to 60MHz via the PLL, knowing that there is a
    // 25MHz crystal on the board.
    //
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                         SYSCTL_OSC_MAIN |
                                         SYSCTL_USE_PLL |
                                         SYSCTL_CFG_VCO_480), 120000000);
}

void stopWDT()
{
}

int registerInterruptHandler(P_EVENT_HANDLER InterruptHdl , void* pValue)
{
    pIrqEventHandler = InterruptHdl;

    return 0;
}

void CC3100_disable()
{
    ROM_GPIOPinWrite(CC3100_ENABLEBASE,CC3100_ENABLEPIN, PIN_LOW);
}

void CC3100_enable()
{
    ROM_GPIOPinWrite(CC3100_ENABLEBASE,CC3100_ENABLEPIN, PIN_HIGH);
}

void CC3100_InterruptEnable()
{
    GPIOIntEnable(CC3100_IRQBASE,CC3100_IRQPIN);
#ifdef SL_IF_TYPE_UART
    ROM_UARTIntEnable(CC3100_UARTBASE, UART_INT_RX);
#endif
}

void CC3100_InterruptDisable()
{
     GPIOIntDisable(CC3100_IRQBASE,CC3100_IRQPIN);
#ifdef SL_IF_TYPE_UART
     ROM_UARTIntDisable(CC3100_UARTBASE, UART_INT_RX);
#endif
}

void MaskIntHdlr()
{
	IntIsMasked = TRUE;
}

void UnMaskIntHdlr()
{
	IntIsMasked = FALSE;
}

void Delay(unsigned long interval)
{
	ROM_SysCtlDelay( ( g_ui32SysClock / (3*1000) ) * interval );
}

void IRQ_intHandler()
{
    unsigned long intStatus;
    intStatus = GPIOIntStatus(CC3100_IRQBASE, 0);
    GPIOIntClear(CC3100_IRQBASE,intStatus);

    if(intStatus & CC3100_IRQPIN)
    {
#ifndef SL_IF_TYPE_UART
    	if(pIrqEventHandler)
        {
            pIrqEventHandler(0);
        }
#endif
    }
}

void UART1_intHandler()
{
	unsigned long intStatus;
	intStatus = UARTIntStatus(CC3100_UARTBASE,0);
	UARTIntClear(CC3100_UARTBASE,intStatus);

#ifdef SL_IF_TYPE_UART
	if((pIrqEventHandler != 0) && (IntIsMasked == FALSE))
	{
		pIrqEventHandler(0);
	}
#endif
}

