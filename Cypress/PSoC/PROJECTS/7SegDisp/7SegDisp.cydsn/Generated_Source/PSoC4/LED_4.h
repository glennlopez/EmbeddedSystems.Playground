/*******************************************************************************
* File Name: LED_4.h  
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

#if !defined(CY_PINS_LED_4_H) /* Pins LED_4_H */
#define CY_PINS_LED_4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_4_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_4_Write(uint8 value) ;
void    LED_4_SetDriveMode(uint8 mode) ;
uint8   LED_4_ReadDataReg(void) ;
uint8   LED_4_Read(void) ;
uint8   LED_4_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_4_DRIVE_MODE_BITS        (3)
#define LED_4_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_4_DRIVE_MODE_BITS))
#define LED_4_DRIVE_MODE_SHIFT       (0x00u)
#define LED_4_DRIVE_MODE_MASK        (0x07u << LED_4_DRIVE_MODE_SHIFT)

#define LED_4_DM_ALG_HIZ         (0x00u << LED_4_DRIVE_MODE_SHIFT)
#define LED_4_DM_DIG_HIZ         (0x01u << LED_4_DRIVE_MODE_SHIFT)
#define LED_4_DM_RES_UP          (0x02u << LED_4_DRIVE_MODE_SHIFT)
#define LED_4_DM_RES_DWN         (0x03u << LED_4_DRIVE_MODE_SHIFT)
#define LED_4_DM_OD_LO           (0x04u << LED_4_DRIVE_MODE_SHIFT)
#define LED_4_DM_OD_HI           (0x05u << LED_4_DRIVE_MODE_SHIFT)
#define LED_4_DM_STRONG          (0x06u << LED_4_DRIVE_MODE_SHIFT)
#define LED_4_DM_RES_UPDWN       (0x07u << LED_4_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define LED_4_MASK               LED_4__MASK
#define LED_4_SHIFT              LED_4__SHIFT
#define LED_4_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_4_PS                     (* (reg32 *) LED_4__PS)
/* Port Configuration */
#define LED_4_PC                     (* (reg32 *) LED_4__PC)
/* Data Register */
#define LED_4_DR                     (* (reg32 *) LED_4__DR)
/* Input Buffer Disable Override */
#define LED_4_INP_DIS                (* (reg32 *) LED_4__PC2)


#if defined(LED_4__INTSTAT)  /* Interrupt Registers */

    #define LED_4_INTSTAT                (* (reg32 *) LED_4__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins LED_4_H */


/* [] END OF FILE */
