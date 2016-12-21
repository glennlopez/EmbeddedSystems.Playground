/*******************************************************************************
* File Name: LEDB.h  
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

#if !defined(CY_PINS_LEDB_H) /* Pins LEDB_H */
#define CY_PINS_LEDB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LEDB_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LEDB_Write(uint8 value) ;
void    LEDB_SetDriveMode(uint8 mode) ;
uint8   LEDB_ReadDataReg(void) ;
uint8   LEDB_Read(void) ;
uint8   LEDB_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LEDB_DRIVE_MODE_BITS        (3)
#define LEDB_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LEDB_DRIVE_MODE_BITS))
#define LEDB_DRIVE_MODE_SHIFT       (0x00u)
#define LEDB_DRIVE_MODE_MASK        (0x07u << LEDB_DRIVE_MODE_SHIFT)

#define LEDB_DM_ALG_HIZ         (0x00u << LEDB_DRIVE_MODE_SHIFT)
#define LEDB_DM_DIG_HIZ         (0x01u << LEDB_DRIVE_MODE_SHIFT)
#define LEDB_DM_RES_UP          (0x02u << LEDB_DRIVE_MODE_SHIFT)
#define LEDB_DM_RES_DWN         (0x03u << LEDB_DRIVE_MODE_SHIFT)
#define LEDB_DM_OD_LO           (0x04u << LEDB_DRIVE_MODE_SHIFT)
#define LEDB_DM_OD_HI           (0x05u << LEDB_DRIVE_MODE_SHIFT)
#define LEDB_DM_STRONG          (0x06u << LEDB_DRIVE_MODE_SHIFT)
#define LEDB_DM_RES_UPDWN       (0x07u << LEDB_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define LEDB_MASK               LEDB__MASK
#define LEDB_SHIFT              LEDB__SHIFT
#define LEDB_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDB_PS                     (* (reg32 *) LEDB__PS)
/* Port Configuration */
#define LEDB_PC                     (* (reg32 *) LEDB__PC)
/* Data Register */
#define LEDB_DR                     (* (reg32 *) LEDB__DR)
/* Input Buffer Disable Override */
#define LEDB_INP_DIS                (* (reg32 *) LEDB__PC2)


#if defined(LEDB__INTSTAT)  /* Interrupt Registers */

    #define LEDB_INTSTAT                (* (reg32 *) LEDB__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins LEDB_H */


/* [] END OF FILE */
