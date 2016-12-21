/*******************************************************************************
* File Name: UART_1_BOOT.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the bootloader
*  communication interface of SCB component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_UART_1_H)
#define CY_SCB_BOOT_UART_1_H

#include "UART_1_PVT.h"

#if (UART_1_SCB_MODE_I2C_INC)
    #include "UART_1_I2C.h"
#endif /* (UART_1_SCB_MODE_I2C_INC) */

#if (UART_1_SCB_MODE_EZI2C_INC)
    #include "UART_1_EZI2C.h"
#endif /* (UART_1_SCB_MODE_EZI2C_INC) */

#if (UART_1_SCB_MODE_SPI_INC || UART_1_SCB_MODE_UART_INC)
    #include "UART_1_SPI_UART.h"
#endif /* (UART_1_SCB_MODE_SPI_INC || UART_1_SCB_MODE_UART_INC) */


/***************************************
*        Function Prototypes
***************************************/

/* Bootloader communication interface enable */
#define UART_1_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_1) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#if (UART_1_SCB_MODE_I2C_INC)

    #define UART_1_I2C_BTLDR_COMM_ENABLED     (UART_1_BTLDR_COMM_ENABLED && \
                                                            (UART_1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_1_I2C_SLAVE_CONST))

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_1_I2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_1_I2CCyBtldrCommStart(void);
    void UART_1_I2CCyBtldrCommStop (void);
    void UART_1_I2CCyBtldrCommReset(void);
    cystatus UART_1_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_1_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define UART_1_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define UART_1_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define UART_1_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (uint16) (b)) ? \
                                                                    ((uint32) (a)) : ((uint32) (b)) )
    #define UART_1_WAIT_1_MS                      (1u)
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_1_I2C_BTLDR_COMM_ENABLED) */

#endif /* (UART_1_SCB_MODE_I2C_INC) */


#if (UART_1_SCB_MODE_EZI2C_INC)

    /* Provide EMPTY bootloader communication functions. EZI2C is NOT supported yet */
    #define UART_1_EZI2C_BTLDR_COMM_ENABLED   (UART_1_BTLDR_COMM_ENABLED && \
                                                         UART_1_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_1_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_1_EzI2CCyBtldrCommStart(void);
    void UART_1_EzI2CCyBtldrCommStop (void);
    void UART_1_EzI2CCyBtldrCommReset(void);
    cystatus UART_1_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_1_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_1_EZI2C_BTLDR_COMM_ENABLED) */

#endif /* (UART_1_SCB_MODE_EZI2C_INC) */

#if (UART_1_SCB_MODE_SPI_INC || UART_1_SCB_MODE_UART_INC)
    /* Provide EMPTY bootloader communication functions. SPI and UART is NOT supported yet */
    #define UART_1_SPI_BTLDR_COMM_ENABLED     (UART_1_BTLDR_COMM_ENABLED && \
                                                        UART_1_SCB_MODE_UNCONFIG_CONST_CFG)

    #define UART_1_UART_BTLDR_COMM_ENABLED    (UART_1_BTLDR_COMM_ENABLED && \
                                                        UART_1_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_1_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UART_1_SpiCyBtldrCommStart(void);
    void UART_1_SpiCyBtldrCommStop (void);
    void UART_1_SpiCyBtldrCommReset(void);
    cystatus UART_1_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_1_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_1_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_1_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UART_1_UartCyBtldrCommStart(void);
    void UART_1_UartCyBtldrCommStop (void);
    void UART_1_UartCyBtldrCommReset(void);
    cystatus UART_1_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_1_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_1_UART_BTLDR_COMM_ENABLED) */

#endif /* (UART_1_SCB_MODE_SPI_INC || UART_1_SCB_MODE_UART_INC) */

#if !defined (UART_1_I2C_BTLDR_COMM_ENABLED)
    #define UART_1_I2C_BTLDR_COMM_ENABLED     (0u)
#endif /* (UART_1_I2C_BTLDR_COMM_ENABLED) */

#if !defined (UART_1_EZI2C_BTLDR_COMM_ENABLED)
    #define UART_1_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_1_EZI2C_BTLDR_COMM_ENABLED) */

#if !defined (UART_1_SPI_BTLDR_COMM_ENABLED)
    #define UART_1_SPI_BTLDR_COMM_ENABLED     (0u)
#endif /* (UART_1_SPI_BTLDR_COMM_ENABLED) */

#if !defined (UART_1_UART_BTLDR_COMM_ENABLED)
    #define UART_1_UART_BTLDR_COMM_ENABLED    (0u)
#endif /* (UART_1_UART_BTLDR_COMM_ENABLED) */

/* Bootloader enabled condition for each mode */
#define UART_1_BTLDR_COMM_MODE_ENABLED    (UART_1_I2C_BTLDR_COMM_ENABLED   || \
                                                     UART_1_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UART_1_SPI_BTLDR_COMM_ENABLED   || \
                                                     UART_1_UART_BTLDR_COMM_ENABLED)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_1_BTLDR_COMM_ENABLED)
    #if (UART_1_BTLDR_COMM_MODE_ENABLED)
        /* Bootloader physical layer functions */
        void UART_1_CyBtldrCommStart(void);
        void UART_1_CyBtldrCommStop (void);
        void UART_1_CyBtldrCommReset(void);
        cystatus UART_1_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UART_1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UART_1_BTLDR_COMM_MODE_ENABLED) */

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_1)
        #define CyBtldrCommStart    UART_1_CyBtldrCommStart
        #define CyBtldrCommStop     UART_1_CyBtldrCommStop
        #define CyBtldrCommReset    UART_1_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_1_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_1_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_1) */
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_1_BTLDR_COMM_ENABLED) */

#endif /* (CY_SCB_BOOT_UART_1_H) */

/* [] END OF FILE */
