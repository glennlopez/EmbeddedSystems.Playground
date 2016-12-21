/*******************************************************************************
* File Name: Segment_7.c  
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
#include "Segment_7.h"


/*******************************************************************************
* Function Name: Segment_7_Write
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
void Segment_7_Write(uint8 value) 
{
    uint8 staticBits = Segment_7_DR & ~Segment_7_MASK;
    Segment_7_DR = staticBits | ((value << Segment_7_SHIFT) & Segment_7_MASK);
}


/*******************************************************************************
* Function Name: Segment_7_SetDriveMode
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
void Segment_7_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Segment_7_0, mode);
}


/*******************************************************************************
* Function Name: Segment_7_Read
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
*  Macro Segment_7_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Segment_7_Read(void) 
{
    return (Segment_7_PS & Segment_7_MASK) >> Segment_7_SHIFT;
}


/*******************************************************************************
* Function Name: Segment_7_ReadDataReg
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
uint8 Segment_7_ReadDataReg(void) 
{
    return (Segment_7_DR & Segment_7_MASK) >> Segment_7_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Segment_7_INTSTAT) 

    /*******************************************************************************
    * Function Name: Segment_7_ClearInterrupt
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
    uint8 Segment_7_ClearInterrupt(void) 
    {
        return (Segment_7_INTSTAT & Segment_7_MASK) >> Segment_7_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
