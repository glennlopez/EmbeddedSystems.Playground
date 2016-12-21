/*******************************************************************************
* File Name: BStatus.h  
* Version 2.5
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

#if !defined(CY_PINS_BStatus_H) /* Pins BStatus_H */
#define CY_PINS_BStatus_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BStatus_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    BStatus_Write(uint8 value) ;
void    BStatus_SetDriveMode(uint8 mode) ;
uint8   BStatus_ReadDataReg(void) ;
uint8   BStatus_Read(void) ;
uint8   BStatus_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BStatus_DRIVE_MODE_BITS        (3)
#define BStatus_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BStatus_DRIVE_MODE_BITS))
#define BStatus_DRIVE_MODE_SHIFT       (0x00u)
#define BStatus_DRIVE_MODE_MASK        (0x07u << BStatus_DRIVE_MODE_SHIFT)

#define BStatus_DM_ALG_HIZ         (0x00u << BStatus_DRIVE_MODE_SHIFT)
#define BStatus_DM_DIG_HIZ         (0x01u << BStatus_DRIVE_MODE_SHIFT)
#define BStatus_DM_RES_UP          (0x02u << BStatus_DRIVE_MODE_SHIFT)
#define BStatus_DM_RES_DWN         (0x03u << BStatus_DRIVE_MODE_SHIFT)
#define BStatus_DM_OD_LO           (0x04u << BStatus_DRIVE_MODE_SHIFT)
#define BStatus_DM_OD_HI           (0x05u << BStatus_DRIVE_MODE_SHIFT)
#define BStatus_DM_STRONG          (0x06u << BStatus_DRIVE_MODE_SHIFT)
#define BStatus_DM_RES_UPDWN       (0x07u << BStatus_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define BStatus_MASK               BStatus__MASK
#define BStatus_SHIFT              BStatus__SHIFT
#define BStatus_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BStatus_PS                     (* (reg32 *) BStatus__PS)
/* Port Configuration */
#define BStatus_PC                     (* (reg32 *) BStatus__PC)
/* Data Register */
#define BStatus_DR                     (* (reg32 *) BStatus__DR)
/* Input Buffer Disable Override */
#define BStatus_INP_DIS                (* (reg32 *) BStatus__PC2)


#if defined(BStatus__INTSTAT)  /* Interrupt Registers */

    #define BStatus_INTSTAT                (* (reg32 *) BStatus__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins BStatus_H */


/* [] END OF FILE */
