/*******************************************************************************
* File Name: CySpc.c  
* Version 2.40
*
*  Description:
*   Provides definitions for the System Performance Component API.
*   The SPC functions are not meant to be called directly by the user application.
*
*  Note:
*
*   
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#if !defined(__CYSPC_H__)
#define __CYSPC_H__


#include <cytypes.h>
#include <CyLib.h>
#include <cydevice_trm.h>


/* Register to send command to the System Performance Controler from the CPU. */
#define SPC_CPU_DATA                    ((reg8 *) CYREG_SPC_CPU_DATA)

/* Register to send command to the System Performance Controler from the DMAC. */
#define SPC_DMA_DATA                    ((reg8 *) CYREG_SPC_DMA_DATA)

/* Command Codes. */
#define SPC_CMD_LD_BYTE                 0x00 /* Loads a single byte of data into the volatile latch of an NVL*/
#define SPC_CMD_LD_MULTI_BYTE           0x01 /* Loads 1 to 32 bytes of data into the row latch of a Flash/EEPROM array.*/
#define SPC_CMD_LD_ROW                  0x02 /* Loads a row of data into the row latch of a Flash/EEPROM array.*/
#define SPC_CMD_RD_BYTE                 0x03 /* Returns a byte from user space of Flash/EEPROM/NVL*/
#define SPC_CMD_RD_MULTI_BYTE           0x04 /* Returns 1 to 256 bytes from user space of Flash/EEPROM. Doesn't span row boundaries.*/
#define SPC_CMD_WR_ROW                  0x05 /* Erases then programs a row in Flash/EEPROM with data in row latch.   */
#define SPC_CMD_WR_USER_NVL             0x06 /* Writes all SONOS cells in a User NVL with the corresponding values in its volatile latches. */
#define SPC_CMD_PRG_ROW                 0x07 /* Programs a row in Flash/EEPROM with the data in the row latch. */
#define SPC_CMD_ER_SECTOR               0x08 /* Erases all data in the addressed sector (block of 64 rows) */
#define SPC_CMD_ER_ALL                  0x09 /* Erases all user data in all Flash arrays followed by erasing all protection data.*/
#define SPC_CMD_RD_HIDDEN               0x0A /* Returns 1 row of data from the Flash hidden rows. Cannot return rows with Smart Write code in them. */
#define SPC_CMD_PRG_PROTECT             0x0B /* Program flash protection bits with data in row latch. Set address after last byte to non-zero if any other bits are set.*/
#define SPC_CMD_CHECKSUM                0x0C /* Compute and return a 4 byte checksum for flash rows 'N' through 'M'.*/
#define SPC_CMD_DWNLD_ALGORITHM         0x0D /* Downloads the Smart Write algorithm and parameters from the Flash hidden rows to the SPC internal SRAMs.*/
#define SPC_CMD_GET_TEMP                0x0E /* Returns the internal die temperature*/
#define SPC_CMD_GET_ADC                 0x0F /* Configures and runs the ADC function and returns the digital output value.*/
#define SPC_CMD_RD_NVL_VOLATILE         0x10 /* Reads a value out of the volatile latch of the addressed byte.*/
#define SPC_CMD_SETUP_TS                0x11 /* Sets up the temperature sensor to drive voltage to external resources.*/
#define SPC_CMD_DISABLE_TS              0x12 /* Disables the temperature sensor from driving its voltage to external resources.*/

/* Size in bytes of the specific commands. */
#define SIZEOF_CMD_ER_SECTOR            2
#define SIZEOF_CMD_LOAD_MBYTE           4
#define SIZEOF_CMD_LOAD_ROW             1
#define SIZEOF_CMD_READ_MBYTE           5
#define SIZEOF_CMD_PRGM_ROW             3
#define SIZEOF_CMD_WR_ROW               5
#define SIZEOF_CMD_GET_TEMP             4
#define SIZEOF_CMD_SETUP_TS             4
#define SIZEOF_CMD_DISABLE_TS           0

/* SPC status register. */
#define SPC_STATUS                      ((reg8 *) CYREG_SPC_SR)
#define CySpcReadStatus                 (*SPC_STATUS >> 2)

/* SPC bit feilds. */
#define SPC_DATA_READY                  (1 << 0)    /* Indicates whether or not the SPC has data that is ready to be read from the SPC CPU or DMA Data Register. */
#define SPC_SPC_IDLE                    (1 << 1)    /* Indicates whether or not the SPC is currently executing an instruction. */
#define SPC_STATUS_CODE_MASK            (0x3F << 2) /* The Status Code represents the exit status of the last executed SPC instruction. */

/* Status codes for the SPC. */
#define SPC_SUCCESS                     0x00   /* Operation Successful */
#define SPC_FAILURE_INVALID_ARRAY_ID    0x01   /* Invalid Array ID for given command */
#define SPC_FAILURE_INVALID_2BYTEKEY    0x02   /* Invalid 2-byte key */
#define SPC_FAILURE_ARRAY_ASLEEP        0x03   /* Addressed Array is Asleep */
#define SPC_FAILURE_EXTERN_ACCESS       0x04   /* External Access Failure (SPC is not in external access mode) */
#define SPC_FAILURE_INVALID_NUMBER      0x05   /* Invalid 'N' Value for given command */
#define SPC_FAILURE_TEST_MODE           0x06   /* Test Mode Failure (SPC is not in test mode) */
#define SPC_FAILURE_ALG_CSUM            0x07   /* Smart Write Algorithm Checksum Failure */
#define SPC_FAILURE_PARAM_CSUM          0x08   /* Smart Write Parameter Checksum Failure */
#define SPC_FAILURE_PROTECTION          0x09   /* Protection Check Failure: protection settings are in a state which prevents the given command from executing */
#define SPC_FAILURE_ADDRESS_PARAM       0x0A   /* Invalid Address parameter for the given command */
#define SPC_FAILURE_COMMAND_CODE        0x0B   /* Invalid Command Code */
#define SPC_FAILURE_ROW_ID              0x0C   /* Invalid Row ID parameter for given command */
#define SPC_FAILURE_TADC_INPUT          0x0D   /* Invalid input value for Get Temp & Get ADC commands */

#define CYRET_SPC_ERROR_MASK            0x80   /* Error mask */

/* 0E - 1B  Reserved */
/* #define 1C-3F    Smart Write Warning/Error codes (TBD) */

/* Software only value, not a valid register value. */
#define SPC_FAILURE_BUSSY               0xFF

/* Array id's. */
#define FIRST_FLASH_ARRAYID             0x00
#define LAST_FLASH_ARRAYID              0x3F
#define FIRST_EE_ARRAYID                0x40
#define LAST_EE_ARRAYID                 0x7F


#define SIZEOF_ECC_ROW                  CYDEV_ECC_ROW_SIZE
#define SIZEOF_FLASH_ROW                CYDEV_FLS_ROW_SIZE
#define SIZEOF_EEPROM_ROW               CYDEV_EEPROM_ROW_SIZE

#define SPC_KEY_ONE                 0xB6
#define SPC_KEY_TWO(x)              ((uint8) (((uint16) 0xD3u) + ((uint16) (x))))

/* 
 * These macros are private to SPC APIs and also SPC APIs are cy_boot's private API */
#define FLASH_SECTOR_ADDRESS(x)     (0xFF & (x))
#define EEPROM_ROW_MASK             ((CYDEV_EE_SIZE >> 4) - 1)
#define EEPROM_SECTOR_ADDRESS(x)    (0x7F & (x))

#define PM_ACT_SPC                  ((reg8 *) CYREG_PM_ACT_CFG0)
#define PM_STBY_SPC                 ((reg8 *) CYREG_PM_STBY_CFG0)
#define PM_SPC_MASK                 (1 << 3)


cystatus CySpcLock(void);
void CySpcUnlock(void);
cystatus CySpcCreateCmdLoadMultiByte(uint8 array, uint16 address, uint16 number);
cystatus CySpcCreateCmdLoadRow(uint8 array);
cystatus CySpcCreateCmdReadMultiByte(uint8 array, uint8 ecc, uint16 address, uint8 number);
cystatus CySpcCreateCmdWriteRow(uint8 array, uint16 address, uint8 tempPolarity, uint8 tempMagnitute);
cystatus CySpcCreateCmdProgramRow(uint8 array, uint16 address);
cystatus CySpcCreateCmdEraseSector(uint8 array, uint16 address);
cystatus CySpcCreateCmdGetTemp(uint8 numSamples, uint16 timerPeriod, uint8 clkDivSelect);
cystatus CySpcCreateCmdSetupTs(uint8 SeqSelect, uint8 SeqFreeze, uint8 ClkDivSel, uint8 CurvCompEnable);
cystatus CySpcCreateCmdDisableTs(void);
cystatus CySpcWriteCommand(uint8 * parameters, uint16 size);
uint8 CySpcReadData(uint8 * buffer, uint8 size) ;
void CySpcActivePower(uint8 state) ;
void CySpcStandbyPower(uint8 state) ;


#endif /*__CYSPC_H__*/
