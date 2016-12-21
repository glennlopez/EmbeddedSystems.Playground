/*******************************************************************************
* File Name: ADC.c  
* Version 2.30
*
* Description:
*  This file provides the source code to the API for the Delta-Sigma ADC
*  Component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "ADC.h"

#if(ADC_DEFAULT_INTERNAL_CLK)
    #include "ADC_theACLK.h"
#endif /* ADC_DEFAULT_INTERNAL_CLK */

#include "ADC_Ext_CP_Clk.h"

#if(ADC_DEFAULT_INPUT_MODE)
    #include "ADC_AMux.h"
#endif /* ADC_DEFAULT_INPUT_MODE */

/* Software flag for checking conversion completed or not */
volatile uint8 ADC_convDone = 0u;

/* Software flag to stop conversion for single sample conversion mode 
   with resolution above 16 bits */
volatile uint8 ADC_stopConversion = 0u;

/* To run the initialization block only at the start up */
uint8 ADC_initVar = 0u;

/* To check whether ADC started or not before switching the configuration */
volatile uint8 ADC_started = 0u;

/* Flag to hold ADC config number. By default active config is 1. */
volatile uint8 ADC_Config = 1u;

volatile int32 ADC_Offset = 0u;
volatile int32 ADC_CountsPerVolt = (uint32)ADC_CFG1_COUNTS_PER_VOLT;

/* Only valid for PSoC5A */
/* Variable to decide whether or not to restore the register values from
    backup structure */
#if (CY_PSOC5A)
    uint8 ADC_restoreReg = 0u;
#endif /* CY_PSOC5A */

/* Valid only for PSoC5A silicon */
#if (CY_PSOC5A)
    /* Backup struct for power mode registers */
    static ADC_POWERMODE_BACKUP_STRUCT ADC_powerModeBackup = 
    {
        /* Initializing the structure fields with power mode registers of 
           config1 */
        ADC_CFG1_DSM_CR14,
        ADC_CFG1_DSM_CR15,
        ADC_CFG1_DSM_CR16,
        ADC_CFG1_DSM_CR17,
        ADC_CFG1_DSM_REF0,
        ADC_CFG1_DSM_BUF0,
        ADC_CFG1_DSM_BUF1,
        ADC_CFG1_DSM_CLK,
        ADC_BYPASS_DISABLED
    };
#endif /* CY_PSOC5A */


/****************************************************************************** 
* Function Name: ADC_Init
*******************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
* ADC_Start().
*  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
*******************************************************************************/
void ADC_Init(void) 
{
    /* Initialize the registers with default customizer settings for config1 */
    ADC_InitConfig(1);

    /* This is only valid if there is an internal clock */
    #if(ADC_DEFAULT_INTERNAL_CLK)
        ADC_theACLK_SetMode(CYCLK_DUTY);
    #endif /* ADC_DEFAULT_INTERNAL_CLK */
    
    /* Set the duty cycle for charge pump clock */
    ADC_Ext_CP_Clk_SetMode(CYCLK_DUTY);

    /* To perform ADC calibration */
    ADC_GainCompensation(ADC_CFG1_RANGE, 
                                      ADC_CFG1_IDEAL_DEC_GAIN, 
                                      ADC_CFG1_IDEAL_ODDDEC_GAIN, 
                                      ADC_CFG1_RESOLUTION);        
}


/******************************************************************************
* Function Name: ADC_Enable
*******************************************************************************
*
* Summary: 
*  Enables the ADC DelSig block operation.
*  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
*******************************************************************************/
void ADC_Enable(void) 
{
    /* Restore the power registers if silicon used is PSoC5A */
    #if (CY_PSOC5A)
        if(ADC_restoreReg && 
           (!(ADC_powerModeBackup.bypassRestore)))
        {
            ADC_RestorePowerRegisters();
            ADC_restoreReg = 0u;
        }
        ADC_powerModeBackup.bypassRestore = ADC_BYPASS_DISABLED;
    #endif /* CY_PSOC5A */

    /* Enable active mode power for ADC */
    ADC_PWRMGR_DEC_REG |= ADC_ACT_PWR_DEC_EN;
    ADC_PWRMGR_DSM_REG |= ADC_ACT_PWR_DSM_EN;
    
     /* Enable alternative active mode power for ADC */
    ADC_STBY_PWRMGR_DEC_REG |= ADC_STBY_PWR_DEC_EN;
    #if (CY_PSOC3 || CY_PSOC5LP)
    ADC_STBY_PWRMGR_DSM_REG |= ADC_STBY_PWR_DSM_EN;
    #endif /* CY_PSOC3 || CY_PSOC5LP */

    /* Config selected is 1, then before enablign the REFBUF0, REFBUF1 and 
	   VCMBUF's enable and press circuit and then after a delay of 3
	   microseconds, disable the press circuit. */
    if (ADC_Config == 1u)
	{
	    /* Disable PRES, Enable power to VCMBUF0, REFBUF0 and REFBUF1, enable 
	       PRES */
	    #if (CY_PSOC3 || CY_PSOC5LP)
	        ADC_RESET_CR4_REG |= ADC_IGNORE_PRESA1;
	        ADC_RESET_CR5_REG |= ADC_IGNORE_PRESA2;
	    #elif (CY_PSOC5A)
	        ADC_RESET_CR1_REG |= ADC_DIS_PRES1;
	        ADC_RESET_CR3_REG |= ADC_DIS_PRES2;
	    #endif /* CY_PSOC5A */
	    
	    ADC_DSM_CR17_REG |= (ADC_DSM_EN_BUF_VREF | ADC_DSM_EN_BUF_VCM);
	    #if ((ADC_CFG1_REFERENCE == ADC_EXT_REF_ON_P03) || \
	         (ADC_CFG1_REFERENCE == ADC_EXT_REF_ON_P32))
	        ADC_DSM_CR17_REG &= ~ADC_DSM_EN_BUF_VREF;
	    #endif /* Check for exteranl reference option */
	    #if ((ADC_CFG1_RANGE == ADC_IR_VSSA_TO_2VREF) && \
	          (CY_PSOC3 || CY_PSOC5LP) && \
	          ((ADC_CFG1_REFERENCE != ADC_EXT_REF_ON_P03) && \
	         (ADC_CFG1_REFERENCE != ADC_EXT_REF_ON_P32)))
	        ADC_DSM_REF0_REG |= ADC_DSM_EN_BUF_VREF_INN;
	    #endif /* ADC_IR_VSSA_TO_2VREF */
	    
	        /* Wait for 3 microseconds */
	    CyDelayUs(3);
        /* Enable the press circuit */
	    #if (CY_PSOC3 || CY_PSOC5LP)
	        ADC_RESET_CR4_REG &= ~ADC_IGNORE_PRESA1;
	        ADC_RESET_CR5_REG &= ~ADC_IGNORE_PRESA2;
	    #elif (CY_PSOC5A)
	        ADC_RESET_CR1_REG &= ~ADC_DIS_PRES1;
	        ADC_RESET_CR3_REG &= ~ADC_DIS_PRES2;
	    #endif /* CY_PSOC5A */
	}
    
    /* Enable negative pumps for DSM  */
    ADC_PUMP_CR1_REG  |= ( ADC_PUMP_CR1_CLKSEL | ADC_PUMP_CR1_FORCE );
 
    /* This is only valid if there is an internal clock */
    #if(ADC_DEFAULT_INTERNAL_CLK)
        ADC_PWRMGR_CLK_REG |= ADC_ACT_PWR_CLK_EN;        
        ADC_STBY_PWRMGR_CLK_REG |= ADC_STBY_PWR_CLK_EN;
    #endif /* ADC_DEFAULT_INTERNAL_CLK */
    
    /* Enable the active and alternate active power for charge pump clock */
    ADC_PWRMGR_CHARGE_PUMP_CLK_REG |= ADC_ACT_PWR_CHARGE_PUMP_CLK_EN;
    ADC_STBY_PWRMGR_CHARGE_PUMP_CLK_REG |= ADC_STBY_PWR_CHARGE_PUMP_CLK_EN;
        
}


#if (CY_PSOC5A) /* valid only for PSoC5A silicon */
    /******************************************************************************* 
    * Function Name: ADC_RestorePowerRegisters
    ********************************************************************************
    *
    * Summary: 
    *  Restores the power registers on calling Start() API. This API is only 
    *   for internal use and valid only for PSoC5A.
    *  
    *
    * Parameters:  
    *  void
    *
    * Return: 
    *  void 
    *
    ***************************************************************************/
    void ADC_RestorePowerRegisters(void) 
    {
        ADC_DSM_CR14_REG = ADC_powerModeBackup.DSM_CR_14;
        ADC_DSM_CR15_REG = ADC_powerModeBackup.DSM_CR_15;
        ADC_DSM_CR16_REG = ADC_powerModeBackup.DSM_CR_16;
        ADC_DSM_CR17_REG = ADC_powerModeBackup.DSM_CR_17;
        ADC_DSM_REF0_REG = ADC_powerModeBackup.DSM_REF0;
        ADC_DSM_BUF0_REG = ADC_powerModeBackup.DSM_BUF0;
        ADC_DSM_BUF1_REG = ADC_powerModeBackup.DSM_BUF1;
        ADC_DSM_CLK_REG = ADC_powerModeBackup.DSM_CLK;
    }


    /************************************************************************** 
    * Function Name: ADC_SavePowerRegisters
    ***************************************************************************
    *
    * Summary: 
    *  Save the power registers before stopping the block operation. This is 
    *  called by Stop() API. This API is only for internal use and valid only 
    *  for PSoC5A.
    *  
    *
    * Parameters:  
    *  void
    *
    * Return: 
    *  void 
    *
    **************************************************************************/
    void ADC_SavePowerRegisters(void) 
    {
        ADC_powerModeBackup.DSM_CR_14 = ADC_DSM_CR14_REG;
        ADC_powerModeBackup.DSM_CR_15 = ADC_DSM_CR15_REG;
        ADC_powerModeBackup.DSM_CR_16 = ADC_DSM_CR16_REG;
        ADC_powerModeBackup.DSM_CR_17 = ADC_DSM_CR17_REG;
        ADC_powerModeBackup.DSM_REF0 = ADC_DSM_REF0_REG;
        ADC_powerModeBackup.DSM_BUF0 = ADC_DSM_BUF0_REG;
        ADC_powerModeBackup.DSM_BUF1 = ADC_DSM_BUF1_REG;
        ADC_powerModeBackup.DSM_CLK = ADC_DSM_CLK_REG;
    }


    /************************************************************************* 
    * Function Name: ADC_SetLowPower
    ***************************************************************************
    *
    * Summary: 
    *  Set all the power registers of DSM block to low power mode. This API is
    *   called by Stop() API. This API is only for internal use and valid for 
    *   only PSoC5A.
    *  
    *
    * Parameters:  
    *  void
    *
    * Return: 
    *  void 
    *
    ***************************************************************************/
    void ADC_SetLowPower(void) 
    {
        ADC_DSM_CR14_REG &= ~ADC_DSM_POWER1_MASK;
        ADC_DSM_CR14_REG |= ADC_DSM_POWER1_44UA;
        
        ADC_DSM_CR15_REG &= ~(ADC_DSM_POWER2_3_MASK | ADC_DSM_POWER_COMP_MASK);
        ADC_DSM_CR15_REG |= (ADC_DSM_POWER2_3_LOW | ADC_DSM_POWER_VERYLOW);
        
        ADC_DSM_CR16_REG &= ~(ADC_DSM_CP_PWRCTL_MASK | ADC_DSM_POWER_SUM_MASK |
                                           ADC_DSM_CP_ENABLE);
        ADC_DSM_CR16_REG |= (ADC_DSM_POWER_SUM_LOW | ADC_DSM_CP_PWRCTL_LOW);
        
        ADC_DSM_CR17_REG &= ~(ADC_DSM_EN_BUF_VREF | ADC_DSM_PWR_CTRL_VCM_MASK |
                                           ADC_DSM_PWR_CTRL_VREF_MASK | ADC_DSM_EN_BUF_VCM |
                                           ADC_DSM_PWR_CTRL_VREF_INN_MASK);
        ADC_DSM_CR17_REG |= (ADC_DSM_PWR_CTRL_VREF_0 | ADC_DSM_PWR_CTRL_VCM_0 |
                                           ADC_DSM_PWR_CTRL_VREF_INN_0);
        
        /* Disable reference buffers */
        ADC_DSM_REF0_REG &= ~(ADC_DSM_EN_BUF_VREF_INN | ADC_DSM_VREF_RES_DIV_EN |
                                           ADC_DSM_VCM_RES_DIV_EN);
            
        /* Disable the positive input buffer */
        ADC_DSM_BUF0_REG &= ~ADC_DSM_ENABLE_P;
        /* Disable the negative input buffer */
        ADC_DSM_BUF1_REG &= ~ADC_DSM_ENABLE_N;
        /* Disable the clock to DSM */
        ADC_DSM_CLK_REG &= ~(ADC_DSM_CLK_CLK_EN | ADC_DSM_CLK_BYPASS_SYNC);
    }
#endif /* CY_PSOC5A */


/******************************************************************************* 
* Function Name: ADC_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Delta Sigma Modulator with the default  
*  values, and sets the power to the given level.  A power level of 0, is the 
*  same as executing the stop function.
*
* Parameters:  
*  None
*
* Return: 
*  void 
*
* Global variables:
*  ADC_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
*******************************************************************************/
void ADC_Start() 
{
    if(ADC_initVar == 0u)
    {
        if(!(ADC_started))
        {
            ADC_Init();
        }
        ADC_initVar = 1u;
    }

    /* Enable the ADC */
    ADC_Enable();
}


/*******************************************************************************
* Function Name: ADC_Stop
********************************************************************************
*
* Summary:
*  Stops and powers down ADC to lowest power state.
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
*******************************************************************************/
void ADC_Stop(void) 
{
    /* Stop conversions */
    ADC_DEC_CR_REG &= ~ADC_DEC_START_CONV;
    ADC_DEC_SR_REG |=  ADC_DEC_INTR_CLEAR;
    
    /* Disable PRES, Disable power to VCMBUF0, REFBUF0 and REFBUF1, 
       enable PRES */
    #if (CY_PSOC3 || CY_PSOC5LP)
        ADC_RESET_CR4_REG |= ADC_IGNORE_PRESA1;
        ADC_RESET_CR5_REG |= ADC_IGNORE_PRESA2;
    #elif (CY_PSOC5A)
        ADC_RESET_CR1_REG |= ADC_DIS_PRES1;
        ADC_RESET_CR3_REG |= ADC_DIS_PRES2;
    #endif /* CY_PSOC5A */
    
    ADC_DSM_CR17_REG &= ~(ADC_DSM_EN_BUF_VREF | ADC_DSM_EN_BUF_VCM);
    ADC_DSM_REF0_REG &= ~ADC_DSM_EN_BUF_VREF_INN;
    
    /* Wait for 3 microseconds. */
    CyDelayUs(3);
    
	/* Enable the press circuit */
    #if (CY_PSOC3 || CY_PSOC5LP)
        ADC_RESET_CR4_REG &= ~ADC_IGNORE_PRESA1;
        ADC_RESET_CR5_REG &= ~ADC_IGNORE_PRESA2;
    #elif (CY_PSOC5A)
        ADC_RESET_CR1_REG &= ~ADC_DIS_PRES1;
        ADC_RESET_CR3_REG &= ~ADC_DIS_PRES2;
    #endif /* CY_PSOC5A */
    
    /* If PSoC5A then don't disable the power instead put the block to  
       low power mode. Also, save current state of all the power configuration 
       registers before putting block to low power mode */
    #if (CY_PSOC5A)
        
        /* set the flag */
        ADC_restoreReg = 1u;
        
        ADC_SavePowerRegisters();
        ADC_SetLowPower();
    #else    
        /* Disable power to the ADC */
        ADC_PWRMGR_DSM_REG &= ~ADC_ACT_PWR_DSM_EN;
    #endif /* CY_PSOC5A */
    
    /* Disable power to Decimator block */
    ADC_PWRMGR_DEC_REG &= ~ADC_ACT_PWR_DEC_EN;
    
    /* Disable alternative active power to the ADC */
    ADC_STBY_PWRMGR_DEC_REG &= ~ADC_STBY_PWR_DEC_EN;
    #if (CY_PSOC3 || CY_PSOC5LP)
    ADC_STBY_PWRMGR_DSM_REG &= ~ADC_STBY_PWR_DSM_EN;
    #endif /* CY_PSOC3 || CY_PSOC5LP */

   /* Disable negative pumps for DSM  */
    ADC_PUMP_CR1_REG &= ~(ADC_PUMP_CR1_CLKSEL | ADC_PUMP_CR1_FORCE );
    
    /* This is only valid if there is an internal clock */
    #if(ADC_DEFAULT_INTERNAL_CLK)
        ADC_PWRMGR_CLK_REG &= ~ADC_ACT_PWR_CLK_EN;
        ADC_STBY_PWRMGR_CLK_REG &= ~ADC_STBY_PWR_CLK_EN;
    #endif /* ADC_DEFAULT_INTERNAL_CLK */
    
    /* Disable power to charge pump clock */
    ADC_PWRMGR_CHARGE_PUMP_CLK_REG &= ~ADC_ACT_PWR_CHARGE_PUMP_CLK_EN;
    ADC_STBY_PWRMGR_CHARGE_PUMP_CLK_REG &= ~ADC_STBY_PWR_CHARGE_PUMP_CLK_EN;
}


/*******************************************************************************
* Function Name: ADC_SetBufferGain
********************************************************************************
*
* Summary:
*  Set input buffer range.
*
* Parameters:  
*  gain:  Two bit value to select a gain of 1, 2, 4, or 8.
*
* Return: 
*  void
*
*******************************************************************************/
void ADC_SetBufferGain(uint8 gain) 
{
    uint8 tmpReg;
    tmpReg = ADC_DSM_BUF1_REG & ~ADC_DSM_GAIN_MASK;
    tmpReg |= (gain << 2);
    ADC_DSM_BUF1_REG = tmpReg;
}


/*******************************************************************************
* Function Name: ADC_SetCoherency
********************************************************************************
*
* Summary:
*  Sets the ADC output register coherency bit.
*
* Parameters:  
*  gain:  Two bit value to set the coherency bit.
          00-Coherency checking off
          01-low byte is key byte
          02-middle byte is the key byte
          03-high byte is the key byte
*
* Return: 
*  void
*
* Side Effects:  If the coherency is changed, for any reason, it should be 
*                changed back to the LSB when the provided "GetResult" API 
*                is used.
*
*******************************************************************************/
void ADC_SetCoherency(uint8 coherency) 
{
    uint8 tmpReg;    
    tmpReg = ADC_DEC_COHER_REG & ~ADC_DEC_SAMP_KEY_MASK;
    tmpReg |= coherency;
    ADC_DEC_COHER_REG = tmpReg;
}


/*******************************************************************************
* Function Name: ADC_SetGCOR
********************************************************************************
*
* Summary:
*  Calculates a new GCOR value and writes it into the GCOR register.
*
* Parameters:  
*  gainAdjust:  floating point value to set GCOR registers.
*
* Return: 
*  uint8:  0-if GCOR value is within the expected range.
           1- if GCOR is outside the expected range.
*
* Side Effects:  The GVAL register is set to the amount of valid bits in the
*                GCOR  register minus one. If GVAL is 15 (0x0F), all 16 bits
*                of the GCOR registers will be valid. If for example GVAL is 
*                11 (0x0B) only 12 bits will be valid. The least 4 bits will
*                be lost when the GCOR value is shifted 4 places to the right.
*
******************************************************************************/
uint8 ADC_SetGCOR(float gainAdjust) 
{
    uint16 tmpReg;
    uint8 status;
    float tmpValue;
    
    tmpReg = ADC_DEC_GCORH_REG;
    tmpReg = (tmpReg << 8) | ADC_DEC_GCOR_REG;
    tmpValue = ((float)tmpReg / ADC_IDEAL_GAIN_CONST);
    tmpValue = tmpValue * gainAdjust;
    
    if (tmpValue > 1.9999)
    {
        status = 1;
    }
    else
    {
        tmpReg = (uint16)(tmpValue * ADC_IDEAL_GAIN_CONST);
        ADC_DEC_GCOR_REG = (uint8)tmpReg;
        ADC_DEC_GCORH_REG = (uint8) (tmpReg >> 8);
        status = 0;
    }
    
    return status;
}


/******************************************************************************
* Function Name: ADC_ReadGCOR
*******************************************************************************
*
* Summary:
*  This API returns the current GCOR register value, normalized based on the 
*  GVAL register settings.
*
* Parameters:  
*  void
*
* Return: 
*  uint16:  Normalized GCOR value.
*
* Side Effects:  If the GVAL register is set to a value greater than 0x0F, then
                 it gives unexpected value.
*
*******************************************************************************/
uint16 ADC_ReadGCOR(void) 
{
    uint8 gValue;
    uint16 gcorValue, gcorRegValue;
    
    gValue = ADC_DEC_GVAL_REG;
    gcorRegValue = CY_GET_REG16(ADC_DEC_GCOR_PTR);
    
    switch (gValue)
    {
        case ADC_GVAL_RESOLUTIN_8:
            gcorValue = gcorRegValue << (ADC_MAX_GVAL - gValue);
            break;
        
        case ADC_GVAL_RESOLUTIN_9:
            gcorValue = gcorRegValue << (ADC_MAX_GVAL - gValue);
            break;
            
        case ADC_GVAL_RESOLUTIN_10:
            gcorValue = gcorRegValue << (ADC_MAX_GVAL - gValue);
            break;
            
        case ADC_GVAL_RESOLUTIN_11:
            gcorValue = gcorRegValue << (ADC_MAX_GVAL - gValue);
            break;
            
        case ADC_GVAL_RESOLUTIN_12:
            gcorValue = gcorRegValue << (ADC_MAX_GVAL - gValue);
            break;
            
        case ADC_GVAL_RESOLUTIN_13:
            gcorValue = gcorRegValue << (ADC_MAX_GVAL - gValue);
            break;
            
        default:
            gcorValue = gcorRegValue;
            break;
    }
        
    return gcorValue;
}


/*******************************************************************************
* Function Name: ADC_SetBufferChop
********************************************************************************
*
* Summary:
*  Sets the Delta Sigma Modulator Buffer chopper mode.
*
* Parameters:  
*  chopen:  If non-zero set the chopper mode.
*  chopFreq:  Chop frequency value.
*
* Return: 
*  void
*
*******************************************************************************/
void ADC_SetBufferChop(uint8 chopen, uint8 chopFreq) 
{
    if(chopen != 0u)
    {
        ADC_DSM_BUF2_REG = (ADC_DSM_BUF_FCHOP_MASK & chopFreq) | \
                                         ADC_DSM_BUF_CHOP_EN;
    }
    else
    {
        ADC_DSM_BUF2_REG = 0x00u;
    }
}


/*******************************************************************************
* Function Name: ADC_StartConvert
********************************************************************************
*
* Summary:
*  Starts ADC conversion using the given mode.
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
*******************************************************************************/
void ADC_StartConvert(void) 
{
    /* Start the conversion */
    ADC_DEC_CR_REG |= ADC_DEC_START_CONV;  
}


/*******************************************************************************
* Function Name: ADC_StopConvert
********************************************************************************
*
* Summary:
*  Starts ADC conversion using the given mode.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ADC_convDone:  Modified when conversion is complete for single
*   sample mode with resolution is above 16.
*
*******************************************************************************/
void ADC_StopConvert(void) 
{
    /* Stop all conversions */
    ADC_DEC_CR_REG &= ~ADC_DEC_START_CONV; 
    
    /* Software flag for checking conversion complete or not. Will be used when
       resolution is above 16 bits and conversion mode is single sample */
    ADC_convDone = 1u;
}


/*******************************************************************************
* Function Name: ADC_IsEndConversion
********************************************************************************
*
* Summary:
*  Queries the ADC to see if conversion is complete
*
* Parameters:  
*  wMode:  Wait mode, 0 if return with answer immediately.
*                     1 if wait until conversion is complete, then return.
*
* Return: 
*  uint8 status:  0 =>  Conversion not complete.
*                 1 =>  Conversion complete.
*
* Global variables:
*  ADC_convDone:  Used to check whether conversion is complete
*  or not for single sample mode with resolution is above 16
*
*******************************************************************************/
uint8 ADC_IsEndConversion(uint8 wMode) 
{
    uint8 status;
        
    /* Check for stop convert if conversion mode is Single Sample with 
       resolution above 16 bit */
    if(ADC_stopConversion == 1u)
    {
        do
        {
            status = ADC_convDone;
        } while((status != ADC_DEC_CONV_DONE) && (wMode == ADC_WAIT_FOR_RESULT));
    }
    else
    {
        do 
        {
            status = ADC_DEC_SR_REG & ADC_DEC_CONV_DONE;
        } while((status != ADC_DEC_CONV_DONE) && (wMode == ADC_WAIT_FOR_RESULT));
    }
    return(status);
}


/*******************************************************************************
* Function Name: ADC_GetResult8
********************************************************************************
*
* Summary:
*  Returns an 8-bit result or the LSB of the last conversion.
*
* Parameters:  
*  void
*
* Return: 
*  int8:  ADC result.
*
*******************************************************************************/
int8 ADC_GetResult8( void ) 
{
     return( ADC_DEC_SAMP_REG );
}


/*******************************************************************************
* Function Name: ADC_GetResult16
********************************************************************************
*
* Summary:
*  Returns a 16-bit result from the last ADC conversion.
*
* Parameters:  
*   void
*
* Return: 
*  int16:  ADC result.
*
*******************************************************************************/
int16 ADC_GetResult16(void) 
{
    uint16 result;
    
    #if (CY_PSOC3)
        result = ADC_DEC_SAMPM_REG ;
        result = (result << 8 ) | ADC_DEC_SAMP_REG;
    #else
        result = (CY_GET_REG16(ADC_DEC_SAMP_PTR));
    #endif /* CY_PSOC3 */
    
    return result;
}


/*******************************************************************************
* Function Name: ADC_GetResult32
********************************************************************************
*
* Summary:
*  Returns an 32-bit result from ADC
*
* Parameters:  
*  void
*
* Return: 
*  int32:  ADC result.
*
*******************************************************************************/
int32 ADC_GetResult32(void) 
{
    uint32 result;

    #if (CY_PSOC3)
        /* to make upper bits fo result to 0 */
        result = (int8) (0xff & ADC_DEC_SAMPH_REG); 
        result = (result << 8) | ADC_DEC_SAMPM_REG;
        result = (result << 8) | ADC_DEC_SAMP_REG;
    #else
        result = CY_GET_REG16(ADC_DEC_SAMPH_PTR);
        result = (result << 16) | (CY_GET_REG16(ADC_DEC_SAMP_PTR));
    #endif /* CY_PSOC3 */
    
    return result;
}


/*******************************************************************************
* Function Name: ADC_SetOffset
********************************************************************************
*
* Summary:
*  This function sets the offset for voltage readings.
*
* Parameters:  
*  int32:  offset  Offset in counts
*
* Return: 
*  void
*
* Global variables:
*  ADC_Offset:  Modified to set the user provided offset. This 
*  variable is used for offset calibration purpose.
*  Affects the ADC_CountsTo_Volts, 
*  ADC_CountsTo_mVolts, ADC_CountsTo_uVolts functions 
*  by subtracting the given offset. 
*
*******************************************************************************/
void ADC_SetOffset(int32 offset) 
{
 
    ADC_Offset = offset;
}


/*******************************************************************************
* Function Name: ADC_SetGain
********************************************************************************
*
* Summary:
*  This function sets the ADC gain in counts per volt.
*
* Parameters:  
*  int32:  offset  Offset in counts
*
* Return: 
*  void 
*
* Global variables:
*  ADC_CountsPerVolt:  modified to set the ADC gain in counts 
*   per volt.
*
*******************************************************************************/
void ADC_SetGain(int32 adcGain) 
{
 
    ADC_CountsPerVolt = adcGain;
}


/*******************************************************************************
* Function Name: ADC_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to mVolts.
*
* Parameters:  
*  int32:  adcCounts   Reading from ADC.
*
* Return: 
*  int32:  Result in mVolts
*
* Global variables:
*  ADC_CountsPerVolt:  used to convert ADC counts to mVolts.
*  ADC_Offset:  Used as the offset while converting ADC counts 
*   to mVolts.
*
*******************************************************************************/
int16 ADC_CountsTo_mVolts( int32 adcCounts) 
{

    int32 mVolts = 0;
    int32 A, B;
	uint8 resolution = 16;

    /* Subtract ADC offset */
    adcCounts -= ADC_Offset;
	
	/* Set the resolution based on the configuration */
	if (ADC_Config == ADC_CFG1)
	{
        resolution = ADC_CFG1_RESOLUTION;
	}	
	else if (ADC_Config == ADC_CFG2)
	{
	    resolution = ADC_CFG2_RESOLUTION;
	}
	else if (ADC_Config == ADC_CFG3)
	{
	    resolution = ADC_CFG3_RESOLUTION;
	}
	else
	{
	    resolution = ADC_CFG4_RESOLUTION;
	}
	
    if(resolution < 17)
    {
        A = 1000;
        B = 1;
    }
    else
    {
        A = 100;
        B = 10;
    }

    mVolts = ((A * adcCounts) / ((int32)ADC_CountsPerVolt/B)) ;   

    return( (int16)mVolts );
}


/*******************************************************************************
* Function Name: ADC_CountsTo_Volts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to Volts
*
* Parameters:  
*  int32:  adcCounts   Reading from ADC.
*
* Return: 
*  float:  Result in Volts
*
* Global variables:
*  ADC_CountsPerVolt:  used to convert to Volts.
*  ADC_Offset:  Used as the offset while converting ADC counts 
*   to Volts.
*
*******************************************************************************/
float ADC_CountsTo_Volts( int32 adcCounts) 
{

    float Volts = 0;

    /* Subtract ADC offset */
    adcCounts -= ADC_Offset;

    Volts = (float)adcCounts / (float)ADC_CountsPerVolt;   
    
    return( Volts );
}


/*******************************************************************************
* Function Name: ADC_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  This function converts ADC counts to uVolts
*
* Parameters:  
*  int32:  adcCounts   Reading from ADC.
*
* Return: 
*  int32:  Result in uVolts
*
* Global variables:
*  ADC_CountsPerVolt:  used to convert ADC counts to mVolts.
*  ADC_Offset:  Used as the offset while converting ADC counts 
*   to mVolts.
*
* Theory: 
* Care must be taken to not exceed the maximum value for a 32 bit signed
* number in the conversion to uVolts and at the same time not loose 
* resolution.
*
* uVolts = ((A * adcCounts) / ((int32)ADC_CountsPerVolt/B)) ;   
*
*  Resolution       A           B
*   8 - 11      1,000,000         1
*  12 - 14        100,000        10
*  15 - 17         10,000       100
*  18 - 20           1000      1000
*
*******************************************************************************/
int32 ADC_CountsTo_uVolts( int32 adcCounts) 
{

    int32 uVolts = 0;
    int32 A, B;
	uint8 resolution = 16;
	
	/* Set the resolution based on the configuration */
	if (ADC_Config == ADC_CFG1)
	{
        resolution = ADC_CFG1_RESOLUTION;
	}	
	else if (ADC_Config == ADC_CFG2)
	{
	    resolution = ADC_CFG2_RESOLUTION;
	}
	else if (ADC_Config == ADC_CFG3)
	{
	    resolution = ADC_CFG3_RESOLUTION;
	}
	else
	{
	    resolution = ADC_CFG4_RESOLUTION;
	}
    
    if(resolution < 12)
    {
        A = 1000000;
        B = 1;
    }
    else if(resolution < 15)
    {
        A = 100000;
        B = 10;
    }
    else if(resolution < 18)
    {
        A = 10000;
        B = 100;
    }
    else
    {
        A = 1000;
        B = 1000;
    }

    /* Subtract ADC offset */
    adcCounts -= ADC_Offset;

    uVolts = ((A * adcCounts) / ((int32)ADC_CountsPerVolt/B)) ;   
  
    return( uVolts );
}


/*******************************************************************************
* Function Name: ADC_IRQ_Start(void)
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. The IRQ_Start() API is included to 
*  support legacy code. The routine has been replaced by the library source 
*  code for interrupts. IRQ_Start() should not be used in new designs.
* 
* Parameters:  
*   void.
*
* Return:
*   void.
*
*******************************************************************************/
void ADC_IRQ_Start(void) 
{
    /* For all we know the interrupt is active. */
    CyIntDisable(ADC_IRQ__INTC_NUMBER );

    /* Set the ISR to point to the ADC_DelSig_1_IRQ Interrupt. */
    CyIntSetVector(ADC_IRQ__INTC_NUMBER, ADC_ISR1);

    /* Set the priority. */
    CyIntSetPriority(ADC_IRQ__INTC_NUMBER, ADC_IRQ_INTC_PRIOR_NUMBER);

    /* Enable interrupt. */
    CyIntEnable(ADC_IRQ__INTC_NUMBER);
}


/*******************************************************************************
* Function Name: ADC_InitConfig(uint8 config)
********************************************************************************
*
* Summary:
*  Initializes all registers based on customizer settings
*
* Parameters:  
*   void
*
* Return: 
*  void
*
* Global variables:
*  ADC_initVar:  used to set the common registers in the beginning.
*  ADC_CountsPerVolt:  Used to set the default counts per volt.
*
*******************************************************************************/
void ADC_InitConfig(uint8 config) 
{
    ADC_stopConversion = 0u;
    
    if(ADC_initVar == 0u)
        {
            ADC_DSM_DEM0_REG    = ADC_CFG1_DSM_DEM0;    
            ADC_DSM_DEM1_REG    = ADC_CFG1_DSM_DEM1;    
            ADC_DSM_MISC_REG    = ADC_CFG1_DSM_MISC;    
            ADC_DSM_CLK_REG    |= ADC_CFG1_DSM_CLK; 
            ADC_DSM_REF1_REG    = ADC_CFG1_DSM_REF1;    
        
            ADC_DSM_OUT0_REG    = ADC_CFG1_DSM_OUT0;    
            ADC_DSM_OUT1_REG    = ADC_CFG1_DSM_OUT1;   
        
            ADC_DSM_CR0_REG     = ADC_CFG1_DSM_CR0;     
            ADC_DSM_CR1_REG     = ADC_CFG1_DSM_CR1;     
            ADC_DSM_CR2_REG     = ADC_CFG1_DSM_CR2;     
            ADC_DSM_CR3_REG     = ADC_CFG1_DSM_CR3;     
            ADC_DSM_CR13_REG    = ADC_CFG1_DSM_CR13;     
            
            ADC_DEC_SR_REG      = ADC_CFG1_DEC_SR;      
            ADC_DEC_COHER_REG   = ADC_CFG1_DEC_COHER;   
        }

    if (config == 1u)
    {
        /* Default Config */   
        ADC_DEC_CR_REG      = ADC_CFG1_DEC_CR;      
        ADC_DEC_SHIFT1_REG  = ADC_CFG1_DEC_SHIFT1;  
        ADC_DEC_SHIFT2_REG  = ADC_CFG1_DEC_SHIFT2;  
        ADC_DEC_DR2_REG     = ADC_CFG1_DEC_DR2;     
        ADC_DEC_DR2H_REG    = ADC_CFG1_DEC_DR2H;    
        ADC_DEC_DR1_REG     = ADC_CFG1_DEC_DR1;     
        ADC_DEC_OCOR_REG    = ADC_CFG1_DEC_OCOR;    
        ADC_DEC_OCORM_REG   = ADC_CFG1_DEC_OCORM;   
        ADC_DEC_OCORH_REG   = ADC_CFG1_DEC_OCORH;   
        
        ADC_DSM_CR4_REG     = ADC_CFG1_DSM_CR4;     
        ADC_DSM_CR5_REG     = ADC_CFG1_DSM_CR5;     
        ADC_DSM_CR6_REG     = ADC_CFG1_DSM_CR6;     
        ADC_DSM_CR7_REG     = ADC_CFG1_DSM_CR7;     
        ADC_DSM_CR8_REG     = ADC_CFG1_DSM_CR8;     
        ADC_DSM_CR9_REG     = ADC_CFG1_DSM_CR9;     
        ADC_DSM_CR10_REG    = ADC_CFG1_DSM_CR10;    
        ADC_DSM_CR11_REG    = ADC_CFG1_DSM_CR11;    
        ADC_DSM_CR12_REG    = ADC_CFG1_DSM_CR12;    
        ADC_DSM_CR14_REG    = ADC_CFG1_DSM_CR14;    
        ADC_DSM_CR15_REG    = ADC_CFG1_DSM_CR15;    
        ADC_DSM_CR16_REG    = ADC_CFG1_DSM_CR16;    
        ADC_DSM_CR17_REG    = ADC_CFG1_DSM_CR17;
		/* Set DSM_REF0_REG by disabling and enabling the PRESS cirucit */
		ADC_SetDSMRef0Reg(ADC_CFG1_DSM_REF0);
        ADC_DSM_REF2_REG    = ADC_CFG1_DSM_REF2;    
        ADC_DSM_REF3_REG    = ADC_CFG1_DSM_REF3;    
        
        ADC_DSM_BUF0_REG    = ADC_CFG1_DSM_BUF0;    
        ADC_DSM_BUF1_REG    = ADC_CFG1_DSM_BUF1;    
        ADC_DSM_BUF2_REG    = ADC_CFG1_DSM_BUF2;   
        ADC_DSM_BUF3_REG    = ADC_CFG1_DSM_BUF3;
        #if (CY_PSOC5A)
            ADC_DSM_CLK_REG    |= ADC_CFG1_DSM_CLK; 
        #endif /* CY_PSOC5A */
        
        /* To select either Vssa or Vref to -ve input of DSM depending on 
          the input  range selected.
        */
        
        #if(ADC_DEFAULT_INPUT_MODE)
            #if (CY_PSOC3 || CY_PSOC5LP)
                #if (ADC_CFG1_RANGE == ADC_IR_VSSA_TO_2VREF)
                    ADC_AMux_Select(1);
                #else
                    ADC_AMux_Select(0);
                #endif /* ADC_IR_VSSA_TO_2VREF) */
            #elif (CY_PSOC5A)
                ADC_AMux_Select(0);
            #endif /* CY_PSOC3 || CY_PSOC5LP */
        #endif /* ADC_DEFAULT_INPUT_MODE */
        
        /* Set the Conversion stop if resolution is above 16 bit and conversion 
           mode is Single sample */
        #if(ADC_CFG1_RESOLUTION > 16 && \
            ADC_CFG1_CONV_MODE == ADC_MODE_SINGLE_SAMPLE) 
            ADC_stopConversion = 1;
        #endif /* Single sample with resolution above 16 bits. */
        ADC_CountsPerVolt = (uint32)ADC_CFG1_COUNTS_PER_VOLT;
        
        /* Start and set interrupt vector */
        CyIntSetPriority(ADC_IRQ__INTC_NUMBER, ADC_IRQ_INTC_PRIOR_NUMBER);
        CyIntSetVector(ADC_IRQ__INTC_NUMBER, ADC_ISR1 );
        CyIntEnable(ADC_IRQ__INTC_NUMBER);
    }
    
    #if(ADC_DEFAULT_NUM_CONFIGS > 1)
        if(config == 2u)
        {
            /* Second Config */
            ADC_DEC_CR_REG      = ADC_CFG2_DEC_CR;      
            ADC_DEC_SHIFT1_REG  = ADC_CFG2_DEC_SHIFT1;  
            ADC_DEC_SHIFT2_REG  = ADC_CFG2_DEC_SHIFT2;  
            ADC_DEC_DR2_REG     = ADC_CFG2_DEC_DR2;     
            ADC_DEC_DR2H_REG    = ADC_CFG2_DEC_DR2H;    
            ADC_DEC_DR1_REG     = ADC_CFG2_DEC_DR1;     
            ADC_DEC_OCOR_REG    = ADC_CFG2_DEC_OCOR;    
            ADC_DEC_OCORM_REG   = ADC_CFG2_DEC_OCORM;   
            ADC_DEC_OCORH_REG   = ADC_CFG2_DEC_OCORH;   
        
            ADC_DSM_CR4_REG     = ADC_CFG2_DSM_CR4;     
            ADC_DSM_CR5_REG     = ADC_CFG2_DSM_CR5;     
            ADC_DSM_CR6_REG     = ADC_CFG2_DSM_CR6;     
            ADC_DSM_CR7_REG     = ADC_CFG2_DSM_CR7;     
            ADC_DSM_CR8_REG     = ADC_CFG2_DSM_CR8;     
            ADC_DSM_CR9_REG     = ADC_CFG2_DSM_CR9;     
            ADC_DSM_CR10_REG    = ADC_CFG2_DSM_CR10;    
            ADC_DSM_CR11_REG    = ADC_CFG2_DSM_CR11;    
            ADC_DSM_CR12_REG    = ADC_CFG2_DSM_CR12;    
            ADC_DSM_CR14_REG    = ADC_CFG2_DSM_CR14;    
            ADC_DSM_CR15_REG    = ADC_CFG2_DSM_CR15;    
            ADC_DSM_CR16_REG    = ADC_CFG2_DSM_CR16;    
            ADC_DSM_CR17_REG    = ADC_CFG2_DSM_CR17;    
			/* Set DSM_REF0_REG by disabling and enabling the PRESS cirucit */
			ADC_SetDSMRef0Reg(ADC_CFG2_DSM_REF0);
            ADC_DSM_REF2_REG    = ADC_CFG2_DSM_REF2;    
            ADC_DSM_REF3_REG    = ADC_CFG2_DSM_REF3;    
        
            ADC_DSM_BUF0_REG    = ADC_CFG2_DSM_BUF0;    
            ADC_DSM_BUF1_REG    = ADC_CFG2_DSM_BUF1;    
            ADC_DSM_BUF2_REG    = ADC_CFG2_DSM_BUF2;    
            ADC_DSM_BUF3_REG    = ADC_CFG2_DSM_BUF3; 
            #if (CY_PSOC5A)
                ADC_DSM_CLK_REG    |= ADC_CFG1_DSM_CLK; 
            #endif /* CY_PSOC5A */
            
            /* To select either Vssa or Vref to -ve input of DSM depending on 
               the input range selected.
            */
            
            #if(ADC_DEFAULT_INPUT_MODE)
                #if (CY_PSOC3 || CY_PSOC5LP)
                    #if (ADC_CFG2_INPUT_RANGE == ADC_IR_VSSA_TO_2VREF)
                        ADC_AMux_Select(1);
                    #else
                        ADC_AMux_Select(0);
                    #endif /* ADC_IR_VSSA_TO_2VREF) */
                #elif (CY_PSOC5A)
                    ADC_AMux_Select(0);
                #endif /* CY_PSOC3 || CY_PSOC5LP */
            #endif /* ADC_DEFAULT_INPUT_MODE */
            
            /* Set the Conversion stop if resolution is above 16 bit and 
               conversion mode is Single sample */
            #if(ADC_CFG2_RESOLUTION > 16 && \
                ADC_CFG2_CONVMODE == ADC_MODE_SINGLE_SAMPLE) 
                ADC_stopConversion = 1;
            #endif /* Single sample with resolution above 16 bits. */
            
            ADC_CountsPerVolt = (uint32)ADC_CFG2_COUNTS_PER_VOLT;
            
            /* Start and set interrupt vector */
            CyIntSetPriority(ADC_IRQ__INTC_NUMBER, ADC_IRQ_INTC_PRIOR_NUMBER);
            CyIntSetVector(ADC_IRQ__INTC_NUMBER, ADC_ISR2 );
            CyIntEnable(ADC_IRQ__INTC_NUMBER);
        }
    #endif /* ADC_DEFAULT_NUM_CONFIGS > 1 */

    #if(ADC_DEFAULT_NUM_CONFIGS > 2)
        if(config == 3u)
        {
            /* Third Config */
            ADC_DEC_CR_REG      = ADC_CFG3_DEC_CR;      
            ADC_DEC_SHIFT1_REG  = ADC_CFG3_DEC_SHIFT1;  
            ADC_DEC_SHIFT2_REG  = ADC_CFG3_DEC_SHIFT2;  
            ADC_DEC_DR2_REG     = ADC_CFG3_DEC_DR2;     
            ADC_DEC_DR2H_REG    = ADC_CFG3_DEC_DR2H;    
            ADC_DEC_DR1_REG     = ADC_CFG3_DEC_DR1;     
            ADC_DEC_OCOR_REG    = ADC_CFG3_DEC_OCOR;    
            ADC_DEC_OCORM_REG   = ADC_CFG3_DEC_OCORM;   
            ADC_DEC_OCORH_REG   = ADC_CFG3_DEC_OCORH;   
         
            ADC_DSM_CR4_REG     = ADC_CFG3_DSM_CR4;     
            ADC_DSM_CR5_REG     = ADC_CFG3_DSM_CR5;     
            ADC_DSM_CR6_REG     = ADC_CFG3_DSM_CR6;     
            ADC_DSM_CR7_REG     = ADC_CFG3_DSM_CR7;     
            ADC_DSM_CR8_REG     = ADC_CFG3_DSM_CR8;     
            ADC_DSM_CR9_REG     = ADC_CFG3_DSM_CR9;     
            ADC_DSM_CR10_REG    = ADC_CFG3_DSM_CR10;    
            ADC_DSM_CR11_REG    = ADC_CFG3_DSM_CR11;    
            ADC_DSM_CR12_REG    = ADC_CFG3_DSM_CR12;    
            ADC_DSM_CR14_REG    = ADC_CFG3_DSM_CR14;    
            ADC_DSM_CR15_REG    = ADC_CFG3_DSM_CR15;    
            ADC_DSM_CR16_REG    = ADC_CFG3_DSM_CR16;    
            ADC_DSM_CR17_REG    = ADC_CFG3_DSM_CR17;    
			/* Set DSM_REF0_REG by disabling and enabling the PRESS cirucit */
			ADC_SetDSMRef0Reg(ADC_CFG3_DSM_REF0);
            ADC_DSM_REF2_REG    = ADC_CFG3_DSM_REF2;    
            ADC_DSM_REF3_REG    = ADC_CFG3_DSM_REF3;    
        
            ADC_DSM_BUF0_REG    = ADC_CFG3_DSM_BUF0;    
            ADC_DSM_BUF1_REG    = ADC_CFG3_DSM_BUF1;    
            ADC_DSM_BUF2_REG    = ADC_CFG3_DSM_BUF2;
            ADC_DSM_BUF3_REG    = ADC_CFG3_DSM_BUF3;
            #if (CY_PSOC5A)
                ADC_DSM_CLK_REG    |= ADC_CFG1_DSM_CLK; 
            #endif /* CY_PSOC5A */
            
            /* To select either Vssa or Vref to -ve input of DSM depending on 
               the input range selected.
            */
            
            #if(ADC_DEFAULT_INPUT_MODE)
                #if (CY_PSOC3 || CY_PSOC5LP)
                    #if (ADC_CFG3_INPUT_RANGE == ADC_IR_VSSA_TO_2VREF)
                        ADC_AMux_Select(1);
                    #else
                        ADC_AMux_Select(0);
                    #endif /* ADC_IR_VSSA_TO_2VREF) */
                #elif (CY_PSOC5A)
                    ADC_AMux_Select(0);
                #endif /* CY_PSOC3 || CY_PSOC5LP */
            #endif /* ADC_DEFAULT_INPUT_MODE */
                       
            /* Set the Conversion stop if resolution is above 16 bit and 
               conversion  mode is Single sample */
            #if(ADC_CFG3_RESOLUTION > 16 && \
                ADC_CFG3_CONVMODE == ADC_MODE_SINGLE_SAMPLE) 
                ADC_stopConversion = 1;
            #endif /* Single sample with resolution above 16 bits */
            
            ADC_CountsPerVolt = (uint32)ADC_CFG3_COUNTS_PER_VOLT;
            
            /* Start and set interrupt vector */
            CyIntSetPriority(ADC_IRQ__INTC_NUMBER, ADC_IRQ_INTC_PRIOR_NUMBER);
            CyIntSetVector(ADC_IRQ__INTC_NUMBER, ADC_ISR3 );
            CyIntEnable(ADC_IRQ__INTC_NUMBER);
        }
    #endif /* ADC_DEFAULT_NUM_CONFIGS > 3 */

    #if(ADC_DEFAULT_NUM_CONFIGS == 4)
        if (config == 4u)
        {
            /* Fourth Config */
            ADC_DEC_CR_REG      = ADC_CFG4_DEC_CR;      
            ADC_DEC_SHIFT1_REG  = ADC_CFG4_DEC_SHIFT1;  
            ADC_DEC_SHIFT2_REG  = ADC_CFG4_DEC_SHIFT2;  
            ADC_DEC_DR2_REG     = ADC_CFG4_DEC_DR2;     
            ADC_DEC_DR2H_REG    = ADC_CFG4_DEC_DR2H;    
            ADC_DEC_DR1_REG     = ADC_CFG4_DEC_DR1;     
            ADC_DEC_OCOR_REG    = ADC_CFG4_DEC_OCOR;    
            ADC_DEC_OCORM_REG   = ADC_CFG4_DEC_OCORM;   
            ADC_DEC_OCORH_REG   = ADC_CFG4_DEC_OCORH;   

            ADC_DSM_CR4_REG     = ADC_CFG4_DSM_CR4;     
            ADC_DSM_CR5_REG     = ADC_CFG4_DSM_CR5;     
            ADC_DSM_CR6_REG     = ADC_CFG4_DSM_CR6;     
            ADC_DSM_CR7_REG     = ADC_CFG4_DSM_CR7;     
            ADC_DSM_CR8_REG     = ADC_CFG4_DSM_CR8;     
            ADC_DSM_CR9_REG     = ADC_CFG4_DSM_CR9;     
            ADC_DSM_CR10_REG    = ADC_CFG4_DSM_CR10;    
            ADC_DSM_CR11_REG    = ADC_CFG4_DSM_CR11;    
            ADC_DSM_CR12_REG    = ADC_CFG4_DSM_CR12;    
            ADC_DSM_CR14_REG    = ADC_CFG4_DSM_CR14;    
            ADC_DSM_CR15_REG    = ADC_CFG4_DSM_CR15;    
            ADC_DSM_CR16_REG    = ADC_CFG4_DSM_CR16;    
            ADC_DSM_CR17_REG    = ADC_CFG4_DSM_CR17;
			/* Set DSM_REF0_REG by disabling and enabling the PRESS cirucit */
			ADC_SetDSMRef0Reg(ADC_CFG4_DSM_REF0);
            ADC_DSM_REF2_REG    = ADC_CFG4_DSM_REF2;    
            ADC_DSM_REF3_REG    = ADC_CFG4_DSM_REF3;    
        
            ADC_DSM_BUF0_REG    = ADC_CFG4_DSM_BUF0;    
            ADC_DSM_BUF1_REG    = ADC_CFG4_DSM_BUF1;    
            ADC_DSM_BUF2_REG    = ADC_CFG4_DSM_BUF2;
            ADC_DSM_BUF3_REG    = ADC_CFG4_DSM_BUF3;
            #if (CY_PSOC5A)
                ADC_DSM_CLK_REG    |= ADC_CFG1_DSM_CLK; 
            #endif /* CY_PSOC5A */
            
            /* To select either Vssa or Vref to -ve input of DSM depending on 
               the input range selected.
            */
            
            #if(ADC_DEFAULT_INPUT_MODE)
                #if (CY_PSOC3 || CY_PSOC5LP)
                    #if (ADC_CFG4_INPUT_RANGE == ADC_IR_VSSA_TO_2VREF)
                        ADC_AMux_Select(1);
                    #else
                        ADC_AMux_Select(0);
                    #endif /* ADC_IR_VSSA_TO_2VREF) */
                #elif (CY_PSOC5A)
                    ADC_AMux_Select(0);
                #endif /* CY_PSOC3 || CY_PSOC5LP */
            #endif /* ADC_DEFAULT_INPUT_MODE */
                       
            /* Set the Conversion stop if resolution is above 16 bit and 
               conversion mode is Single sample */
            #if(ADC_CFG4_RESOLUTION > 16 && \
                ADC_CFG4_CONVMODE == ADC_MODE_SINGLE_SAMPLE) 
                ADC_stopConversion = 1;
            #endif /* Single sample with resolution above 16 bits */
            
            ADC_CountsPerVolt = (uint32)ADC_CFG4_COUNTS_PER_VOLT;

            /* Start and set interrupt vector */
            CyIntSetPriority(ADC_IRQ__INTC_NUMBER, ADC_IRQ_INTC_PRIOR_NUMBER);
            CyIntSetVector(ADC_IRQ__INTC_NUMBER, ADC_ISR4 );
            CyIntEnable(ADC_IRQ__INTC_NUMBER);
        }
    #endif /* ADC_DEFAULT_NUM_CONFIGS > 4 */
}


/*******************************************************************************
* Function Name: ADC_RoundValue(uint32 busClockFreq, 
*                                            uint32 clockFreq)
********************************************************************************
*
* Summary:
*  Function to round an integer value.
*
* Parameters:  
*  busClockFreq:  Frequency of the bus clock.
*  clockFreq:  Frequency of the component clock.
*
* Return: 
*  uint16: rounded integer value.
*
*******************************************************************************/
uint16 ADC_RoundValue(uint32 busClockFreq, uint32 clockFreq) \
                                  
{
    uint16 divider1, divider2;
    
    divider1 = ((busClockFreq * 10) / clockFreq);
    divider2 = (busClockFreq / clockFreq);
    if ( divider1 - (divider2 * 10) >= 5)
    {
        divider2 += 1;
    }
    return divider2;
}
         

/*******************************************************************************
* Function Name: ADC_SelectCofiguration(uint8 config, 
*                                                    uint8 restart)
********************************************************************************
*
* Summary:
*  Selects the user defined configuration. This API first stops the current ADC
*  and then initializes the registers with the default values for that config. 
*  This also performs calibration by writing GCOR registers with trim values 
*  stored in the flash.
*
* Parameters:  
*  config:  configuration user wants to select.
*
* Return: 
*  void
*
*******************************************************************************/
void ADC_SelectConfiguration(uint8 config, uint8 restart) \
                                              
{
    uint8 inputRange = 0, resolution = 16;
    uint16 idealGain = 0, adcClockDivider = 1;    
    uint16 cpClockDivider = 1;
    uint16 idealOddGain = 0;
    
    /* Check whether the config is valid or not */
    if( config <= ADC_DEFAULT_NUM_CONFIGS)
    {   
       /* Set the flag to ensure start() API dont override the config
           selected if ADC is not already started */
        if(ADC_initVar == 0u)
        {
            ADC_started = 1u;
        }
		
		/* Update the config flag */
		ADC_Config = config;
       
        /* Stop the ADC  */
        ADC_Stop();
        
        #if (CY_PSOC5A)
            /* Set the structure field which checks whether or not to
               restore the power registers */
            ADC_powerModeBackup.bypassRestore = ADC_BYPASS_ENABLED;
        #endif /* CY_PSOC5A */
        
        /* Set the  ADC registers based on the configuration */
        ADC_InitConfig(config);
        
        /* Trim value calculation */
        if(config == 1u)
        {
            inputRange = ADC_CFG1_RANGE;
            resolution = ADC_CFG1_RESOLUTION;
            idealGain = ADC_CFG1_IDEAL_DEC_GAIN;
            idealOddGain = ADC_CFG1_IDEAL_ODDDEC_GAIN;
            adcClockDivider = ADC_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                       (uint32)ADC_CFG1_CLOCK_FREQ);
            cpClockDivider = ADC_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                       (uint32)ADC_CFG1_CP_CLOCK_FREQ);
        }

        #if (ADC_DEFAULT_NUM_CONFIGS > 1)
            if(config == 2u)
            {
                inputRange = ADC_CFG2_INPUT_RANGE;
                resolution = ADC_CFG2_RESOLUTION;
                idealGain = ADC_CFG2_IDEAL_DEC_GAIN;
                idealOddGain = ADC_CFG2_IDEAL_ODDDEC_GAIN;
                adcClockDivider = ADC_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                            (uint32)ADC_CFG2_CLOCK_FREQ);
                cpClockDivider = ADC_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                       (uint32)ADC_CFG2_CP_CLOCK_FREQ);
            }
        #endif /* ADC_DEFAULT_NUM_CONFIGS > 1 */

        #if(ADC_DEFAULT_NUM_CONFIGS > 2)
            if(config == 3u)
            {
                inputRange = ADC_CFG3_INPUT_RANGE;
                resolution = ADC_CFG3_RESOLUTION;
                idealGain = ADC_CFG3_IDEAL_DEC_GAIN;
                idealOddGain = ADC_CFG3_IDEAL_ODDDEC_GAIN;
                adcClockDivider = ADC_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                            (uint32)ADC_CFG3_CLOCK_FREQ);
                cpClockDivider = ADC_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                       (uint32)ADC_CFG3_CP_CLOCK_FREQ);
            }
        #endif /* ADC_DEFAULT_NUM_CONFIGS > 2 */

        #if (ADC_DEFAULT_NUM_CONFIGS > 3)
            if(config == 4u)
            {
                inputRange = ADC_CFG4_INPUT_RANGE;
                resolution = ADC_CFG4_RESOLUTION;
                idealGain = ADC_CFG4_IDEAL_DEC_GAIN;
                idealOddGain = ADC_CFG4_IDEAL_ODDDEC_GAIN;
                adcClockDivider = ADC_RoundValue((uint32)BCLK__BUS_CLK__HZ,  
                                                            (uint32)ADC_CFG4_CLOCK_FREQ);
                cpClockDivider = ADC_RoundValue((uint32)BCLK__BUS_CLK__HZ,
                                                       (uint32)ADC_CFG4_CP_CLOCK_FREQ);
            }
        #endif /* ADC_DEFAULT_NUM_CONFIGS > 3 */
        
        adcClockDivider = adcClockDivider - 1;
        /* Set the proper divider for the internal clock */
        #if(ADC_DEFAULT_INTERNAL_CLK)
            ADC_theACLK_SetDividerRegister(adcClockDivider, 1);
        #endif /* ADC_DEFAULT_INTERNAL_CLK */
        
        cpClockDivider = cpClockDivider - 1;
        /* Set the proper divider for the Charge pump clock */
        ADC_Ext_CP_Clk_SetDividerRegister(cpClockDivider, 1);
        
        /* Compensate the gain */
        ADC_GainCompensation(inputRange, idealGain, idealOddGain, resolution);
        
        if(restart == 1u)
        {        
            /* Restart the ADC */
            ADC_Start();
            
            /* Code to disable the REFBUF0 if reference chosen is External ref */
            #if (((ADC_CFG2_REFERENCE == ADC_EXT_REF_ON_P03) || \
                 (ADC_CFG2_REFERENCE == ADC_EXT_REF_ON_P32)) || \
                 ((ADC_CFG3_REFERENCE == ADC_EXT_REF_ON_P03) || \
                 (ADC_CFG3_REFERENCE == ADC_EXT_REF_ON_P32)) || \
                 ((ADC_CFG4_REFERENCE == ADC_EXT_REF_ON_P03) || \
                 (ADC_CFG4_REFERENCE == ADC_EXT_REF_ON_P32)))
                if (((config == 2) && 
                    ((ADC_CFG2_REFERENCE == ADC_EXT_REF_ON_P03) ||
                    (ADC_CFG2_REFERENCE == ADC_EXT_REF_ON_P32))) ||
                    ((config == 3) && 
                    ((ADC_CFG3_REFERENCE == ADC_EXT_REF_ON_P03) ||
                    (ADC_CFG3_REFERENCE == ADC_EXT_REF_ON_P32))) ||
                    ((config == 4) && 
                    ((ADC_CFG4_REFERENCE == ADC_EXT_REF_ON_P03) ||
                    (ADC_CFG4_REFERENCE == ADC_EXT_REF_ON_P32))))
                {
                    /* Disable PRES, Enable power to VCMBUF0, REFBUF0 and 
                       REFBUF1, enable PRES */
                    #if (CY_PSOC3 || CY_PSOC5LP)
                        ADC_RESET_CR4_REG |= ADC_IGNORE_PRESA1;
                        ADC_RESET_CR5_REG |= ADC_IGNORE_PRESA2;
                    #elif (CY_PSOC5A)
                        ADC_RESET_CR1_REG |= ADC_DIS_PRES1;
                        ADC_RESET_CR3_REG |= ADC_DIS_PRES2;
                    #endif /* CY_PSOC5A */
        
                    /* Disable the REFBUF0 */
                    ADC_DSM_CR17_REG &= ~ADC_DSM_EN_BUF_VREF;
                    
                    /* Wait for 3 microseconds */
                    CyDelayUs(3);
                    /* Enable the press circuit */
                    #if (CY_PSOC3 || CY_PSOC5LP)
                        ADC_RESET_CR4_REG &= ~ADC_IGNORE_PRESA1;
                        ADC_RESET_CR5_REG &= ~ADC_IGNORE_PRESA2;
                    #elif (CY_PSOC5A)
                        ADC_RESET_CR1_REG &= ~ADC_DIS_PRES1;
                        ADC_RESET_CR3_REG &= ~ADC_DIS_PRES2;
                    #endif /* CY_PSOC5A */
                }
            #endif /* */
            
            #if ((CY_PSOC3 || CY_PSOC5LP) && \
                 ((ADC_CFG2_INPUT_RANGE == ADC_IR_VSSA_TO_2VREF) || \
                  (ADC_CFG3_INPUT_RANGE == ADC_IR_VSSA_TO_2VREF) || \
                  (ADC_CFG4_INPUT_RANGE == ADC_IR_VSSA_TO_2VREF)))
                if(((config == 2) && 
                    (ADC_CFG2_INPUT_RANGE == ADC_IR_VSSA_TO_2VREF) && 
                    ((ADC_CFG2_REFERENCE != ADC_EXT_REF_ON_P03) && 
                     (ADC_CFG2_REFERENCE != ADC_EXT_REF_ON_P32))) ||
                     ((config == 3) && 
                      (ADC_CFG3_INPUT_RANGE == ADC_IR_VSSA_TO_2VREF) && 
                     ((ADC_CFG3_REFERENCE != ADC_EXT_REF_ON_P03) && 
                     (ADC_CFG3_REFERENCE != ADC_EXT_REF_ON_P32))) ||
                     ((config == 4) && 
                      (ADC_CFG4_INPUT_RANGE == ADC_IR_VSSA_TO_2VREF) && 
                     ((ADC_CFG4_REFERENCE != ADC_EXT_REF_ON_P03) && 
                     (ADC_CFG4_REFERENCE != ADC_EXT_REF_ON_P32))))
                {
                    /* Disable PRES, Enable power to VCMBUF0, REFBUF0 and 
                       REFBUF1, enable PRES */
                    #if (CY_PSOC3 || CY_PSOC5LP)
                        ADC_RESET_CR4_REG |= ADC_IGNORE_PRESA1;
                        ADC_RESET_CR5_REG |= ADC_IGNORE_PRESA2;
                    #elif (CY_PSOC5A)
                        ADC_RESET_CR1_REG |= ADC_DIS_PRES1;
                        ADC_RESET_CR3_REG |= ADC_DIS_PRES2;
                    #endif /* CY_PSOC5A */
        
                    /* Enable the REFBUF1 */
                    ADC_DSM_REF0_REG |= ADC_DSM_EN_BUF_VREF_INN;
                    
                    /* Wait for 3 microseconds */
                    CyDelayUs(3);
                    /* Enable the press circuit */
                    #if (CY_PSOC3 || CY_PSOC5LP)
                        ADC_RESET_CR4_REG &= ~ADC_IGNORE_PRESA1;
                        ADC_RESET_CR5_REG &= ~ADC_IGNORE_PRESA2;
                    #elif (CY_PSOC5A)
                        ADC_RESET_CR1_REG &= ~ADC_DIS_PRES1;
                        ADC_RESET_CR3_REG &= ~ADC_DIS_PRES2;
                    #endif /* CY_PSOC5A */
                }
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
            /* Restart the ADC conversion */
            ADC_StartConvert();
        }
    }
}     


/*******************************************************************************
* Function Name: ADC_GainCompensation(uint8, uint16, uint16, uint8)
********************************************************************************
*
* Summary:
*  This API calculates the trim value and then loads this to GCOR register.
*
* Parameters:  
*  inputRange:  input range for which trim value is to be calculated.
*  IdealDecGain:  Ideal Decimator gain for the selected resolution and 
*                 conversion  mode.
*  IdealOddDecGain:  Ideal odd decimation gain for the selected resolution and 
                     conversion mode.
*  resolution:  Resolution to select the proper flash location for trim value.
*
* Return: 
*  void
*
*******************************************************************************/
void ADC_GainCompensation(uint8 inputRange, uint16 IdealDecGain, uint16 IdealOddDecGain,  \
                                       uint8 resolution) 
{
    int8 flash;
    int16 Normalised;
    uint16 GcorValue;
    uint32 GcorTmp;
    
    switch(inputRange)
    {         
        case ADC_IR_VNEG_VREF_DIFF:
        
        /* Normalize the flash Value */
        if(resolution > 15)
        {
            flash = ADC_DEC_TRIM_VREF_DIFF_16_20; 
        }    
        else
        {
            flash = ADC_DEC_TRIM_VREF_DIFF_8_15;
        }        
        break;
        
        case ADC_IR_VNEG_VREF_2_DIFF:
        
        /* Normalize the flash Value */
        if(resolution > 15)
        {
            flash = ADC_DEC_TRIM_VREF_2_DIFF_16_20;
        }    
        else
        {
            flash = ADC_DEC_TRIM_VREF_2_DIFF_8_15;
        }    
        break;
        
        case ADC_IR_VNEG_VREF_4_DIFF:
        
        /* Normalize the flash Value */
        if(resolution > 15)
        {
            flash = ADC_DEC_TRIM_VREF_4_DIFF_16_20;
        }    
        else
        {
            flash = ADC_DEC_TRIM_VREF_4_DIFF_8_15;
        }    
        break;
        
        case ADC_IR_VNEG_VREF_16_DIFF:
        
        /* Normalize the flash Value */
        if(resolution > 15)
        {
            flash = ADC_DEC_TRIM_VREF_16_DIFF_16_20;
        }    
        else
        {
            flash = ADC_DEC_TRIM_VREF_16_DIFF_8_15;
        }    
        break;
        
        default:
            flash = 0;
        break;
    }    
    if(inputRange == ADC_IR_VSSA_TO_VREF || inputRange == ADC_IR_VSSA_TO_2VREF || 
       inputRange == ADC_IR_VSSA_TO_VDDA || inputRange == ADC_IR_VSSA_TO_6VREF || 
       inputRange == ADC_IR_VNEG_2VREF_DIFF || inputRange == ADC_IR_VNEG_6VREF_DIFF ||
       inputRange == ADC_IR_VNEG_VREF_8_DIFF)
    {
        Normalised  = 0;
    }
    else
    {
        Normalised  = ((int16)flash) * 32;
    }
                    
    /* Add two values */
    GcorValue = IdealDecGain + Normalised;  
    GcorTmp = (uint32)GcorValue * (uint32)IdealOddDecGain;
    GcorValue = (uint16)(GcorTmp / ADC_IDEAL_GAIN_CONST);
        
    if (resolution < 14)
    {
        GcorValue = (GcorValue >> (15 - (resolution + 1)));
        ADC_DEC_GVAL_REG = (resolution + 1);
    }
    else
    {
        /* Use all 16 bits */
        ADC_DEC_GVAL_REG = 15u;  
    }
      
    /* Load the gain correction register */    
    ADC_DEC_GCOR_REG  = (uint8)GcorValue;
    ADC_DEC_GCORH_REG = (uint8)(GcorValue >> 8);    
    
    /* Workaround for 0 to 2*Vref mode with PSoC5A siliocn */
    #if( CY_PSOC5A) 
        if( inputRange == ADC_IR_VSSA_TO_2VREF)
        {
            ADC_DEC_GCOR_REG = 0x00u;
            ADC_DEC_GCORH_REG = 0x00u;
            ADC_DEC_GVAL_REG = 0x00u;
        }
    #endif /* CY_PSOC5A */
}


/******************************************************************************
* Function Name: ADC_SetDSMRef0Reg(uint8)
******************************************************************************
*
* Summary:
*  This API sets the DSM_REF0 register. This is written for internal use.
*
* Parameters:  
*  value:  Value to be written to DSM_REF0 register.
*
* Return: 
*  void
*
******************************************************************************/
void ADC_SetDSMRef0Reg(uint8 value) 
{
    /* Disable PRES, Enable power to VCMBUF0, REFBUF0 and REFBUF1, enable 
       PRES */
    #if (CY_PSOC3 || CY_PSOC5LP)
        ADC_RESET_CR4_REG |= (ADC_IGNORE_PRESA1 | ADC_IGNORE_PRESD1);
        ADC_RESET_CR5_REG |= (ADC_IGNORE_PRESA2 | ADC_IGNORE_PRESD2);
    #elif (CY_PSOC5A)
        ADC_RESET_CR1_REG |= ADC_DIS_PRES1;
        ADC_RESET_CR3_REG |= ADC_DIS_PRES2;
    #endif /* CY_PSOC5A */
        ADC_DSM_REF0_REG = value;   
		
	/* Wait for 3 microseconds */
    CyDelayUs(3);
    /* Enable the press circuit */
    #if (CY_PSOC3 || CY_PSOC5LP)
        ADC_RESET_CR4_REG &= ~(ADC_IGNORE_PRESA1 | ADC_IGNORE_PRESD1);
        ADC_RESET_CR5_REG &= ~(ADC_IGNORE_PRESA2 | ADC_IGNORE_PRESD2);
    #elif (CY_PSOC5A)
        ADC_RESET_CR1_REG &= ~ADC_DIS_PRES1;
        ADC_RESET_CR3_REG &= ~ADC_DIS_PRES2;
    #endif /* CY_PSOC5A */
}


/* [] END OF FILE */
