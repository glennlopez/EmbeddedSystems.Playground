/*******************************************************************************
* File Name: Common_3.c  
* Version 1.60
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "Common_3.h"


/*******************************************************************************
* Function Name: Common_3_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void Common_3_Write(uint8 value) 
{
    uint8 staticBits = Common_3_DR & ~Common_3_MASK;
    Common_3_DR = staticBits | ((value << Common_3_SHIFT) & Common_3_MASK);
}


/*******************************************************************************
* Function Name: Common_3_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void Common_3_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Common_3_0, mode);
}


/*******************************************************************************
* Function Name: Common_3_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Common_3_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Common_3_Read(void) 
{
    return (Common_3_PS & Common_3_MASK) >> Common_3_SHIFT;
}


/*******************************************************************************
* Function Name: Common_3_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Common_3_ReadDataReg(void) 
{
    return (Common_3_DR & Common_3_MASK) >> Common_3_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Common_3_INTSTAT) 

    /*******************************************************************************
    * Function Name: Common_3_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Common_3_ClearInterrupt(void) 
    {
        return (Common_3_INTSTAT & Common_3_MASK) >> Common_3_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
