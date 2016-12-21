/*******************************************************************************
* File Name: Segment_6.h  
* Version 1.60
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_Segment_6_H) /* Pins Segment_6_H */
#define CY_PINS_Segment_6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Segment_6_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Segment_6_Write(uint8 value) ;
void    Segment_6_SetDriveMode(uint8 mode) ;
uint8   Segment_6_ReadDataReg(void) ;
uint8   Segment_6_Read(void) ;
uint8   Segment_6_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Segment_6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Segment_6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Segment_6_DM_RES_UP          PIN_DM_RES_UP
#define Segment_6_DM_RES_DWN         PIN_DM_RES_DWN
#define Segment_6_DM_OD_LO           PIN_DM_OD_LO
#define Segment_6_DM_OD_HI           PIN_DM_OD_HI
#define Segment_6_DM_STRONG          PIN_DM_STRONG
#define Segment_6_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Segment_6_MASK               Segment_6__MASK
#define Segment_6_SHIFT              Segment_6__SHIFT
#define Segment_6_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Segment_6_PS                     (* (reg8 *) Segment_6__PS)
/* Data Register */
#define Segment_6_DR                     (* (reg8 *) Segment_6__DR)
/* Port Number */
#define Segment_6_PRT_NUM                (* (reg8 *) Segment_6__PRT) 
/* Connect to Analog Globals */                                                  
#define Segment_6_AG                     (* (reg8 *) Segment_6__AG)                       
/* Analog MUX bux enable */
#define Segment_6_AMUX                   (* (reg8 *) Segment_6__AMUX) 
/* Bidirectional Enable */                                                        
#define Segment_6_BIE                    (* (reg8 *) Segment_6__BIE)
/* Bit-mask for Aliased Register Access */
#define Segment_6_BIT_MASK               (* (reg8 *) Segment_6__BIT_MASK)
/* Bypass Enable */
#define Segment_6_BYP                    (* (reg8 *) Segment_6__BYP)
/* Port wide control signals */                                                   
#define Segment_6_CTL                    (* (reg8 *) Segment_6__CTL)
/* Drive Modes */
#define Segment_6_DM0                    (* (reg8 *) Segment_6__DM0) 
#define Segment_6_DM1                    (* (reg8 *) Segment_6__DM1)
#define Segment_6_DM2                    (* (reg8 *) Segment_6__DM2) 
/* Input Buffer Disable Override */
#define Segment_6_INP_DIS                (* (reg8 *) Segment_6__INP_DIS)
/* LCD Common or Segment Drive */
#define Segment_6_LCD_COM_SEG            (* (reg8 *) Segment_6__LCD_COM_SEG)
/* Enable Segment LCD */
#define Segment_6_LCD_EN                 (* (reg8 *) Segment_6__LCD_EN)
/* Slew Rate Control */
#define Segment_6_SLW                    (* (reg8 *) Segment_6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Segment_6_PRTDSI__CAPS_SEL       (* (reg8 *) Segment_6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Segment_6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Segment_6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Segment_6_PRTDSI__OE_SEL0        (* (reg8 *) Segment_6__PRTDSI__OE_SEL0) 
#define Segment_6_PRTDSI__OE_SEL1        (* (reg8 *) Segment_6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Segment_6_PRTDSI__OUT_SEL0       (* (reg8 *) Segment_6__PRTDSI__OUT_SEL0) 
#define Segment_6_PRTDSI__OUT_SEL1       (* (reg8 *) Segment_6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Segment_6_PRTDSI__SYNC_OUT       (* (reg8 *) Segment_6__PRTDSI__SYNC_OUT) 


#if defined(Segment_6__INTSTAT)  /* Interrupt Registers */

    #define Segment_6_INTSTAT                (* (reg8 *) Segment_6__INTSTAT)
    #define Segment_6_SNAP                   (* (reg8 *) Segment_6__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Segment_6_H */


/* [] END OF FILE */
