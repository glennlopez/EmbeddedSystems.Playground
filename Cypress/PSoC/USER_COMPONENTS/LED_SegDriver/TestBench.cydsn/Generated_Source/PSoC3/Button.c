/*******************************************************************************
* File Name: Button.c  
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
#include "Button.h"


/*******************************************************************************
* Function Name: Button_Write
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
void Button_Write(uint8 value) 
{
    uint8 staticBits = Button_DR & ~Button_MASK;
    Button_DR = staticBits | ((value << Button_SHIFT) & Button_MASK);
}


/*******************************************************************************
* Function Name: Button_SetDriveMode
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
void Button_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Button_0, mode);
}


/*******************************************************************************
* Function Name: Button_Read
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
*  Macro Button_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Button_Read(void) 
{
    return (Button_PS & Button_MASK) >> Button_SHIFT;
}


/*******************************************************************************
* Function Name: Button_ReadDataReg
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
uint8 Button_ReadDataReg(void) 
{
    return (Button_DR & Button_MASK) >> Button_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Button_INTSTAT) 

    /*******************************************************************************
    * Function Name: Button_ClearInterrupt
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
    uint8 Button_ClearInterrupt(void) 
    {
        return (Button_INTSTAT & Button_MASK) >> Button_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
