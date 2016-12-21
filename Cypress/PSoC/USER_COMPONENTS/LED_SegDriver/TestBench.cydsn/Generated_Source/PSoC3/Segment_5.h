/*******************************************************************************
* File Name: Segment_5.h  
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

#if !defined(CY_PINS_Segment_5_H) /* Pins Segment_5_H */
#define CY_PINS_Segment_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Segment_5_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Segment_5_Write(uint8 value) ;
void    Segment_5_SetDriveMode(uint8 mode) ;
uint8   Segment_5_ReadDataReg(void) ;
uint8   Segment_5_Read(void) ;
uint8   Segment_5_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Segment_5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Segment_5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Segment_5_DM_RES_UP          PIN_DM_RES_UP
#define Segment_5_DM_RES_DWN         PIN_DM_RES_DWN
#define Segment_5_DM_OD_LO           PIN_DM_OD_LO
#define Segment_5_DM_OD_HI           PIN_DM_OD_HI
#define Segment_5_DM_STRONG          PIN_DM_STRONG
#define Segment_5_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Segment_5_MASK               Segment_5__MASK
#define Segment_5_SHIFT              Segment_5__SHIFT
#define Segment_5_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Segment_5_PS                     (* (reg8 *) Segment_5__PS)
/* Data Register */
#define Segment_5_DR                     (* (reg8 *) Segment_5__DR)
/* Port Number */
#define Segment_5_PRT_NUM                (* (reg8 *) Segment_5__PRT) 
/* Connect to Analog Globals */                                                  
#define Segment_5_AG                     (* (reg8 *) Segment_5__AG)                       
/* Analog MUX bux enable */
#define Segment_5_AMUX                   (* (reg8 *) Segment_5__AMUX) 
/* Bidirectional Enable */                                                        
#define Segment_5_BIE                    (* (reg8 *) Segment_5__BIE)
/* Bit-mask for Aliased Register Access */
#define Segment_5_BIT_MASK               (* (reg8 *) Segment_5__BIT_MASK)
/* Bypass Enable */
#define Segment_5_BYP                    (* (reg8 *) Segment_5__BYP)
/* Port wide control signals */                                                   
#define Segment_5_CTL                    (* (reg8 *) Segment_5__CTL)
/* Drive Modes */
#define Segment_5_DM0                    (* (reg8 *) Segment_5__DM0) 
#define Segment_5_DM1                    (* (reg8 *) Segment_5__DM1)
#define Segment_5_DM2                    (* (reg8 *) Segment_5__DM2) 
/* Input Buffer Disable Override */
#define Segment_5_INP_DIS                (* (reg8 *) Segment_5__INP_DIS)
/* LCD Common or Segment Drive */
#define Segment_5_LCD_COM_SEG            (* (reg8 *) Segment_5__LCD_COM_SEG)
/* Enable Segment LCD */
#define Segment_5_LCD_EN                 (* (reg8 *) Segment_5__LCD_EN)
/* Slew Rate Control */
#define Segment_5_SLW                    (* (reg8 *) Segment_5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Segment_5_PRTDSI__CAPS_SEL       (* (reg8 *) Segment_5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Segment_5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Segment_5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Segment_5_PRTDSI__OE_SEL0        (* (reg8 *) Segment_5__PRTDSI__OE_SEL0) 
#define Segment_5_PRTDSI__OE_SEL1        (* (reg8 *) Segment_5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Segment_5_PRTDSI__OUT_SEL0       (* (reg8 *) Segment_5__PRTDSI__OUT_SEL0) 
#define Segment_5_PRTDSI__OUT_SEL1       (* (reg8 *) Segment_5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Segment_5_PRTDSI__SYNC_OUT       (* (reg8 *) Segment_5__PRTDSI__SYNC_OUT) 


#if defined(Segment_5__INTSTAT)  /* Interrupt Registers */

    #define Segment_5_INTSTAT                (* (reg8 *) Segment_5__INTSTAT)
    #define Segment_5_SNAP                   (* (reg8 *) Segment_5__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Segment_5_H */


/* [] END OF FILE */
