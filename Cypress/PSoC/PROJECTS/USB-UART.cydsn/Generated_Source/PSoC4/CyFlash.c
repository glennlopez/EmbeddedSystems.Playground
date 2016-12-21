/*******************************************************************************
* File Name: CyFlash.c
* Version 4.20
*
*  Description:
*   Provides an API for the FLASH.
*
*  Note:
*   This code is endian agnostic.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2010-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyFlash.h"

static CY_SYS_FLASH_CLOCK_BACKUP_STRUCT cySysFlashBackup;

static cystatus CySysFlashClockBackup(void);
static cystatus CySysFlashClockRestore(void);
#if(CY_IP_FMLT)
    static cystatus CySysFlashClockConfig(void);
#endif  /* (CY_IP_FMLT) */


/*******************************************************************************
* Function Name: CySysFlashWriteRow
********************************************************************************
*
* Summary:
*  Erases a row of Flash and programs it with the new data.
*
* Parameters:
*  uint16 rowNum:
*   The flash row number. The number of the flash rows is defined by the
*   CY_FLASH_NUMBER_ROWS macro for the selected device. Refer to the device
*   datasheet for the details.
*
*  uint8* rowData:
*   Array of bytes to write. The size of the array must be equal to the flash
*   row size. The flash row size for the selected device is defined by
*   the CY_FLASH_SIZEOF_ROW macro. Refer to the device datasheet for the
*   details.
*
* Return:
*  Status
*     Value                     Description
*    CY_SYS_FLASH_SUCCESS           Successful
*    CY_SYS_FLASH_INVALID_ADDR      Specified flash row address is invalid
*    CY_SYS_FLASH_PROTECTED         Specified flash row is protected
*    Other non-zero                 Failure
*
* Side Effects:
*   The IMO must be enabled before calling this function. The operation of the
*   flash writing hardware is dependent on the IMO.
*
*   For PSoC 4000 devices this API will automatically modify the clock settings
*   for the device. Writing to flash requires that changes be made to the IMO
*   and HFCLK settings. The configuration is restored before returning. HFCLK
*   will have several frequency changes during the operation of this API between
*   a minimum frequency of the current IMO frequency divided by 8 and a maximum
*   frequency of 12 MHz. This will impact the operation of most of the hardware
*   in the device.
*
*******************************************************************************/
uint32 CySysFlashWriteRow(uint32 rowNum, const uint8 rowData[])
{
    volatile uint32 retValue = CY_SYS_FLASH_SUCCESS;
    volatile uint32 clkCnfRetValue = CY_SYS_FLASH_SUCCESS;
    volatile uint32   parameters[(CY_FLASH_SIZEOF_ROW + CY_FLASH_SRAM_ROM_DATA)/4u];
    uint8  interruptState;

    #if (CY_PSOC4_4000 || CY_PSOC4_4100 || CY_PSOC4_4200)
        uint32 rowDataTmp[CY_FLASH_SIZEOF_ROW / sizeof(uint32)];

        uint32 needChecksumWorkaround = 0u;
        uint32 savedIndex = 0u;
        uint32 savedValue = 0u;
        uint32 checksum = 0u;
        uint32 bits = 0u;
        uint32 i;
    #endif  /* (CY_PSOC4_4000 || CY_PSOC4_4100 || CY_PSOC4_4200) */

    if ((rowNum < CY_FLASH_NUMBER_ROWS) && (rowData != 0u))
    {
        #if (CY_PSOC4_4000 || CY_PSOC4_4100 || CY_PSOC4_4200)

            (void) memcpy((void *)rowDataTmp, rowData, CY_FLASH_SIZEOF_ROW);

            for (i = 0u; i < (CY_FLASH_SIZEOF_ROW / sizeof(uint32)); i++)
            {
                uint32 tmp = rowDataTmp[i];
                if (tmp != 0u)
                {
                    checksum += tmp;
                    bits |= tmp;
                    savedIndex = i;
                }
            }

            needChecksumWorkaround = ((checksum == 0u) && (bits != 0u)) ? 1u : 0u;
            if (needChecksumWorkaround != 0u)
            {
                savedValue = rowDataTmp[savedIndex];
                rowDataTmp[savedIndex] = 0u;
            }
        #endif  /* (CY_PSOC4_4000 || CY_PSOC4_4100 || CY_PSOC4_4200) */

        /* Load Flash Bytes */
        parameters[0u] = (uint32) (CY_FLASH_GET_MACRO_FROM_ROW(rowNum)        << CY_FLASH_PARAM_MACRO_SEL_OFFSET) |
                         (uint32) (CY_FLASH_PAGE_LATCH_START_ADDR             << CY_FLASH_PARAM_ADDR_OFFSET     ) |
                         (uint32) (CY_FLASH_KEY_TWO(CY_FLASH_API_OPCODE_LOAD) << CY_FLASH_PARAM_KEY_TWO_OFFSET  ) |
                         CY_FLASH_KEY_ONE;
        parameters[1u] = CY_FLASH_SIZEOF_ROW - 1u;
    #if (CY_PSOC4_4000 || CY_PSOC4_4100 || CY_PSOC4_4200)
        (void)memcpy((void *)&parameters[2u], rowDataTmp, CY_FLASH_SIZEOF_ROW);
    #else
        (void)memcpy((void *)&parameters[2u], rowData, CY_FLASH_SIZEOF_ROW);
    #endif /* (CY_PSOC4_4000 || CY_PSOC4_4100 || CY_PSOC4_4200) */
        CY_FLASH_CPUSS_SYSARG_REG = (uint32) &parameters[0u];
        CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_CPUSS_REQ_START | CY_FLASH_API_OPCODE_LOAD;
        retValue = CY_FLASH_API_RETURN;

        if(retValue == CY_SYS_FLASH_SUCCESS)
        {
            /***************************************************************
            * Mask all the exceptions to guarantee that Flash write will
            * occur in the atomic way. It will not affect system call
            * execution (flash row write) since it is executed in the NMI
            * context.
            ***************************************************************/
            interruptState = CyEnterCriticalSection();

            clkCnfRetValue = CySysFlashClockBackup();

        #if(CY_IP_FMLT)
            if(clkCnfRetValue == CY_SYS_FLASH_SUCCESS)
            {
                retValue = CySysFlashClockConfig();
            }
        #endif  /* (CY_IP_FMLT) */

            if(retValue == CY_SYS_FLASH_SUCCESS)
            {
                /* Write Row */
                parameters[0u]  = (uint32) (((uint32) CY_FLASH_KEY_TWO(CY_FLASH_API_OPCODE_WRITE_ROW) <<  CY_FLASH_PARAM_KEY_TWO_OFFSET) | CY_FLASH_KEY_ONE);
                parameters[0u] |= (uint32)(rowNum << 16u);

                CY_FLASH_CPUSS_SYSARG_REG = (uint32) &parameters[0u];
                CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_CPUSS_REQ_START | CY_FLASH_API_OPCODE_WRITE_ROW;
                retValue = CY_FLASH_API_RETURN;
            }

            #if (CY_PSOC4_4000 || CY_PSOC4_4100 || CY_PSOC4_4200)

                if ((retValue == CYRET_SUCCESS) && (needChecksumWorkaround != 0u))
                {
                    (void)memset((void *)rowDataTmp, 0, CY_FLASH_SIZEOF_ROW);
                    rowDataTmp[savedIndex] = savedValue;

                    /* Load Flash Bytes */
                    parameters[0u] = (uint32) (CY_FLASH_GET_MACRO_FROM_ROW(rowNum)        << CY_FLASH_PARAM_MACRO_SEL_OFFSET) |
                                     (uint32) (CY_FLASH_PAGE_LATCH_START_ADDR             << CY_FLASH_PARAM_ADDR_OFFSET     ) |
                                     (uint32) (CY_FLASH_KEY_TWO(CY_FLASH_API_OPCODE_LOAD) << CY_FLASH_PARAM_KEY_TWO_OFFSET  ) |
                                     CY_FLASH_KEY_ONE;
                    parameters[1u] = CY_FLASH_SIZEOF_ROW - 1u;
                    (void)memcpy((void *)&parameters[2u], rowDataTmp, CY_FLASH_SIZEOF_ROW);
                    CY_FLASH_CPUSS_SYSARG_REG = (uint32) &parameters[0u];
                    CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_CPUSS_REQ_START | CY_FLASH_API_OPCODE_LOAD;
                    retValue = CY_FLASH_API_RETURN;


                    if(retValue == CY_SYS_FLASH_SUCCESS)
                    {
                        /* Program Row */
                        parameters[0u]  = (uint32) (((uint32) CY_FLASH_KEY_TWO(CY_FLASH_API_OPCODE_PROGRAM_ROW) <<  CY_FLASH_PARAM_KEY_TWO_OFFSET) | CY_FLASH_KEY_ONE);
                        parameters[0u] |= (uint32)(rowNum << 16u);

                        CY_FLASH_CPUSS_SYSARG_REG = (uint32) &parameters[0u];
                        CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_CPUSS_REQ_START | CY_FLASH_API_OPCODE_PROGRAM_ROW;
                        retValue = CY_FLASH_API_RETURN;
                    }
                }
            #endif  /* (CY_PSOC4_4000 || CY_PSOC4_4100 || CY_PSOC4_4200) */

            if(clkCnfRetValue == CY_SYS_FLASH_SUCCESS)
            {
                clkCnfRetValue = CySysFlashClockRestore();
            }

            CyExitCriticalSection(interruptState);
        }
    }
    else
    {
        retValue = CY_SYS_FLASH_INVALID_ADDR;
    }

    return (retValue);
}





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
*  freq: The System clock frequency in MHz. Note: Invalid frequency will be
*  ignored in Release mode and the CPU will be halted if project is compiled in
*  Debug mode.
*
* Return:
*  None
*
*******************************************************************************/
void CySysFlashSetWaitCycles(uint32 freq)
{
    uint8  interruptState;

    #if (CY_IP_CPUSS)

        interruptState = CyEnterCriticalSection();

        if ( freq <= CY_FLASH_SYSCLK_BOUNDARY_MHZ )
        {
            CY_SYS_CLK_SELECT_REG &= (uint32)(~CY_FLASH_WAIT_STATE_EN);
        }
        else
        {
            CY_SYS_CLK_SELECT_REG |= CY_FLASH_WAIT_STATE_EN;
        }

        CyExitCriticalSection(interruptState);

    #else
        interruptState = CyEnterCriticalSection();

        if (freq <= CY_FLASH_CTL_WS_0_FREQ_MAX)
        {
            CY_FLASH_CTL_REG = (CY_FLASH_CTL_REG & ~CY_FLASH_CTL_WS_MASK) | CY_FLASH_CTL_WS_0_VALUE;
        } else
        if (freq <= CY_FLASH_CTL_WS_1_FREQ_MAX)
        {
            CY_FLASH_CTL_REG = (CY_FLASH_CTL_REG & ~CY_FLASH_CTL_WS_MASK) | CY_FLASH_CTL_WS_1_VALUE;
        } else
    #if (CY_IP_FMLT)
        if (freq <= CY_FLASH_CTL_WS_2_FREQ_MAX)
        {
            CY_FLASH_CTL_REG = (CY_FLASH_CTL_REG & ~CY_FLASH_CTL_WS_MASK) | CY_FLASH_CTL_WS_2_VALUE;
        }
    #endif  /* (CY_IP_FMLT) */
        else
        {
            /* Halt CPU in debug mode if frequency is invalid */
            CYASSERT(0u != 0u);
        }

        CyExitCriticalSection(interruptState);

    #endif  /* (CY_IP_CPUSS) */
}


/*******************************************************************************
* Function Name: CySysFlashClockBackup
********************************************************************************
*
* Summary:
*  Backups the device clock configuration.
*
* Parameters:
*  None
*
* Return:
*  The same as CySysFlashWriteRow().
*
*******************************************************************************/
static cystatus CySysFlashClockBackup(void)
{
    cystatus retValue = CY_SYS_FLASH_SUCCESS;
#if(!CY_IP_FM)
    #if !(CY_PSOC4_4000)
        volatile uint32   parameters[2u];
    #endif  /* !(CY_PSOC4_4000) */
#endif  /* (!CY_IP_FM) */

#if(CY_IP_FM)

    /***************************************************************
    * Preserve IMO configuration that could be changed during
    * system call execution (Cypress ID #150448).
    ***************************************************************/
    cySysFlashBackup.imoConfigReg = CY_SYS_CLK_IMO_CONFIG_REG;

#else   /* (CY_IP_FMLT) */

    #if (CY_PSOC4_4000)

        /***************************************************************************
        * Perform firmware clock settings backup for the PSOC4 4000 devices (the
        * corresponding system call is not available).
        ***************************************************************************/

        /***************************************************************************
        * The registers listed below are modified by CySysFlashClockConfig().
        *
        * The registers to be saved:
        * - CY_SYS_CLK_IMO_CONFIG_REG - IMO enable state.
        * - CY_SYS_CLK_SELECT_REG     - HFCLK source, divider, pump source. Save
        *                               entire register as it can be directly
        *                               written on restore (no special
        *                               requirements).
        * - CY_SYS_CLK_IMO_SELECT_REG - Save IMO frequency.
        *
        * The registers not to be saved:
        * - CY_SYS_CLK_IMO_TRIM1_REG  - No need to save. Function of frequency.
        *                               Restored by CySysClkWriteImoFreq().
        * - CY_SYS_CLK_IMO_TRIM3_REG  - No need to save. Function of frequency.
        *                               Restored by CySysClkWriteImoFreq().
        * - REG_CPUSS_FLASH_CTL       - Flash wait cycles. Unmodified due to system
        *                               clock 16 MHz limit.
        ***************************************************************************/

        cySysFlashBackup.clkSelectReg = CY_SYS_CLK_SELECT_REG;
        cySysFlashBackup.clkImoEna    = CY_SYS_CLK_IMO_CONFIG_REG & CY_SYS_CLK_IMO_CONFIG_ENABLE;
        cySysFlashBackup.clkImoFreq   = CY_SYS_CLK_IMO_MIN_FREQ_MHZ + (CY_SYS_CLK_IMO_SELECT_REG << 2u);

    #else

        /* FM-Lite Clock Backup System Call */
        parameters[0u] = (uint32) ((CY_FLASH_KEY_TWO(CY_FLASH_API_OPCODE_CLK_BACKUP) <<  CY_FLASH_PARAM_KEY_TWO_OFFSET) | CY_FLASH_KEY_ONE);
        parameters[1u] = (uint32) &cySysFlashBackup.clockSettings[0u];
        CY_FLASH_CPUSS_SYSARG_REG = (uint32) &parameters[0u];
        CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_CPUSS_REQ_START | CY_FLASH_API_OPCODE_CLK_BACKUP;
        retValue = CY_FLASH_API_RETURN;

    #endif  /* (CY_PSOC4_4000) */

#endif  /* (CY_IP_FM) */

    return (retValue);
}


#if(CY_IP_FMLT)
/*******************************************************************************
* Function Name: CySysFlashClockConfig
********************************************************************************
*
* Summary:
*  Configures the device clocks for the flash writing.
*
* Parameters:
*  None
*
* Return:
*  The same as CySysFlashWriteRow().
*
*******************************************************************************/
static cystatus CySysFlashClockConfig(void)
{
    cystatus retValue = CY_SYS_FLASH_SUCCESS;

    /***************************************************************************
    * The FM-Lite IP uses the IMO at 48MHz for the pump clock and SPC timer
    * clock. The PUMP_SEL and HF clock must be set to IMO before calling Flash
    * write or erase operation.
    ***************************************************************************/
#if (CY_PSOC4_4000)

    /***************************************************************************
    * Perform firmware clock settings setup for the PSOC4 4000 devices (the
    * corresponding system call is not reliable):
    * - The IMO frequency should be 48 MHz
    * - The IMO should be source for the HFCLK
    * - The IMO should be the source for the charge pump clock
    *
    * Note The structure members used below are initialized by
    * the CySysFlashClockBackup() function.
    ***************************************************************************/
    if ((cySysFlashBackup.clkImoFreq != 48u) ||
        ((cySysFlashBackup.clkSelectReg & CY_SYS_CLK_SELECT_DIRECT_SEL_MASK) != CY_SYS_CLK_HFCLK_IMO) ||
        (((cySysFlashBackup.clkSelectReg >> CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT) & CY_SYS_CLK_SELECT_PUMP_SEL_MASK) !=
            CY_SYS_CLK_SELECT_PUMP_SEL_IMO))
    {
        /***********************************************************************
         Set HFCLK divider to divide-by-4 to ensure that System clock frequency
        * is within the valid limit (16 MHz for the PSoC4 4000).
        ***********************************************************************/
        CySysClkWriteHfclkDiv(CY_SYS_CLK_HFCLK_DIV_4);

        /* The IMO frequency should be 48 MHz */
        if (cySysFlashBackup.clkImoFreq != 48u)
        {
            CySysClkWriteImoFreq(48u);
        }
        CySysClkImoStart();

        /* The IMO should be source for the HFCLK */
        CySysClkWriteHfclkDirect(CY_SYS_CLK_HFCLK_IMO);

        /* The IMO should be the source for the charge pump clock */
        CY_SYS_CLK_SELECT_REG =  (CY_SYS_CLK_SELECT_REG &
            ((uint32)~(uint32)(CY_SYS_CLK_SELECT_PUMP_SEL_MASK << CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT))) |
            ((uint32)((uint32)1u << CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT));
    }

#else

    /* FM-Lite Clock Configuration */
    CY_FLASH_CPUSS_SYSARG_REG = (uint32) ((CY_FLASH_KEY_TWO(CY_FLASH_API_OPCODE_CLK_CONFIG) <<  CY_FLASH_PARAM_KEY_TWO_OFFSET) | CY_FLASH_KEY_ONE);
    CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_CPUSS_REQ_START | CY_FLASH_API_OPCODE_CLK_CONFIG;
    retValue = CY_FLASH_API_RETURN;

#endif  /* (CY_PSOC4_4000) */

    return (retValue);
}
#endif  /* (CY_IP_FMLT) */


/*******************************************************************************
* Function Name: CySysFlashClockRestore
********************************************************************************
*
* Summary:
*  Restores the device clock configuration.
*
* Parameters:
*  None
*
* Return:
*  The same as CySysFlashWriteRow().
*
*******************************************************************************/
static cystatus CySysFlashClockRestore(void)
{
    cystatus retValue = CY_SYS_FLASH_SUCCESS;
#if(!CY_IP_FM)
    #if !(CY_PSOC4_4000)
        volatile uint32   parameters[2u];
    #endif  /* !(CY_PSOC4_4000) */
#endif  /* (!CY_IP_FM) */

#if(CY_IP_FM)

    /***************************************************************
    * Restore IMO configuration that could be changed during
    * system call execution (Cypress ID #150448).
    ***************************************************************/
    CY_SYS_CLK_IMO_CONFIG_REG = cySysFlashBackup.imoConfigReg;

#else

    #if (CY_PSOC4_4000)

        /***************************************************************************
        * Perform firmware clock settings restore for the PSOC4 4000 devices (the
        * corresponding system call is not available).
        ***************************************************************************/

        /* Restore clock settings */
        if ((cySysFlashBackup.clkImoFreq != 48u) ||
            ((cySysFlashBackup.clkSelectReg & CY_SYS_CLK_SELECT_DIRECT_SEL_MASK) != CY_SYS_CLK_HFCLK_IMO) ||
            (((cySysFlashBackup.clkSelectReg >> CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT) & CY_SYS_CLK_SELECT_PUMP_SEL_MASK) !=
                CY_SYS_CLK_SELECT_PUMP_SEL_IMO))
        {
            /* Restore IMO frequency if needed */
            if (cySysFlashBackup.clkImoFreq != 48u)
            {
                CySysClkWriteImoFreq(cySysFlashBackup.clkImoFreq);
            }

            /* Restore HFCLK clock source */
            CySysClkWriteHfclkDirect(cySysFlashBackup.clkSelectReg & CY_SYS_CLK_SELECT_DIRECT_SEL_MASK);

            /* Restore HFCLK divider and source for pump  */
            CY_SYS_CLK_SELECT_REG = cySysFlashBackup.clkSelectReg;

            /* Stop IMO if needed */
            if (0u == cySysFlashBackup.clkImoEna)
            {
                CySysClkImoStop();
            }
        }

    #else

        /* FM-Lite Clock Restore */
        parameters[0u] = (uint32) ((CY_FLASH_KEY_TWO(CY_FLASH_API_OPCODE_CLK_RESTORE) <<  CY_FLASH_PARAM_KEY_TWO_OFFSET) | CY_FLASH_KEY_ONE);
        parameters[1u] = (uint32) &cySysFlashBackup.clockSettings[0u];
        CY_FLASH_CPUSS_SYSARG_REG = (uint32) &parameters[0u];
        CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_CPUSS_REQ_START | CY_FLASH_API_OPCODE_CLK_RESTORE;
        retValue = CY_FLASH_API_RETURN;

    #endif  /* (CY_PSOC4_4000) */

#endif  /* (CY_IP_FM) */

    return (retValue);
}


/* [] END OF FILE */
