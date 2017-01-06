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
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

int spi_Close(Fd_t fd)
{
    /* Disable WLAN Interrupt ... */
    CC3100_InterruptDisable();

    return 0;
}

Fd_t spi_Open(char *ifName, unsigned long flags)
{
    //
    // Enable required SSI and GPIO peripherals.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI_PORT);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_IRQ_PORT);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_nHIB_PORT);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI_BASE);

    //
    // Set pin muxing to route the SPI signals to the relevant pins.
    //
    GPIOPinConfigure(SPI_CLK_MUX_SEL);
    GPIOPinConfigure(SPI_RX_MUX_SEL);
    GPIOPinConfigure(SPI_TX_MUX_SEL);
    //GPIOPinConfigure(GPIO_PB5_SSI2FSS);

    //
    // Configure the appropriate pins to be SSI instead of GPIO
    //
    GPIOPinTypeSSI(SPI_PORT,(SPI_TX_PIN | SPI_RX_PIN | SPI_CLK_PIN));

    //
    // Ensure that the SSI is disabled before making any configuration
    // changes.
    //
    SSIDisable(SPI_BASE);
    
    //
    // Configure SSI with 8 bit data, Polarity '0', Phase '1' and clock
    // frequency of 4Mhz.
    //
    SSIConfigSetExpClk(SPI_BASE, g_ui32SysClock, SSI_FRF_MOTO_MODE_0,
            SSI_MODE_MASTER, 4000000, 8);

    // Configure CS  and nHIB/Enable lines (CS High, nHIB Low)
    GPIOPinTypeGPIOOutput(SPI_CS_PORT, SPI_CS_PIN);
    GPIOPinTypeGPIOOutput(SPI_GPIO_nHIB_BASE, SPI_nHIB_PIN); 
    GPIOPinWrite(SPI_GPIO_nHIB_BASE,SPI_nHIB_PIN, PIN_LOW); // not necesary on cc3100
    GPIOPinWrite(SPI_CS_PORT,SPI_CS_PIN, PIN_HIGH);

    //
    // Enable the SSI now that configuration is complete.
    //
    SSIEnable(SPI_BASE);

    //
    // configure host IRQ line
    //
    GPIOPinTypeGPIOInput(SPI_GPIO_IRQ_BASE, SPI_IRQ_PIN);
    GPIOPadConfigSet(SPI_GPIO_IRQ_BASE, SPI_IRQ_PIN, GPIO_STRENGTH_2MA,
                     GPIO_PIN_TYPE_STD_WPD);
    GPIOIntTypeSet(SPI_GPIO_IRQ_BASE, SPI_IRQ_PIN, GPIO_RISING_EDGE);
    GPIOIntClear(SPI_GPIO_IRQ_BASE,SPI_IRQ_PIN);
    GPIOIntDisable(SPI_GPIO_IRQ_BASE,SPI_IRQ_PIN);
    IntEnable(INT_GPIO_SPI);

    IntMasterEnable();

    /* 1 ms delay */
    ROM_SysCtlDelay( (g_ui32SysClock/(3*1000))*1 );

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
        while(SSIDataPutNonBlocking(SPI_BASE, (unsigned long)*pBuff) != TRUE);
        while(SSIDataGetNonBlocking(SPI_BASE, &ulDummy) != TRUE);
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
        while(SSIDataPutNonBlocking(SPI_BASE, 0xFF) != TRUE);
        while(SSIDataGetNonBlocking(SPI_BASE, &ulBuff) != TRUE);
        pBuff[i] = (unsigned char)ulBuff;
    }
    DEASSERT_CS();

    return len;
}
#endif /* SL_IF_TYPE_UART */
