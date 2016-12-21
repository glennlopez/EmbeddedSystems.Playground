/*******************************************************************************
* File Name: PWM_G_PM.c
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

#include "PWM_G.h"

static PWM_G_BACKUP_STRUCT PWM_G_backup;


/*******************************************************************************
* Function Name: PWM_G_SaveConfig
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
void PWM_G_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_G_Sleep
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
void PWM_G_Sleep(void)
{
    if(0u != (PWM_G_BLOCK_CONTROL_REG & PWM_G_MASK))
    {
        PWM_G_backup.enableState = 1u;
    }
    else
    {
        PWM_G_backup.enableState = 0u;
    }

    PWM_G_Stop();
    PWM_G_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_G_RestoreConfig
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
void PWM_G_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_G_Wakeup
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
void PWM_G_Wakeup(void)
{
    PWM_G_RestoreConfig();

    if(0u != PWM_G_backup.enableState)
    {
        PWM_G_Enable();
    }
}


/* [] END OF FILE */
