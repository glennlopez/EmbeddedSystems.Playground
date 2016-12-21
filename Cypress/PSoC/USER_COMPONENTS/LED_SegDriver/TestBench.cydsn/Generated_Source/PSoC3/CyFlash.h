/******************************************************************************
* File Name: CyFlash.h
* Version 2.40
*
*  Description:
*   Provides the function definitions for the FLASH/EEPROM.
*
*  Note: 
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(__CYFLASH_H__)
#define __CYFLASH_H__

#include <CYTYPES.H>
#include <CYLIB.H>
#include <CYSPC.H>

extern uint8 dieTemperature[2];

/***************************************
* Conditional Compilation Parameters
***************************************/
    
#if !defined(CYDEV_FLS_BASE)
    #define CYDEV_FLS_BASE    CYDEV_FLASH_BASE
#endif

/***************************************
*     Function Prototypes
***************************************/
/* Flash Functions */
void CyFlash_Start(void) ;
void CyFlash_Stop(void) ;
cystatus CySetTemp(void) ;
cystatus CySetFlashEEBuffer(uint8 * buffer) ;
cystatus CyWriteRowFull(uint8 arrayId, uint16 rowNumber, uint8 * rowData, uint16 rowSize) ;
cystatus CyWriteRowData(uint8 arrayId, uint16 rowAddress, uint8 * rowData) ;
#if (CYDEV_ECC_ENABLE == 0 && CYDEV_CONFIGURATION_ECC == 0)
    cystatus CyWriteRowConfig(uint8 arrayId, uint16 rowAddress, uint8 * rowECC) ;
#endif
void CyFlash_SetWaitCycles(uint8 freq) ;

/* EEPROM Functions */
#if (CY_PSOC3_ES3 || CY_PSOC5_ES2)
    void CyEEPROM_Start(void) ;
    void CyEEPROM_Stop(void) ;    
#endif
void CyEEPROM_ReadReserve(void) ;
void CyEEPROM_ReadRelease(void) ;


/***************************************
*     Registers
***************************************/

#define FLASH_SIZE                  CYDEV_FLS_SIZE
#define FLASH_SIZEOF_SECTOR         CYDEV_FLS_SECTOR_SIZE
#define FLASH_NUMBER_ROWS           (CYDEV_FLS_SIZE / CYDEV_FLS_ROW_SIZE)
#define FLASH_NUMBER_SECTORS        (CYDEV_FLS_SIZE / CYDEV_FLS_SECTOR_SIZE)

#define EEPROM_SIZE                 CYDEV_EE_SIZE
#define EEPROM_SIZEOF_SECTOR        EEPROM_SIZE
#define EEPROM_NUMBER_ROWS          (EEPROM_SIZE / CYDEV_EEPROM_ROW_SIZE)
#define EEPROM_NUMBER_SECTORS       (CYDEV_EE_SIZE / EEPROM_SIZEOF_SECTOR)

/* Power Mode Registers */
#if (CY_PSOC3_ES2 || CY_PSOC5_ES1)
    #define PM_ACT_EEFLASH          ((reg8 *) CYREG_PM_ACT_CFG0)
    #define PM_STBY_EEFLASH         ((reg8 *) CYREG_PM_STBY_CFG0)
#endif
#if (CY_PSOC3_ES3 || CY_PSOC5_ES2)
    #define PM_ACT_EE_PTR             ((reg8 *) CYREG_PM_ACT_CFG12)
    #define PM_STBY_EE_PTR            ((reg8 *) CYREG_PM_STBY_CFG12)
    #define PM_ACT_FLASH_PTR          ((reg8 *) CYREG_PM_ACT_CFG12)
    #define PM_STBY_FLASH_PTR         ((reg8 *) CYREG_PM_STBY_CFG12)    
#endif

/* Cache Control Register */
#if (CY_PSOC3_ES2 || CY_PSOC3_ES3)
    #define FLASH_CYCLES_PTR          ((reg8 *) CYREG_CACHE_CR)
#endif
#if (CY_PSOC5_ES1 || CY_PSOC5_ES2)
    #define FLASH_CYCLES_PTR          ((reg8 *) CYREG_CACHE_CC_CTL)
#endif
#define AHUB_EE_REQ_ACK_PTR           ((reg8 *) CYREG_SPC_EE_SCR)


/***************************************
*     Register Constants
***************************************/

#define ECC_ADDR                    0x80u

/* Power Mode Masks */
#if (CY_PSOC3_ES2 || CY_PSOC5_ES1)
    #define PM_FLASH_EE_MASK        0x80u
#endif
#if (CY_PSOC3_ES3 || CY_PSOC5_ES2)
    #define PM_EE_MASK        0x10u
    #define PM_FLASH_MASK     0x01u
#endif

/* Frequency Constants */
#if (CY_PSOC3_ES2)
    #define LESSER_OR_EQUAL_24MHz 0x01u
    #define LESSER_OR_EQUAL_48MHz 0x02u
    #define GREATER_48MHz         0x03u
#endif    
#if (CY_PSOC3_ES3)
    #define LESSER_OR_EQUAL_22MHz 0x01u
    #define LESSER_OR_EQUAL_44MHz 0x02u
    #define GREATER_44MHz         0x03u
#endif
#if (CY_PSOC5_ES1)
    #define LESSER_OR_EQUAL_16MHz 0x01u
    #define LESSER_OR_EQUAL_33MHz 0x02u
    #define LESSER_OR_EQUAL_50MHz 0x03u
    #define GREATER_51MHz         0x00u
#endif

#define FLASH_CYCLES_MASK_SHIFT     0x06u
#define FLASH_CYCLES_MASK           (0x03u << FLASH_CYCLES_MASK_SHIFT)

/***************************************
*       Type defines
***************************************/

/* Default values for getting temperature. */
#define TEMP_NUMBER_OF_SAMPLES  0x1u
#define TEMP_TIMER_PERIOD       0xFFFu
#define TEMP_CLK_DIV_SELECT     0x4u
#define NUM_SAMPLES             (1 << (TEMP_NUMBER_OF_SAMPLES))
#define SPC_CLK_PERIOD          120 /* nano sec. */
#define CY_SYS_ns_PER_TICK      1000
#define FRM_EXEC_TIME           (1000) /* In nano seconds. */
#define GET_TEMP_TIME           (1 << (NUM_SAMPLES + 1)) * \
                                (SPC_CLK_PERIOD * TEMP_CLK_DIV_SELECT) * \
                                TEMP_TIMER_PERIOD + \
                                FRM_EXEC_TIME
#define TEMP_MAX_WAIT           ((GET_TEMP_TIME  ) / CY_SYS_ns_PER_TICK) /* In system ticks. */



/* __CYFLASH_H__ */
#endif
