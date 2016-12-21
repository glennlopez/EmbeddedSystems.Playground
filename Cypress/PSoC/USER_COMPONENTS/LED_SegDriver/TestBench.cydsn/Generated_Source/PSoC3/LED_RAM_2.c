/*******************************************************************************
* File Name: LED_RAM_2.c  
* Version 1.60
*
* Description:
*  This file contains API to enable firmware control of a control register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "LED_RAM_2.h"

#if !defined(LED_RAM_2_ctrl_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: LED_RAM_2_Write
********************************************************************************
*
* Summary:
*  Write a byte to a control register.
*
* Parameters:  
*  control:  The value to be assigned to the control register. 
*
* Return: 
*  void 
*
* Reentrant:
*  Yes
*  
*******************************************************************************/
void LED_RAM_2_Write(uint8 control) 
{
    LED_RAM_2_Control = control;
}


/*******************************************************************************
* Function Name: LED_RAM_2_Read
********************************************************************************
*
* Summary:
*  Read the current value assigned to a control register.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the control register
*
* Reentrant:
*  Yes
*  
*******************************************************************************/
uint8 LED_RAM_2_Read(void) 
{
    return LED_RAM_2_Control;
}

#endif /* End check for removal by optimization */
