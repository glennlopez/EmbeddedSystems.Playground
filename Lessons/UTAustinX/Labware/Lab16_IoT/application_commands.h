//*****************************************************************************
//
// application_commands.h - Prototypes for the evaluation board
//  command line utils.
//
// Copyright (c) 2014 Texas Instruments Incorporated.  All rights reserved.
// TI Information - Selective Disclosure
//
//*****************************************************************************

#ifndef __APPLICATION_COMMANDS_H__
#define __APPLICATION_COMMANDS_H__

//*****************************************************************************
//
// Defines for the command line argument parser provided as a standard part of
// TivaWare.
//
//*****************************************************************************
#define CMDLINE_MAX_ARGS (3)

//*****************************************************************************
//
// Maximum size of command line command buffer.
//
//*****************************************************************************
#define MAX_COMMAND_SIZE (128)

//*****************************************************************************
//
// Success / Fail defines
//
//*****************************************************************************
#define COMMAND_SUCCESS (0)
#define COMMAND_FAIL    (-1)

//*****************************************************************************
//
// Sentinel use to make code easier to understand
//
//*****************************************************************************
#define SENTINEL_EMPTY 0xFFFFFFFF

//*****************************************************************************
//
// CC3000 Deffinitions
//
//*****************************************************************************
#define PLATFORM_VERSION                            (5)

#define UART_COMMAND_CC3000_SIMPLE_CONFIG_START     (0x31)
#define UART_COMMAND_CC3000_CONNECT                 (0x32)
#define UART_COMMAND_SOCKET_OPEN                    (0x33)
#define UART_COMMAND_SEND_DATA                      (0x34)
#define UART_COMMAND_RCV_DATA                       (0x35)
#define UART_COMMAND_BSD_BIND                       (0x36)
#define UART_COMMAND_SOCKET_CLOSE                   (0x37)
#define UART_COMMAND_IP_CONFIG                      (0x38)
#define UART_COMMAND_CC3000_DISCONNECT              (0x39)
#define UART_COMMAND_CC3000_DEL_POLICY              (0x61)
#define UART_COMMAND_SEND_DNS_ADVERTIZE             (0x62)

#define CC3000_APP_BUFFER_SIZE                      (255)
#define CC3000_RX_BUFFER_OVERHEAD_SIZE              (20)

#define DISABLE                                     (0)
#define ENABLE                                      (1)
#define SL_VERSION_LENGTH                           (11)
#define NETAPP_IPCONFIG_MAC_OFFSET                  (20)

//*****************************************************************************
//
// Declaration for the callback functions that will implement the command line
// functionality.  These functions get called by the command line interpreter
// when the corresponding command is typed into the command line.
//
//*****************************************************************************
extern int CMD_help (int argc, char **argv);
extern int CMD_smartConfig (int argc, char **argv);
extern int CMD_connect (int argc, char **argv);
extern int CMD_socketOpen (int argc, char **argv);
extern int CMD_sendData (int argc, char **argv);
extern int CMD_receiveData (int argc, char **argv);
extern int CMD_bind (int argc, char **argv);
extern int CMD_socketClose (int argc, char **argv);
extern int CMD_ipConfig (int argc, char **argv);
extern int CMD_disconnect (int argc, char **argv);
extern int CMD_deletePolicy (int argc, char **argv);
extern int CMD_mdnsadvertise (int argc, char **argv);
extern int CMD_cc3000reset (int argc, char **argv);
extern int CMD_ping (int argc, char **argv);

#endif // __APPLICATION_COMMANDS_H__
