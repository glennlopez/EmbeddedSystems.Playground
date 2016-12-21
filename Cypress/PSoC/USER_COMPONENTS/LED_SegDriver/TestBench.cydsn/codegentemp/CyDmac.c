/*******************************************************************************
* File Name: CyDmac.c  
* Version 2.40
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*   This API is the library version not the auto generated code that gets
*   generated when the user places a DMA component on the schematic.
*   The auto generated code would use the APi's in this module.
*
*  Note:
*   This code is endian agnostic.
*
*   The Transfer Descriptor memory can be used as regular memory if the TD's
*   are not being used.
*
*   This code uses the first byte of each TD to manage
*   the free list of TD's. The user can over write this once the TD is
*   allocated.
*
*  Note: 
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
* 
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <CYDMAC.H>

/* Current Number of free elements in the list. */
static uint8 CyDmaTdCurrentNumber;

/* Index of the first available TD. */
static uint8 CyDmaTdFreeIndex;

/* Bit map of DMA channel ownership. */
static uint32 CyDmaChannels = DMA_CHANNELS_USED__MASK0;

/*Pointer type conversions are restricted to avoid conflicts with compiler 
optimizations. */
typedef union { volatile uint8 bytes[2]; uint16 word; } CONVERT_WORD;

/*******************************************************************************
* Function Name: CyDmacConfigure
********************************************************************************
* Summary:
*   Sets the DMAC Configuration register with the default values.
*   Initializes the linked list of Transfer Descriptors.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void CyDmacConfigure(void)
{
    uint8 index;


    /* Set TD list variables. */
    CyDmaTdFreeIndex = NUMBEROF_TDS - 1;
    CyDmaTdCurrentNumber = NUMBEROF_TDS;

    /* Make TD free list. */
    for(index = NUMBEROF_TDS - 1; index; index--)
    {
        DMAC_TDMEM[index].TD0[0] = index - 1;
    }

    /* Make the last one point to zero. */
    DMAC_TDMEM[index].TD0[0] = 0;
}


/*******************************************************************************
* Function Name: CyDmacError
********************************************************************************
* Summary:
* Gets the error bits from the DMAC.
*
* Parameters:
*   void.
*
*
*
* Return:
*   Returns the 4 bits of error data from the DMAC error register.
*
*   should each bit get described here?
*
*
*******************************************************************************/
uint8 CyDmacError(void) 
{
    return (0x0Fu & *DMAC_ERR);
}


/*******************************************************************************
* Function Name: CyDmacClearError
********************************************************************************
* Summary:
*   Clears the error bits in the error register of the DMAC..
*
* Parameters:
* error:
*   Clears the error bits in the DMAC error register.
*
*
*
* Return:
*   void.
*
* Theory:
*   Once an error occurs the error bits are sticky and are only cleared
*   by a write to the error register.
*
*******************************************************************************/
void CyDmacClearError(uint8 error) 
{
    *DMAC_ERR = 0x0Fu & error;
}


/*******************************************************************************
* Function Name: CyDmacErrorAddress
********************************************************************************
* Summary:
*   when an BUS_TIMEOUT, UNPOP_ACC and PERIPH_ERR occurs the address
*   of the error is written to the error address register and
*   can be read with this function.
*
*   If there are multiple errors, only the address of the first is
*   saved.
*
* Parameters:
*   void.
*
*
*
* Return:
*   The address that caused the error.
*
*
*******************************************************************************/
uint32 CyDmacErrorAddress(void) 
{
    return CY_GET_REG32(DMAC_ERR_ADR);
}


/*******************************************************************************
* Function Name: CyDmaChAlloc
********************************************************************************
* Summary:
*   Allocates a channel of the DMAC to be used by the caller.
*
* Parameters:
*   void.
*
*
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL if there are no channels left. 
*
*
*******************************************************************************/
uint8 CyDmaChAlloc(void) 
{
    uint8 interruptState;
    uint8 index;
    uint32 channel;


    /* Enter critical section! */
    interruptState = CyEnterCriticalSection();

    /* Look for a free channel. */
    for(index = 0, channel = 1; index < NUMBEROF_CHANNELS; index++, channel <<= 1)
    {
        if(!(CyDmaChannels & channel))
        {
            /* Mark the channel as used. */
            CyDmaChannels |= channel;
            break;
        }
    }

    if(index >= NUMBEROF_CHANNELS)
    {
        index = DMA_INVALID_CHANNEL;    
    }

    /* Exit critical section! */
    CyExitCriticalSection(interruptState);

    return index;
}


/*******************************************************************************
* Function Name: CyDmaChFree
********************************************************************************
* Summary:
* Frees a channel allocated by DmaChAlloc.
*
* Parameters:
* chHandle:
*   Handle to the DMA channel previously allocated by a call to DmaChAlloc.
*
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaChFree(uint8 chHandle) 
{
    cystatus status;


    if(chHandle < NUMBEROF_CHANNELS)
    {
        /* Enter critical section! */
        uint8 interruptState = CyEnterCriticalSection();

        /* Clear the bit mask that keeps track of ownership. */
        CyDmaChannels &= ~(1 << chHandle);

        /* Exit critical section! */
        CyExitCriticalSection(interruptState);
        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaChEnable
********************************************************************************
* Summary:
* Enables the DMA channel for execution depending on how it was configured.
*
* Parameters:
* chHandle:
*   Handle to the dma channel to be enabled.
*
* preserveTds;
*   0 if elements of TD should reflect current state of TD execuction.
*   1 if the DMA controller should not change values of the TD.
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaChEnable(uint8 chHandle, uint8 preserveTds) 
{
    cystatus status;


    if(chHandle < NUMBEROF_CHANNELS)
    {
        DMAC_CH[chHandle].basic_cfg[0] = (DMAC_CH[chHandle].basic_cfg[0] &  ~0x20u) | ((preserveTds) ? 0x21u:0x01u);
        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaChDisable
********************************************************************************
* Summary:
*   Disables the DMA channel.
*
* Parameters:
* chHandle:
*   Handle to the dma channel.
*
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
* Theory:
*   Once this function has been called. DmaChStatus can be polled
*   to determine when the Channel has been disabled and determine
*   which TD was being executed.
*
*   If it is currently executing it will
*   allow the current burst to finish naturally.
*
*******************************************************************************/
cystatus CyDmaChDisable(uint8 chHandle) 
{
    cystatus status;


    if(chHandle < NUMBEROF_CHANNELS)
    {
        DMAC_CH[chHandle].basic_cfg[0] &= ~0x21u;
        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}

/*******************************************************************************
* Function Name: CyDmaClearPendingDrq
********************************************************************************
* Summary:
*   Clears pending DMA data request.
*
* Parameters:
* chHandle:
*   Handle to the dma channel.
*
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*******************************************************************************/
cystatus CyDmaClearPendingDrq(uint8 chHandle) 
{
	cystatus status;
	
	if(chHandle < NUMBEROF_CHANNELS)
	{
		DMAC_CH[chHandle].action[0] |= CPU_TERM_CHAIN;
		DMAC_CH[chHandle].basic_cfg[0] |= 0x01u;
		status = CYRET_SUCCESS;
	}
	else
	{
		status = CYRET_BAD_PARAM;
	}
	
	return status;
}


/*******************************************************************************
* Function Name: CyDmaChPriority
********************************************************************************
* Summary:
* Sets the priority of a DMA channel.
*
* Parameters:
* chHandle:
*   Handle to the dma channel.
*
* priority:
*   Priority to set the channel to, 0 - 7.
*
*
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaChPriority(uint8 chHandle, uint8 priority) 
{
    uint8 Value;
    cystatus status;


    if(chHandle < NUMBEROF_CHANNELS)
    {
        Value = DMAC_CH[chHandle].basic_cfg[0] & ~(0x0Eu);
        DMAC_CH[chHandle].basic_cfg[0] = Value | ((priority & 0x7u) << 0x01u);
        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaChSetExtendedAddress
********************************************************************************
* Summary:
*   Sets the high 16 bits of the source and destination addresses for
*   the DMA channel (all TD's in the chain).
*
* Parameters:
* chHandle:
*   Handle to the dma channel.
*
* source:
*   The source of the DMA transfer.
*
* destination:
*   The destination of the DMA transfer.
*
*
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaChSetExtendedAddress(uint8 chHandle, uint16 source, uint16 destination) 
{
    cystatus status;

#if CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A
    /* 0x1FFF8000-0x1FFFFFFF needs to use alias at 0x20008000-0x2000FFFF */
    if (source == 0x1FFF)
        source = 0x2000;
    if (destination == 0x1FFF)
        destination = 0x2000;
#endif

    if(chHandle < NUMBEROF_CHANNELS)
    {
        /* Set Source address. */
        CONVERT_WORD *convert = (CONVERT_WORD *)&DMAC_CFGMEM[chHandle].CFG1[0];
        CY_SET_REG16(&convert->word, source);

        /* Set Destination address. */
        CY_SET_REG16((reg16 *) &DMAC_CFGMEM[chHandle].CFG1[2], destination);
        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaChSetTd
********************************************************************************
* Summary:
* Set the initial TD for the channel.
*
* Parameters:
* chHandle:
*   Handle to the dma channel.
*
* startTd:
*   Index of TD to set as the first TD associated with the Channel.
*
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaChSetInitialTd(uint8 chHandle, uint8 startTd) 
{
    cystatus status;


    if(chHandle < NUMBEROF_CHANNELS)
    {
        DMAC_CH[chHandle].basic_status[1] = startTd;
        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaChSetRequest
********************************************************************************
* Summary:
*   Allows the caller to terminate a chain of TD's, terminate one TD or
*   Create a direct request to start the DMA channel.
*
* Parameters:
* chHandle:
*   Handle to the dma channel.
*
* request:
*   3 bit field describing the request.
*
*   CPU_REQ       
*   CPU_TERM_TD   
*   CPU_TERM_CHAIN
*
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaChSetRequest(uint8 chHandle, uint8 request) 
{
    cystatus status;


    if(chHandle < NUMBEROF_CHANNELS)
    {
        DMAC_CH[chHandle].action[0] |= (request & (CPU_REQ | CPU_TERM_TD | CPU_TERM_CHAIN));
        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaChGetRequest
********************************************************************************
* Summary:
*   Allows the caller of DmaChSetRequest to check if the request was
*   satisfied.
*
* Parameters:
* chHandle:
*   Handle to the dma channel.
*
*
*
* Return:
*   The state of the 3 bit field describing the requests previous
*   request. If the bit is cleared the request has be satisfied.
*
*   DMA_INVALID_CHANNEL if the handle is invalid.
*
*
*******************************************************************************/
cystatus CyDmaChGetRequest(uint8 chHandle) 
{
    cystatus status;


    if(chHandle < NUMBEROF_CHANNELS)
    {
        status = DMAC_CH[chHandle].action[0] & (CPU_REQ | CPU_TERM_TD | CPU_TERM_CHAIN);
    }
    else
    {
        status = DMA_INVALID_CHANNEL;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaChStatus
********************************************************************************
* Summary:
*   Determines the status of the current Transfer descriptor.
*
* Parameters:
* chHandle:
*   Handle to the dma channel.
*
* currentTd:
*   Address to store the Index of the current Transfer Descriptor.
*   Can be NULL if the value is not needed.
*
* state:
*   Address to store the State of the Channel.
*   Can be NULL if the value is not needed.
*
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*   
*
* Theory:
*   The caller can check on the activity of the Current TD and the
*   Chain.
*
*******************************************************************************/
cystatus CyDmaChStatus(uint8 chHandle, uint8 * currentTd, uint8 * state) 
{
    cystatus status;


    if(chHandle < NUMBEROF_CHANNELS)
    {
        if(currentTd)
        {
            *currentTd = DMAC_CH[chHandle].basic_status[1] & 0x7Fu;
        }

        if(state)
        {
            *state= DMAC_CH[chHandle].basic_status[0];
        }

        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaChSetConfiguration
********************************************************************************
* Summary:
* Sets Configuration information for the channel.
*
* Parameters:
* chHandle:
*   Handle to the dma channel.
*
* burstCount:
*   Number of bytes in a burst. Valid value 0-127
*
* requestPerBurst:
*   A DMA request is required per burst.
*
* tdDone0:
*   Selects one of the TERMOUT0 interrupt lines to signal completion.
*
* tdDone1:
*   Selects one of the TERMOUT1 interrupt lines to signal complete.
*
*
* tdStop:
*   Selects one of the TERMIN interrupt lines to signal to the DMAC
*   that the TD should terminate.
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaChSetConfiguration(uint8 chHandle, uint8 burstCount, uint8 requestPerBurst, uint8 tdDone0, uint8 tdDone1, uint8 tdStop) 
{
    cystatus status;

    
    if(chHandle < NUMBEROF_CHANNELS)
    {
        DMAC_CFGMEM[chHandle].CFG0[0] = (burstCount & 0x7Fu) | ((requestPerBurst & 0x1u) << 7);
        DMAC_CFGMEM[chHandle].CFG0[1] = ((tdDone1 & 0xFu) << 4) | (tdDone0 & 0xFu);
        DMAC_CFGMEM[chHandle].CFG0[2] = 0x0Fu & tdStop;
        DMAC_CFGMEM[chHandle].CFG0[3] = 0; /* burstcount_remain. */

        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaTdAllocate
********************************************************************************
* Summary:
*   Removes a Transfer Descriptor from the free list for use by the
*   caller.
*   Zero based index of the TD to be used by the caller. Since there are 128 TDs 
*   minus the reserved TDs (0-23), the value returned would range from 24 to 127 
*   not 24 to 128.
*
* Parameters:
*   void.
*
*
* Return:
*   Zero based index of the Transfer Descriptor to be used by the
*   caller. Zero is a valid TD index. DMA_INVALID_TD implies
*   there are no free TD's available.
*
*
*******************************************************************************/
uint8 CyDmaTdAllocate(void) 
{
    uint8 interruptState;
    uint8 Element;


    /* Enter critical section! */
    interruptState = CyEnterCriticalSection();

    if(CyDmaTdCurrentNumber > NUMBEROF_CHANNELS)
    {
        /* Get pointer to the Next available. */
        Element = CyDmaTdFreeIndex;

        /* Decrement the count. */
        CyDmaTdCurrentNumber--;

        /* Update the next available pointer. */
        CyDmaTdFreeIndex = DMAC_TDMEM[Element].TD0[0];
    }
    else
    {
        Element = DMA_INVALID_TD;
    }

    /* Exit critical section! */
    CyExitCriticalSection(interruptState);

    return Element;
}


/*******************************************************************************
* Function Name: CyDmaTdFree
********************************************************************************
* Summary:
*   Returns a Transfer Descriptor back to the free list.
*
* Parameters:
* tdHandle:
*   Zero based index of the Transfer Descriptor to be freed.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void CyDmaTdFree(uint8 tdHandle) 
{
    if(tdHandle < NUMBEROF_TDS)
    {
        /* Enter critical section! */
        uint8 interruptState = CyEnterCriticalSection();

        /* Get pointer to the Next available. */
        DMAC_TDMEM[tdHandle].TD0[0] = CyDmaTdFreeIndex;

        /* Set new Next Available. */
        CyDmaTdFreeIndex = tdHandle;

        /* Keep track of how many left. */
        CyDmaTdCurrentNumber++;

        /* Exit critical section! */
        CyExitCriticalSection(interruptState);
    }
}


/*******************************************************************************
* Function Name: CyDmaTdFreeCount
********************************************************************************
* Summary:
*   Returns the number of free Transfer Descriptors available to be
*   allocated.
*
* Parameters:
*   void.
*
* Return:
*   The number of free Transfer Descriptors.
*
*
*******************************************************************************/
uint8 CyDmaTdFreeCount(void) 
{
    return (CyDmaTdCurrentNumber - NUMBEROF_CHANNELS);
}


/*******************************************************************************
* Function Name: CyDmaTdSetConfiguration
********************************************************************************
* Summary:
* Configures the TD.
*
* Parameters:
* tdHandle:
*   Handle to the TD.
*
* transferCount:
*   Size of the data transfer (in bytes) for this Transfer Descriptor.
*
* nextTd:
*   Zero based index of the next Transfer Descriptor in the TD chain.
*   Zero is a valid pointer to the next TD, DMA_END_CHAIN_TD is end of chain.
*
* configuration:
*   Bit field with the following meaning.   
*   
*   bit 7 swap_en 0
*   bit 6 swap_size
*   bit 5 auto_exec_next
*   bit 4 termin_en
*   bit 3 termout1_en
*   bit 2 termout0_en
*   bit 1 inc_dst_adr
*   bit 0 inc_src_adr
*   
*   As defined in HeaderFile
*   
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaTdSetConfiguration(uint8 tdHandle, uint16 transferCount, uint8 nextTd, uint8 configuration) 
{
    cystatus status;


    if(tdHandle < NUMBEROF_TDS && !(0xF000u & transferCount))
    {
        /* Set 12 bits transfer count. */
        CONVERT_WORD *convert = (CONVERT_WORD *)&DMAC_TDMEM[tdHandle].TD0[0];
        CY_SET_REG16(&convert->word, transferCount);

        /* Set Next TD pointer. */
        DMAC_TDMEM[tdHandle].TD0[2] = nextTd;

        /* Configure the TD */
        DMAC_TDMEM[tdHandle].TD0[3] = configuration;

        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaTdGetConfiguration
********************************************************************************
* Summary:
* Gets the configuration for the Configures.
*
*   if NULL is passed for a pointer parameter, that value will be
*   skipped. The user can requestion only the values they are
*   interested in.
*
* Parameters:
* tdHandle:
*   Handle to the TD.
*
* transferCount:
*   Address to store the Size of the data transfer (in bytes) for
*   this Transfer Descriptor.
*
* nextTd:
*   Address to store the Zero based index of the next Transfer
*   Descriptor in the TD chain.
*
* configurattion:
*   Address to store the Bit field of configuration bits.
*   
*   bit 7 swap_en 0
*   bit 6 swap_size
*   bit 5 auto_exec_next
*   bit 4 termin_en
*   bit 3 termout1_en
*   bit 2 termout0_en
*   bit 1 inc_dst_adr
*   bit 0 inc_src_adr
*   
*   As defined in HeaderFile
*   
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaTdGetConfiguration(uint8 tdHandle, uint16 * transferCount, uint8 * nextTd, uint8 * configuration) 
{
    cystatus status;


    if(tdHandle < NUMBEROF_TDS)
    {
        /* If we have a pointer. */
        if(transferCount)
        {
            /* Get the 12 bitss of the transfer count. */
            CONVERT_WORD *convert = (CONVERT_WORD *)&DMAC_TDMEM[tdHandle].TD0[0];
            *transferCount = 0x0FFFu & CY_GET_REG16(&convert->word);
        }

        /* If we have a pointer. */
        if(nextTd)
        {
            /* Get the Next TD pointer. */
            *nextTd = DMAC_TDMEM[tdHandle].TD0[2];
        }

        /* If we have a pointer. */
        if(configuration)
        {
            /* Get the configuration the TD */
            *configuration = DMAC_TDMEM[tdHandle].TD0[3];
        }

        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaTdSetAddress
********************************************************************************
* Summary:
*   Sets the lower 16 bits of the source and destination addresses
*   for this TD only.
*
* Parameters:
* tdHandle:
*   Handle to the TD.
*
* source:
*   lower 16 address bits of the Source of the data transfer.
*
* destination:
*   lower 16 address bits of the Destination of the data transfer.
*
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaTdSetAddress(uint8 tdHandle, uint16 source, uint16 destination) 
{
    cystatus status;


    if(tdHandle < NUMBEROF_TDS)
    {
        /* Set Source address. */
        CONVERT_WORD *convert = (CONVERT_WORD *)&DMAC_TDMEM[tdHandle].TD1[0];
        CY_SET_REG16(&convert->word, source);

        /* Set Destination address. */
        CY_SET_REG16((reg16 *) &DMAC_TDMEM[tdHandle].TD1[2], destination);

        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}


/*******************************************************************************
* Function Name: CyDmaTdGetAddress
********************************************************************************
* Summary:
*   Gets the lower 16 bits of the source and/or destination addresses
*   for this TD only.
*
*   if NULL is passed for a pointer parameter, that value will be
*   skipped. The user can requestion only the values they are
*   interested in.
*
* Parameters:
* tdHandle:
*   Handle to the TD.
*
* source:
*   Address to store the lower 16 address bits of the Source of the
*   data transfer.
*
* destination:
*   Address to store the lower 16 address bits of the Destination of
*   the data transfer.
*
*
* Return:
*   0 in successful or CYRET_BAD_PARAM.
*
*
*******************************************************************************/
cystatus CyDmaTdGetAddress(uint8 tdHandle, uint16 * source, uint16 * destination) 
{
    cystatus status;


    if(tdHandle < NUMBEROF_TDS)
    {
        /* If we have a pointer. */
        if(source)
        {
            /* Get Source address. */
            CONVERT_WORD *convert = (CONVERT_WORD *)&DMAC_TDMEM[tdHandle].TD1[0];
            *source = CY_GET_REG16(&convert->word);
        }

        /* If we have a pointer. */
        if(destination)
        {
            /* Get Destination address. */
            *destination = CY_GET_REG16((reg16 *) &DMAC_TDMEM[tdHandle].TD1[2]);
        }

        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return status;
}

/*******************************************************************************
* Function Name: CyDmaChRoundRobin
********************************************************************************
* Summary:
*   Either enables or disables the Round-Robin scheduling enforcement algorithm. Within a
priority level a Round-Robin fairness algorithm is enforced.
*
* Parameters:
* chHandle:
*   Handle to the dma channel.
* enableRR:
*   0 Disable Round-Robin fairness algorithm
*   1 Enable Round-Robin fairness algorithm
*
* Return:
*   CYRET_SUCCESS if successful or CYRET_BAD_PARAM if chHandle is invalid.
*
*******************************************************************************/
cystatus CyDmaChRoundRobin(uint8 chHandle, uint8 enableRR)
{
    cystatus status;
	
	if(chHandle < NUMBEROF_CHANNELS)
	{
		DMAC_CH[chHandle].basic_cfg[0] = (DMAC_CH[chHandle].basic_cfg[0] &  ~ROUND_ROBIN_ENABLE) | ((enableRR) ? ROUND_ROBIN_ENABLE:~ROUND_ROBIN_ENABLE);
		status = CYRET_SUCCESS;
	}
	else
	{
		status = CYRET_BAD_PARAM;
	}
	
	return status;
}

/* [] END OF FILE */
