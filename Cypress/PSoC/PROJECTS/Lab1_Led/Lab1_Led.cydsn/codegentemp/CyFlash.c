/*******************************************************************************
* File Name: CyFlash.c
* Version 4.11
*
*  Description:
*   Provides an API for the FLASH.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2010-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyFlash.h"
#include "cyPm.h"

#if ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_4A) || (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_4D))
    #define CYFLASH_CHECKSUM_WORKAROUND     1u
#endif  /* ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_4A) || (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_4D)) */


#if (CY_PSOC4A)

    struct CySysFlashClockState
    {
        uint32   imoConfigReg;
    };

#else

    struct CySysFlashClockState
    {
        uint32 clkSelectReg;
        uint32 clkImoEna;
        uint32 clkImoFreq;
    };

#endif  /* (CY_PSOC4A) */


static uint32 CySysFlashExecSysCall(uint32 cmd, volatile const void *arg);
static uint32 CySysFlashCallProgramRow(uint32 rowNum, uint32 operation);
static uint32 CySysFlashHandleLoadResult(void);
#if (CY_PSOC4A)
    static void CySysFlashSetupClock(struct CySysFlashClockState *saved);
    static void CySysFlashRestoreClock(const struct CySysFlashClockState *saved);
#else
    static void CySysFlashSetupClock(struct CySysFlashClockState *saved);
    static void CySysFlashRestoreClock(const struct CySysFlashClockState *saved);
#endif  /* (CY_PSOC4A) */


#if (CY_PSOC4A)

    /*******************************************************************************
    * Function Name: CySysFlashSetupClock
    ********************************************************************************
    *
    * Summary:
    *  Configures the device clock settings for the flash write.
    *
    * Parameters:
    *  saved:
    *   Pointer to the structure where the data are saved.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    static void CySysFlashSetupClock(struct CySysFlashClockState *saved)
    {
        /* Preserve IMO configuration that could be changed
        * during syscall execution (Cypress ID #150448).
        */
        saved->imoConfigReg = CY_SYS_CLK_IMO_CONFIG_REG;
    }


    /*******************************************************************************
    * Function Name: CySysFlashRestoreClock
    ********************************************************************************
    *
    * Summary:
    *  Restores the device clock settings.
    *
    * Parameters:
    *  saved:
    *   Pointer to the structure from where the data are saved.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    static void CySysFlashRestoreClock(const struct CySysFlashClockState *saved)
    {
        CY_SYS_CLK_IMO_CONFIG_REG = saved->imoConfigReg;
    }

#else

    /*******************************************************************************
    * Function Name: CySysFlashSetupClock
    ********************************************************************************
    *
    * Summary:
    *  Configures the device clock settings for the flash write.
    *
    * Parameters:
    *  saved:
    *   Pointer to the structure where the data are saved.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    static void CySysFlashSetupClock(struct CySysFlashClockState *saved)
    {
        saved->clkSelectReg = CY_SYS_CLK_SELECT_REG;
        saved->clkImoEna    = CY_SYS_CLK_IMO_CONFIG_REG & CY_SYS_CLK_IMO_CONFIG_ENABLE;
        saved->clkImoFreq   = CY_SYS_CLK_IMO_MIN_FREQ_MHZ + (CY_SYS_CLK_IMO_SELECT_REG << 2);

        /* The FM-Lite IP (s8fmlt) uses the IMO at 48MHz for the pump clock and SPC
         * timer clock. The PUMP_SEL and HF clock must be set to IMO before calling
         * Flash write or erase operation.
        */
        if ((saved->clkImoFreq != 48u) ||
            ((saved->clkSelectReg & CY_SYS_CLK_SELECT_DIRECT_SEL_MASK) != CY_SYS_CLK_HFCLK_IMO) ||
            (((saved->clkSelectReg >> CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT) & CY_SYS_CLK_SELECT_PUMP_SEL_MASK) !=
                CY_SYS_CLK_SELECT_PUMP_SEL_IMO))
        {
            CySysClkWriteHfclkDiv(CY_SYS_CLK_HFCLK_DIV_4);
            if (saved->clkImoFreq != 48u)
            {
                CySysClkWriteImoFreq(48u);
            }
            CySysClkImoStart();
            CySysClkWriteHfclkDirect(CY_SYS_CLK_HFCLK_IMO);
            /* Set IMO output as clock source for charge pump clock */
            CY_SYS_CLK_SELECT_REG &=
                ((uint32)~(uint32)(CY_SYS_CLK_SELECT_PUMP_SEL_MASK << CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT));
            CY_SYS_CLK_SELECT_REG |= (uint32)((uint32)1u << CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT);
        }
    }


    /*******************************************************************************
    * Function Name: CySysFlashRestoreClock
    ********************************************************************************
    *
    * Summary:
    *  Restores the device clock settings.
    *
    * Parameters:
    *  saved:
    *   Pointer to the structure from where the data are saved.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    static void CySysFlashRestoreClock(const struct CySysFlashClockState *saved)
    {
        if ((saved->clkImoFreq != 48u) ||
            ((saved->clkSelectReg & CY_SYS_CLK_SELECT_DIRECT_SEL_MASK) != CY_SYS_CLK_HFCLK_IMO) ||
            (((saved->clkSelectReg >> CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT) & CY_SYS_CLK_SELECT_PUMP_SEL_MASK) !=
                CY_SYS_CLK_SELECT_PUMP_SEL_IMO))
        {
            if (saved->clkImoFreq != 48u)
            {
                CySysClkWriteImoFreq(saved->clkImoFreq);
            }
            CySysClkWriteHfclkDiv(CY_SYS_CLK_HFCLK_DIV_8);
            CySysClkWriteHfclkDirect(saved->clkSelectReg & CY_SYS_CLK_SELECT_DIRECT_SEL_MASK);
            CY_SYS_CLK_SELECT_REG = saved->clkSelectReg;
            if (0u == saved->clkImoEna)
            {
                CySysClkImoStop();
            }
        }
    }

#endif  /* (CY_PSOC4A) */


/*******************************************************************************
* Function Name: CySysFlashExecSysCall
********************************************************************************
*
* Summary:
*  Executes specified system call command.
*
* Parameters:
*  uint32 cmd:
*   CY_FLASH_SILICON_ID_OPCODE - This returns a 12 bit Family ID, 16 bit
*                                 Silicon ID and 8 bit Revision ID.
*
*   CY_FLASH_LOAD_BYTE_OPCODE  - Loads data to the page latch buffer to be
*                                programmed into the FLASH.
*
*  volatile void *arg:
*   Parameters of the command specified by the cmd parameter.
*
* Return:
*  Result of the system call execution.
*
*******************************************************************************/
static uint32 CySysFlashExecSysCall(uint32 cmd, volatile const void *arg)
{
    CY_FLASH_CPUSS_SYSARG_REG = (uint32)arg;
    CY_FLASH_CPUSS_SYSREQ_REG = cmd | CY_FLASH_CPUSS_REQ_START;
    while ((CY_FLASH_CPUSS_SYSREQ_REG & CY_FLASH_CPUSS_REQ_START) != 0u)
    {
        /* Wait for command to be executed */
    }
    return CY_FLASH_CPUSS_SYSARG_REG;
}


/*******************************************************************************
* Function Name: CySysFlashCallProgramRow
********************************************************************************
*
* Summary:
*  Executes the Program Row command.
*
* Parameters:
*  uint32 rowNum:
*   Flash row number.
*
*  uint32 operation:
*    Operation to be executed:
*    CY_FLASH_WRITE_ROW_OPCODE - Write row: erase and program flash row.
*    CY_FLASH_PROGRAM_ROW_OPCODE - Program flash row.
*
*
* Return:
*  Status of the last executed command.
*
*******************************************************************************/
static uint32 CySysFlashCallProgramRow(uint32 rowNum, uint32 operation)
{
    volatile struct
    {
        uint8 key1;
        uint8 key2;
        uint16 row;
    } args;

    args.key1 = (uint8)CY_FLASH_SROM_KEY1;
    args.key2 = (uint8)(CY_FLASH_SROM_KEY2 + operation);
    args.row = (uint16) rowNum;

    return CySysFlashExecSysCall(operation, &args);
}


/*******************************************************************************
* Function Name: CySysFlashHandleLoadResult
********************************************************************************
*
* Summary:
*  Returns the status of the last executed command.
*
* Parameters:
*  None
*
* Return:
*  Status of the last executed command.
*
*******************************************************************************/
static uint32 CySysFlashHandleLoadResult(void)
{
    uint32 value = CY_FLASH_CPUSS_SYSARG_REG;
    uint32 retValue = CYRET_SUCCESS;

    /* Check if value is written to SRAM_BASE */
    while (((value & CY_FLASH_SROM_CMD_RETURN_MASK) != CY_FLASH_SROM_CMD_RETURN_SUCC) && (retValue == CYRET_SUCCESS))
    {
        if ((value & CY_FLASH_SROM_CMD_RETURN_MASK) == CY_FLASH_SROM_CMD_RETURN_MASK)
        {
            retValue = value;   /* Error value */
        }
        value = CY_FLASH_CPUSS_SYSARG_REG;
    }
    return retValue;
}


/*******************************************************************************
* Function Name: CySysFlashWriteRow
********************************************************************************
*
* Summary:
*  Writes a row of Flash.
*
* Parameters:
*  uint16 rowNum:
*   Row number. Each row is 128 bytes so a 32KB flash memory will have a valid
*   range of [0-255].
*
*  uint8* rowData:
*   Array of bytes to write.
*
* Return:
*  Status
*     Value             Description
*    CYRET_SUCCESS     Successful
*    CYRET_LOCKED      Flash writing already in use
*    CYRET_CANCELED    Command not accepted
*    CYRET_BAD_PARAM   One or more invalid parameters
*    Other non-zero    Failure
*
*******************************************************************************/
cystatus CySysFlashWriteRow(uint32 rowNum, const uint8 rowData[])
{
    cystatus retValue = CYRET_SUCCESS;
    uint32 statusCode;
    uint8 interruptState;
    struct CySysFlashClockState savedClkCfg;
    volatile struct
    {
        uint8 key1;
        uint8 key2;
        uint8 byteAddr;
        uint8 flashMacro;
        uint32 numBytesMinusOne;
        uint32 data[CY_FLASH_SIZEOF_ROW / sizeof(uint32)];
    } loadBuf;
#ifdef CYFLASH_CHECKSUM_WORKAROUND
    uint32 needChecksumWorkaround = 0u;
    uint32 savedIndex = 0u;
    uint32 savedValue = 0u;
    uint32 checksum = 0u;
    uint32 bits = 0u;
    uint32 i;
#endif  /* CYFLASH_CHECKSUM_WORKAROUND */

    if ((rowNum < CY_FLASH_NUMBER_ROWS) && (rowData != 0u))
    {

        loadBuf.key1 = (uint8)CY_FLASH_SROM_KEY1;
        loadBuf.key2 = (uint8)CY_FLASH_SROM_KEY2_LOAD;
        loadBuf.byteAddr = (uint8)0u;

    #if(CY_FLASH_NUMBER_ROWS > 255u)
        loadBuf.flashMacro = (uint8)(rowNum >> 8);
    #else
        loadBuf.flashMacro = (uint8)0u;
    #endif  /* (CY_FLASH_NUMBER_ROWS > 255u) */

        loadBuf.numBytesMinusOne = (CY_FLASH_SIZEOF_ROW - 1u);
        (void)memcpy((void *)loadBuf.data, rowData, CY_FLASH_SIZEOF_ROW);

    #ifdef CYFLASH_CHECKSUM_WORKAROUND
        for (i = 0u; i < (CY_FLASH_SIZEOF_ROW / sizeof(uint32)); i++)
        {
            uint32 w = loadBuf.data[i];
            if (w != 0u)
            {
                checksum += w;
                bits |= w;
                savedIndex = i;
            }
        }

        needChecksumWorkaround = ((checksum == 0u) && (bits != 0u)) ? 1u : 0u;
        if (needChecksumWorkaround != 0u)
        {
            savedValue = loadBuf.data[savedIndex];
            loadBuf.data[savedIndex] = 0u;
        }
    #endif  /* CYFLASH_CHECKSUM_WORKAROUND */

        /* First load data. Then invoke Write row command. */
        (void)CySysFlashExecSysCall(CY_FLASH_LOAD_BYTE_OPCODE, &loadBuf);
        retValue = CySysFlashHandleLoadResult();
        if(retValue == CYRET_SUCCESS)
        {
            /* Mask all exceptions to guarantee that IMO configuration will be changed
            * in the atomic way. It will not affect the syscall execution (flash row write)
            * since it is executed in the NMI context.
            */
            interruptState = CyEnterCriticalSection();
            CySysFlashSetupClock(&savedClkCfg);

            statusCode = CySysFlashCallProgramRow(rowNum, CY_FLASH_WRITE_ROW_OPCODE);
            if (statusCode != CY_FLASH_SROM_CMD_RETURN_SUCC)
            {
                retValue = statusCode;
            }

        #ifdef CYFLASH_CHECKSUM_WORKAROUND
            if ((retValue == CYRET_SUCCESS) && (needChecksumWorkaround != 0u))
            {
                (void)memset((void *)loadBuf.data, 0, CY_FLASH_SIZEOF_ROW);
                loadBuf.data[savedIndex] = savedValue;
                (void)CySysFlashExecSysCall(CY_FLASH_LOAD_BYTE_OPCODE, &loadBuf);
                retValue = CySysFlashHandleLoadResult();
                if (retValue == CYRET_SUCCESS)
                {
                    statusCode = CySysFlashCallProgramRow(rowNum, CY_FLASH_PROGRAM_ROW_OPCODE);
                    if (statusCode != CY_FLASH_SROM_CMD_RETURN_SUCC)
                    {
                        retValue = statusCode;
                    }
                }
            }
        #endif  /* CYFLASH_CHECKSUM_WORKAROUND */

            CySysFlashRestoreClock(&savedClkCfg);
            CyExitCriticalSection(interruptState);
        }
    }
    else
    {
        retValue = CYRET_BAD_PARAM;
    }

    return (retValue);
}

#if(CY_PSOC4A)

    /*******************************************************************************
    * Function Name: CySysFlashSetWaitCycles
    ********************************************************************************
    *
    * Summary:
    *  Sets the number of clock cycles the cache will wait before it samples data
    *  coming back from Flash. This function must be called before increasing the
    *  SYSCLK clock frequency. It can optionally be called after lowering SYSCLK
    *  clock frequency in order to improve the CPU performance.
    *
    * Parameters:
    *  freq: Valid range [3-48].  Frequency for operation of the IMO.
    *  Note: Invalid frequency will be ignored.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysFlashSetWaitCycles(uint32 freq)
    {
        if ((freq >= CY_SYS_CLK_IMO_MIN_FREQ_MHZ) && (freq <= CY_SYS_CLK_IMO_MAX_FREQ_MHZ))
        {
            if ( freq <= CY_FLASH_SYSCLK_BOUNDARY_MHZ )
            {
                CY_SYS_CLK_SELECT_REG &= (uint32)(~CY_FLASH_WAIT_STATE_EN);
            }
            else
            {
                CY_SYS_CLK_SELECT_REG |= CY_FLASH_WAIT_STATE_EN;
            }
        }
        else
        {
            /* Halt CPU in debug mode if frequency is invalid */
            CYASSERT(0u != 0u);
        }
    }

#endif  /* (CY_PSOC4A) */

/* [] END OF FILE */
