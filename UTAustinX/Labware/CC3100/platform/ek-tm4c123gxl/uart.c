/*
 * uart.c - tiva-c launchpad uart interface implementation
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

#ifdef SL_IF_TYPE_UART
#include "simplelink.h"
#include "board.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "uart.h"


extern BOOLEAN IntIsMasked;


int uart_Close(Fd_t fd)
{
	/* Disable WLAN Interrupt ... */
	CC3100_InterruptDisable();

	return 0;
}


Fd_t uart_Open(char *ifName, unsigned long flags)
{
	/* Configure CS (PE0) and nHIB (PE4) lines */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4);
	ROM_GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, PIN_LOW);


	/* configuring UART interface */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

	GPIOPinConfigure(GPIO_PB0_U1RX);
	GPIOPinConfigure(GPIO_PB1_U1TX);
	ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	GPIOPinConfigure(GPIO_PC4_U1RTS);
	GPIOPinConfigure(GPIO_PC5_U1CTS);
	ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

	GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA,
				GPIO_PIN_TYPE_STD_WPU);
	/* configure with baud rate 115200 */
	ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), 115200,
	                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
	                             UART_CONFIG_PAR_NONE));

    UARTFlowControlSet(UART1_BASE, UART_FLOWCONTROL_TX | UART_FLOWCONTROL_RX);

    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

    ROM_UARTEnable(UART1_BASE);
    ROM_UARTFIFOEnable(UART1_BASE);

    ROM_IntEnable(INT_UART1);
    ROM_UARTIntEnable(UART1_BASE, UART_INT_RX);
    ROM_UARTIntDisable(UART1_BASE, UART_INT_TX | UART_INT_RT);


	/* configure host IRQ line */
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA,
			GPIO_PIN_TYPE_STD_WPD);
	GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_RISING_EDGE);
	GPIOIntClear(GPIO_PORTB_BASE,GPIO_PIN_2);
	GPIOIntDisable(GPIO_PORTB_BASE,GPIO_PIN_2);
	ROM_IntEnable(INT_GPIOB);
	ROM_IntMasterEnable();

	IntIsMasked = FALSE;

	/* Enable WLAN interrupt */
	CC3100_InterruptEnable();

	/* 50 ms delay */
	ROM_SysCtlDelay((ROM_SysCtlClockGet()/(3*1000))*50 );


	return NONOS_RET_OK;
}


int uart_Read(Fd_t fd, unsigned char *pBuff, int len)
{
	int i = 0;
	ROM_UARTIntDisable(UART1_BASE, UART_INT_RX);

	for(i=0; i< len; i++)
	{
		pBuff[i] = (unsigned char)UARTCharGet(UART1_BASE);
	}

	ROM_UARTIntEnable(UART1_BASE, UART_INT_RX);

	return len;
}


int uart_Write(Fd_t fd, unsigned char *pBuff, int len)
{
	int len_to_return = len;

	while(len)
	{
		/* Wait until UART channel is busy or CTS line from NWP is high */
		UARTCharPut(UART1_BASE, *pBuff);
		len--;
		pBuff++;
	}

	return len_to_return;
}
#endif /* SL_IF_TYPE_UART */
