/*
 * cli_uart.c - msp430f5529 launchpad application uart interface implementation
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


//*****************************************************************************
//
//! \addtogroup CLI_UART
//! @{
//
//*****************************************************************************

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "cli_uart.h"

#define ASCII_ENTER     0x0D
#define LOOP_FOREVER    1

//
// Global variable that holds clock frequency
//
extern uint32_t	g_ui32SysClock;

#ifdef _USE_CLI_
unsigned char *g_ucUARTBuffer;

int cli_have_cmd = 0;
#endif


int
CLI_Read(unsigned char *pBuff)
{
	if(pBuff == NULL)
		return -1;

#ifdef _USE_CLI_
	g_ucUARTBuffer = pBuff;


	while(LOOP_FOREVER)
	{
		*g_ucUARTBuffer = (unsigned char)ROM_UARTCharGet(UART0_BASE);

		if(*g_ucUARTBuffer == ASCII_ENTER)
		{
			*g_ucUARTBuffer = 0x00;
			break;
		}

		g_ucUARTBuffer++;
	}

	return strlen((const char *)pBuff);

#else
	return 0;
#endif
}


int
CLI_Write(unsigned char *inBuff)
{
    if(inBuff == NULL)
        return -1;

#ifdef _USE_CLI_
    unsigned short ret = 0;
    unsigned short usLength = strlen((const char *)inBuff);
    ret = usLength;

    while (usLength)
    {
    	ROM_UARTCharPut(UART0_BASE, *inBuff);
        usLength--;
        inBuff++;
    }
    return (int)ret;
#else
    return 0;
#endif
}


void
CLI_Configure(void)
{
#ifdef _USE_CLI_

    /* Enable the UART0 and GPIOA peripherals clock. */
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /* Set GPIO A0 and A1 as UART pins. */
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Configure the UART for 115,200, 8-N-1 operation. */
    ROM_UARTConfigSetExpClk(UART0_BASE, g_ui32SysClock, 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

#endif
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
