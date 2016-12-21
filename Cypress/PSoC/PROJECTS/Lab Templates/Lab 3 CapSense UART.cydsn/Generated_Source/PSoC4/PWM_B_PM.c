/*******************************************************************************
* File Name: PWM_B_PM.c
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

#include "PWM_B.h"

static PWM_B_BACKUP_STRUCT PWM_B_backup;


/*******************************************************************************
* Function Name: PWM_B_SaveConfig
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
void PWM_B_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_B_Sleep
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
void PWM_B_Sleep(void)
{
    if(0u != (PWM_B_BLOCK_CONTROL_REG & PWM_B_MASK))
    {
        PWM_B_backup.enableState = 1u;
    }
    else
    {
        PWM_B_backup.enableState = 0u;
    }

    PWM_B_Stop();
    PWM_B_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_B_RestoreConfig
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
void PWM_B_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_B_Wakeup
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
void PWM_B_Wakeup(void)
{
    PWM_B_RestoreConfig();

    if(0u != PWM_B_backup.enableState)
    {
        PWM_B_Enable();
    }
}


/* [] END OF FILE */
