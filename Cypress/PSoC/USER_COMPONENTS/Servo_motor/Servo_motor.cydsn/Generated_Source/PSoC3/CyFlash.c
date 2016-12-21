/*******************************************************************************
* File Name: CyFlash.c
* Version 3.20
*
*  Description:
*   Provides an API for the FLASH/EEPROM.
*
*  Note:
*   This code is endian agnostic.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyFlash.h"


/*******************************************************************************
* Holds die temperature, updated by CySetTemp(). Used for flash writting.
* The first byte is the sign of the temperature (0 = negative, 1 = positive).
* The second byte is the magnitude.
*******************************************************************************/
uint8 dieTemperature[CY_FLASH_DIE_TEMP_DATA_SIZE];

#if(CYDEV_ECC_ENABLE == 0)
    static uint8 * rowBuffer = 0;
#endif  /* (CYDEV_ECC_ENABLE == 0) */


/*******************************************************************************
* Function Name: CyFlash_Start
********************************************************************************
*
* Summary:
*  Enable the EEPROM/Flash.
*
*  Note: For PSoC 5, this will enable both Flash and EEPROM. For PSoC 3 and
*  PSOC 5LP  this will enable only Flash.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyFlash_Start(void) 
{
    #if(CY_PSOC5A)

        /* Active Power Mode */
        *PM_ACT_EEFLASH |= PM_FLASH_EE_MASK;

        /* Standby Power Mode */
        *PM_STBY_EEFLASH |= PM_FLASH_EE_MASK;

    #endif  /* (CY_PSOC5A) */

    #if(CY_PSOC3 || CY_PSOC5LP)

        /* Active Power Mode */
        *PM_ACT_FLASH_PTR |= PM_FLASH_MASK;

        /* Standby Power Mode */
        *PM_STBY_FLASH_PTR |= PM_FLASH_MASK;

    #endif  /* (CY_PSOC3 || CY_PSOC5LP) */
}


/*******************************************************************************
* Function Name: CyFlash_Stop
********************************************************************************
*
* Summary:
*  Disable the EEPROM/Flash.
*
*  Note:
*  PSoC5 ES1:        disable both Flash and EEPROM.
*  PSoC3 ES3/PSOC5A: disable only Flash.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This setting is ignored as long as the CPU is currently running.  This will
*  only take effect when the CPU is later disabled.
*
*******************************************************************************/
void CyFlash_Stop(void) 
{
    #if (CY_PSOC5A)

        /* Active Power Mode */
        *PM_ACT_EEFLASH &= ~PM_FLASH_EE_MASK;

        /* Standby Power Mode */
        *PM_STBY_EEFLASH &= ~PM_FLASH_EE_MASK;

    #endif  /* (CY_PSOC5A) */

    #if (CY_PSOC3 || CY_PSOC5LP)

        /* Active Power Mode */
        *PM_ACT_FLASH_PTR &= ~PM_FLASH_MASK;

        /* Standby Power Mode */
        *PM_STBY_FLASH_PTR &= ~PM_FLASH_MASK;

    #endif  /* (CY_PSOC3 || CY_PSOC5LP) */
}


/*******************************************************************************
* Function Name: CySetTempInt
********************************************************************************
*
* Summary:
*  Sends a command to the SPC to read the die temperature. Sets a global value
*  used by the Write functions. This function must be called once before
*  executing a series of Flash writing functions.
*
* Parameters:
*  None
*
* Return:
*  status:
*   CYRET_SUCCESS - if successful
*   CYRET_LOCKED  - if Flash writing already in use
*   CYRET_UNKNOWN - if there was an SPC error
*
*******************************************************************************/
cystatus CySetTempInt(void) 
{
    cystatus status;

    /* Make sure SPC is powered */
    CySpcStart();

    /* Plan for failure. */
    status = CYRET_UNKNOWN;

    if(CySpcLock() == CYRET_SUCCESS)
    {
        /* Write the command. */
        #if(CY_PSOC5A)
            if(CYRET_STARTED == CySpcGetTemp(TEMP_NUMBER_OF_SAMPLES, TEMP_TIMER_PERIOD, TEMP_CLK_DIV_SELECT))
        #else
            if(CYRET_STARTED == CySpcGetTemp(TEMP_NUMBER_OF_SAMPLES))
        #endif  /* (CY_PSOC5A) */
            {
                do
                {
                    if(CySpcReadData(dieTemperature, CY_FLASH_DIE_TEMP_DATA_SIZE) == CY_FLASH_DIE_TEMP_DATA_SIZE)
                    {
                        status = CYRET_SUCCESS;

                        while(CY_SPC_BUSY)
                        {
                            /* Spin until idle. */
                            CyDelayUs(1u);
                        }
                        break;
                    }

                } while(CY_SPC_BUSY);
            }

            CySpcUnlock();
    }
    else
    {
        status = CYRET_LOCKED;
    }

    return (status);
}


/*******************************************************************************
* Function Name: CySetTemp
********************************************************************************
*
* Summary:
*  This is a wraparound for CySetTempInt(). It is used to return second
*  successful read of temperature value.
*
* Parameters:
*  None
*
* Return:
*  status:
*   CYRET_SUCCESS if successful.
*   CYRET_LOCKED  if Flash writing already in use
*   CYRET_UNKNOWN if there was an SPC error.
*
*  uint8 dieTemperature[2]:
*   Holds die temperature for the flash writting algorithm. The first byte is
*   the sign of the temperature (0 = negative, 1 = positive). The second byte is
*   the magnitude.
*
*******************************************************************************/
cystatus CySetTemp(void) 
{
    cystatus status = CySetTempInt();

    if(status == CYRET_SUCCESS)
    {
        status = CySetTempInt();
    }

    return (status);
}


/*******************************************************************************
* Function Name: CySetFlashEEBuffer
********************************************************************************
*
* Summary:
*  Sets the user supplied temporary buffer to store SPC data while performing
*  flash and EEPROM commands. This buffer is only necessary when Flash ECC is
*  disabled.
*
* Parameters:
*  buffer:
*   Address of block of memory to store temporary memory. The size of the block
*   of memory is CYDEV_FLS_ROW_SIZE + CYDEV_ECC_ROW_SIZE.
*
* Return:
*  status:
*   CYRET_SUCCESS if successful.
*   CYRET_BAD_PARAM if the buffer is NULL
*
*******************************************************************************/
cystatus CySetFlashEEBuffer(uint8 * buffer) 
{
    cystatus status = CYRET_SUCCESS;

    CySpcStart();

    #if(CYDEV_ECC_ENABLE == 0)

        if(NULL == buffer)
        {
            status = CYRET_BAD_PARAM;
        }
        else if(CySpcLock() != CYRET_SUCCESS)
        {
            status = CYRET_LOCKED;
        }
        else
        {
            rowBuffer = buffer;
            CySpcUnlock();
        }

    #else

        /* To supress the warning */
        buffer = buffer;

    #endif  /* (CYDEV_ECC_ENABLE == 0u) */

    return(status);
}


#if(CYDEV_ECC_ENABLE == 1)

    /*******************************************************************************
    * Function Name: CyWriteRowData
    ********************************************************************************
    *
    * Summary:
    *   Sends a command to the SPC to load and program a row of data in flash.
    *
    * Parameters:
    *  arrayID:
    *   ID of the array to write.
    *  rowAddress:
    *   rowAddress of flash row to program.
    *  rowData:
    *   Array of bytes to write.
    *
    * Return:
    *  status:
    *   CYRET_SUCCESS if successful.
    *   CYRET_LOCKED if the SPC is already in use.
    *   CYRET_CANCELED if command not accepted
    *   CYRET_UNKNOWN if there was an SPC error.
    *
    *******************************************************************************/
    cystatus CyWriteRowData(uint8 arrayId, uint16 rowAddress, uint8 * rowData) 
    {
        uint16 rowSize;
        cystatus status;

        rowSize = (arrayId > CY_SPC_LAST_FLASH_ARRAYID) ? CYDEV_EEPROM_ROW_SIZE : CYDEV_FLS_ROW_SIZE;
        status = CyWriteRowFull(arrayId, rowAddress, rowData, rowSize);

        return(status);
    }

#else

    /*******************************************************************************
    * Function Name: CyWriteRowData
    ********************************************************************************
    *
    * Summary:
    *   Sends a command to the SPC to load and program a row of data in flash.
    *
    * Parameters:
    *  arrayID      : ID of the array to write.
    *  rowAddress   : rowAddress of flash row to program.
    *  rowData      : Array of bytes to write.
    *
    * Return:
    *  status:
    *   CYRET_SUCCESS if successful.
    *   CYRET_LOCKED if the SPC is already in use.
    *   CYRET_CANCELED if command not accepted
    *   CYRET_UNKNOWN if there was an SPC error.
    *
    *******************************************************************************/
    cystatus CyWriteRowData(uint8 arrayId, uint16 rowAddress, uint8 * rowData) 
    {
        uint8 index;
        uint32 offset;
        uint16 rowSize;
        cystatus status;

        rowSize = (arrayId > CY_SPC_LAST_FLASH_ARRAYID) ? \
                    CYDEV_EEPROM_ROW_SIZE : \
                    (CYDEV_FLS_ROW_SIZE + CYDEV_ECC_ROW_SIZE);

        if(rowSize != CYDEV_EEPROM_ROW_SIZE)
        {
            /* Save the ECC area. */
            offset = CYDEV_ECC_BASE + ((uint32) arrayId * CYDEV_ECC_SECTOR_SIZE) +
                    ((uint32) rowAddress * CYDEV_ECC_ROW_SIZE);

            for (index = 0; index < CYDEV_ECC_ROW_SIZE; index++)
            {
                rowBuffer[CYDEV_FLS_ROW_SIZE + index] = CY_GET_XTND_REG8((void CYFAR *)(offset + index));
            }
        }

        /* Copy the rowdata to the temporary buffer. */
        memcpy(rowBuffer, rowData, CYDEV_FLS_ROW_SIZE);

        status = CyWriteRowFull(arrayId, rowAddress, rowBuffer, rowSize);

        return(status);
    }

#endif /* (CYDEV_ECC_ENABLE == 0u) */


#if ((CYDEV_ECC_ENABLE == 0u) && (CYDEV_CONFIGURATION_ECC == 0u))

    /*******************************************************************************
    * Function Name: CyWriteRowConfig
    ********************************************************************************
    *
    * Summary:
    *  Sends a command to the SPC to load and program a row of config data in flash.
    *  This function is only valid for Flash array IDs (not for EEPROM).
    *
    * Parameters:
    *  arrayId:
    *   ID of the array to write
    *  rowAddress:
    *   Address of the sector to erase.
    *  rowData:
    *   Array of bytes to write.
    *
    * Return:
    *  status:
    *   CYRET_SUCCESS if successful.
    *   CYRET_LOCKED if the SPC is already in use.
    *   CYRET_CANCELED if command not accepted
    *   CYRET_UNKNOWN if there was an SPC error.
    *
    *******************************************************************************/
    cystatus CyWriteRowConfig(uint8 arrayId, uint16 rowAddress, uint8 * rowData) 
    {
        uint32 offset;
        uint16 index;
        cystatus status;

        /* Read the existing flash data. */
        offset = CYDEV_FLS_BASE + ((uint32) arrayId * CYDEV_FLS_SECTOR_SIZE) +
            ((uint32) rowAddress * CYDEV_FLS_ROW_SIZE);

        for (index = 0; index < CYDEV_FLS_ROW_SIZE; index++)
        {
            rowBuffer[index] = CY_GET_XTND_REG8((void CYFAR *)(offset + index));
        }

        /* Copy the rowData to the temporary buffer. */
        memcpy(&rowBuffer[CYDEV_FLS_ROW_SIZE], rowData, CYDEV_ECC_ROW_SIZE);

        status = CyWriteRowFull(arrayId, rowAddress, rowBuffer, CYDEV_FLS_ROW_SIZE + CYDEV_ECC_ROW_SIZE);

        return (status);
    }

#endif  /* ((CYDEV_ECC_ENABLE == 0u) && (CYDEV_CONFIGURATION_ECC == 0u)) */



/*******************************************************************************
* Function Name: CyWriteRowFull
********************************************************************************
* Summary:
*   Sends a command to the SPC to load and program a row of data in flash.
*   rowData array is expected to contain Flash and ECC data if needed.
*
* Parameters:
*       arrayId: FLASH or EEPROM array id.
*       rowData: pointer to a row of data to write.
*       rowNumber: Zero based number of the row.
*       rowSize: Size of the row.
*
* Return:
*   CYRET_SUCCESS if successful.
*   CYRET_LOCKED if the SPC is already in use.
*   CYRET_CANCELED if command not accepted
*   CYRET_UNKNOWN if there was an SPC error.
*
*******************************************************************************/
cystatus CyWriteRowFull(uint8 arrayId, uint16 rowNumber, uint8* rowData, uint16 rowSize) \
        
{
    cystatus status;

    if(CySpcLock() == CYRET_SUCCESS)
    {
        /* Load row data into SPC internal latch */
        status = CySpcLoadRow(arrayId, rowData, rowSize);

        if(CYRET_STARTED == status)
        {
            while(CY_SPC_BUSY)
            {
                /* Wait for SPC to finish and get SPC status */
                CyDelayUs(1u);
            }

            /* Hide SPC status */
            if(CY_SPC_STATUS_SUCCESS == CY_SPC_READ_STATUS)
            {
                status = CYRET_SUCCESS;
            }
            else
            {
                status = CYRET_UNKNOWN;
            }

            if(CYRET_SUCCESS == status)
            {
                /* Erase and program flash with the data from SPC interval latch */
                status = CySpcWriteRow(arrayId, rowNumber, dieTemperature[0u], dieTemperature[1u]);

                if(CYRET_STARTED == status)
                {
                    while(CY_SPC_BUSY)
                    {
                        /* Wait for SPC to finish and get SPC status */
                        CyDelayUs(1u);
                    }

                    /* Hide SPC status */
                    if(CY_SPC_STATUS_SUCCESS == CY_SPC_READ_STATUS)
                    {
                        status = CYRET_SUCCESS;
                    }
                    else
                    {
                        status = CYRET_UNKNOWN;
                    }
                }
            }

        }

        CySpcUnlock();
    }
    else
    {
        status = CYRET_LOCKED;
    }

    return(status);
}


/*******************************************************************************
* Function Name: CyFlash_SetWaitCycles
********************************************************************************
*
* Summary:
*  Sets the number of clock cycles the cache will wait before it samples data
*  coming back from Flash. This function must be called before increasing CPU
*  clock frequency. It can optionally be called after lowering CPU clock
*  frequency in order to improve CPU performance.
*
* Parameters:
*  freq:
*   Frequency of operation in Megahertz.
*
* Return:
*  None
*
*******************************************************************************/
void CyFlash_SetWaitCycles(uint8 freq) 
{
    /* Set Flash Cycles bit fields with frequency value */

    #if (CY_PSOC3)

        if (freq <= 22u)
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (LESSER_OR_EQUAL_22MHz << FLASH_CYCLES_MASK_SHIFT));
        }
        else if (freq <= 44u)
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (LESSER_OR_EQUAL_44MHz << FLASH_CYCLES_MASK_SHIFT));
        }
        else
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (GREATER_44MHz << FLASH_CYCLES_MASK_SHIFT));
        }

    #endif  /* (CY_PSOC3) */


    #if (CY_PSOC5A)

        if (freq <= 16u)
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (LESSER_OR_EQUAL_16MHz << FLASH_CYCLES_MASK_SHIFT));
        }
        else if (freq <= 33u)
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (LESSER_OR_EQUAL_33MHz << FLASH_CYCLES_MASK_SHIFT));
        }
        else if (freq <= 50u)
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (LESSER_OR_EQUAL_50MHz << FLASH_CYCLES_MASK_SHIFT));
        }
        else
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (GREATER_51MHz << FLASH_CYCLES_MASK_SHIFT));
        }

    #endif  /* (CY_PSOC5A) */


    #if (CY_PSOC5LP)

        if (freq <= 16u)
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (LESSER_OR_EQUAL_16MHz << FLASH_CYCLES_MASK_SHIFT));
        }
        else if (freq <= 33u)
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (LESSER_OR_EQUAL_33MHz << FLASH_CYCLES_MASK_SHIFT));
        }
        else if (freq <= 50u)
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (LESSER_OR_EQUAL_50MHz << FLASH_CYCLES_MASK_SHIFT));
        }
        else
        {
            *FLASH_CYCLES_PTR = ((*FLASH_CYCLES_PTR & ~FLASH_CYCLES_MASK) |
                (GREATER_51MHz << FLASH_CYCLES_MASK_SHIFT));
        }

    #endif  /* (CY_PSOC5LP) */
}


#if (CY_PSOC3 || CY_PSOC5LP)

    /*******************************************************************************
    * Function Name: CyEEPROM_Start
    ********************************************************************************
    *
    * Summary:
    *  Enable the EEPROM.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyEEPROM_Start(void) 
    {
        /* Active Power Mode */
        *PM_ACT_EE_PTR |= PM_EE_MASK;

        /* Standby Power Mode */
        *PM_STBY_EE_PTR |= PM_EE_MASK;
    }


    /*******************************************************************************
    * Function Name: CyEEPROM_Stop
    ********************************************************************************
    *
    * Summary:
    *  Disable the EEPROM.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyEEPROM_Stop (void) 
    {
        /* Active Power Mode */
        *PM_ACT_EE_PTR &= ~PM_EE_MASK;

        /* Standby Power Mode */
        *PM_STBY_EE_PTR &= ~PM_EE_MASK;
    }

#endif /* (CY_PSOC3 || CY_PSOC5LP) */


/*******************************************************************************
* Function Name: CyEEPROM_ReadReserve
********************************************************************************
*
* Summary:
*  Request access to the EEPROM for reading and wait until access is available.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyEEPROM_ReadReserve(void) 
{
    /* Make a request for PHUB to have access */
    *AHUB_EE_REQ_ACK_PTR |= 0x01u;

    /* Wait for acknowledgement from PHUB */
    while (!(*AHUB_EE_REQ_ACK_PTR & 0x02u));
}


/*******************************************************************************
* Function Name: CyEEPROM_ReadRelease
********************************************************************************
*
* Summary:
*  Release the read reservation of the EEPROM.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyEEPROM_ReadRelease(void) 
{
    *AHUB_EE_REQ_ACK_PTR |= 0x00u;
}


/* [] END OF FILE */
