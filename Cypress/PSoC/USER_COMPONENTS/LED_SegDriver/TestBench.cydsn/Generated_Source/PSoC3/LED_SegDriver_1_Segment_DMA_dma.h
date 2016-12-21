/******************************************************************************
* File Name: LED_SegDriver_1_Segment_DMA_dma.h  
* Version 1.50
*
*  Description:
*   Provides the function definitions for the DMA Controller.
*
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#if !defined(__LED_SegDriver_1_Segment_DMA_DMA_H__)
#define __LED_SegDriver_1_Segment_DMA_DMA_H__



#include <CYDMAC.H>
#include <CYFITTER.H>

#define LED_SegDriver_1_Segment_DMA__TD_TERMOUT_EN ((LED_SegDriver_1_Segment_DMA__TERMOUT0_EN ? TD_TERMOUT0_EN : 0) | \
    (LED_SegDriver_1_Segment_DMA__TERMOUT1_EN ? TD_TERMOUT1_EN : 0))

/* Zero based index of LED_SegDriver_1_Segment_DMA dma channel */
extern uint8 LED_SegDriver_1_Segment_DMA_DmaHandle;


uint8 LED_SegDriver_1_Segment_DMA_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress);
void  LED_SegDriver_1_Segment_DMA_DmaRelease(void) ;


/* __LED_SegDriver_1_Segment_DMA_DMA_H__ */
#endif
