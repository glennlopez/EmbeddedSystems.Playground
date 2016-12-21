/*******************************************************************************
* File Name: CyLib.c
* Version 2.40
*
*  Description:
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include <CyLib.h>


uint8 CYXDATA CyResetStatus;

/* CYLIB CLOCK funcs begin*/

/*******************************************************************************
* Function Name: CyPLL_OUT_Start
********************************************************************************
*
* Summary:
*   Enables the PLL.  Optionally waits for it to become stable.
*   Waits at least 250us or until it is detected that the PLL is stable.
*
* Parameters:
*   wait:
*    0: Return immediately after configuration
*    1: Wait for PLL lock or timeout.
*
* Return:
*   Status
*     CYRET_SUCCESS - Completed successfully
*    CYRET_TIMEOUT - Timeout occurred without detecting a stable clock.  
*     If the input source of the clock is jittery, then the lock indication 
*     may not occur.  However, after the timeout has expired the generated PLL 
*     clock can still be used..
*
*******************************************************************************/
cystatus CyPLL_OUT_Start(uint8 wait) 
{
    cystatus status = CYRET_SUCCESS;
    uint8 pm_tw_cfg2_state;
    uint8 pm_tw_cfg0_state;
    uint8 ilo_clock_state;
    
    FASTCLK_PLL_CFG0 |= PLL_CONTROL_ENABLE;
    
    /*Non-zero wait value*/
    if (wait != 0) 
    {
        /*Need to turn on the 100KHz ILO if it happens to not already be running.*/
        ilo_clock_state = SLOWCLK_ILO_CR0;
        if(!(ilo_clock_state & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Start100K();
        }
        
        /*Use ILO 100Khz*/
        pm_tw_cfg2_state = PM_TW_CFG2;
        pm_tw_cfg0_state = PM_TW_CFG0;
        
        /* FTW_EN (bit 0) must be clear to change the period*/
        PM_TW_CFG2 &= FTW_CLEAR_FTW_BITS;
        
        /* Set the FTW interval of 25 100KHz ILO clocks
        Should result in status getting set at a (100/25)KHz rate*/
        PM_TW_CFG0 =  25-1;
        /* Enable FTW, but not the interrupt*/
        PM_TW_CFG2 = FTW_ENABLE;        
        
        status = CYRET_TIMEOUT;
        /*check the CyPmReadStatus() return value, 0th bit is ftw*/
        while (CyPmReadStatus(1) == 0)
        {
            /* Wait for the interrupt status*/
            if(FASTCLK_PLL_SR & PLL_STATUS_LOCK)
            {
                if(FASTCLK_PLL_SR & PLL_STATUS_LOCK)
                {
                    /*A stable clock.                    */
                    status = CYRET_SUCCESS;
                    break;
                }
            }
        }
        /*reset the clock */
        if(!(ilo_clock_state & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Stop100K();
        }

        /*restore the FTW*/
        PM_TW_CFG0 = pm_tw_cfg0_state;
        PM_TW_CFG2 = pm_tw_cfg2_state;
    }
    return status;
}


/*******************************************************************************
* Function Name: CyPLL_OUT_Stop
********************************************************************************
* Summary:
*   Disables the PLL.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyPLL_OUT_Stop(void) 
{
    /* Disable the PLL. */
    FASTCLK_PLL_CFG0 &= ~PLL_CONTROL_ENABLE;
}


/*******************************************************************************
* Function Name: CyPLL_OUT_SetPQ
********************************************************************************
* Summary:
*   Sets the P and Q dividers and the charge pump current.  
*   The Frequency Out will be P/Q * Frequency In.  
*   The PLL must be disabled before calling this function.
*
*
* Parameters:
*   P: Valid range [4 - 255]
*   Q: Valid range [1 - 16].  Input Frequency / Q must be in the range of 1MHz to 3MHz.
*   current: Valid range [1 - 7].  Charge pump current in uA.  
*            Recommendation of 2uA for output frequencies of 67MHz or less and 
*            3uA for higher output frequencies.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyPLL_OUT_SetPQ(uint8 P, uint8 Q, uint8 current) 
{
    CYASSERT(!(FASTCLK_PLL_CFG0 & PLL_STATUS_ENABLED));
    
    /*Set the CYREG_FASTCLK_PLL_P register
    Settings less than 4 do not give valid outputs. Valid range is 4 - 255*/
    if (P >= MIN_FASTCLK_PLL_P_VALUE)
    {
        FASTCLK_PLL_P = P;
    }
    /*Set the CYREG_FASTCLK_PLL_Q register*/
    if (Q <= MAX_FASTCLK_PLL_Q_VALUE && Q >= MIN_FASTCLK_PLL_Q_VALUE)
    {
        FASTCLK_PLL_Q = Q-1;
    }
    if(current >= MIN_FASTCLK_PLL_CUR_VALUE && current <= MAX_FASTCLK_PLL_CUR_VALUE)
    {
        /*
        Bits     Name         Description
        6:4     icpsel[2:0] Charge Pump current select; BROS tables contain 
                            important stability information for given frequencies,
                            P values, and other parameters
        1:0     vco_gain[1:0] VCO loop gain
        */
        FASTCLK_PLL_CFG1 = ((current - 1) << PLL_CURRENT_POSITION) | PLL_VCO_GAIN_2;
    }
}


/*******************************************************************************
* Function Name: CyPLL_OUT_SetSource
********************************************************************************
* Summary:
*   Sets the input clock source to the PLL.  The PLL must be disabled before 
*   calling this function.
*
* Parameters:
*   source: One of the three available PLL clock sources
*            0 :        IMO
*            1 :        MHz Crystal
*            2 :        DSI
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyPLL_OUT_SetSource(uint8 source) 
{
    CYASSERT(!(FASTCLK_PLL_CFG0 & PLL_STATUS_ENABLED));
    
    /*Set the 1:0 bits of CLKDIST_CR */
    /*  Value    Name    Description
        2'h0     IMO     IMO is selected
        2'h1     XTAL    33MHz XTAL is selected
        2'h2     DSI     Digital System Interconnect is selected*/
    switch(source)
    {
        case CY_PLL_SOURCE_IMO:
        case CY_PLL_SOURCE_XTAL:
        case CY_PLL_SOURCE_DSI:
            CLKDIST_CR = ((CLKDIST_CR & CLOCK_CONTROL_DIST_MASK) | source);
        break;
    }
}


/*******************************************************************************
* Function Name: CyIMO_Start
********************************************************************************
* Summary:
*   Enables the IMO.  Optionally waits at least 6us for it to settle.
*
*
* Parameters:
*   wait:
*   0: Return immediately after configuration
*   1: Wait for at least 6us for the IMO to settle.
*
*
* Return:
*   void.
*
* Side Effects and Restrictions:
*   If wait is enabled: Uses the Fast Timewheel to time the wait.
*   Any other use of the Fast Timewheel will be stopped during the period of -
*   this function and then restored.
*   Uses the 100KHz ILO.  If not enabled, this function will enable the 100KHz -
*   ILO for the period of this function.
*
*******************************************************************************/
void CyIMO_Start(uint8 wait) 
{
    uint8 pm_tw_cfg2_state;
    uint8 pm_tw_cfg0_state;
    uint8 ilo_clock_state;

    /* Set the bit to enable the clock. */
    PM_ACT_CFG0 |= IMO_PM_ENABLE;

    /*Wait for 6 us*/
    if(wait)
    {
        /*Need to turn on the 100KHz ILO if it happens to not already be running.*/
        ilo_clock_state = SLOWCLK_ILO_CR0;
        if(!(ilo_clock_state & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Start100K();
        }
        
        /*Use ILO 100Khz*/
        pm_tw_cfg2_state = PM_TW_CFG2;
        pm_tw_cfg0_state = PM_TW_CFG0;
        
        /* FTW_EN (bit 0) must be clear to change the period*/
        PM_TW_CFG2 &= FTW_CLEAR_FTW_BITS;
        
        /* Set the FTW interval of 1 100KHz ILO clocks
        Should result in status getting set at a (100/1)KHz rate*/
        PM_TW_CFG0 = 1-1;
        /* Enable FTW, but not the interrupt*/
        PM_TW_CFG2 = FTW_ENABLE;        
        
        /*Read FTW value*/
        while (CyPmReadStatus(1) == 0)
        {
            /* Wait for the interrupt status*/
        }

        /*reset the clock */
        if(!(ilo_clock_state & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Stop100K();
        }
        /*restore the FTW*/
        PM_TW_CFG0 = pm_tw_cfg0_state;
        PM_TW_CFG2 = pm_tw_cfg2_state;
    }
}


/*******************************************************************************
* Function Name: CyIMO_Stop
********************************************************************************
* Summary:
*   Disables the IMO.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
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
* Summary:
*   Returns the USB power status value.
*    A private function to cy_boot.
*
*
* Parameters:
*   None.
*
*
* Return:
*   uint8: one if the USB is enabled, 0 if not enabled.
*
*******************************************************************************/
uint8 CyUSB_PowerOnCheck()
{
    uint8 powered_on = 0;
    /*
     Check whether the device is in Active or AltActive
     Check whether USB is powered on
    */
    if((((CY_PM_MODE_CSR_REG & CY_PM_MODE_CSR_MASK) == CY_PM_MODE_CSR_ACTIVE) && 
         (CY_PM_ACT_CFG5_REG & CY_ACT_USB_ENABLED)) ||
       (((CY_PM_MODE_CSR_REG & CY_PM_MODE_CSR_MASK) == CY_PM_MODE_CSR_ALT_ACT) && 
         (CY_PM_STBY_CFG5_REG & CY_ALT_ACT_USB_ENABLED)))
    
    {
        powered_on = 1;
    }
    return powered_on;
}

/*******************************************************************************
* Function Name: CyIMO_SetTrimValue
********************************************************************************
* Summary:
*   Sets the IMO factory trim values.
*
* Parameters:
*   freq.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyIMO_SetTrimValue(uint8 freq) 
{
    uint8 usb_power_on = CyUSB_PowerOnCheck();

    /*If USB is powered */
    if(usb_power_on == 1) 
    {    
        /*Unlock USB write*/
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

        case CY_IMO_FREQ_62MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_67MHZ_PTR);
        break;

        case CY_IMO_FREQ_74MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_80MHZ_PTR);
        break;
        
        case CY_IMO_FREQ_USB:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_USB_PTR);
        /*If USB is powered */
        if(usb_power_on == 1) 
        {
            /*Lock the USB Oscillator*/
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
* Summary:
*   Alows the caller to set the IMO fequency (3, 6, 12, 24, 48, 62 MHZ).
*   Sets the frequency of the IMO.  
*   Changes may be made while the IMO is running.  
*   When the USB setting is chosen the USB clock locking circuit is enabled.  
*   Otherwise this circuit is disabled.
*   If the IMO is currently driving the Master clock, then the Flash wait states
*   must be set appropriately before making this change -
*   by using CyFlash_SetWaitCycles().
*   If the frequency is set to CY_IMO_FREQ_USB then IMO Doubler is turned ON 
*   and otherwise IMO Doubler will be turned off.
*
*
* Parameters:
*   frequency,    CY_IMO_FREQ_3MHZ  to set 3 MHz,
*                 CY_IMO_FREQ_6MHZ  to set 6 MHz,
*                 CY_IMO_FREQ_12MHZ to set 12MHz,
*                 CY_IMO_FREQ_24MHZ to set 24MHz,
*                 CY_IMO_FREQ_48MHZ to set 48MHz,
*                 CY_IMO_FREQ_62MHZ to set 62.6MHz.
*                 CY_IMO_FREQ_74MHZ    to set 74.7 MHz (PSoC 5)
*                 CY_IMO_FREQ_USB    to set 24 MHz (Trimmed for USB operation)
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyIMO_SetFreq(uint8 freq) 
{
    uint8 current_freq;
    uint8 next_freq;
    
    /*
    When changing the IMO frequency the Trim values must also be set accordingly.  
    This requires reading the current frequency.  
    If the new frequency is faster, then set the new trim and then change the
    frequency, otherwise change the frequency and then set the new trim values.
    */

    /*
    Value Name         Description
    3'h0 F_RANGE_0 12 MHz (normal)
    3'h1 F_RANGE_1 6 MHz (normal); 12 MHz (fast start)
    3'h2 F_RANGE_2 24 MHz
    3'h3 F_RANGE_3 3 MHz (normal); 12 MHz (fast start)
    3'h4 F_RANGE_4 48 MHz
    3'h5 F_RANGE_5 67 MHz
    3'h6 F_RANGE_6 80 MHz (normal); 48 MHz (fast start)
    3'h7 F_RANGE_7 96 MHz (normal); 48 MHz (fast start)
    */
    current_freq = FASTCLK_IMO_CR & ~CLOCK_IMO_RANGE_CLEAR;
    /*Check if the requested frequency is USB.*/
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

        case 5:
        current_freq = CY_IMO_FREQ_62MHZ;
        break;

        case 6:
        current_freq = CY_IMO_FREQ_74MHZ;
        break;
    }
    
    if (next_freq >= current_freq)
    {
        /*Set the new trim first*/
        CyIMO_SetTrimValue(freq);
    }
    
    /*Set the usbclk_on bit when using CY_IMO_FREQ_USB, if not clear it*/
    switch(freq)
    {
        case CY_IMO_FREQ_3MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) | CLOCK_IMO_3MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

        case CY_IMO_FREQ_6MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) | CLOCK_IMO_6MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

        case CY_IMO_FREQ_12MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) | CLOCK_IMO_12MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

        case CY_IMO_FREQ_24MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) | CLOCK_IMO_24MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

        case CY_IMO_FREQ_48MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) | CLOCK_IMO_48MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

        case CY_IMO_FREQ_62MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) | CLOCK_IMO_62MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;

        case CY_IMO_FREQ_74MHZ:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) | CLOCK_IMO_74MHZ_VALUE) & ~FASTCLK_IMO_USBCLK_ON_SET;
        break;
        
        case CY_IMO_FREQ_USB:
        FASTCLK_IMO_CR = ((FASTCLK_IMO_CR & CLOCK_IMO_RANGE_CLEAR) | CLOCK_IMO_24MHZ_VALUE) | FASTCLK_IMO_USBCLK_ON_SET;
        break;
        
        default:
        /*Not a correct fequency value.*/
        CYASSERT(0);
        break;
    }

    /*Turn on the IMO Doubler, if switching to CY_IMO_FREQ_USB*/
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
        /*Set the new trim after setting the frequency*/
        CyIMO_SetTrimValue(freq);
    }
}


/*******************************************************************************
* Function Name: CyIMO_SetSource
********************************************************************************
* Summary:
*   Sets the source of the clock output from the IMO block.  
*   The output from the IMO is by default the IMO itself.  
*   Optionally the MHz Crystal or a DSI input can be the source of the 
*   IMO output instead.  
*   If the IMO is currently driving the Master clock, 
*   then the Flash wait states must be set appropriately before making this 
*   change by using CyFlash_SetWaitCycles().
*
*
* Parameters:
*   source, CY_IMO_SOURCE_DSI to set the DSI as source.
*           CY_IMO_SOURCE_XTAL to set the MHz as source.
*           CY_IMO_SOURCE_IMO to set the IMO itself.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyIMO_SetSource(uint8 source) 
{
    /*Set the xclken bit of FASTCLK_IMO_CR regigster*/
    /*
        IMO2X_SRC     bit in CLKDIST_CR
        
        Bit field encoding: IMO2X_INPUT_SEL_ENUM
        Value Name Description
        1'b0  DSI  Digital System Interconnect is used as a source to IMO doubler
        1'b1  XTAL External clock source is used as a source to IMO doubler
        
        xclken         bit in FASTCLK_IMO_CR
        
        Value      Name      Description
        1'b0     XCLKEN_0     IMO doubler runs from the IMOCLK
        1'b1     XCLKEN_1     IMO doubler runs from the selected 'external' clock. 
                            This is a signal on a global - source is TBD.
    */
    
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
            /*Not a correct source value.*/
            CYASSERT(0);
            break;        
    }
}


/*******************************************************************************
* Function Name: CyIMO_EnableDoubler
********************************************************************************
* Summary:
*   Enables the IMO doubler.  The 2x frequency clock is used to convert 
*   a 24MHz input to a 48MHz output for use by the USB block.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyIMO_EnableDoubler(void) 
{
    /*Set the FASTCLK_IMO_CR_PTR regigster's 4th bit*/
    FASTCLK_IMO_CR |= IMO_DOUBLER_ENABLE;
}


/*******************************************************************************
* Function Name: CyIMO_DisableDoubler
********************************************************************************
* Summary:
*   Disables the IMO doubler.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyIMO_DisableDoubler(void) 
{
    /*Set the FASTCLK_IMO_CR_PTR regigster's 4th bit*/
    FASTCLK_IMO_CR &= ~IMO_DOUBLER_ENABLE;
}


/*******************************************************************************
* Function Name: CyMasterClk_SetSource
********************************************************************************
* Summary:
*   Sets the source of the master clock.  
*   The current source and the new source must both be running and stable 
*   before calling this function.  
*   The Flash wait states must be set appropriately before making this change 
*   by using CyFlash_SetWaitCycles().
*
*
* Parameters:
*   source: One of the four available Master clock sources.
*     CY_MASTER_SOURCE_IMO
*     CY_MASTER_SOURCE_PLL
*     CY_MASTER_SOURCE_XTAL
*     CY_MASTER_SOURCE_DSI
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyMasterClk_SetSource(uint8 source) 
{
    /*
    Switching the master clock source is implemented as below:
    if (master_clk divider == 0)
        set master_clk divider = 3
        change master_clk source
        set master_clk divider back to 0
    else
        change master_clk source

    1) Write a non-zero period to the master mux clock divider (MSTR0). 
    Recommended value is 3. This results in    a divide of the master clock by 4.
    2) Write the new select to the mux select register (MSTR1).
    3) Restore the zero period (if desired) to the master mux clock divider (MSTR0).        
    */
    uint8 master_reg_1;

#if (CY_PSOC3_ES2 || CY_PSOC5_ES1)
    uint8 master_reg_0;

    /* Read the current setting */
    master_reg_0 = CLKDIST_MSTR0;
    if (master_reg_0 == 0x00u)
    {
        CLKDIST_MSTR0 = 3;
    }
#endif

    /* Read the current setting */
    master_reg_1 = CLKDIST_MSTR1;

    CLKDIST_MSTR1 = (master_reg_1 & MASTER_CLK_SRC_CLEAR) | (source & ~MASTER_CLK_SRC_CLEAR);
    
#if (CY_PSOC3_ES2 || CY_PSOC5_ES1)
    /*Restore the registry value.*/
    if (master_reg_0 == 0x00u)
    {
        CLKDIST_MSTR0 = 0;
    }
#endif
}


/*******************************************************************************
* Function Name: CyMasterClk_SetDivider
********************************************************************************
* Summary:
*   Sets the divider value used to generate Master Clock.  
*   The Flash wait states must be set appropriately before making this change 
*   by using CyFlash_SetWaitCycles().
*
*
* Parameters:
*   divider: Valid range [0-255].  
*   The clock will be divided by this value + 1.  
*   For example to divide by 2 this parameter should be set to 1.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyMasterClk_SetDivider(uint8 divider) 
{
    CLKDIST_MSTR0 = divider;
}


/*******************************************************************************
* Function Name: CyBusClk_Internal_SetDivider
********************************************************************************
* Summary:
*   Sets the divider value used to generate Bus Clock.  
*   The Flash wait states must be set appropriately before making this change 
*   by using CyFlash_SetWaitCycles().
*
*
* Parameters:
*   divider: Valid range [0-65535].
*   The clock will be divided by this value + 1.
*   For example to divide by 2 this parameter should be set to 1.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyBusClk_Internal_SetDivider(uint16 divider)
{
    /*Clear all the masks (CLKDIST_AMASK, CLKDIST_DMASK)*/
    CLKDIST_AMASK &= BUS_AMASK_CLEAR;
    CLKDIST_DMASK = BUS_DMASK_CLEAR;
    
    /*set the MASK for bus clock, CLKDIST_BCFG2
    Bits      Name      Description
    7         MASK     Mask bit to enable shadow loads
    1'b1      ENABLE      Enable shadow loads*/
    CLKDIST_BCFG2 |= CLKDIST_WRK0_MASK_SET;
    
    /*We change both bytes before we enable/start the clock.*/
    CY_SET_REG16(CLKDIST_WRK0_PTR, divider);
    
    /*load the value , set the CLKDIST_LD LOAD bit*/
    CLKDIST_LD |= CLKDIST_LD_LOAD_SET;    
}


/*******************************************************************************
* Function Name: CyBusClk_SetDivider
********************************************************************************
* Summary:
*   Sets the divider value used to generate Bus Clock.  
*   The Flash wait states must be set appropriately before making this change 
*   by using CyFlash_SetWaitCycles().
*
*
* Parameters:
*   divider: Valid range [0-65535].  
*   The clock will be divided by this value + 1.  
*   For example to divide by 2 this parameter should be set to 1..
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyBusClk_SetDivider(uint16 divider) 
{
    uint16 current_busclk_divider;
    uint8 current_masterclk_divider;

    /*Bus clock divider value.*/
    current_busclk_divider = CY_GET_REG16(CLKDIST_BCFG0_PTR);
    
    /*Work around to set the bus clock divider value.*/
    if (divider == 0 || current_busclk_divider == 0)
    {
        /*save away the master clock divider value*/
        current_masterclk_divider = CY_GET_REG8(CLKDIST_MSTR0_PTR);
        if (current_masterclk_divider < MASTERCLK_DIVIDER_VALUE)
        {    
            /*set master clock divider to 7 */
            CyMasterClk_SetDivider(MASTERCLK_DIVIDER_VALUE);
        }
        if (divider == 0)
        {
            /*
            set the SSS bit 
            set the divider register desired value*/
            CLKDIST_BCFG2 |= CLKDIST_BCFG2_SSS_SET;
            CyBusClk_Internal_SetDivider(divider);
        }
        else 
        {
            /*
            set the divider register to divider argument value
            clear the SSS bit            */
            CyBusClk_Internal_SetDivider(divider);
            CLKDIST_BCFG2 &= ~CLKDIST_BCFG2_SSS_SET;
        }
        /*Restore the master clock */
        CyMasterClk_SetDivider(current_masterclk_divider);
    }
    else
    {
        CyBusClk_Internal_SetDivider(divider);
    }
}


/*******************************************************************************
* Function Name: CyCpuClk_SetDivider
********************************************************************************
* Summary:
*   Sets the divider value used to generate the CPU Clock.  Only applicable for PSoC 3.
*
*
* Parameters:
*   divider: Valid range [0-15].  
*   The clock will be divided by this value + 1.  
*   For example to divide by 2 this parameter should be set to 1.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyCpuClk_SetDivider(uint8 divider) 
{
#if CY_PSOC3_ES3
    CLKDIST_MSTR1 = (CLKDIST_MSTR1 & CLKDIST_MSTR1_DIV_CLEAR) | (divider << CLKDIST_DIV_POSITION);
#elif CY_PSOC3_ES2
    CPUCLK_DIV = (CPUCLK_DIV & ~CPUCLK_DIV) | (divider & SFR_USER_CPUCLK_DIV_MASK);
#endif /*end (CY_PSOC3_ES3)*/
}


/*******************************************************************************
* Function Name: CyUsbClk_SetSource
********************************************************************************
* Summary:
*   Sets the source of the USB clock.
*
*
* Parameters:
*   source: One of the four available USB clock sources
*             USB_CLK_IMO2X     - imo2x  is selected
*             USB_CLK_IMO       - imo is selected
*             USB_CLK_PLL       - pll is selected
*             USB_CLK_DSI       - dsi is selected
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyUsbClk_SetSource(uint8 source) 
{
    /* SRC_SEL[1:0] of CLKDIST.UCFG*/
    CLKDIST_UCFG = (CLKDIST_UCFG & ~USB_CLKDIST_CONFIG_MASK) | (USB_CLKDIST_CONFIG_MASK & source);
}


/*******************************************************************************
* Function Name: CyILO_Start1K
********************************************************************************
* Summary:
*   Enables the ILO 1 KHz oscillator.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyILO_Start1K(void) 
{
    /*Set the bit 1 of ILO RS */
    SLOWCLK_ILO_CR0 |= ILO_CONTROL_1KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Stop1K
********************************************************************************
* Summary:
*   Disables the ILO 1 KHz oscillator.
*   Note: Stopping the ILO 1 kHz could break the active WDT functionality.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyILO_Stop1K(void) 
{
    /*Clear the bit 1 of ILO RS */
    SLOWCLK_ILO_CR0 &= ~ILO_CONTROL_1KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Start100K
********************************************************************************
* Summary:
*   Enables the ILO 100 KHz oscillator.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyILO_Start100K(void) 
{
    /*Set the bit 2 of ILO RS */
    SLOWCLK_ILO_CR0 |= ILO_CONTROL_100KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Stop100K
********************************************************************************
* Summary:
*   Disables the ILO 100 KHz oscillator.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyILO_Stop100K(void) 
{
    /*Clear the bit 2 of ILO RS */
    SLOWCLK_ILO_CR0 &= ~ILO_CONTROL_100KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Enable33K
********************************************************************************
* Summary:
*   Enables the ILO 33 KHz divider.  
*   Note that the 33 KHz clock is generated from the 100 KHz oscillator, 
*   so it must also be running in order to generate the 33 KHz output.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyILO_Enable33K(void) 
{
    /*Set the bit 5 of ILO RS */
    SLOWCLK_ILO_CR0 |= ILO_CONTROL_33KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Disable33K
********************************************************************************
* Summary:
*   Disables the ILO 33 KHz divider.  
*   Note that the 33 KHz clock is generated from the 100 KHz oscillator, 
*   but this API does not disable the 100 KHz clock.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyILO_Disable33K(void) 
{
    /*Clear the bit 5 of ILO RS */
    SLOWCLK_ILO_CR0 &= ~ILO_CONTROL_33KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_SetSource
********************************************************************************
* Summary:
*   Sets the source of the clock output from the ILO block.
*
*
* Parameters:
*   source: One of the three available ILO output sources
*       Value        Define                Source
*       0            CY_ILO_SOURCE_100K    ILO 100 KHz
*       1            CY_ILO_SOURCE_33K     ILO 33 KHz
*       2            CY_ILO_SOURCE_1K      ILO 1 KHz
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyILO_SetSource(uint8 source) 
{
    /*Bits 3:2       ILO_OUT[1:0] of CLKDIST_CR */
    CLKDIST_CR = (CLKDIST_CR & CY_ILO_SOURCE_BITS_CLEAR) | ((source << 2) & ~CY_ILO_SOURCE_BITS_CLEAR);
}


/*******************************************************************************
* Function Name: CyILO_SetPowerMode
********************************************************************************
* Summary:
*   Sets the power mode used by the ILO during power down.  
*   Allows for lower power down power usage resulting in a slower startup time.
*
*
* Parameters:
*   mode, 
*       Value        Define                Source
*         0      CY_ILO_FAST_START  Faster start-up, internal bias left on when powered down
*         1      CY_ILO_SLOW_START  Slower start-up, internal bias off when powered down
*
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
* Summary:
*   Enables the 32KHz Crystal Oscillator.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyXTAL_32KHZ_Start(void) 
{
    volatile uint32  timeout;
    volatile uint32* timeout_p = &timeout;
    
    SLOWCLK_X32_TST = X32_TST_SETALL;
#if (CY_PSOC3_ES3 || CY_PSOC5_ES2)
    MFGCFG_X32_TR = X32_TR_DPMODE;
#endif

    /*set the low power mode*/
    SLOWCLK_X32_CFG = (SLOWCLK_X32_CFG & ~X32_CFG_LP_BITS_MASK) | X32_CFG_LP_DEFAULT;

#if (CY_PSOC3_ES3 || CY_PSOC5_ES2)
    /*set the power mode bit*/
    SLOWCLK_X32_CR |= X32_CONTROL_PDBEN;
#endif
    
    /* Enable the oscillator. */
    SLOWCLK_X32_CR |= X32_CONTROL_X32EN;
    for (timeout = 1000; *timeout_p; timeout--) 
    { 
        if (SLOWCLK_X32_CR & 0x20u)
            break;
        CyDelay(1);
    }

    /*Check the readiness*/
    if ((CyXTAL_32KHZ_ReadStatus() & CY_XTAL32K_ANA_STAT) == CY_XTAL32K_ANA_STAT)
    {
        CyXTAL_32KHZ_SetPowerMode(0);
    }
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_Stop
********************************************************************************
* Summary:
*   Disables the 32KHz Crystal Oscillator.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyXTAL_32KHZ_Stop(void) 
{

#if (CY_PSOC3_ES3 || CY_PSOC5_ES2)
    SLOWCLK_X32_TST = X32_TST_SETALL;
    MFGCFG_X32_TR = X32_TR_CLEAR;
    SLOWCLK_X32_CFG = (SLOWCLK_X32_CFG & ~X32_CFG_LP_BITS_MASK) | X32_CFG_LP_DEFAULT;
#endif

    /* Disable the oscillator. */
    SLOWCLK_X32_CR &= ~X32_CONTROL_X32EN;
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_ReadStatus
********************************************************************************
* Summary:
*   Reads the two status bits for the 32 KHz oscillator.
*
*
* Parameters:
*   None
*
*
* Return:
*   Value     Define                    Source
*   20        CY_XTAL32K_ANA_STAT       Analog measurement   
*                                       1: Stable
*                                       0: Not stable
*   10        CY_XTAL32K_DIG_STAT       Digital measurement (Requires the 33 KHz 
*                                       ILO to make this measurement)
*                                       1: Stable
*                                       0: Not stable
*
*******************************************************************************/
uint8 CyXTAL_32KHZ_ReadStatus() 
{
    uint8 status;
    status = SLOWCLK_X32_CR;
    /*
    Bits 5:4
    */
    return (status & CY_XTAL32K_STAT_FIELDS);
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_SetPowerMode
********************************************************************************
* Summary:
*   Sets the power mode for the 32 KHz oscillator used during sleep mode.  
*   Allows for lower power during sleep when there are fewer sources of noise.  
*   During active mode the oscillator is always run in high power mode.
*
* Parameters:
*   mode
*       0: High power mode
*       1: Low power mode during sleep
*
*
* Return:
*   Previous power mode.
*
*******************************************************************************/
uint8 CyXTAL_32KHZ_SetPowerMode(uint8 mode) 
{
    uint8 state;

    /* Get current state. */
    state = SLOWCLK_X32_CR;

#if (CY_PSOC3_ES3 || CY_PSOC5_ES2)
    /*Set the TST register*/
    SLOWCLK_X32_TST = X32_TST_SETALL;
#endif

    /* Set the the oscillator power mode. */
    if(mode == CY_X32_LOWPOWER_MODE)
    {
#if (CY_PSOC3_ES3 || CY_PSOC5_ES2)
        MFGCFG_X32_TR = X32_TR_LPMODE;
        SLOWCLK_X32_CFG = (SLOWCLK_X32_CFG & ~X32_CFG_LP_BITS_MASK) | X32_CFG_LP_LOWPOWER;
        /*allow 20uS delay*/
        CyDelayUs(20);
#endif
        SLOWCLK_X32_CR = (state | X32_CONTROL_LPM);
    }
    else
    {
#if (CY_PSOC3_ES3 || CY_PSOC5_ES2)
        MFGCFG_X32_TR = X32_TR_HPMODE;
        SLOWCLK_X32_CFG = (SLOWCLK_X32_CFG & ~X32_CFG_LP_BITS_MASK) | X32_CFG_LP_DEFAULT;
#endif
        /*set it in HPM mode*/
        SLOWCLK_X32_CR = (state & ~X32_CONTROL_LPM);
    }

    /* Return the old mode. 
        Bit 1 position.*/
    return ((state & X32_CONTROL_LPM) >> X32_CONTROL_LPM_POSITION);
}


/*******************************************************************************
* Function Name: CyXTAL_Start
********************************************************************************
* Summary:
*   Enables the megahertz crystal.  
*   Waits until the XERR bit is low (no error) for a millisecond or 
*   until the number of milliseconds specified by the wait parameter has expired.
*
*
* Parameters:
*   wait: Valid range [0-255].
*   This is the timeout value in milliseconds.  
*   The appropriate value is crystal specific.
*
*
* Return:
*   CYRET_SUCCESS - Completed successfully
*   CYRET_TIMEOUT - Timeout occurred without detecting a low value on XERR..
*
* Side Effects and Restrictions:
*   If wait is enabled (non-zero wait):
*    Uses the Fast Timewheel to time the wait.  Any other use of the 
*    Fast Timewheel will be stopped during the period of this function and 
*    then restored.
*    Uses the 100KHz ILO.  If not enabled, this function will enable 
*    the 100KHz ILO for the period of this function.
*    No changes to the setup of the ILO, Fast Timewheel, Central Timewheel or 
*    Once Per Second interrupt may be made by interrupt routines during 
*    the period of this function.  
*    The current operation of the ILO, Central Timewheel and Once Per Second 
*    interrupt are maintained during the operation of this function provided 
*    the reading of the Power Manager Interrupt Status Register is 
*    only done using the CyPmReadStatus() function.
*******************************************************************************/
cystatus CyXTAL_Start(uint8 wait) 
{
    cystatus status = CYRET_SUCCESS;
    uint8 pm_tw_cfg2_state = 0;
    uint8 pm_tw_cfg0_state = 0;
    uint8 ilo_clock_state = 0;
    volatile uint8 count = 0;
    volatile uint8 wait_msec = wait;

    FASTCLK_XMHZ_CSR |= XMHZ_CONTROL_ENABLE;
    
    if(wait > 0) 
    {
        /*    Need to turn on the 100KHz ILO if it happens to not already be running.*/
        ilo_clock_state = SLOWCLK_ILO_CR0;
        if(!(ilo_clock_state & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Start100K();
        }
        status = CYRET_TIMEOUT;
        
        /*Store the value*/
        pm_tw_cfg2_state = PM_TW_CFG2;
        pm_tw_cfg0_state = PM_TW_CFG0;

        /* FTW_EN (bit 0) must be clear to change the period*/
        PM_TW_CFG2 &= FTW_CLEAR_FTW_BITS;
        
        /* Set the FTW interval of 25 100KHz ILO clocks
        Should result in status getting set at a (100/25)KHz rate*/
        PM_TW_CFG0 = 25-1;
        /* Enable FTW, but not the interrupt*/
        PM_TW_CFG2 = FTW_ENABLE;
    }
    
    for(; wait_msec > 0; wait_msec--)
    {
        /*read XERR bit to clear it */
        FASTCLK_XMHZ_CSR;
        
        /*wait for milliseconds.. 4 times 250uS delay*/
        for(count = 4; count > 0; count --)
        {
            /*CyPmReadStatus()*/
            while (CyPmReadStatus(1) == 0)
            {
                /* Wait for the interrupt status*/
            }            
        } /* end of for(count = 4; count > 0; count --)*/
        /*High output indicates oscillator failure. 
        Only use this after start-up interval is completed (1ms).*/
        if ((FASTCLK_XMHZ_CSR & X32_CONTROL_XERR_MASK) == 0) 
        {
            status = CYRET_SUCCESS;
            break;
        }
    } /* end for(; wait_msec > 0; wait_msec--) */

    if(wait > 0)
    {
        if (!(ilo_clock_state & ILO_CONTROL_100KHZ_ON))
        {
            /*reset the clock */
            CyILO_Stop100K();
        }

        /*restore the FTW*/
        PM_TW_CFG0 = pm_tw_cfg0_state;
        PM_TW_CFG2 = pm_tw_cfg2_state;
    }
    
    return status;
}


/*******************************************************************************
* Function Name: CyXTAL_Stop
********************************************************************************
* Summary:
*   Disables the megahertz crystal oscillator.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyXTAL_Stop(void) 
{
    /* Disable the the oscillator. */
    FASTCLK_XMHZ_CSR &= ~XMHZ_CONTROL_ENABLE;
}


/*******************************************************************************
* Function Name: CyXTAL_EnableErrStatus
********************************************************************************
* Summary:
*    Enables the generation of the XERR status bit for the megahertz crystal.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyXTAL_EnableErrStatus(void) 
{
    /*1'b0      XFB_DIS_0      enabled. If oscillator has insufficient amplitude, XERR bit will be high. */
    FASTCLK_XMHZ_CSR &= ~X32_CONTROL_XERR_DIS;
}


/*******************************************************************************
* Function Name: CyXTAL_DisableErrStatus
********************************************************************************
* Summary:
*    Disables the generation of the XERR status bit for the megahertz crystal..
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyXTAL_DisableErrStatus(void) 
{
    /*1'b0      XFB_DIS_0      enabled. If oscillator has insufficient amplitude, XERR bit will be high. */
    FASTCLK_XMHZ_CSR |= X32_CONTROL_XERR_DIS;
}


/*******************************************************************************
* Function Name: CyXTAL_ReadStatus
********************************************************************************
* Summary:
*    Reads the XERR status bit for the megahertz crystal.  
*    This status bit is a sticky clear on read value.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Status
*    0: No error
*    1: Error.
*
*******************************************************************************/
uint8 CyXTAL_ReadStatus(void) 
{
    /*Bits      Name      Description
        7         xerr     High output indicates oscillator failure. 
    Only use this after start-up interval is completed. This can be used for 
    status and failure recovery.
    */
    return ((FASTCLK_XMHZ_CSR & X32_CONTROL_XERR_MASK) >> X32_CONTROL_XERR_POSITION);
}


/*******************************************************************************
* Function Name: CyXTAL_EnableFaultRecovery
********************************************************************************
* Summary:
*    Enables the fault recovery circuit which will switch to the IMO 
*    in the case of a fault in the megahertz crystal circuit.  
*    The crystal must be up and running with the XERR bit at 0, 
*    before calling this function to prevent immediate fault switchover.
*    This function does not work as intended for PSoC5 TM in case of MHz XTAL 
*    is driving Bus clock.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyXTAL_EnableFaultRecovery(void) 
{
    /*6th bit       xprot of FASTCLK_XMHZ_CSR 
    */
    FASTCLK_XMHZ_CSR |= X32_CONTROL_FAULT_RECOVER;
}


/*******************************************************************************
* Function Name: CyXTAL_DisableFaultRecovery
********************************************************************************
* Summary:
*    Disables the fault recovery circuit which will switch to the IMO 
*     in the case of a fault in the megahertz crystal circuit.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyXTAL_DisableFaultRecovery(void) 
{
    /*6th bit       xprot of FASTCLK_XMHZ_CSR 
    */
    FASTCLK_XMHZ_CSR &= ~X32_CONTROL_FAULT_RECOVER;
}


/*******************************************************************************
* Function Name: CyXTAL_SetStartup
********************************************************************************
* Summary:
*   Sets the startup settings for the crystal. Logic model outputs 
*   a frequency (setting + 4)MHz when enabled. 
*   This is artificial as the actual frequency is determined by an attached 
*   external crystal.
*
*
* Parameters:
*   setting: Valid range [0-31].  
*    Value is dependent on the frequency and quality of the crystal being used.  
*    PSoC3: Refer to the Register TRM for appropriate values for a specific crystal.
*    PSoC5 TM: Use 0x0F for 4-8 MHz range and 0x19 for 8-25MHz range.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyXTAL_SetStartup(uint8 setting) 
{
    /*Valid range 0-31*/
    FASTCLK_XMHZ_CFG0 = (FASTCLK_XMHZ_CFG0 & ~FASTCLK_XMHZ_GAINMASK) | 
                         (setting & FASTCLK_XMHZ_GAINMASK);
}


#if CY_PSOC3_ES3
/*******************************************************************************
* Function Name: CyXTAL_SetFbVoltage
********************************************************************************
* Summary:
*   Sets the feedback reference voltage to use for the crystal circuit. 
*   This function is only available for ES3 silicon.
*
* Parameters:
*   setting: Valid range [0-15].
*   Refer to the Register TRM for details on the mapping of the setting value to 
*   specific voltages.
*
*
* Return:
*   void.
*
*
* Side Effects and Restrictions:
*   The feedback reference voltage must be greater than the watchdog reference 
*   voltage.
*
*******************************************************************************/
void CyXTAL_SetFbVoltage(uint8 setting) 
{
    /*
    The register with this value has changed between ES2 and ES3 silicon.
    */
    FASTCLK_XMHZ_CFG1 = ((FASTCLK_XMHZ_CFG1 & ~FASTCLK_XMHZ_VREFMASK) | 
                         (setting & FASTCLK_XMHZ_VREFMASK));
}


/*******************************************************************************
* Function Name: CyXTAL_SetWdVoltage
********************************************************************************
* Summary:
*   Sets the reference voltage used by the watchdog to detect a failure 
*   in the crystal circuit. 
*   This function is only available for ES3 silicon.
*
* Parameters:
*   setting: Valid range [0-7].  
*   Refer to the Register TRM for details on the mapping of the setting value to 
*   specific voltages.
*
*
* Return:
*   void.
*
* Side Effects and Restrictions:
*   The feedback reference voltage must be greater than the watchdog 
*   reference voltage.
*
*******************************************************************************/
void CyXTAL_SetWdVoltage(uint8 setting) 
{
    /*
    The register with this value has changed between ES2 and ES3 silicon.
    */
    FASTCLK_XMHZ_CFG1 = ((FASTCLK_XMHZ_CFG1 & ~FASTCLK_XMHZ_VREF_WD_MASK) | 
                         ((setting << 4) & FASTCLK_XMHZ_VREF_WD_MASK));
}

#endif /*CY_PSOC3_ES3*/

/* CYLIB CLOCK funcs end */


/* CYLIB SYSTEM funcs begin */


/*******************************************************************************
* Function Name: CyHalt
********************************************************************************
* Summary:
*  Halts the CPU
*
*
* Parameters:
*   reason: Value to be used during debugging.
*
*
* Return: 
*   void.
*
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
#endif
}


/*******************************************************************************
* Function Name: CySoftwareReset
********************************************************************************
* Summary:
*  Forces a software reset of the device.
*
*
* Parameters:
*   None.
*
*
* Return: 
*   void.
*
*
*******************************************************************************/
void CySoftwareReset()
{
    /* Perform a reset by writing the software reset bit in reset control register 2 */
    *RESET_CR2 = 0x1;
}

/* CYLIB SYSTEM funcs end */


uint32 cydelay_freq_hz = BCLK__BUS_CLK__HZ;
uint32 cydelay_freq_khz = (BCLK__BUS_CLK__HZ + 999u) / 1000u;
uint8 cydelay_freq_mhz = (uint8)((BCLK__BUS_CLK__HZ + 999999u) / 1000000u);
uint32 cydelay_32k_ms = 32768 * ((BCLK__BUS_CLK__HZ + 999u) / 1000u);


/*******************************************************************************
* Function Name: CyDelay
********************************************************************************
* Summary:
*   Blocks for milliseconds.
*    Note: CyDelay has been implemented with the instruction cache assumed enabled. 
*      When instruction cache is disabled on PSoC5, CyDelay will be two times 
*      larger. Ex: With instruction cache disabled CyDelay(100) would result 
*      in about 200ms delay instead of 100ms.
*
* Parameters:
*   milliseconds: number of milliseconds to delay.
*
* Return:
*   void.
*
*******************************************************************************/
void CyDelay(uint32 milliseconds) CYREENTRANT
{
    while (milliseconds > 32768)
    {
        /* This loop prevents overflow.
         * At 100MHz, milliseconds * delay_freq_khz overflows at about 42 seconds
         */
        CyDelayCycles(cydelay_32k_ms);
        milliseconds -= 32768;
    }

    CyDelayCycles(milliseconds * cydelay_freq_khz);
}


/*******************************************************************************
* Function Name: CyDelayUs
********************************************************************************
* Summary:
*   Blocks for microseconds.
*    Note: CyDelay has been implemented with the instruction cache assumed enabled. 
*      When instruction cache is disabled on PSoC5, CyDelayUs will be two times 
*      larger. Ex: With instruction cache disabled CyDelayUs(100) would result 
*      in about 200us delay instead of 100us.
*
* Parameters:
*   microseconds: number of microseconds to delay.
*
* Return:
*   void.
*
*******************************************************************************/
#if defined(__ARMCC_VERSION)
void CyDelayUs(uint16 microseconds) CYREENTRANT
{
    CyDelayCycles((uint32)microseconds * cydelay_freq_mhz);
}
#elif defined(__GNUC__)
void CyDelayUs(uint16 microseconds) CYREENTRANT
{
    CyDelayCycles((uint32)microseconds * cydelay_freq_mhz);
}
#endif


/*******************************************************************************
* Function Name: CyDelayFreq
********************************************************************************
* Summary:
*   Sets clock frequency for CyDelay.
*
* Parameters:
*   freq: Frequency of bus clock in Hertz.
*
* Return:
*   void.
*
*******************************************************************************/
void CyDelayFreq(uint32 freq) CYREENTRANT
{
    if (freq != 0u)
        cydelay_freq_hz = freq;
    else
        cydelay_freq_hz = BCLK__BUS_CLK__HZ;
    cydelay_freq_mhz = (uint8)((cydelay_freq_hz + 999999u) / 1000000u);
    cydelay_freq_khz = (cydelay_freq_hz + 999u) / 1000u;
    cydelay_32k_ms = 32768 * cydelay_freq_khz;
}

/*******************************************************************************
* Function Name: CyWdtStart
********************************************************************************
* Summary:
*  Enables the watchdog timer.  
*  The timer is configured for the specified count interval, the central timewheel 
*  is cleared, the setting for low power mode is configured and the watchdog 
*  timer is enabled.  
*  Once enabled the watchdog cannot be disabled.  
*  The watchdog must be cleared using the CyWdtClear() function before 
*  three ticks of the watchdog timer occur.
*  The ILO 1 KHz must be enabled for proper WDT operation.
*
* Parameters: 
*   ticks: One of the four available timer periods.
*         CYWDT_2_TICKS     -    2 CTW Ticks ==> 2ms (nominal)
*         CYWDT_16_TICKS    -   16 CTW Ticks ==> 16ms (nominal)
*         CYWDT_128_TICKS   -  128 CTW Ticks ==> 128ms (nominal)
*         CYWDT_1024_TICKS  - 1024 CTW Ticks ==> 1024ms (nominal)
*   lpMode: Low power mode configuration
*         CYWDT_LPMODE_NOCHANGE - No Change
*         CYWDT_LPMODE_MAXINTER - Switch to longest timer mode during sleep/hibernate
*         CYWDT_LPMODE_DISABLED - Disable WDT during sleep/hibernate
* 
* Return: 
*  None.
*
*******************************************************************************/
void CyWdtStart(uint8 ticks, uint8 lpMode)
{
#if (CY_PSOC3_ES2 || CY_PSOC5_ES1)
    CyILO_Start1K();
#endif

    /* Set the number of ticks. */
    *CYWDT_CFG = (ticks & CYWDT_TICKS_MASK) | (*CYWDT_CFG & ~CYWDT_TICKS_MASK);
    
    /*Clear the central time wheel.*/
    *CYWDT_CFG = CYWDT_RESET | *CYWDT_CFG;
    *CYWDT_CFG = ~CYWDT_RESET & *CYWDT_CFG;
    
    /*To avoid warning of lpmode being unreferenced.*/
    lpMode = lpMode;
#if (CY_PSOC3_ES3 || CY_PSOC5_ES2)
    /*Setting the low power mode*/
    *CYWDT_CFG = ((lpMode << CYWDT_LPMODE_SHIFT) & CYWDT_LPMODE_MASK) | (*CYWDT_CFG & ~CYWDT_LPMODE_MASK);
#endif
    
    /* Enables the watchdog timer.*/
    *CYWDT_CFG = CYWDT_ENABLE_BIT | *CYWDT_CFG;
}

/*******************************************************************************
* Function Name: CyWdtClear
********************************************************************************
* Summary:
*  Clears (feeds) the watchdog timer.
*
*
* Parameters: 
*  None.
*
*
* Return: 
*  None.
*
*******************************************************************************/
void CyWdtClear(void)
{
    /* Clears the Watchdog timer. */
#if (((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A) && (CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2)) || \
     ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A) && (CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_ES1)))
    /* PSoC3 ES2 and PSoC5 ES1 watchdog time clear requires workaround */
    uint8 wdt_cfg_value = *CYWDT_CFG; 
    *CYWDT_CR = 1; 
    *CYWDT_CFG = 0; 
    *CYWDT_CFG = wdt_cfg_value;
#else
    *CYWDT_CR = 1;
#endif 
}

/*******************************************************************************
* Function Name: CyDisableInts
********************************************************************************
* Summary:
*  Disables the interrupt enable for each interrupt.
*
*
* Parameters: 
*  None.
*
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

    return intState;
}

/*******************************************************************************
* Function Name: CyEnableInts
********************************************************************************
* Summary:
*  Enables interrupts to a given state.
*
*
* Parameters:
*   mask, 32 bit mask of interrupts to enable.
*
*
* Return: 
*  void.
*
*******************************************************************************/
void CyEnableInts(uint32 mask) 
{
    /* Set interrupts as enabled. */
    CY_SET_REG32(CYINT_ENABLE, mask);
}


/*******************************************************************************
* Function Name: CyIntSetVector
********************************************************************************
* Summary:
*   Sets the interrupt vector of the specified interrupt number.
*
*
* Parameters:
*   number: Valid range [0-31].  Interrupt number
*
*   address: Pointer to an interrupt service routine
*
* Return:
*   Previous interrupt vector value.
*
*******************************************************************************/
cyisraddress CyIntSetVector(uint8 number, cyisraddress address) 
{
    cyisraddress oldIsr;

    CYASSERT(number <= CY_INT_NUMBER_MAX);
    /* Save old Interrupt service routine. */
    oldIsr = (cyisraddress) CY_GET_REG16(&CYINT_VECT_TABLE[number & CY_INT_NUMBER_MASK]);

    /* Set new Interrupt service routine. */
    CY_SET_REG16(&CYINT_VECT_TABLE[number], (uint16) address);

    return oldIsr;
}

/*******************************************************************************
* Function Name: CyIntGetVector
********************************************************************************
* Summary:
*   Gets the interrupt vector of the specified interrupt number.
*
*
* Parameters:
*   number: Valid range [0-31].  Interrupt number
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress CyIntGetVector(uint8 number) 
{
    CYASSERT(number <= CY_INT_NUMBER_MAX);
    return (cyisraddress) CY_GET_REG16(&CYINT_VECT_TABLE[number & CY_INT_NUMBER_MASK]);
}

/*******************************************************************************
* Function Name: CyIntSetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*   number: The number of the interrupt, 0 - 31.
*
* Return:
*   void.
*
*
*******************************************************************************/
void CyIntSetPriority(uint8 number, uint8 priority) 
{
    CYASSERT(priority <= CY_INT_PRIORITY_MAX);
    CYASSERT(number <= CY_INT_NUMBER_MAX);
    CYINT_PRIORITY[number & CY_INT_NUMBER_MASK] = (priority & CY_INT_PRIORITY_MASK) << 5;
}

/*******************************************************************************
* Function Name: CyIntGetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   number: The number of the interrupt, 0 - 31.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 CyIntGetPriority(uint8 number) 
{
    uint8 priority;

    CYASSERT(number <= CY_INT_NUMBER_MAX);

    priority = CYINT_PRIORITY[number & CY_INT_NUMBER_MASK] >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: CyIntEnable
********************************************************************************
* Summary:
*   Enables the specified interrupt number.
*
*
* Parameters:
*   number: Valid range [0-31].  Interrupt number
*
*
* Return:
*   void.
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
* Summary:
*   Gets the enable state of the specified interrupt number.
*
*
* Parameters:
*   number: Valid range [0-31].  Interrupt number.
*
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
    return (*stateReg & (1 << (0x07 & number))) ? 1:0;
}

/*******************************************************************************
* Function Name: CyIntDisable
********************************************************************************
* Summary:
*   Disables the specified interrupt number.
*
*
* Parameters:
*   number: Valid range [0-31].  Interrupt number.
*
*
* Return:
*   void.
*
*******************************************************************************/
void CyIntDisable(uint8 number) CYREENTRANT
{
    reg8 * clearReg;

    CYASSERT(number <= CY_INT_NUMBER_MAX);

    /* Get a pointer to the Interrupt enable register. */
    clearReg = CYINT_CLEAR + ((number & CY_INT_NUMBER_MASK) >> 3);

    /* Enable the interrupt. */
    *clearReg = 1 << (0x07 & number);
}

/*******************************************************************************
* Function Name: CyIntSetPending
********************************************************************************
* Summary:
*   Forces the specified interrupt number to be pending.
*
*
* Parameters:
*   number: Valid range [0-31].  Interrupt number.
*
*
* Return:
*   void.
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
*   Clears any pending interrupt for the specified interrupt number.
*
* Parameters:
*   number: Valid range [0-31].  Interrupt number.
*
*
* Return:
*   void.
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

/* cystrcpy, cystrlen, CyGetSwapReg16 and CySetSwapReg16 are obsolete functions.
and are not recommended for use in new code. */
/*******************************************************************************
* Function Name: cystrcpy
********************************************************************************
* Summary:
*   Recommended not use these function, these are defined for compatibility.
*
*******************************************************************************/
char * cystrcpy(char * s1, char * s2)
{
    return strcpy(s1, s2);
}

/*******************************************************************************
* Function Name: cystrlen
********************************************************************************
* Summary:
*   Recommended not use these function, these are defined for compatibility.
*
*******************************************************************************/
uint32 cystrlen(const char * s)
{
    return strlen(s);
}

/*******************************************************************************
* Function Name: CyGetSwapReg16
********************************************************************************
* Summary:
*   Recommended not use these function, these are defined for compatibility.
*
*******************************************************************************/
uint16  CyGetSwapReg16(uint16 CYXDATA* addr)
{
    return cyread16_nodpx((void CYFAR *) addr);
}

/*******************************************************************************
* Function Name: CySetSwapReg16
********************************************************************************
* Summary:
*   Recommended not use these function, these are defined for compatibility.
*
*******************************************************************************/
void CySetSwapReg16(uint16 CYXDATA* addr, uint16 value)    
{
    cywrite16_nodpx((void CYFAR *) addr, value);
}
