/*******************************************************************************
* File Name: LED_3.h  
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

#if !defined(CY_PINS_LED_3_H) /* Pins LED_3_H */
#define CY_PINS_LED_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_3_Write(uint8 value) ;
void    LED_3_SetDriveMode(uint8 mode) ;
uint8   LED_3_ReadDataReg(void) ;
uint8   LED_3_Read(void) ;
uint8   LED_3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_3_DRIVE_MODE_BITS        (3)
#define LED_3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_3_DRIVE_MODE_BITS))
#define LED_3_DRIVE_MODE_SHIFT       (0x00u)
#define LED_3_DRIVE_MODE_MASK        (0x07u << LED_3_DRIVE_MODE_SHIFT)

#define LED_3_DM_ALG_HIZ         (0x00u << LED_3_DRIVE_MODE_SHIFT)
#define LED_3_DM_DIG_HIZ         (0x01u << LED_3_DRIVE_MODE_SHIFT)
#define LED_3_DM_RES_UP          (0x02u << LED_3_DRIVE_MODE_SHIFT)
#define LED_3_DM_RES_DWN         (0x03u << LED_3_DRIVE_MODE_SHIFT)
#define LED_3_DM_OD_LO           (0x04u << LED_3_DRIVE_MODE_SHIFT)
#define LED_3_DM_OD_HI           (0x05u << LED_3_DRIVE_MODE_SHIFT)
#define LED_3_DM_STRONG          (0x06u << LED_3_DRIVE_MODE_SHIFT)
#define LED_3_DM_RES_UPDWN       (0x07u << LED_3_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define LED_3_MASK               LED_3__MASK
#define LED_3_SHIFT              LED_3__SHIFT
#define LED_3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_3_PS                     (* (reg32 *) LED_3__PS)
/* Port Configuration */
#define LED_3_PC                     (* (reg32 *) LED_3__PC)
/* Data Register */
#define LED_3_DR                     (* (reg32 *) LED_3__DR)
/* Input Buffer Disable Override */
#define LED_3_INP_DIS                (* (reg32 *) LED_3__PC2)


#if defined(LED_3__INTSTAT)  /* Interrupt Registers */

    #define LED_3_INTSTAT                (* (reg32 *) LED_3__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins LED_3_H */


/* [] END OF FILE */
