/*******************************************************************************
* FILENAME: cyutils.c
* Version 3.20
*
*  Description:
*   CyUtils provides function to handle 24-bit value writes.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"

#if defined(__GNUC__) || defined(__ARMCC_VERSION)

    /***************************************************************************
    * Function Name: CySetReg24
    ****************************************************************************
    *
    * Summary:
    *  Writes the 24-bit value to the specified register.
    *
    * Parameters:
    *  addr : adress where data must be written
    *  value: data that must be written
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    ***************************************************************************/
    void CySetReg24(uint8 volatile *addr, uint32 value)
    {
        *addr = (uint8)value;
        addr++;
        value >>= 8;
        *addr = (uint8)value;
        addr++;
        value >>= 8;
        *addr = (uint8)value;
    }

#endif  /* defined(__GNUC__) || defined(__ARMCC_VERSION) */


/* [] END OF FILE */
