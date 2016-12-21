/*******************************************************************************
* File Name: PWM_R_PM.c
* Version 1.0
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_R.h"

static PWM_R_BACKUP_STRUCT PWM_R_backup;


/*******************************************************************************
* Function Name: PWM_R_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_R_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_R_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_R_Sleep(void)
{
    if(0u != (PWM_R_BLOCK_CONTROL_REG & PWM_R_MASK))
    {
        PWM_R_backup.enableState = 1u;
    }
    else
    {
        PWM_R_backup.enableState = 0u;
    }

    PWM_R_Stop();
    PWM_R_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_R_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_R_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_R_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_R_Wakeup(void)
{
    PWM_R_RestoreConfig();

    if(0u != PWM_R_backup.enableState)
    {
        PWM_R_Enable();
    }
}


/* [] END OF FILE */
