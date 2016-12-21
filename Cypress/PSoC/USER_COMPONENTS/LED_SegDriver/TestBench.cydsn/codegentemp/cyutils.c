/*******************************************************************************
* FILENAME: cyutils.c
* Version 2.40
*  
*  Description:
*   CyUtils provides functions to handles endian issues for 16 and 32-bit 
*   registers.
* 
*  Note:
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <cytypes.h>

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
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
#endif
