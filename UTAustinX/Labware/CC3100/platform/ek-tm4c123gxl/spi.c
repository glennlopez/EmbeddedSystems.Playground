/*
 * spi.c - tiva-c launchpad spi interface implementation
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

#ifndef SL_IF_TYPE_UART
#include "simplelink.h"
#include "board.h"
#include "spi.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"
#include "inc/hw_ints.h"
#include "driverlib/ssi.h"
#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"



#define ASSERT_CS()         GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0, PIN_LOW)
#define DEASSERT_CS()       GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0, PIN_HIGH)


int spi_Close(Fd_t fd)
{
    /* Disable WLAN Interrupt ... */
    CC3100_InterruptDisable();

    return 0;
}

Fd_t spi_Open(char *ifName, unsigned long flags)
{
    /* Configure CS (PE0) and nHIB (PE4) lines */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_4);
    ROM_GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, PIN_LOW);
    ROM_GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0, PIN_HIGH);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB4_SSI2CLK);
    GPIOPinConfigure(GPIO_PB5_SSI2FSS);
    GPIOPinConfigure(GPIO_PB6_SSI2RX);
    GPIOPinConfigure(GPIO_PB7_SSI2TX);

    GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6
            | GPIO_PIN_7);


    /* CLOCK IS CONFIGURED AT 4 MHz */
    SSIConfigSetExpClk(SSI2_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
            SSI_MODE_MASTER, 4000000, 8);

    SSIEnable(SSI2_BASE);

    /* configure host IRQ line */
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA,
            GPIO_PIN_TYPE_STD_WPD);
    GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_RISING_EDGE);
    GPIOIntClear(GPIO_PORTB_BASE,GPIO_PIN_2);
    GPIOIntDisable(GPIO_PORTB_BASE,GPIO_PIN_2);
    IntEnable(INT_GPIOB);
    IntMasterEnable();

    /* 1 ms delay */
    ROM_SysCtlDelay( (ROM_SysCtlClockGet()/(3*1000))*1 );

    /* Enable WLAN interrupt */
    CC3100_InterruptEnable();

    return NONOS_RET_OK;
}


int spi_Write(Fd_t fd, unsigned char *pBuff, int len)
{
    int len_to_return = len;
    unsigned long ulDummy;

    ASSERT_CS();

    while(len)
    {
        while(SSIDataPutNonBlocking(SSI2_BASE, (unsigned long)*pBuff) != TRUE);
        while(SSIDataGetNonBlocking(SSI2_BASE, &ulDummy) != TRUE);
        pBuff++;
        len--;
    }
    DEASSERT_CS();

    return len_to_return;
}


int spi_Read(Fd_t fd, unsigned char *pBuff, int len)
{
    int i = 0;
    unsigned long ulBuff;

    ASSERT_CS();

    for(i=0; i< len; i++)
    {
        while(SSIDataPutNonBlocking(SSI2_BASE, 0xFF) != TRUE);
        while(SSIDataGetNonBlocking(SSI2_BASE, &ulBuff) != TRUE);
        pBuff[i] = (unsigned char)ulBuff;
    }
    DEASSERT_CS();

    return len;
}
#endif /* SL_IF_TYPE_UART */
