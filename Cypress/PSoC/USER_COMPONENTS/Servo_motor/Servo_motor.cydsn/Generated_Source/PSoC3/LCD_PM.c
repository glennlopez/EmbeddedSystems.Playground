/*******************************************************************************
* File Name: LCD_PM.c
* Version 1.60
*
* Description:
*  This file provides the API source code for the Static Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD.h"


void LCD_SaveConfig(void) ;
void LCD_RestoreConfig(void) ;
extern void LCD_Enable(void) ;

static LCD_BACKUP_STRUCT LCD_backup;

extern uint8 LCD_enableState;


/*******************************************************************************
* Function Name: LCD_SaveConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_RestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_Sleep
********************************************************************************
*
* Summary:
*  Prepares component for entering the sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Sleep(void) 
{
    LCD_backup.enableState = LCD_enableState;
    LCD_SaveConfig();
    LCD_Stop();
}


/*******************************************************************************
* Function Name: LCD_Wakeup
********************************************************************************
*
* Summary:
*  Wakes component from sleep mode. Configures DMA and enables the component for
*  normal operation.
*
* Parameters:
*  LCD_enableState - Global variable.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - Function completed successfully.
*       CYRET_LOCKED - The object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Wakeup(void) 
{
    LCD_RestoreConfig();

    if(LCD_backup.enableState == 1u)
    {
        LCD_Enable();
    }
}


/* [] END OF FILE */
