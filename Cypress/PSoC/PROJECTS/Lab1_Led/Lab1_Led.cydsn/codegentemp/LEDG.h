/*******************************************************************************
* File Name: LEDG.h  
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

#if !defined(CY_PINS_LEDG_H) /* Pins LEDG_H */
#define CY_PINS_LEDG_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LEDG_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LEDG_Write(uint8 value) ;
void    LEDG_SetDriveMode(uint8 mode) ;
uint8   LEDG_ReadDataReg(void) ;
uint8   LEDG_Read(void) ;
uint8   LEDG_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LEDG_DRIVE_MODE_BITS        (3)
#define LEDG_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LEDG_DRIVE_MODE_BITS))
#define LEDG_DRIVE_MODE_SHIFT       (0x00u)
#define LEDG_DRIVE_MODE_MASK        (0x07u << LEDG_DRIVE_MODE_SHIFT)

#define LEDG_DM_ALG_HIZ         (0x00u << LEDG_DRIVE_MODE_SHIFT)
#define LEDG_DM_DIG_HIZ         (0x01u << LEDG_DRIVE_MODE_SHIFT)
#define LEDG_DM_RES_UP          (0x02u << LEDG_DRIVE_MODE_SHIFT)
#define LEDG_DM_RES_DWN         (0x03u << LEDG_DRIVE_MODE_SHIFT)
#define LEDG_DM_OD_LO           (0x04u << LEDG_DRIVE_MODE_SHIFT)
#define LEDG_DM_OD_HI           (0x05u << LEDG_DRIVE_MODE_SHIFT)
#define LEDG_DM_STRONG          (0x06u << LEDG_DRIVE_MODE_SHIFT)
#define LEDG_DM_RES_UPDWN       (0x07u << LEDG_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define LEDG_MASK               LEDG__MASK
#define LEDG_SHIFT              LEDG__SHIFT
#define LEDG_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDG_PS                     (* (reg32 *) LEDG__PS)
/* Port Configuration */
#define LEDG_PC                     (* (reg32 *) LEDG__PC)
/* Data Register */
#define LEDG_DR                     (* (reg32 *) LEDG__DR)
/* Input Buffer Disable Override */
#define LEDG_INP_DIS                (* (reg32 *) LEDG__PC2)


#if defined(LEDG__INTSTAT)  /* Interrupt Registers */

    #define LEDG_INTSTAT                (* (reg32 *) LEDG__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins LEDG_H */


/* [] END OF FILE */
