/*******************************************************************************
* File Name: Pin_10.h  
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

#if !defined(CY_PINS_Pin_10_H) /* Pins Pin_10_H */
#define CY_PINS_Pin_10_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_10_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_10_Write(uint8 value) ;
void    Pin_10_SetDriveMode(uint8 mode) ;
uint8   Pin_10_ReadDataReg(void) ;
uint8   Pin_10_Read(void) ;
uint8   Pin_10_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_10_DRIVE_MODE_BITS        (3)
#define Pin_10_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_10_DRIVE_MODE_BITS))
#define Pin_10_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_10_DRIVE_MODE_MASK        (0x07u << Pin_10_DRIVE_MODE_SHIFT)

#define Pin_10_DM_ALG_HIZ         (0x00u << Pin_10_DRIVE_MODE_SHIFT)
#define Pin_10_DM_DIG_HIZ         (0x01u << Pin_10_DRIVE_MODE_SHIFT)
#define Pin_10_DM_RES_UP          (0x02u << Pin_10_DRIVE_MODE_SHIFT)
#define Pin_10_DM_RES_DWN         (0x03u << Pin_10_DRIVE_MODE_SHIFT)
#define Pin_10_DM_OD_LO           (0x04u << Pin_10_DRIVE_MODE_SHIFT)
#define Pin_10_DM_OD_HI           (0x05u << Pin_10_DRIVE_MODE_SHIFT)
#define Pin_10_DM_STRONG          (0x06u << Pin_10_DRIVE_MODE_SHIFT)
#define Pin_10_DM_RES_UPDWN       (0x07u << Pin_10_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Pin_10_MASK               Pin_10__MASK
#define Pin_10_SHIFT              Pin_10__SHIFT
#define Pin_10_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_10_PS                     (* (reg32 *) Pin_10__PS)
/* Port Configuration */
#define Pin_10_PC                     (* (reg32 *) Pin_10__PC)
/* Data Register */
#define Pin_10_DR                     (* (reg32 *) Pin_10__DR)
/* Input Buffer Disable Override */
#define Pin_10_INP_DIS                (* (reg32 *) Pin_10__PC2)


#if defined(Pin_10__INTSTAT)  /* Interrupt Registers */

    #define Pin_10_INTSTAT                (* (reg32 *) Pin_10__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_10_H */


/* [] END OF FILE */
