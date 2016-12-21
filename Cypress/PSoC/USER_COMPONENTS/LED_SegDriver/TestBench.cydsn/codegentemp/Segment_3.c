/*******************************************************************************
* File Name: Segment_3.c  
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
#include "Segment_3.h"


/*******************************************************************************
* Function Name: Segment_3_Write
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
void Segment_3_Write(uint8 value) 
{
    uint8 staticBits = Segment_3_DR & ~Segment_3_MASK;
    Segment_3_DR = staticBits | ((value << Segment_3_SHIFT) & Segment_3_MASK);
}


/*******************************************************************************
* Function Name: Segment_3_SetDriveMode
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
void Segment_3_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Segment_3_0, mode);
}


/*******************************************************************************
* Function Name: Segment_3_Read
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
*  Macro Segment_3_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Segment_3_Read(void) 
{
    return (Segment_3_PS & Segment_3_MASK) >> Segment_3_SHIFT;
}


/*******************************************************************************
* Function Name: Segment_3_ReadDataReg
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
uint8 Segment_3_ReadDataReg(void) 
{
    return (Segment_3_DR & Segment_3_MASK) >> Segment_3_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Segment_3_INTSTAT) 

    /*******************************************************************************
    * Function Name: Segment_3_ClearInterrupt
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
    uint8 Segment_3_ClearInterrupt(void) 
    {
        return (Segment_3_INTSTAT & Segment_3_MASK) >> Segment_3_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
