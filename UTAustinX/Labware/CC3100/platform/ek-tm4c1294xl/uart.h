//
// uart.h - tiva-c launchpad uart interface implementation. Please note that
//                  UART will NOT work with the Tiva Connected Launchpad.
//                  This is because there are no UART CTS / RTS lines to 
//                  connect to on this board. Please use SSI instead.
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//

#ifdef SL_IF_TYPE_UART
#error "UART mode not supported on the connected launchpad"
#error "UART CTS and RTS lines are not provided on the EK-TM4c1294xl board"
#error "please use SSI mode instead."
#ifndef __UART_H__

#define __UART_H__


#ifdef __cplusplus
extern "C" {
#endif


#define UART_IF_OPEN_FLAG_NONE    0
#define UART_IF_OPEN_FLAG_RE_OPEN 1


#if defined(CC3100_USE_BOOSTERPACK1)
//*****************************************************************************
//
// Pins used with the BoosterPack1 connector.
//
//*****************************************************************************
#define CC3100_UART_BASE            UART7_BASE
#define CC3100_UART_SYSPERIPH       SYSCTL_PERIPH_UART7

#endif

#if defined(CC3100_USE_BOOSTERPACK2)
//*****************************************************************************
//
// Pins used with the BoosterPack2 connector.
//
//*****************************************************************************
#define CC3100_UART_BASE            UART6_BASE
#define CC3100_UART_SYSPERIPH       SYSCTL_PERIPH_UART6

#endif

/*!
    \brief   type definition for the uart channel file descriptor

    \note    On each porting or platform the type could be whatever is needed
            - integer, pointer to structure etc.
*/
typedef unsigned int Fd_t;


/*!
    \brief open uart communication port with baud rate 115200 to be used for 
	       communicating with a SimpleLink device

    Given an interface name and option flags, this function opens the UART
    communication port and creates a file descriptor. This file descriptor can
    be used afterwards to read and write data from and to this specific uart
    channel.
    The all uart attributes are all set to hardcoded values in this function.

    \param[in]      ifName    -    points to the interface name/path. The
                    interface name is an optional attributes that the simple
                    link driver receives on opening the device. in systems that
                    the uart channel is not implemented as part of the os device
                    drivers, this parameter could be NULL.
    \param[in]      flags     -    option flags

    \return         upon successful completion, the function shall open the uart
                    channel and return a non-negative integer representing the
                    file descriptor. Otherwise, -1 shall be returned

    \sa             uart_Close , uart_Read , uart_Write
    \note
    \warning
*/

Fd_t uart_Open(char *ifName, unsigned long flags);


/*!
    \brief closes an opened uart communication port

    \param[in]      fd    -     file descriptor of an opened UART channel

    \return         upon successful completion, the function shall return 0.
                    Otherwise, -1 shall be returned

    \sa             uart_Open
    \note
    \warning
*/
int uart_Close(Fd_t fd);


/*!
    \brief attempts to read up to len bytes from UART channel into a buffer
           starting at pBuff.

    \param[in]      fd     -    file descriptor of an opened UART channel

    \param[in]      pBuff  -    points to first location to start writing the
                    data

    \param[in]      len    -    number of bytes to read from the UART channel

    \return         upon successful completion, the function shall return 0.
                    Otherwise, -1 shall be returned

    \sa             uart_Open , uart_Write
    \note
    \warning
*/
int uart_Read(Fd_t fd, unsigned char *pBuff, int len);


/*!
    \brief attempts to write up to len bytes to the UART channel

    \param[in]      fd        -    file descriptor of an opened UART channel

    \param[in]      pBuff     -    points to first location to start getting the
                    data from

    \param[in]      len       -    number of bytes to write to the UART channel

    \return         upon successful completion, the function shall return 0.
                    Otherwise, -1 shall be returned

    \sa             uart_Open , uart_Read
    \note           This function could be implemented as zero copy and return
                    only upon successful completion of writing the whole buffer,
                    but in cases that memory allocation is not too tight, the
                    function could copy the data to internal buffer, return
                    back and complete the write in parallel to other activities
                    as long as the other UART activities would be blocked until
                    the entire buffer write would be completed
    \warning
*/
int uart_Write(Fd_t fd, unsigned char *pBuff, int len);


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif  /* __UART_H__ */
#endif /* SL_IF_TYPE_UART */
