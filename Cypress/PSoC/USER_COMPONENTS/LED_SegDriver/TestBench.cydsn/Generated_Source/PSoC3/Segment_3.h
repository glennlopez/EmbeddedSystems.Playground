/*******************************************************************************
* File Name: Segment_3.h  
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

#if !defined(CY_PINS_Segment_3_H) /* Pins Segment_3_H */
#define CY_PINS_Segment_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Segment_3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Segment_3_Write(uint8 value) ;
void    Segment_3_SetDriveMode(uint8 mode) ;
uint8   Segment_3_ReadDataReg(void) ;
uint8   Segment_3_Read(void) ;
uint8   Segment_3_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Segment_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Segment_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Segment_3_DM_RES_UP          PIN_DM_RES_UP
#define Segment_3_DM_RES_DWN         PIN_DM_RES_DWN
#define Segment_3_DM_OD_LO           PIN_DM_OD_LO
#define Segment_3_DM_OD_HI           PIN_DM_OD_HI
#define Segment_3_DM_STRONG          PIN_DM_STRONG
#define Segment_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Segment_3_MASK               Segment_3__MASK
#define Segment_3_SHIFT              Segment_3__SHIFT
#define Segment_3_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Segment_3_PS                     (* (reg8 *) Segment_3__PS)
/* Data Register */
#define Segment_3_DR                     (* (reg8 *) Segment_3__DR)
/* Port Number */
#define Segment_3_PRT_NUM                (* (reg8 *) Segment_3__PRT) 
/* Connect to Analog Globals */                                                  
#define Segment_3_AG                     (* (reg8 *) Segment_3__AG)                       
/* Analog MUX bux enable */
#define Segment_3_AMUX                   (* (reg8 *) Segment_3__AMUX) 
/* Bidirectional Enable */                                                        
#define Segment_3_BIE                    (* (reg8 *) Segment_3__BIE)
/* Bit-mask for Aliased Register Access */
#define Segment_3_BIT_MASK               (* (reg8 *) Segment_3__BIT_MASK)
/* Bypass Enable */
#define Segment_3_BYP                    (* (reg8 *) Segment_3__BYP)
/* Port wide control signals */                                                   
#define Segment_3_CTL                    (* (reg8 *) Segment_3__CTL)
/* Drive Modes */
#define Segment_3_DM0                    (* (reg8 *) Segment_3__DM0) 
#define Segment_3_DM1                    (* (reg8 *) Segment_3__DM1)
#define Segment_3_DM2                    (* (reg8 *) Segment_3__DM2) 
/* Input Buffer Disable Override */
#define Segment_3_INP_DIS                (* (reg8 *) Segment_3__INP_DIS)
/* LCD Common or Segment Drive */
#define Segment_3_LCD_COM_SEG            (* (reg8 *) Segment_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Segment_3_LCD_EN                 (* (reg8 *) Segment_3__LCD_EN)
/* Slew Rate Control */
#define Segment_3_SLW                    (* (reg8 *) Segment_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Segment_3_PRTDSI__CAPS_SEL       (* (reg8 *) Segment_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Segment_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Segment_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Segment_3_PRTDSI__OE_SEL0        (* (reg8 *) Segment_3__PRTDSI__OE_SEL0) 
#define Segment_3_PRTDSI__OE_SEL1        (* (reg8 *) Segment_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Segment_3_PRTDSI__OUT_SEL0       (* (reg8 *) Segment_3__PRTDSI__OUT_SEL0) 
#define Segment_3_PRTDSI__OUT_SEL1       (* (reg8 *) Segment_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Segment_3_PRTDSI__SYNC_OUT       (* (reg8 *) Segment_3__PRTDSI__SYNC_OUT) 


#if defined(Segment_3__INTSTAT)  /* Interrupt Registers */

    #define Segment_3_INTSTAT                (* (reg8 *) Segment_3__INTSTAT)
    #define Segment_3_SNAP                   (* (reg8 *) Segment_3__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Segment_3_H */


/* [] END OF FILE */
