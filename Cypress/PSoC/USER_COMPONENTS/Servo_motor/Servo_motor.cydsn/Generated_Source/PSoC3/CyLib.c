/*******************************************************************************
* File Name: CyLib.c
* Version 3.20
*
*  Description:
*   Provides system API for the clocking, interrupts and watchdog timer.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"

uint8 CYXDATA CyResetStatus;

uint32 cydelay_freq_hz  = BCLK__BUS_CLK__HZ;
uint32 cydelay_freq_khz = (BCLK__BUS_CLK__HZ + 999u) / 1000u;
uint8  cydelay_freq_mhz = (uint8)((BCLK__BUS_CLK__HZ + 999999u) / 1000000u);
uint32 cydelay_32k_ms   = 32768 * ((BCLK__BUS_CLK__HZ + 999u) / 1000u);

/* Function Prototypes */
uint8 CyUSB_PowerOnCheck(void)  ;
void CyIMO_SetTrimValue(uint8 freq) ;
void CyBusClk_Internal_SetDivider(uint16 divider);


/*******************************************************************************
* Function Name: CyPLL_OUT_Start
********************************************************************************
*
* Summary:
*   Enables the PLL.  Optionally waits for it to become stable.
*   Waits at least 250 us or until it is detected that the PLL is stable.
*
* Parameters:
*   wait:
*    0: Return immediately after configuration
*    1: Wait for PLL lock or timeout.
*
* Return:
*   Status
*    CYRET_SUCCESS - Completed successfully
*    CYRET_TIMEOUT - Timeout occurred without detecting a stable clock.
*     If the input source of the clock is jittery, then the lock indication
*     may not occur.  However, after the timeout has expired the generated PLL
*     clock can still be used.
*
* Side Effects:
*  If wait is enabled: This function wses the Fast Time Wheel to time the wait.
*  Any other use of the Fast Time Wheel will be stopped during the period of
*  this function and then restored. This function also uses the 100 KHz ILO.
*  If not enabled, this function will enable the 100 KHz ILO for the period of
*  this function.
*
*  No changes to the setup of the ILO, Fast Time Wheel, Central Time Wheel or
*  Once Per Second interrupt may be made by interrupt routines during the period
*  of this function execution. The current operation of the ILO, Central Time
*  Wheel and Once Per Second interrupt are maintained during the operation of
*  this function provided the reading of the Power Manager Interrupt Status
*  Register is only done using the CyPmReadStatus() function.
*
*******************************************************************************/
cystatus CyPLL_OUT_Start(uint8 wait) 
{
    cystatus status = CYRET_SUCCESS;

    uint8 iloEnableState;
    uint8 pmTwCfg0;
    uint8 pmTwCfg2;


    /* Enables the PLL circuit  */
    CY_CLK_PLL_CFG0_REG |= CY_CLK_PLL_ENABLE;

    if(wait != 0)
    {
        /* Save 100 KHz ILO, FTW interval, enable and interrupt enable */
        iloEnableState = SLOWCLK_ILO_CR0;
        pmTwCfg0 = CY_PM_TW_CFG0_REG;
        pmTwCfg2 = CY_PM_TW_CFG2_REG;

        CyPmFtwSetInterval(CY_CLK_PLL_FTW_INTERVAL);

        status = CYRET_TIMEOUT;


        while(CyPmReadStatus(CY_PM_FTW_INT) != CY_PM_FTW_INT)
        {
            /* Wait for the interrupt status */
            if(0u != (CY_CLK_PLL_SR_REG & CY_CLK_PLL_LOCK_STATUS))
            {
                if(0u != (CY_CLK_PLL_SR_REG & CY_CLK_PLL_LOCK_STATUS))
                {
                    status = CYRET_SUCCESS;
                    break;
                }
            }
        }


        /* Restore 100 KHz ILO, FTW interval, enable and interrupt enable */
        if(0u == (iloEnableState & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Stop100K();
        }
        CY_PM_TW_CFG0_REG = pmTwCfg0;
        CY_PM_TW_CFG2_REG = pmTwCfg2;
    }

    return(status);
}


/*******************************************************************************
* Function Name: CyPLL_OUT_Stop
********************************************************************************
*
* Summary:
*  Disables the PLL.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyPLL_OUT_Stop(void) 
{
    CY_CLK_PLL_CFG0_REG &= ~CY_CLK_PLL_ENABLE;
}


/*******************************************************************************
* Function Name: CyPLL_OUT_SetPQ
********************************************************************************
*
* Summary:
*  Sets the P and Q dividers and the charge pump current.
*  The Frequency Out will be P/Q * Frequency In.
*  The PLL must be disabled before calling this function.
*
* Parameters:
*  uint8 P:
*   Valid range [8 - 255].
*
*  uint8 Q:
*   Valid range [1 - 16]. Input Frequency / Q must be in range of 1 to 3 MHz.

*  uint8 current:
*   Valid range [1 - 7]. Charge pump current in uA. Refer to the device TRM and
*   datasheet for more information.
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*******************************************************************************/
void CyPLL_OUT_SetPQ(uint8 P, uint8 Q, uint8 current) 
{
    /* Halt CPU in debug mode if PLL is enabled */
    CYASSERT(0u == (CY_CLK_PLL_CFG0_REG & CY_CLK_PLL_ENABLE));

    /* Halt CPU in debug mode if P divider is less than required */
    CYASSERT(P >= CY_CLK_PLL_MIN_P_VALUE);

    /* Halt CPU in debug mode if Q divider is out of range */
    CYASSERT((Q <= CY_CLK_PLL_MAX_Q_VALUE) && (Q >= CY_CLK_PLL_MIN_Q_VALUE));

    /* Halt CPU in debug mode if pump current is out of range */
    CYASSERT((current >= CY_CLK_PLL_MIN_CUR_VALUE) && (current <= CY_CLK_PLL_MAX_CUR_VALUE));


    /* Set new values */
    CY_CLK_PLL_P_REG = P;
    CY_CLK_PLL_Q_REG = Q - 1;
    CY_CLK_PLL_CFG1_REG = (CY_CLK_PLL_CFG1_REG & CY_CLK_PLL_CURRENT_MASK) |
                            ((current - 1) << CY_CLK_PLL_CURRENT_POSITION);
}


/*******************************************************************************
* Function Name: CyPLL_OUT_SetSource
********************************************************************************
*
* Summary:
*  Sets the input clock source to the PLL. The PLL must be disabled before
*  calling this function.
*
* Parameters:
*   source: One of the three available PLL clock sources
*            0 :        IMO
*            1 :        MHz Crystal
*            2 :        DSI
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*******************************************************************************/
void CyPLL_OUT_SetSource(uint8 source) 
{
    /* Halt CPU in debug mode if PLL is enabled */
    CYASSERT(0u == (CY_CLK_PLL_CFG0_REG & CY_CLK_PLL_ENABLE));

    switch(source)
    {
        case CY_PLL_SOURCE_IMO:
        case CY_PLL_SOURCE_XTAL:
        case CY_PLL_SOURCE_DSI:
            CLKDIST_CR = ((CLKDIST_CR & CLOCK_CONTROL_DIST_MASK) | source);
        break;

        default:
            CYASSERT(0);
        break;
    }
}


/*******************************************************************************
* Function Name: CyIMO_Start
********************************************************************************
*
* Summary:
*  Enables the IMO. Optionally waits at least 6 us for it to settle.
*
* Parameters:
*  uint8 wait:
*   0: Return immediately after configuration
*   1: Wait for at least 6us for the IMO to settle.
*
* Return:
*  None
*
* Side Effects:
*  If wait is enabled: This function wses the Fast Time Wheel to time the wait.
*  Any other use of the Fast Time Wheel will be stopped during the period of
*  this function and then restored. This function also uses the 100 KHz ILO.
*  If not enabled, this function will enable the 100 KHz ILO for the period of
*  this function.
*
*  No changes to the setup of the ILO, Fast Time Wheel, Central Time Wheel or
*  Once Per Second interrupt may be made by interrupt routines during the period
*  of this function execution. The current operation of the ILO, Central Time
*  Wheel and Once Per Second interrupt are maintained during the operation of
*  this function provided the reading of the Power Manager Interrupt Status
*  Register is only done using the CyPmReadStatus() function.
*
*******************************************************************************/
void CyIMO_Start(uint8 wait) 
{
    uint8 pm_tw_cfg2_state;
    uint8 pm_tw_cfg0_state;
    uint8 ilo_clock_state;

    /* Set the bit to enable the clock. */
    PM_ACT_CFG0 |= IMO_PM_ENABLE;

    /* Wait for 6 us */
    if(wait)
    {
        /* Need to turn on the 100KHz ILO if it happens to not already be running.*/
        ilo_clock_state = SLOWCLK_ILO_CR0;
        if(!(ilo_clock_state & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Start100K();
        }

        /* Use ILO 100 KHz */
        pm_tw_cfg2_state = PM_TW_CFG2;
        pm_tw_cfg0_state = PM_TW_CFG0;

        /* FTW_EN (bit 0) must be clear to change the period*/
        PM_TW_CFG2 &= FTW_CLEAR_FTW_BITS;

        /* Set the FTW interval of 1 100KHz ILO clocks
        Should result in status getting set at a (100/1)KHz rate*/
        PM_TW_CFG0 = 1-1;
        /* Enable FTW, but not the interrupt*/
        PM_TW_CFG2 = FTW_ENABLE;

        /* Read FTW value */
        while (CyPmReadStatus(1) == 0)
        {
            /* Wait for the interrupt status*/
        }

        /* Reset the clock */
        if(!(ilo_clock_state & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Stop100K();
        }

        /* Restore the FTW */
        PM_TW_CFG0 = pm_tw_cfg0_state;
        PM_TW_CFG2 = pm_tw_cfg2_state;
    }
}


/*******************************************************************************
* Function Name: CyIMO_Stop
********************************************************************************
*
* Summary:
*   Disables the IMO.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyIMO_Stop(void) 
{
    /* Clear the bit to disable the clock. */
    PM_ACT_CFG0 &= ~IMO_PM_ENABLE;
}


/*******************************************************************************
* Function Name: CyUSB_PowerOnCheck
********************************************************************************
*
* Summary:
*  Returns the USB power status value. A private function to cy_boot.
*
* Parameters:
*   None
*
* Return:
*   uint8: one if the USB is enabled, 0 if not enabled.
*
*******************************************************************************/
uint8 CyUSB_PowerOnCheck(void)  
{
    uint8 powered_on = 0u;

    /* Check whether device is in Active or AltActiv and if USB is powered on */
    if((((CY_PM_MODE_CSR_REG & CY_PM_MODE_CSR_MASK) == CY_PM_MODE_CSR_ACTIVE) &&
         (CY_PM_ACT_CFG5_REG & CY_ACT_USB_ENABLED)) ||
      (((CY_PM_MODE_CSR_REG & CY_PM_MODE_CSR_MASK) == CY_PM_MODE_CSR_ALT_ACT) &&
        (CY_PM_STBY_CFG5_REG & CY_ALT_ACT_USB_ENABLED)))
    {
        powered_on = 1;
    }

    return (powered_on);
}


/*******************************************************************************
* Function Name: CyIMO_SetTrimValue
********************************************************************************
*
* Summary:
*  Sets the IMO factory trim values.
*
* Parameters:
*  uint8 freq - frequency for which trims must be set
*
* Return:
*  None
*
*******************************************************************************/
void CyIMO_SetTrimValue(uint8 freq) 
{
    uint8 usb_power_on = CyUSB_PowerOnCheck();

    /* If USB is powered */
    if(usb_power_on == 1)
    {
        /* Unlock USB write */
        CY_USB_CR1 &= ~CLOCK_USB_ENABLE;
    }
    switch(freq)
    {
    case CY_IMO_FREQ_3MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_3MHZ_PTR);
        break;

    case CY_IMO_FREQ_6MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_6MHZ_PTR);
        break;

    case CY_IMO_FREQ_12MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_12MHZ_PTR);
        break;

    case CY_IMO_FREQ_24MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_24MHZ_PTR);
        break;

    case CY_IMO_FREQ_48MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_MFG_CFG_IMO_TR1_PTR);
        break;

    /* The IMO frequencies above 48 MHz are not supported by PSoC5 */
    #if(!CY_PSOC5A)

        case CY_IMO_FREQ_62MHZ:
            IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_67MHZ_PTR);
            break;

    #endif  /* (!CY_PSOC5A) */

    case CY_IMO_FREQ_USB:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_USB_PTR);

        /* If USB is powered */
        if(usb_power_on == 1)
        {
            /* Lock the USB Oscillator */
            CY_USB_CR1 |= CLOCK_USB_ENABLE;
        }
        break;

    default:
            CYASSERT(0);
        break;
    }

}


/*******************************************************************************
* Function Name: CyIMO_SetFreq
********************************************************************************
*
* Summary:
*  Sets the frequency of the IMO. Changes may be made while the IMO is running.
*
* Parameters:
*  freq: Frequency of IMO operation
*       CY_IMO_FREQ_3MHZ  to set  3   MHz
*       CY_IMO_FREQ_6MHZ  to set  6   MHz
*       CY_IMO_FREQ_12MHZ to set 12   MHz
*       CY_IMO_FREQ_24MHZ to set 24   MHz
*       CY_IMO_FREQ_48MHZ to set 48   MHz
*       CY_IMO_FREQ_62MHZ to set 62.6 MHz (unsupported by PSoC 5)
*       CY_IMO_FREQ_USB   to set 24   MHz (Trimmed for USB operation)
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*  When the USB setting is chosen, the USB clock locking circuit is enabled.
*  Otherwise this circuit is disabled. The USB block must be powered before
*  selecting the USB setting.
*
*******************************************************************************/
void CyIMO_SetFreq(uint8 freq) 
{
    uint8 current_freq;
    uint8 next_freq;

    /***************************************************************************
    * When changing the IMO frequency the Trim values must also be set
    * accordingly.This requires reading the current frequency. If the new
    * frequency is faster, then set the new trim and then change the frequency,
    * otherwise change the frequency and then set the new trim values.
    ***************************************************************************/

    current_freq = FASTCLK_IMO_CR & ~CLOCK_IMO_RANGE_CLEAR;

    /* Check if the requested frequency is USB. */
    next_freq = (freq == CY_IMO_FREQ_USB) ? CY_IMO_FREQ_24MHZ : freq;

    switch (current_freq)
    {
    case 0:
        current_freq = CY_IMO_FREQ_12MHZ;
        break;

    case 1:
        current_freq = CY_IMO_FREQ_6MHZ;
        break;

    case 2:
        current_freq = CY_IMO_FREQ_24MHZ;
        break;

    case 3:
        current_freq = CY_IMO_FREQ_3MHZ;
        break;

    case 4:
        current_freq = CY_IMO_FREQ_48MHZ;
        break;

    /* The IMO frequencies above 48 MHz are not supported by PSoC5 */
    #if(!CY_PSOC5A)

        case 5:
            current_freq = CY_IMO_FREQ_62MHZ;
            break;

    #endif  /* (!CY_PSOC5A) */

    default:
        CYASSERT((uint32) 0);
        break;
    }

    if (next_freq >= current_freq)
    {
        /* Set the new trim first */
        CyIMO_SetTrimValue(freq);
    }

    /* Set the usbclk_on bit when using CY_IMO_FREQ_USB, if not clear it */
    switch(freq)
    {
    case CY_IMO_FREQ_3MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) |
            CLOCK_IMO_3MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

    case CY_IMO_FREQ_6MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) |
            CLOCK_IMO_6MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

    case CY_IMO_FREQ_12MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) |
            CLOCK_IMO_12MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

    case CY_IMO_FREQ_24MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) |
            CLOCK_IMO_24MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

    case CY_IMO_FREQ_48MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) |
            CLOCK_IMO_48MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

    /* The IMO frequencies above 48 MHz are not supported by PSoC5 */
    #if(!CY_PSOC5A)

    case CY_IMO_FREQ_62MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) |
            CLOCK_IMO_62MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

    #endif  /* (!CY_PSOC5A) */

    case CY_IMO_FREQ_USB:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) |
            CLOCK_IMO_24MHZ_VALUE) | FASTCLK_IMO_USBCLK_ON_SET;
        break;

    default:
        CYASSERT((uint32) 0);
        break;
    }

    /* Turn on the IMO Doubler, if switching to CY_IMO_FREQ_USB */
    if (freq == CY_IMO_FREQ_USB)
    {
        CyIMO_EnableDoubler();
    }
    else
    {
        CyIMO_DisableDoubler();
    }

    if (next_freq < current_freq)
    {
        /* Set the new trim after setting the frequency */
        CyIMO_SetTrimValue(freq);
    }
}


/*******************************************************************************
* Function Name: CyIMO_SetSource
********************************************************************************
*
* Summary:
*  Sets the source of the clock output from the IMO block.
*
*  The output from the IMO is by default the IMO itself. Optionally the MHz
*  Crystal or a DSI input can be the source of the IMO output instead.
*
* Parameters:
*   source, CY_IMO_SOURCE_DSI to set the DSI as source.
*           CY_IMO_SOURCE_XTAL to set the MHz as source.
*           CY_IMO_SOURCE_IMO to set the IMO itself.
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*******************************************************************************/
void CyIMO_SetSource(uint8 source) 
{
    /* Set the xclken bit of FASTCLK_IMO_CR regigster */
    switch(source)
    {
    case CY_IMO_SOURCE_DSI:
        CLKDIST_CR &= ~CLOCK_IMO2X_XTAL;
        FASTCLK_IMO_CR |= CLOCK_IMO_IMO;
        break;

    case CY_IMO_SOURCE_XTAL:
        CLKDIST_CR |= CLOCK_IMO2X_XTAL;
        FASTCLK_IMO_CR |= CLOCK_IMO_IMO;
        break;

    case CY_IMO_SOURCE_IMO:
        FASTCLK_IMO_CR &= ~CLOCK_IMO_IMO;
        break;

    default:
        /* Incorrect source value */
        CYASSERT((uint32) 0);
        break;
    }
}


/*******************************************************************************
* Function Name: CyIMO_EnableDoubler
********************************************************************************
*
* Summary:
*  Enables the IMO doubler.  The 2x frequency clock is used to convert a 24 MHz
*  input to a 48 MHz output for use by the USB block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyIMO_EnableDoubler(void) 
{
    /* Set the FASTCLK_IMO_CR_PTR regigster's 4th bit */
    FASTCLK_IMO_CR |= IMO_DOUBLER_ENABLE;
}


/*******************************************************************************
* Function Name: CyIMO_DisableDoubler
********************************************************************************
*
* Summary:
*   Disables the IMO doubler.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyIMO_DisableDoubler(void) 
{
    FASTCLK_IMO_CR &= ~IMO_DOUBLER_ENABLE;
}


/*******************************************************************************
* Function Name: CyMasterClk_SetSource
********************************************************************************
*
* Summary:
*  Sets the source of the master clock.
*
* Parameters:
*   source: One of the four available Master clock sources.
*     CY_MASTER_SOURCE_IMO
*     CY_MASTER_SOURCE_PLL
*     CY_MASTER_SOURCE_XTAL
*     CY_MASTER_SOURCE_DSI
*
* Return:
*  None
*
* Side Effects:
*  The current source and the new source must both be running and stable before
*  calling this function.
*
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*******************************************************************************/
void CyMasterClk_SetSource(uint8 source) 
{
    uint8 master_reg_1;

    #if(CY_PSOC5A)

        uint8 master_reg_0;

        /* Read the current setting */
        master_reg_0 = CLKDIST_MSTR0;

        /* Write a non-zero period to the master mux clock divider */
        if (master_reg_0 == 0x00u)
        {
            CLKDIST_MSTR0 = 3;
        }

    #endif  /* (CY_PSOC5A) */

    /* Read the current setting */
    master_reg_1 = CLKDIST_MSTR1;
    CLKDIST_MSTR1 = (master_reg_1 & MASTER_CLK_SRC_CLEAR) | (source & ~MASTER_CLK_SRC_CLEAR);

    #if(CY_PSOC5A)

        /* Restore zero period (if desired) to the master mux clock divider */
        if (master_reg_0 == 0x00u)
        {
            CLKDIST_MSTR0 = 0;
        }

    #endif  /* (CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: CyMasterClk_SetDivider
********************************************************************************
*
* Summary:
*  Sets the divider value used to generate Master Clock.
*
* Parameters:
*  uint8 divider:
*   Valid range [0-255]. The clock will be divided by this value + 1.
*   For example to divide by 2 this parameter should be set to 1.
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*  When changing the Master or Bus clock divider value from div-by-n to div-by-1
*  the first clock cycle output after the div-by-1 can be up to 4 ns shorter
*  than the final/expected div-by-1 period.
*
*******************************************************************************/
void CyMasterClk_SetDivider(uint8 divider) 
{
    CLKDIST_MSTR0 = divider;
}


/*******************************************************************************
* Function Name: CyBusClk_Internal_SetDivider
********************************************************************************
*
* Summary:
*  Function used by CyBusClk_SetDivider(). For internal use only.
*
* Parameters:
*   divider: Valid range [0-65535].
*   The clock will be divided by this value + 1.
*   For example to divide by 2 this parameter should be set to 1.
*
* Return:
*  None
*
*******************************************************************************/
void CyBusClk_Internal_SetDivider(uint16 divider)
{
    /* Clear all the masks (CLKDIST_AMASK, CLKDIST_DMASK) */
    CLKDIST_AMASK &= BUS_AMASK_CLEAR;
    CLKDIST_DMASK = BUS_DMASK_CLEAR;

    CLKDIST_BCFG2 |= CLKDIST_WRK0_MASK_SET;

    /* Change both bytes before we enable/start the clock. */
    CY_SET_REG16(CLKDIST_WRK0_PTR, divider);

    /* Load the value, set the CLKDIST_LD LOAD bit*/
    CLKDIST_LD |= CLKDIST_LD_LOAD_SET;
}


/*******************************************************************************
* Function Name: CyBusClk_SetDivider
********************************************************************************
*
* Summary:
*  Sets the divider value used to generate Bus Clock.
*
* Parameters:
*  divider: Valid range [0-65535]. The clock will be divided by this value + 1.
*  For example to divide by 2 this parameter should be set to 1.
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*******************************************************************************/
void CyBusClk_SetDivider(uint16 divider) 
{
    uint16 current_busclk_divider;
    uint8 current_masterclk_divider;

    /* Bus clock divider value */
    current_busclk_divider = CY_GET_REG16(CLKDIST_BCFG0_PTR);

    /* Work around to set the bus clock divider value */
    if ((divider == 0) || (current_busclk_divider == 0))
    {
        /* Save away the master clock divider value */
        current_masterclk_divider = CY_GET_REG8(CLKDIST_MSTR0_PTR);
        if (current_masterclk_divider < MASTERCLK_DIVIDER_VALUE)
        {
            /* Set master clock divider to 7 */
            CyMasterClk_SetDivider(MASTERCLK_DIVIDER_VALUE);
        }

        if (divider == 0)
        {
            /* Set the SSS bit and the divider register desired value */
            CLKDIST_BCFG2 |= CLKDIST_BCFG2_SSS_SET;
            CyBusClk_Internal_SetDivider(divider);
        }
        else
        {
            CyBusClk_Internal_SetDivider(divider);
            CLKDIST_BCFG2 &= ~CLKDIST_BCFG2_SSS_SET;
        }

        /* Restore the master clock */
        CyMasterClk_SetDivider(current_masterclk_divider);
    }
    else
    {
        CyBusClk_Internal_SetDivider(divider);
    }
}


#if(CY_PSOC3)

    /*******************************************************************************
    * Function Name: CyCpuClk_SetDivider
    ********************************************************************************
    *
    * Summary:
    *  Sets the divider value used to generate the CPU Clock. Only applicable for
    *  PSoC 3 parts.
    *
    * Parameters:
    *  divider: Valid range [0-15]. The clock will be divided by this value + 1.
    *  For example to divide by 2 this parameter should be set to 1.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  If as result of this function execution the CPU clock frequency is increased
    *  then the number of clock cycles the cache will wait before it samples data
    *  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
    *  with appropriate parameter. It can be optionally called if CPU clock
    *  frequency is lowered in order to improve CPU performance.
    *  See CyFlash_SetWaitCycles() description for more information.
    *
    *******************************************************************************/
    void CyCpuClk_SetDivider(uint8 divider) 
    {
            CLKDIST_MSTR1 = (CLKDIST_MSTR1 & CLKDIST_MSTR1_DIV_CLEAR) |
                                (divider << CLKDIST_DIV_POSITION);
    }

#endif /* (CY_PSOC3) */


/*******************************************************************************
* Function Name: CyUsbClk_SetSource
********************************************************************************
*
* Summary:
*  Sets the source of the USB clock.
*
* Parameters:
*  source: One of the four available USB clock sources
*             USB_CLK_IMO2X     - IMO 2x
*             USB_CLK_IMO       - IMO
*             USB_CLK_PLL       - PLL
*             USB_CLK_DSI       - DSI
*
* Return:
*  None
*
*******************************************************************************/
void CyUsbClk_SetSource(uint8 source) 
{
    CLKDIST_UCFG = (CLKDIST_UCFG & ~USB_CLKDIST_CONFIG_MASK) |
                        (USB_CLKDIST_CONFIG_MASK & source);
}


/*******************************************************************************
* Function Name: CyILO_Start1K
********************************************************************************
*
* Summary:
*  Enables the ILO 1 KHz oscillator.
*
*  Note The ILO 1 KHz oscillator is always enabled by default, regardless of the
*  selection in the Clock Editor. Therefore, this API is only needed if the
*  oscillator was turned off manually.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_Start1K(void) 
{
    /* Set the bit 1 of ILO RS */
    SLOWCLK_ILO_CR0 |= ILO_CONTROL_1KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Stop1K
********************************************************************************
*
* Summary:
*  Disables the ILO 1 KHz oscillator.
*
*  Note The ILO 1 KHz oscillator must be enabled if Sleep or Hibernate low power
*  mode APIs are expected to be used. For more information, refer to the Power
*  Management section of this document.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  PSoC5: Stopping the ILO 1 kHz could break the active WDT functionality.
*
*******************************************************************************/
void CyILO_Stop1K(void) 
{
    /* Clear the bit 1 of ILO RS */
    SLOWCLK_ILO_CR0 &= ~ILO_CONTROL_1KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Start100K
********************************************************************************
*
* Summary:
*  Enables the ILO 100 KHz oscillator.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_Start100K(void) 
{
    /* Set the bit 2 of ILO RS */
    SLOWCLK_ILO_CR0 |= ILO_CONTROL_100KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Stop100K
********************************************************************************
*
* Summary:
*  Disables the ILO 100 KHz oscillator.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_Stop100K(void) 
{
    /* Clear the bit 2 of ILO RS */
    SLOWCLK_ILO_CR0 &= ~ILO_CONTROL_100KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Enable33K
********************************************************************************
*
* Summary:
*  Enables the ILO 33 KHz divider.
*
*  Note that the 33 KHz clock is generated from the 100 KHz oscillator,
*  so it must also be running in order to generate the 33 KHz output.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_Enable33K(void) 
{
    /* Set the bit 5 of ILO RS */
    SLOWCLK_ILO_CR0 |= ILO_CONTROL_33KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Disable33K
********************************************************************************
*
* Summary:
*  Disables the ILO 33 KHz divider.
*
*  Note that the 33 KHz clock is generated from the 100 KHz oscillator, but this
*  API does not disable the 100 KHz clock.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_Disable33K(void) 
{
    /* Clear the bit 5 of ILO RS */
    SLOWCLK_ILO_CR0 &= ~ILO_CONTROL_33KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_SetSource
********************************************************************************
*
* Summary:
*  Sets the source of the clock output from the ILO block.
*
* Parameters:
*  source: One of the three available ILO output sources
*       Value        Define                Source
*       0            CY_ILO_SOURCE_100K    ILO 100 KHz
*       1            CY_ILO_SOURCE_33K     ILO 33 KHz
*       2            CY_ILO_SOURCE_1K      ILO 1 KHz
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_SetSource(uint8 source) 
{
    CLKDIST_CR = (CLKDIST_CR & CY_ILO_SOURCE_BITS_CLEAR) |
                    ((source << 2) & ~CY_ILO_SOURCE_BITS_CLEAR);
}


/*******************************************************************************
* Function Name: CyILO_SetPowerMode
********************************************************************************
*
* Summary:
*  Sets the power mode used by the ILO during power down. Allows for lower power
*  down power usage resulting in a slower startup time.
*
* Parameters:
*  uint8 mode
*   CY_ILO_FAST_START - Faster start-up, internal bias left on when powered down
*   CY_ILO_SLOW_START - Slower start-up, internal bias off when powered down
*
* Return:
*   Prevous power mode state.
*
*******************************************************************************/
uint8 CyILO_SetPowerMode(uint8 mode) 
{
    uint8 state;

    /* Get current state. */
    state = SLOWCLK_ILO_CR0;

    /* Set the the oscillator power mode. */
    if(mode != CY_ILO_FAST_START)
    {
        SLOWCLK_ILO_CR0 = (state | ILO_CONTROL_PD_MODE);
    }
    else
    {
        SLOWCLK_ILO_CR0 = (state & ~ILO_CONTROL_PD_MODE);
    }

    /* Return the old mode. */
    return ((state & ILO_CONTROL_PD_MODE) >> ILO_CONTROL_PD_POSITION);
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_Start
********************************************************************************
*
* Summary:
*  Enables the 32 KHz Crystal Oscillator.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyXTAL_32KHZ_Start(void) 
{
    volatile uint32 i;

    CY_CLK_XTAL32_TST_REG = CY_CLK_XTAL32_TST_DEFAULT;
    CY_CLK_XTAL32_TR_REG  = CY_CLK_XTAL32_TR_STARTUP;
    CY_CLK_XTAL32_CFG_REG = (CY_CLK_XTAL32_CFG_REG & ~CY_CLK_XTAL32_CFG_LP_MASK) | CY_CLK_XTAL32_CFG_LP_DEFAULT;

    #if(CY_PSOC3)
        CY_CLK_XTAL32_CR_REG |= CY_CLK_XTAL32_CR_PDBEN;
    #endif  /* (CY_PSOC3) */

    /* Enable operation of the 32K Crystal Oscillator */
    CY_CLK_XTAL32_CR_REG |= CY_CLK_XTAL32_CR_EN;

    for (i = 1000u; i > 0u; i--)
    {
        if(0u != (CyXTAL_32KHZ_ReadStatus() & CY_XTAL32K_ANA_STAT))
        {
            /* Ready - switch to the hign power mode */
            (void) CyXTAL_32KHZ_SetPowerMode(0u);

            break;
        }
        CyDelayUs(1u);
    }
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_Stop
********************************************************************************
*
* Summary:
*  Disables the 32KHz Crystal Oscillator.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyXTAL_32KHZ_Stop(void) 
{
    CY_CLK_XTAL32_TST_REG  = CY_CLK_XTAL32_TST_DEFAULT;
    CY_CLK_XTAL32_TR_REG   = CY_CLK_XTAL32_TR_POWERDOWN;
    CY_CLK_XTAL32_CFG_REG = (CY_CLK_XTAL32_CFG_REG & ~CY_CLK_XTAL32_CFG_LP_MASK) | CY_CLK_XTAL32_CFG_LP_DEFAULT;
    CY_CLK_XTAL32_CR_REG &= ~(CY_CLK_XTAL32_CR_EN | CY_CLK_XTAL32_CR_LPM);

    #if(CY_PSOC3)
        CY_CLK_XTAL32_CR_REG &= ~CY_CLK_XTAL32_CR_PDBEN;
    #endif  /* (CY_PSOC3) */
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_ReadStatus
********************************************************************************
*
* Summary:
*  Returns status of the 32 KHz oscillator.
*
* Parameters:
*  None
*
* Return:
*  Value     Define                    Source
*  20        CY_XTAL32K_ANA_STAT       Analog measurement
*                                       1: Stable
*                                       0: Not stable
*
*******************************************************************************/
uint8 CyXTAL_32KHZ_ReadStatus(void) 
{
    return(CY_CLK_XTAL32_CR_REG & CY_XTAL32K_ANA_STAT);
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_SetPowerMode
********************************************************************************
*
* Summary:
*  Sets the power mode for the 32 KHz oscillator used during sleep mode.
*  Allows for lower power during sleep when there are fewer sources of noise.
*  During active mode the oscillator is always run in high power mode.
*
* Parameters:
*  uint8 mode
*       0: High power mode
*       1: Low power mode during sleep
*
* Return:
*  Previous power mode.
*
*******************************************************************************/
uint8 CyXTAL_32KHZ_SetPowerMode(uint8 mode) 
{
    uint8 state = (0u != (CY_CLK_XTAL32_CR_REG & CY_CLK_XTAL32_CR_LPM)) ? 1u : 0u;

    CY_CLK_XTAL32_TST_REG = CY_CLK_XTAL32_TST_DEFAULT;

    if(1u == mode)
    {
        /* Low power mode during Sleep */
        CY_CLK_XTAL32_TR_REG  = CY_CLK_XTAL32_TR_LOW_POWER;
        CyDelayUs(10u);
        CY_CLK_XTAL32_CFG_REG = (CY_CLK_XTAL32_CFG_REG & ~CY_CLK_XTAL32_CFG_LP_MASK) | CY_CLK_XTAL32_CFG_LP_LOWPOWER;
        CyDelayUs(20u);
        CY_CLK_XTAL32_CR_REG |= CY_CLK_XTAL32_CR_LPM;
    }
    else
    {
        /* High power mode */
        CY_CLK_XTAL32_TR_REG  = CY_CLK_XTAL32_TR_HIGH_POWER;
        CyDelayUs(10u);
        CY_CLK_XTAL32_CFG_REG = (CY_CLK_XTAL32_CFG_REG & ~CY_CLK_XTAL32_CFG_LP_MASK) | CY_CLK_XTAL32_CFG_LP_DEFAULT;
        CY_CLK_XTAL32_CR_REG &= ~CY_CLK_XTAL32_CR_LPM;
    }

    return(state);
}


/*******************************************************************************
* Function Name: CyXTAL_Start
********************************************************************************
*
* Summary:
*  Enables the megahertz crystal.
*
*  PSoC3:
*  Waits until the XERR bit is low (no error) for a millisecond or until the
*  number of milliseconds specified by the wait parameter has expired.
*
*  PSoC5:
*  Waits for CY_CLK_XMHZ_MIN_TIMEOUT milliseconds (or number of milliseconds
*  specified by parameter if it is greater than CY_CLK_XMHZ_MIN_TIMEOUT. The
*  XERR bit status is not checked.
*
* Parameters:
*   wait: Valid range [0-255].
*   This is the timeout value in milliseconds.
*   The appropriate value is crystal specific.
*
* Return:
*   CYRET_SUCCESS - Completed successfully
*   CYRET_TIMEOUT - Timeout occurred without detecting a low value on XERR.
*
* Side Effects and Restrictions:
*  If wait is enabled (non-zero wait). Uses the Fast Timewheel to time the wait.
*  Any other use of the Fast Timewheel (FTW) will be stopped during the period
*  of this function and then restored.
*
*  Uses the 100KHz ILO.  If not enabled, this function will enable the 100KHz
*  ILO for the period of this function. No changes to the setup of the ILO,
*  Fast Timewheel, Central Timewheel or Once Per Second interrupt may be made
*  by interrupt routines during the period of this function.
*
*  The current operation of the ILO, Central Timewheel and Once Per Second
*  interrupt are maintained during the operation of this function provided the
*  reading of the Power Manager Interrupt Status Register is only done using the
*  CyPmReadStatus() function.
*
*******************************************************************************/
cystatus CyXTAL_Start(uint8 wait) 
{
    cystatus status = CYRET_SUCCESS;

    #if(CY_PSOC5A)
        volatile uint8  timeout = (wait < CY_CLK_XMHZ_MIN_TIMEOUT) ? CY_CLK_XMHZ_MIN_TIMEOUT : wait;
    #else
        volatile uint8  timeout = wait;
    #endif  /* (CY_PSOC5A) */

    volatile uint8 count;
    uint8 iloEnableState;
    uint8 pmTwCfg0;
    uint8 pmTwCfg2;


    /* Enables the MHz crystal oscillator circuit  */
    CY_CLK_XMHZ_CSR_REG |= CY_CLK_XMHZ_CSR_ENABLE;


    if(wait > 0)
    {
        /* Save 100 KHz ILO, FTW interval, enable and interrupt enable */
        iloEnableState = SLOWCLK_ILO_CR0;
        pmTwCfg0 = CY_PM_TW_CFG0_REG;
        pmTwCfg2 = CY_PM_TW_CFG2_REG;

        /* Set 250 us interval */
        CyPmFtwSetInterval(CY_CLK_XMHZ_FTW_INTERVAL);
        status = CYRET_TIMEOUT;


        for( ; timeout > 0; timeout--)
        {
            #if(!CY_PSOC5A)

                /* Read XERR bit to clear it */
                (void) CY_CLK_XMHZ_CSR_REG;

            #endif  /* (!CY_PSOC5A) */


            /* Wait for a millisecond - 4 x 250 us */
            for(count = 4u; count > 0u; count--)
            {
                while(!(CY_PM_FTW_INT == CyPmReadStatus(CY_PM_FTW_INT)))
                {
                    /* Wait for the FTW interrupt event */
                }
            }


            #if(!CY_PSOC5A)

                /*******************************************************************
                * High output indicates oscillator failure.
                * Only can be used after start-up interval (1 ms) is completed.
                *******************************************************************/
                if(0u == (CY_CLK_XMHZ_CSR_REG & CY_CLK_XMHZ_CSR_XERR))
                {
                    status = CYRET_SUCCESS;
                    break;
                }

            #endif  /* (!CY_PSOC5A) */
        }


        /* Restore 100 KHz ILO, FTW interval, enable and interrupt enable */
        if(0u == (iloEnableState & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Stop100K();
        }
        CY_PM_TW_CFG0_REG = pmTwCfg0;
        CY_PM_TW_CFG2_REG = pmTwCfg2;
    }

    return(status);
}


/*******************************************************************************
* Function Name: CyXTAL_Stop
********************************************************************************
*
* Summary:
*  Disables the megahertz crystal oscillator.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyXTAL_Stop(void) 
{
    /* Disable the the oscillator. */
    FASTCLK_XMHZ_CSR &= ~XMHZ_CONTROL_ENABLE;
}


#if(!CY_PSOC5A)

    /*******************************************************************************
    * Function Name: CyXTAL_EnableErrStatus
    ********************************************************************************
    *
    * Summary:
    *  Enables the generation of the XERR status bit for the megahertz crystal.
    *  This function is not available for PSoC5.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_EnableErrStatus(void) 
    {
        /* If oscillator has insufficient amplitude, XERR bit will be high. */
        CY_CLK_XMHZ_CSR_REG &= ~CY_CLK_XMHZ_CSR_XFB;
    }


    /*******************************************************************************
    * Function Name: CyXTAL_DisableErrStatus
    ********************************************************************************
    *
    * Summary:
    *  Disables the generation of the XERR status bit for the megahertz crystal.
    *  This function is not available for PSoC5.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_DisableErrStatus(void) 
    {
        /* If oscillator has insufficient amplitude, XERR bit will be high. */
        CY_CLK_XMHZ_CSR_REG |= CY_CLK_XMHZ_CSR_XFB;
    }


    /*******************************************************************************
    * Function Name: CyXTAL_ReadStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the XERR status bit for the megahertz crystal. This status bit is a
    *  sticky clear on read value. This function is not available for PSoC5.
    *
    * Parameters:
    *  None
    *
    * Return:
    *   Status
    *    0: No error
    *    1: Error
    *
    *******************************************************************************/
    uint8 CyXTAL_ReadStatus(void) 
    {
        /***************************************************************************
        * High output indicates oscillator failure. Only use this after start-up
        * interval is completed. This can be used for status and failure recovery.
        ***************************************************************************/
        return((0u != (CY_CLK_XMHZ_CSR_REG & CY_CLK_XMHZ_CSR_XERR)) ? 1u : 0u);
    }


    /*******************************************************************************
    * Function Name: CyXTAL_EnableFaultRecovery
    ********************************************************************************
    *
    * Summary:
    *  Enables the fault recovery circuit which will switch to the IMO in the case
    *  of a fault in the megahertz crystal circuit. The crystal must be up and
    *  running with the XERR bit at 0, before calling this function to prevent
    *  immediate fault switchover. This function is not available for PSoC5.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_EnableFaultRecovery(void) 
    {
        CY_CLK_XMHZ_CSR_REG |= CY_CLK_XMHZ_CSR_XPROT;
    }


    /*******************************************************************************
    * Function Name: CyXTAL_DisableFaultRecovery
    ********************************************************************************
    *
    * Summary:
    *  Disables the fault recovery circuit which will switch to the IMO in the case
    *  of a fault in the megahertz crystal circuit. This function is not available
    *  for PSoC5.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_DisableFaultRecovery(void) 
    {
        CY_CLK_XMHZ_CSR_REG &= ~CY_CLK_XMHZ_CSR_XPROT;
    }

#endif  /* (!CY_PSOC5A) */

/*******************************************************************************
* Function Name: CyXTAL_SetStartup
********************************************************************************
*
* Summary:
*  Sets the startup settings for the crystal. Logic model outputs a frequency
*  (setting + 4) MHz when enabled.
*
*  This is artificial as the actual frequency is determined by an attached
*  external crystal.
*
* Parameters:
*  setting: Valid range [0-31].
*   Value is dependent on the frequency and quality of the crystal being used.
*   Refer to the device TRM and datasheet for more information.
*
* Return:
*  None
*
*******************************************************************************/
void CyXTAL_SetStartup(uint8 setting) 
{
    CY_CLK_XMHZ_CFG0_REG = (CY_CLK_XMHZ_CFG0_REG & ~CY_CLK_XMHZ_CFG0_XCFG_MASK) |
                           (setting & CY_CLK_XMHZ_CFG0_XCFG_MASK);
}


#if(CY_PSOC3 || CY_PSOC5LP)
    /*******************************************************************************
    * Function Name: CyXTAL_SetFbVoltage
    ********************************************************************************
    *
    * Summary:
    *  Sets the feedback reference voltage to use for the crystal circuit.
    *  This function is only available for PSoC3 and PSoC 5LP.
    *
    * Parameters:
    *  setting: Valid range [0-15].
    *  Refer to the device TRM and datasheet for more information.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_SetFbVoltage(uint8 setting) 
    {
        CY_CLK_XMHZ_CFG1_REG = ((CY_CLK_XMHZ_CFG1_REG & ~CY_CLK_XMHZ_CFG1_VREF_FB_MASK) |
                                (setting & CY_CLK_XMHZ_CFG1_VREF_FB_MASK));
    }


    /*******************************************************************************
    * Function Name: CyXTAL_SetWdVoltage
    ********************************************************************************
    *
    * Summary:
    *  Sets the reference voltage used by the watchdog to detect a failure in the
    *  crystal circuit. This function is only available for PSoC3 and PSoC 5LP.
    *
    * Parameters:
    *  setting: Valid range [0-7].
    *  Refer to the device TRM and datasheet for more information.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_SetWdVoltage(uint8 setting) 
    {
        CY_CLK_XMHZ_CFG1_REG = ((CY_CLK_XMHZ_CFG1_REG & ~CY_CLK_XMHZ_CFG1_VREF_WD_MASK) |
                                ((setting << 4) & CY_CLK_XMHZ_CFG1_VREF_WD_MASK));
    }

#endif /* (CY_PSOC3 || CY_PSOC5LP) */


/*******************************************************************************
* Function Name: CyHalt
********************************************************************************
*
* Summary:
*  Halts the CPU.
*
* Parameters:
*  uint8 reason: Value to be used during debugging.
*
* Return:
*  None
*
*******************************************************************************/
void CyHalt(uint8 reason) CYREENTRANT
{
    reason = reason;

    #if defined (__ARMCC_VERSION)
        __breakpoint(0x0);
    #elif defined(__GNUC__)
        __asm("    bkpt    1");
    #elif defined(__C51__)
        CYDEV_HALT_CPU;
    #endif  /* (__ARMCC_VERSION) */
}


/*******************************************************************************
* Function Name: CySoftwareReset
********************************************************************************
*
* Summary:
*  Forces a software reset of the device.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySoftwareReset(void) 
{
    /* Perform software reset */
    *RESET_CR2 = 0x1;
}


/*******************************************************************************
* Function Name: CyDelay
********************************************************************************
*
* Summary:
*  Blocks for milliseconds.
*
*  Note:
*  CyDelay has been implemented with the instruction cache assumed enabled. When
*  instruction cache is disabled on PSoC5, CyDelay will be two times larger. For
*  example, with instruction cache disabled CyDelay(100) would result in about
*  200 ms delay instead of 100 ms.
*
* Parameters:
*  milliseconds: number of milliseconds to delay.
*
* Return:
*   None
*
*******************************************************************************/
void CyDelay(uint32 milliseconds) CYREENTRANT
{
    while (milliseconds > 32768)
    {
        /***********************************************************************
        * This loop prevents overflow.At 100MHz, milliseconds * delay_freq_khz
        * overflows at about 42 seconds.
        ***********************************************************************/
        CyDelayCycles(cydelay_32k_ms);
        milliseconds -= 32768;
    }

    CyDelayCycles(milliseconds * cydelay_freq_khz);
}


#if(!CY_PSOC3)

    /* For PSoC3 devices function is defined in CyBootAsmKeil.a51 file */

    /*******************************************************************************
    * Function Name: CyDelayUs
    ********************************************************************************
    *
    * Summary:
    *  Blocks for microseconds.
    *
    *  Note:
    *   CyDelay has been implemented with the instruction cache assumed enabled.
    *   When instruction cache is disabled on PSoC5, CyDelayUs will be two times
    *   larger. Ex: With instruction cache disabled CyDelayUs(100) would result
    *   in about 200us delay instead of 100us.
    *
    * Parameters:
    *  uint16 microseconds: number of microseconds to delay.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  CyDelayUS has been implemented with the instruction cache assumed enabled.
    *  When instruction cache is disabled on PSoC 5, CyDelayUs will be two times
    *  larger. For example, with instruction cache disabled CyDelayUs(100) would
    *  result in about 200 us delay instead of 100 us.
    *
    *  If the bus clock frequency is a small non-integer number, the actual delay
    *  can be up to twice as long as the nominal value. The actual delay cannot be
    *  shorter than the nominal one.
    *******************************************************************************/
    void CyDelayUs(uint16 microseconds) CYREENTRANT
    {
        CyDelayCycles((uint32)microseconds * cydelay_freq_mhz);
    }

#endif  /* (!CY_PSOC3) */


/*******************************************************************************
* Function Name: CyDelayFreq
********************************************************************************
*
* Summary:
*  Sets clock frequency for CyDelay.
*
* Parameters:
*  freq: Frequency of bus clock in Hertz.
*
* Return:
*  None
*
*******************************************************************************/
void CyDelayFreq(uint32 freq) CYREENTRANT
{
    if (freq != 0u)
    {
        cydelay_freq_hz = freq;
    }
    else
    {
        cydelay_freq_hz = BCLK__BUS_CLK__HZ;
    }

    cydelay_freq_mhz = (uint8)((cydelay_freq_hz + 999999u) / 1000000u);
    cydelay_freq_khz = (cydelay_freq_hz + 999u) / 1000u;
    cydelay_32k_ms   = 32768 * cydelay_freq_khz;
}


/*******************************************************************************
* Function Name: CyWdtStart
********************************************************************************
*
* Summary:
*  Enables the watchdog timer.
*
*  The timer is configured for the specified count interval, the central
*  timewheel is cleared, the setting for low power mode is configured and the
*  watchdog timer is enabled.
*
*  Once enabled the watchdog cannot be disabled. The watchdog counts each time
*  the Central Time Wheel (CTW) reaches the period specified. The watchdog must
*  be cleared using the CyWdtClear() function before three ticks of the watchdog
*  timer occur. The CTW is free running, so this will occur after between 2 and
*  3 timer periods elapse.
*
*  PSoC5: The watchdog timer should not be used during sleep modes. Since the
*  WDT cannot be disabled after it is enabled, the WDT timeout period can be
*  set to be greater than the sleep wakeup period, then feed the dog on each
*  wakeup from Sleep.
*
* Parameters:
*  ticks: One of the four available timer periods. Once WDT enabled, the
   interval cannot be changed.
*         CYWDT_2_TICKS     -     4 - 6     ms
*         CYWDT_16_TICKS    -    32 - 48    ms
*         CYWDT_128_TICKS   -   256 - 384   ms
*         CYWDT_1024_TICKS  - 2.048 - 3.072 s
*
*  lpMode: Low power mode configuration. This parameter is ignored for PSoC 5.
*          The WDT always acts as if CYWDT_LPMODE_NOCHANGE is passed.
*
*          CYWDT_LPMODE_NOCHANGE - No Change
*          CYWDT_LPMODE_MAXINTER - Switch to longest timer mode during low power
*                                 mode
*          CYWDT_LPMODE_DISABLED - Disable WDT during low power mode
*
* Return:
*  None
*
* Side Effects:
*  PSoC5: The ILO 1 KHz must be enabled for proper WDT operation. Stopping the
*  ILO 1 kHz could break the active WDT functionality.
*
*******************************************************************************/
void CyWdtStart(uint8 ticks, uint8 lpMode) 
{
    #if(CY_PSOC5A)
        CyILO_Start1K();
    #endif  /* (CY_PSOC5A) */

    /* Set WDT interval */
    CY_WDT_CFG_REG = (CY_WDT_CFG_REG & ~CY_WDT_CFG_INTERVAL_MASK) | (ticks & CY_WDT_CFG_INTERVAL_MASK);

    /* Reset CTW to ensure that first watchdog period is full */
    CY_WDT_CFG_REG |= CY_WDT_CFG_CTW_RESET;
    CY_WDT_CFG_REG &= ~CY_WDT_CFG_CTW_RESET;

    #if(!CY_PSOC5A)

        /* Setting the low power mode */
        CY_WDT_CFG_REG = ((lpMode << CY_WDT_CFG_LPMODE_SHIFT) & CY_WDT_CFG_LPMODE_MASK) |
                          (CY_WDT_CFG_REG & ~CY_WDT_CFG_LPMODE_MASK);
    #else

        /* To avoid warning of lpmode being unreferenced. */
        lpMode = lpMode;

    #endif  /* (!CY_PSOC5A) */

    /* Enables the watchdog reset */
    CY_WDT_CFG_REG |= CY_WDT_CFG_WDR_EN;
}


/*******************************************************************************
* Function Name: CyWdtClear
********************************************************************************
*
* Summary:
*  Clears (feeds) the watchdog timer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyWdtClear(void) 
{
    #if(CY_PSOC5A)

        /* PSoC5 ES1 watchdog time clear requires workaround */
        uint8 wdtCfg = CY_WDT_CFG_REG;
        CY_WDT_CR_REG  = CY_WDT_CR_FEED;
        CY_WDT_CFG_REG = CY_WDT_CFG_CLEAR_ALL;
        CY_WDT_CFG_REG = wdtCfg;

    #else

        CY_WDT_CR_REG = CY_WDT_CR_FEED;

    #endif  /* (CY_PSOC5A) */
}



/*******************************************************************************
* Function Name: CyVdLvDigitEnable
********************************************************************************
*
* Summary:
*  Enables the digital low voltage monitors to generate interrupt on Vddd
*   archives specified threshold and optionally resets device.
*
* Parameters:
*  reset: Option to reset device at a specified Vddd threshold:
*           0 - Device is not reset.
*           1 - Device is reset.
*         This option is applicable for PSoC 3/PSoC 5LP devices only.
*
*  threshold: Sets the trip level for the voltage monitor.
*  Values from 1.70 V to 5.45 V(for PSoC 3/PSoC 5LP) and from 2.45 V to 5.45 V
*  (for PSoC 5TM) are accepted with the approximately 250 mV interval.
*
* Return:
*  None
*
*******************************************************************************/
void CyVdLvDigitEnable(uint8 reset, uint8 threshold) 
{
    *CYINT_CLEAR |= 0x01u;

    #if(CY_PSOC3 || CY_PSOC5LP)
        CY_VD_PRES_CONTROL_REG &= (~CY_VD_PRESD_EN);
    #endif /*(CY_PSOC3 || CY_PSOC5LP)*/

    CY_VD_LVI_TRIP_REG = (threshold & CY_VD_LVI_TRIP_LVID_MASK) | (CY_VD_LVI_TRIP_REG & ~CY_VD_LVI_TRIP_LVID_MASK);
    CY_VD_LVI_HVI_CONTROL_REG |= CY_VD_LVID_EN;

    /* Timeout to eliminate glitches on the LVI/HVI when enabling */
    CyDelayUs(1u);
	
	(void)CY_VD_PERSISTENT_STATUS_REG;

    #if(CY_PSOC3 || CY_PSOC5LP)
        if(0u != reset)
        {
            CY_VD_PRES_CONTROL_REG |= CY_VD_PRESD_EN;
        }
        else
        {
            CY_VD_PRES_CONTROL_REG &= (~CY_VD_PRESD_EN);
        }
    #else
        reset = reset;
    #endif /*(CY_PSOC3 || CY_PSOC5LP)*/

    *CYINT_CLR_PEND |= 0x01u;
    *CYINT_ENABLE   |= 0x01u;
}


/*******************************************************************************
* Function Name: CyVdLvAnalogEnable
********************************************************************************
*
* Summary:
*  Enables the analog low voltage monitors to generate interrupt on Vdda
*   archives specified threshold and optionally resets device.
*
* Parameters:
*  reset: Option to reset device at a specified Vdda threshold:
*           0 - Device is not reset.
*           1 - Device is reset.
*         This option is applicable for PSoC 3/PSoC 5LP devices only.
*
*  threshold: Sets the trip level for the voltage monitor.
*  Values from 1.70 V to 5.45 V(for PSoC 3/PSoC 5LP) and from 2.45 V to 5.45 V
*  (for PSoC 5TM) are accepted with the approximately 250 mV interval.
*
* Return:
*  None
*
*******************************************************************************/
void CyVdLvAnalogEnable(uint8 reset, uint8 threshold) 
{
    *CYINT_CLEAR |= 0x01u;

    #if(CY_PSOC3 || CY_PSOC5LP)
        CY_VD_PRES_CONTROL_REG &= (~CY_VD_PRESA_EN);
    #endif /*(CY_PSOC3 || CY_PSOC5LP)*/

    CY_VD_LVI_TRIP_REG = (threshold << 4) | (CY_VD_LVI_TRIP_REG & 0x0F);
    CY_VD_LVI_HVI_CONTROL_REG |= CY_VD_LVIA_EN;

    /* Timeout to eliminate glitches on the LVI/HVI when enabling */
    CyDelayUs(1u);
	
	(void)CY_VD_PERSISTENT_STATUS_REG;

    #if(CY_PSOC3 || CY_PSOC5LP)
        if(0u != reset)
        {
            CY_VD_PRES_CONTROL_REG |= CY_VD_PRESA_EN;
        }
        else
        {
            CY_VD_PRES_CONTROL_REG &= (~CY_VD_PRESA_EN);
        }
    #else
        reset = reset;
    #endif /*(CY_PSOC3 || CY_PSOC5LP)*/

    *CYINT_CLR_PEND |= 0x01u;
    *CYINT_ENABLE   |= 0x01u;
}


/*******************************************************************************
* Function Name: CyVdLvDigitDisable
********************************************************************************
*
* Summary:
*  Disables the digital low voltage monitor (interrupt and device reset are
*  disabled).
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyVdLvDigitDisable(void) 
{
    CY_VD_LVI_HVI_CONTROL_REG &= (~CY_VD_LVID_EN);

    #if(CY_PSOC3 || CY_PSOC5LP)
        CY_VD_PRES_CONTROL_REG &= (~CY_VD_PRESD_EN);
    #endif /*(CY_PSOC3 || CY_PSOC5LP)*/

    while(CY_VD_PERSISTENT_STATUS_REG & 0x07u);

}


/*******************************************************************************
* Function Name: CyVdLvAnalogDisable
********************************************************************************
*
* Summary:
*  Disables the analog low voltage monitor
*  (interrupt and device reset are disabled).
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyVdLvAnalogDisable(void) 
{
    CY_VD_LVI_HVI_CONTROL_REG &= (~CY_VD_LVIA_EN);

    #if(CY_PSOC3 || CY_PSOC5LP)
        CY_VD_PRES_CONTROL_REG &= (~CY_VD_PRESA_EN);
    #endif /*(CY_PSOC3 || CY_PSOC5LP)*/

    while(CY_VD_PERSISTENT_STATUS_REG & 0x07u);
}


/*******************************************************************************
* Function Name: CyVdHvAnalogEnable
********************************************************************************
*
* Summary:
*  Enables the analog high voltage monitors to generate interrupt on
*  Vdda archives 5.75 V threshold and optionally resets device.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyVdHvAnalogEnable(void) 
{
    *CYINT_CLEAR |= 0x01u;

    #if(CY_PSOC3 || CY_PSOC5LP)
        CY_VD_PRES_CONTROL_REG &= (~CY_VD_PRESA_EN);
    #endif /*(CY_PSOC3 || CY_PSOC5LP)*/

    CY_VD_LVI_HVI_CONTROL_REG |= CY_VD_HVIA_EN;

    /* Timeout to eliminate glitches on the LVI/HVI when enabling */
    CyDelayUs(1u);
	
	(void)CY_VD_PERSISTENT_STATUS_REG;

    *CYINT_CLR_PEND |= 0x01u;
    *CYINT_ENABLE   |= 0x01u;
}


/*******************************************************************************
* Function Name: CyVdHvAnalogDisable
********************************************************************************
*
* Summary:
*  Disables the analog low voltage monitor
*  (interrupt and device reset are disabled).
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyVdHvAnalogDisable(void) 
{
    CY_VD_LVI_HVI_CONTROL_REG &= (~CY_VD_HVIA_EN);
}


/*******************************************************************************
* Function Name: CyVdStickyStatus
********************************************************************************
*
* Summary:
*  Manages the Reset and Voltage Detection Status Register 0.
*  This register has the interrupt status for the HVIA, LVID and LVIA.
*  This hardware register clears on read.
*
* Parameters:
*  mask: Bits in the shadow register to clear.
*       Value        Define                Bit To Clear
*       0x01         CY_VD_LVID            LVID
*       0x02         CY_VD_LVIA            LVIA
*       0x04         CY_VD_HVIA            HVIA
*
* Return:
*  Status.  Same enumerated bit values as used for the mask parameter.
*
*******************************************************************************/
uint8 CyVdStickyStatus(uint8 mask) 
{
    uint8 status;

    status = CY_VD_PERSISTENT_STATUS_REG;
    CY_VD_PERSISTENT_STATUS_REG &= (~mask);

    return(status);
}


/*******************************************************************************
* Function Name: CyVdRealTimeStatus
********************************************************************************
*
* Summary:
*  Returns the real time voltage detection status.
*
* Parameters:
*  None
*
* Return:
*  Status. Same enumerated bit values as used for the mask parameter.
*
*******************************************************************************/
uint8 CyVdRealTimeStatus(void) 
{
    uint8 interruptState;
    uint8 VdFlagsState;

    interruptState = CyEnterCriticalSection();
    VdFlagsState = CY_VD_RT_STATUS_REG;
    CyExitCriticalSection(interruptState);

    return(VdFlagsState);
}


/*******************************************************************************
* Function Name: CyDisableInts
********************************************************************************
*
* Summary:
*  Disables the interrupt enable for each interrupt.
*
* Parameters:
*  None
*
* Return:
*  32 bit mask of previously enabled interrupts.
*
*******************************************************************************/
uint32 CyDisableInts(void) 
{
    uint32 intState;

    /* Get the curreent interrutp state. */
    intState = CY_GET_REG32(CYINT_CLEAR);

    /* Disable all of the interrupts. */
    CY_SET_REG32(CYINT_CLEAR, 0xFFFFFFFF);

    return (intState);
}


/*******************************************************************************
* Function Name: CyEnableInts
********************************************************************************
*
* Summary:
*  Enables interrupts to a given state.
*
* Parameters:
*  uint32 mask: 32 bit mask of interrupts to enable.
*
* Return:
*  None
*
*******************************************************************************/
void CyEnableInts(uint32 mask) 
{
    /* Set interrupts as enabled. */
    CY_SET_REG32(CYINT_ENABLE, mask);
}

#if(CY_PSOC5)

    /*******************************************************************************
    * Function Name: CyFlushCache
    ********************************************************************************
    * Summary:
    *  Flushes the PSoC 5 cache by invalidating all entries.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyFlushCache() CYREENTRANT
    {
        /* read the register, set the flush bit, write back */
        uint16 ctrlreg = *CACHE_CC_CTL;
        ctrlreg |= 0x4;
        *CACHE_CC_CTL = ctrlreg;

        /* Cache is invalidated on next cycle */

        /***************************************************************************
        * Execute a few NOPs to fill the ARM CM3 pipeline with instructions so that
        * instructions about to execute won't depend on data in the cache, and will
        * maintain data integrity.
        ***************************************************************************/
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
    }


    /*******************************************************************************
    * Function Name: CyIntSetSysVector
    ********************************************************************************
    * Summary:
    *  Sets the interrupt vector of the specified system interrupt number. System
    *  interrupts are present only for the ARM platform. These interrupts are for
    *  SysTick, PendSV and others.
    *
    * Parameters:
    *  number: Interrupt number, valid range [0-15].
       address: Pointer to an interrupt service routine.
    *
    * Return:
    *   The old ISR vector at this location.
    *
    *******************************************************************************/
    cyisraddress CyIntSetSysVector(uint8 number, cyisraddress address) CYREENTRANT
    {
        cyisraddress oldIsr;
        cyisraddress *ramVectorTable = *CYINT_VECT_TABLE;

        CYASSERT(number <= CY_INT_SYS_NUMBER_MAX);

        /* Save old Interrupt service routine. */
        oldIsr = ramVectorTable[number & CY_INT_SYS_NUMBER_MASK];

        /* Set new Interrupt service routine. */
        ramVectorTable[number & CY_INT_SYS_NUMBER_MASK] = address;

        return (oldIsr);
    }


    /*******************************************************************************
    * Function Name: CyIntGetSysVector
    ********************************************************************************
    *
    * Summary:
    *  Gets the interrupt vector of the specified system interrupt number. System
    *  interrupts are present only for the ARM platform. These interrupts are for
    *  SysTick, PendSV and others.
    *
    * Parameters:
    *   number: The interrupt number, valid range [0-15].
    *
    * Return:
    *   Address of the ISR in the interrupt vector table.
    *
    *******************************************************************************/
    cyisraddress CyIntGetSysVector(uint8 number) CYREENTRANT
    {
        cyisraddress *ramVectorTable = *CYINT_VECT_TABLE;
        CYASSERT(number <= CY_INT_SYS_NUMBER_MAX);

        return ramVectorTable[number & CY_INT_SYS_NUMBER_MASK];
    }


    /*******************************************************************************
    * Function Name: CyIntSetVector
    ********************************************************************************
    *
    * Summary:
    *  Sets the interrupt vector of the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number
    *  address: Pointer to an interrupt service routine
    *
    * Return:
    *   Previous interrupt vector value.
    *
    *******************************************************************************/
    cyisraddress CyIntSetVector(uint8 number, cyisraddress address) 
    {
        cyisraddress oldIsr;
        cyisraddress *ramVectorTable = *CYINT_VECT_TABLE;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Save old Interrupt service routine. */
        oldIsr = ramVectorTable[CYINT_IRQ_BASE + (number & CY_INT_NUMBER_MASK)];

        /* Set new Interrupt service routine. */
        ramVectorTable[CYINT_IRQ_BASE + (number & CY_INT_NUMBER_MASK)] = address;

        return (oldIsr);
    }


    /*******************************************************************************
    * Function Name: CyIntGetVector
    ********************************************************************************
    *
    * Summary:
    *  Gets the interrupt vector of the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number
    *
    * Return:
    *  Address of the ISR in the interrupt vector table.
    *
    *******************************************************************************/
    cyisraddress CyIntGetVector(uint8 number) 
    {
        cyisraddress *ramVectorTable = *CYINT_VECT_TABLE;
        CYASSERT(number <= CY_INT_NUMBER_MAX);

        return ramVectorTable[CYINT_IRQ_BASE + (number & CY_INT_NUMBER_MASK)];
    }


    /*******************************************************************************
    * Function Name: CyIntSetPriority
    ********************************************************************************
    *
    * Summary:
    *  Sets the Priority of the Interrupt.
    *
    * Parameters:
    *  priority: Priority of the interrupt. 0 - 7, 0 being the highest.
    *  number: The number of the interrupt, 0 - 31.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntSetPriority(uint8 number, uint8 priority) 
    {
        CYASSERT(priority <= CY_INT_PRIORITY_MAX);
        CYASSERT(number <= CY_INT_NUMBER_MAX);
        CYINT_PRIORITY[number & CY_INT_NUMBER_MASK] = (priority & CY_INT_PRIORITY_MASK)<< 5;
    }


    /*******************************************************************************
    * Function Name: CyIntGetPriority
    ********************************************************************************
    *
    * Summary:
    *  Gets the Priority of the Interrupt.
    *
    * Parameters:
    *  number: The number of the interrupt, 0 - 31.
    *
    * Return:
    *  Priority of the interrupt. 0 - 7, 0 being the highest.
    *
    *******************************************************************************/
    uint8 CyIntGetPriority(uint8 number) 
    {
        uint8 priority;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        priority = CYINT_PRIORITY[number & CY_INT_NUMBER_MASK] >> 5;

        return (priority);
    }


    /*******************************************************************************
    * Function Name: CyIntEnable
    ********************************************************************************
    *
    * Summary:
    *  Enables the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntEnable(uint8 number) CYREENTRANT
    {
        reg32 * enableReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt enable register. */
        enableReg = CYINT_ENABLE;

        /* Enable the interrupt. */
        *enableReg = 1 << (0x1F & number);
    }


    /*******************************************************************************
    * Function Name: CyIntGetState
    ********************************************************************************
    *
    * Summary:
    *   Gets the enable state of the specified interrupt number.
    *
    * Parameters:
    *   number: Valid range [0-31].  Interrupt number.
    *
    * Return:
    *   Enable status: 1 if enabled, 0 if disabled
    *
    *******************************************************************************/
    uint8 CyIntGetState(uint8 number) 
    {
        reg32 * stateReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt enable register. */
        stateReg = CYINT_ENABLE;

        /* Get the state of the interrupt. */
        return (*stateReg & (1 << (0x1F & number))) ? 1:0;
    }


    /*******************************************************************************
    * Function Name: CyIntDisable
    ********************************************************************************
    *
    * Summary:
    *  Disables the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntDisable(uint8 number) CYREENTRANT
    {
        reg32 * clearReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt enable register. */
        clearReg = CYINT_CLEAR;

        /* Enable the interrupt. */
        *clearReg = 1 << (0x1F & number);
    }


    /*******************************************************************************
    * Function Name: CyIntSetPending
    ********************************************************************************
    *
    * Summary:
    *   Forces the specified interrupt number to be pending.
    *
    * Parameters:
    *   number: Valid range [0-31].  Interrupt number.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntSetPending(uint8 number) 
    {
        reg32 * pendReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt set pending register. */
        pendReg = CYINT_SET_PEND;

        /* Pending the interrupt. */
        *pendReg = 1 << (0x1F & number);
    }


    /*******************************************************************************
    * Function Name: CyIntClearPending
    ********************************************************************************
    *
    * Summary:
    *   Clears any pending interrupt for the specified interrupt number.
    *
    * Parameters:
    *   number: Valid range [0-31].  Interrupt number.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntClearPending(uint8 number) 
    {
        reg32 * pendReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt clear pending register. */
        pendReg = CYINT_CLR_PEND;

        /* Clear the pending interrupt. */
        *pendReg = 1 << (0x1F & number);
    }

#else   /* PSoC3 */

    /*******************************************************************************
    * Function Name: CyIntSetVector
    ********************************************************************************
    *
    * Summary:
    *  Sets the interrupt vector of the specified interrupt number.
    *
    * Parameters:
    *  number:  Valid range [0-31].  Interrupt number
    *  address: Pointer to an interrupt service routine
    *
    * Return:
    *  Previous interrupt vector value.
    *
    *******************************************************************************/
    cyisraddress CyIntSetVector(uint8 number, cyisraddress address) 
    {
        cyisraddress oldIsr;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Save old Interrupt service routine. */
        oldIsr = (cyisraddress) \
                    CY_GET_REG16(&CYINT_VECT_TABLE[number & CY_INT_NUMBER_MASK]);

        /* Set new Interrupt service routine. */
        CY_SET_REG16(&CYINT_VECT_TABLE[number], (uint16) address);

        return (oldIsr);
    }


    /*******************************************************************************
    * Function Name: CyIntGetVector
    ********************************************************************************
    *
    * Summary:
    *  Gets the interrupt vector of the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number
    *
    * Return:
    *  Address of the ISR in the interrupt vector table.
    *
    *******************************************************************************/
    cyisraddress CyIntGetVector(uint8 number) 
    {
        CYASSERT(number <= CY_INT_NUMBER_MAX);

        return ((cyisraddress) \
                CY_GET_REG16(&CYINT_VECT_TABLE[number & CY_INT_NUMBER_MASK]));
    }


    /*******************************************************************************
    * Function Name: CyIntSetPriority
    ********************************************************************************
    *
    * Summary:
    *  Sets the Priority of the Interrupt.
    *
    * Parameters:
    *  priority: Priority of the interrupt. 0 - 7, 0 being the highest.
    *  number:   The number of the interrupt, 0 - 31.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntSetPriority(uint8 number, uint8 priority) 
    {
        CYASSERT(priority <= CY_INT_PRIORITY_MAX);
        CYASSERT(number <= CY_INT_NUMBER_MAX);
        CYINT_PRIORITY[number & CY_INT_NUMBER_MASK] =
                    (priority & CY_INT_PRIORITY_MASK) << 5;
    }


    /*******************************************************************************
    * Function Name: CyIntGetPriority
    ********************************************************************************
    *
    * Summary:
    *  Gets the Priority of the Interrupt.
    *
    * Parameters:
    *  number: The number of the interrupt, 0 - 31.
    *
    * Return:
    *  Priority of the interrupt. 0 - 7, 0 being the highest.
    *
    *******************************************************************************/
    uint8 CyIntGetPriority(uint8 number) 
    {
        uint8 priority;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        priority = CYINT_PRIORITY[number & CY_INT_NUMBER_MASK] >> 5;

        return (priority);
    }


    /*******************************************************************************
    * Function Name: CyIntEnable
    ********************************************************************************
    *
    * Summary:
    *  Enables the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntEnable(uint8 number) CYREENTRANT
    {
        reg8 * enableReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt enable register. */
        enableReg = CYINT_ENABLE + ((number & CY_INT_NUMBER_MASK) >> 3);

        /* Enable the interrupt. */
        *enableReg = 1 << (0x07 & number);
    }


    /*******************************************************************************
    * Function Name: CyIntGetState
    ********************************************************************************
    *
    * Summary:
    *   Gets the enable state of the specified interrupt number.
    *
    * Parameters:
    *   number: Valid range [0-31].  Interrupt number.
    *
    * Return:
    *   Enable status: 1 if enabled, 0 if disabled
    *
    *******************************************************************************/
    uint8 CyIntGetState(uint8 number) 
    {
        reg8 * stateReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);
        /* Get a pointer to the Interrupt enable register. */
        stateReg = CYINT_ENABLE + ((number & CY_INT_NUMBER_MASK) >> 3);

        /* Get the state of the interrupt. */
        return ((*stateReg & (1 << (0x07 & number))) ? 1:0);
    }


    /*******************************************************************************
    * Function Name: CyIntDisable
    ********************************************************************************
    *
    * Summary:
    *  Disables the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntDisable(uint8 number) CYREENTRANT
    {
        reg8 * clearReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt enable register. */
        clearReg = CYINT_CLEAR + ((number & CY_INT_NUMBER_MASK) >> 3);

        /* Disable the interrupt. */
        *clearReg = 1 << (0x07 & number);
    }


    /*******************************************************************************
    * Function Name: CyIntSetPending
    ********************************************************************************
    *
    * Summary:
    *  Forces the specified interrupt number to be pending.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntSetPending(uint8 number) 
    {
        reg8 * pendReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt set pending register. */
        pendReg = CYINT_SET_PEND + ((number & CY_INT_NUMBER_MASK) >> 3);

        /* Enable the interrupt. */
        *pendReg = 1 << (0x07 & number);
    }


    /*******************************************************************************
    * Function Name: CyIntClearPending
    ********************************************************************************
    * Summary:
    *  Clears any pending interrupt for the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntClearPending(uint8 number) 
    {
        reg8 * pendReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt clear pending register. */
        pendReg = CYINT_CLR_PEND + ((number & CY_INT_NUMBER_MASK) >> 3);

        /* Enable the interrupt. */
        *pendReg = 1 << (0x07 & number);
    }

#endif  /* (CY_PSOC5) */


/* [] END OF FILE */
