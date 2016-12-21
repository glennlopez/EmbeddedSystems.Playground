/*******************************************************************************
* File Name: ADC_PM.c  
* Version 2.30
*
* Description:
*  This file provides the power manager source code to the API for the 
*  Delta-Sigma ADC Component.
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

static ADC_BACKUP_STRUCT ADC_backup = 
{
    ADC_DISABLED,
    ADC_CFG1_DEC_CR
};


/*******************************************************************************  
* Function Name: ADC_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
* Global variables:
*  ADC_backup:  This global structure variable is used to store 
*  configuration registers which are non retention whenever user wants to go 
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void ADC_SaveConfig(void) 
{
    ADC_backup.deccr = ADC_DEC_CR_REG;
}


/*******************************************************************************  
* Function Name: ADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
* Global variables:
*  ADC_backup:  This global structure variable is used to restore 
*  configuration registers which are non retention whenever user wants to switch 
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void ADC_RestoreConfig(void) 
{
    ADC_DEC_CR_REG = ADC_backup.deccr;
}


/******************************************************************************* 
* Function Name: ADC_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration. 
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ADC_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ADC_Sleep(void) 
{
    /* Save ADC enable state */
    if((ADC_ACT_PWR_DEC_EN == (ADC_PWRMGR_DEC_REG & ADC_ACT_PWR_DEC_EN)) &&
       (ADC_ACT_PWR_DSM_EN == (ADC_PWRMGR_DSM_REG & ADC_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        ADC_backup.enableState = ADC_ENABLED;
    }
    else
    {
        /* Component is disabled */
        ADC_backup.enableState = ADC_DISABLED;
    }

    /* Stop the configuration */
    ADC_Stop();

    /* Save the user configuration */
    ADC_SaveConfig();
}


/******************************************************************************* 
* Function Name: ADC_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ADC_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ADC_Wakeup(void) 
{
    /* Restore the configuration */
    ADC_RestoreConfig();

    /* Enable's the component operation */
    if(ADC_backup.enableState == ADC_ENABLED)
    {
        ADC_Enable();

        /* Start the conversion only if conversion is not triggered by the hardware */
        if(!(ADC_DEC_CR_REG & ADC_DEC_XSTART_EN))
        {
            ADC_StartConvert();
        }

    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
