/*******************************************************************************
* File Name: LEDR.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LEDR_H) /* Pins LEDR_H */
#define CY_PINS_LEDR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LEDR_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LEDR_Write(uint8 value) ;
void    LEDR_SetDriveMode(uint8 mode) ;
uint8   LEDR_ReadDataReg(void) ;
uint8   LEDR_Read(void) ;
uint8   LEDR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LEDR_DRIVE_MODE_BITS        (3)
#define LEDR_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LEDR_DRIVE_MODE_BITS))

#define LEDR_DM_ALG_HIZ         (0x00u)
#define LEDR_DM_DIG_HIZ         (0x01u)
#define LEDR_DM_RES_UP          (0x02u)
#define LEDR_DM_RES_DWN         (0x03u)
#define LEDR_DM_OD_LO           (0x04u)
#define LEDR_DM_OD_HI           (0x05u)
#define LEDR_DM_STRONG          (0x06u)
#define LEDR_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define LEDR_MASK               LEDR__MASK
#define LEDR_SHIFT              LEDR__SHIFT
#define LEDR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDR_PS                     (* (reg32 *) LEDR__PS)
/* Port Configuration */
#define LEDR_PC                     (* (reg32 *) LEDR__PC)
/* Data Register */
#define LEDR_DR                     (* (reg32 *) LEDR__DR)
/* Input Buffer Disable Override */
#define LEDR_INP_DIS                (* (reg32 *) LEDR__PC2)


#if defined(LEDR__INTSTAT)  /* Interrupt Registers */

    #define LEDR_INTSTAT                (* (reg32 *) LEDR__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define LEDR_DRIVE_MODE_SHIFT       (0x00u)
#define LEDR_DRIVE_MODE_MASK        (0x07u << LEDR_DRIVE_MODE_SHIFT)


#endif /* End Pins LEDR_H */


/* [] END OF FILE */
