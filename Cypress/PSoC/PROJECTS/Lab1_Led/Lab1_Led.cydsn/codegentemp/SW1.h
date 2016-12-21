/*******************************************************************************
* File Name: SW1.h  
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

#if !defined(CY_PINS_SW1_H) /* Pins SW1_H */
#define CY_PINS_SW1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SW1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SW1_Write(uint8 value) ;
void    SW1_SetDriveMode(uint8 mode) ;
uint8   SW1_ReadDataReg(void) ;
uint8   SW1_Read(void) ;
uint8   SW1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SW1_DRIVE_MODE_BITS        (3)
#define SW1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SW1_DRIVE_MODE_BITS))
#define SW1_DRIVE_MODE_SHIFT       (0x00u)
#define SW1_DRIVE_MODE_MASK        (0x07u << SW1_DRIVE_MODE_SHIFT)

#define SW1_DM_ALG_HIZ         (0x00u << SW1_DRIVE_MODE_SHIFT)
#define SW1_DM_DIG_HIZ         (0x01u << SW1_DRIVE_MODE_SHIFT)
#define SW1_DM_RES_UP          (0x02u << SW1_DRIVE_MODE_SHIFT)
#define SW1_DM_RES_DWN         (0x03u << SW1_DRIVE_MODE_SHIFT)
#define SW1_DM_OD_LO           (0x04u << SW1_DRIVE_MODE_SHIFT)
#define SW1_DM_OD_HI           (0x05u << SW1_DRIVE_MODE_SHIFT)
#define SW1_DM_STRONG          (0x06u << SW1_DRIVE_MODE_SHIFT)
#define SW1_DM_RES_UPDWN       (0x07u << SW1_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define SW1_MASK               SW1__MASK
#define SW1_SHIFT              SW1__SHIFT
#define SW1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SW1_PS                     (* (reg32 *) SW1__PS)
/* Port Configuration */
#define SW1_PC                     (* (reg32 *) SW1__PC)
/* Data Register */
#define SW1_DR                     (* (reg32 *) SW1__DR)
/* Input Buffer Disable Override */
#define SW1_INP_DIS                (* (reg32 *) SW1__PC2)


#if defined(SW1__INTSTAT)  /* Interrupt Registers */

    #define SW1_INTSTAT                (* (reg32 *) SW1__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins SW1_H */


/* [] END OF FILE */
