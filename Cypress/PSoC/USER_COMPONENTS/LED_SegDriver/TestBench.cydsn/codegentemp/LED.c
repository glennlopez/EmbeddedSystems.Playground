/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "LED.h"

/* variables */

#if LED_Seg7_Support
	/* number 0 - 15 to 7 segment decoder table */
	uint8 LED_seg7_Table[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
	uint8 LED_seg7_Alpha_Table[26] = {0x77,0x7C,0x58,0x5E,0x79,0x71,0x3d,0x74,0x10,0x1e,0x76,0x38,0x55,0x54,0x5c,0x73,0x67,0x50,0x6d,0x78,0x1c,0x1c,0x1d,0x76,0x6e,0x5b};
#endif

/* storage for the display buffer */
uint8 LED_Segment_RAM[8] = {0, 0, 0, 0, 0, 0, 0, 0};

/* data array for the common control register */
uint8 LED_Common_RAM[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

#if LED_PWM_Enable
	/* data array for the PWM */
	uint8 LED_Brightness_RAM[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
#endif

static uint8 LED_Segment_DMA_Chan;
static uint8 LED_Segment_DMA_TD;

static uint8 LED_Common_DMA_Chan;
static uint8 LED_Common_DMA_TD;

#if LED_PWM_Enable
	static uint8 LED_Brightness_DMA_Chan;
	static uint8 LED_Brightness_DMA_TD;
#endif

/* Defines */

/* DMA Configuration for LED_Segment_DMA */
#define LED_Segment_DMA_BYTES_PER_BURST 1
#define LED_Segment_DMA_REQUEST_PER_BURST 1
#define LED_Segment_DMA_SRC_BASE (CYDEV_SRAM_BASE)
#define LED_Segment_DMA_DST_BASE (CYDEV_SRAM_BASE)

/* DMA Configuration for LED_Common_DMA */
#define LED_Common_DMA_BYTES_PER_BURST 1
#define LED_Common_DMA_REQUEST_PER_BURST 1
#define LED_Common_DMA_SRC_BASE (CYDEV_SRAM_BASE)
#define LED_Common_DMA_DST_BASE (CYDEV_SRAM_BASE)

#if LED_PWM_Enable
	/* DMA Configuration for LED_Brightness_DMA */
	#define LED_Brightness_DMA_BYTES_PER_BURST 1
	#define LED_Brightness_DMA_REQUEST_PER_BURST 1
	#define LED_Brightness_DMA_SRC_BASE (CYDEV_SRAM_BASE)
	#define LED_Brightness_DMA_DST_BASE (CYDEV_SRAM_BASE)
#endif

/* allocates Transaction descriptors for the DMA channels, and configures each DMA channel
optionally starts the PWM*/
void LED_Start()
{
	static uint8 LED_InitVar = 0; /* The LED_InitVar ensures that the TDs are only allocated once */
	
	if(LED_InitVar == 0)
	{
		/* allocate TDs */
		LED_Segment_DMA_TD = CyDmaTdAllocate();
		LED_Common_DMA_TD = CyDmaTdAllocate();
		#if LED_PWM_Enable
			LED_Brightness_DMA_TD = CyDmaTdAllocate();
		#endif
		
		LED_InitVar = 1;
	}
	
	#ifndef LED_RAM_1_ctrl_reg__REMOVED /* removes this code if the control register is optimized out, this prevents build errors if nothing is connected to the LED compnent */
		/* Segment DMA configuration
		Set DMA channels Bytes per burst, requests per burst, and upper 16 bits of source and destination */
		LED_Segment_DMA_Chan = LED_Segment_DMA_DmaInitialize(LED_Segment_DMA_BYTES_PER_BURST, LED_Segment_DMA_REQUEST_PER_BURST, HI16(LED_Segment_DMA_SRC_BASE), HI16(LED_Segment_DMA_DST_BASE));
		/* Configure the TD to transfer LED_Num_Commons bytes total, chain to itself, increment source address (read throught the segment ram array) and issue a NRQ on completion */
		CyDmaTdSetConfiguration(LED_Segment_DMA_TD, LED_Num_Commons , LED_Segment_DMA_TD, LED_Segment_DMA__TD_TERMOUT_EN | TD_INC_SRC_ADR);
		/* Configure the TD to grab from the Segment_RAM array and write it into the RAM_1 control register */
		CyDmaTdSetAddress(LED_Segment_DMA_TD, LO16((uint32)&(LED_Segment_RAM[0])), LO16((uint32)&LED_RAM_1_Control));
		/* set the channels initial TD */
		CyDmaChSetInitialTd(LED_Segment_DMA_Chan, LED_Segment_DMA_TD);
		/* clear spurious queued requests */
		CyDmaChSetRequest(LED_Segment_DMA_Chan, CPU_TERM_CHAIN);
		CyDmaChEnable(LED_Segment_DMA_Chan, 1);
		CyDmaChEnable(LED_Segment_DMA_Chan, 1);
	#endif
	
	#ifndef LED_RAM_2_ctrl_reg__REMOVED /* removes this code if the control register is optimized out, this prevents build errors if nothing is connected to the LED compnent */
		/* Common DMA configuration
		Set DMA channels Bytes per burst, requests per burst, and upper 16 bits of source and destination */
		LED_Common_DMA_Chan = LED_Common_DMA_DmaInitialize(LED_Common_DMA_BYTES_PER_BURST, LED_Common_DMA_REQUEST_PER_BURST, HI16(LED_Common_DMA_SRC_BASE), HI16(LED_Common_DMA_DST_BASE));
		/* Configure the TD to transfer LED_Num_Commons bytes total, chain to itself, increment source address (read throught the common ram array) and issue a NRQ on completion */
		CyDmaTdSetConfiguration(LED_Common_DMA_TD, LED_Num_Commons , LED_Common_DMA_TD, LED_Common_DMA__TD_TERMOUT_EN | TD_INC_SRC_ADR);
		/* Configure the TD to grab from the Common_RAM array and write it into the RAM_2 control register */
		CyDmaTdSetAddress(LED_Common_DMA_TD, LO16((uint32)&(LED_Common_RAM[0])), LO16((uint32)&LED_RAM_2_Control));
		/* set the channels initial TD */
		CyDmaChSetInitialTd(LED_Common_DMA_Chan, LED_Common_DMA_TD);
		/* clear spurious queued requests */
		CyDmaChSetRequest(LED_Common_DMA_Chan, CPU_TERM_CHAIN);
		CyDmaChEnable(LED_Common_DMA_Chan, 1);
		CyDmaChEnable(LED_Common_DMA_Chan, 1);
	#endif

	#if LED_PWM_Enable

		/* Brightness DMA configuration
		Set DMA channels Bytes per burst, requests per burst, and upper 16 bits of source and destination */
		LED_Brightness_DMA_Chan = LED_Brightness_DMA_DmaInitialize(LED_Brightness_DMA_BYTES_PER_BURST, LED_Brightness_DMA_REQUEST_PER_BURST, HI16(LED_Brightness_DMA_SRC_BASE), HI16(LED_Brightness_DMA_DST_BASE));
		/* Configure the TD to transfer LED_Num_Commons bytes total, chain to itself, increment source address (read throught the brightness ram array) and issue a NRQ on completion */
		CyDmaTdSetConfiguration(LED_Brightness_DMA_TD, LED_Num_Commons , LED_Brightness_DMA_TD, LED_Brightness_DMA__TD_TERMOUT_EN | TD_INC_SRC_ADR);
		/* Configure the TD to grab from the Brightness_RAM array and write it into the PWM Duty Cycle register */
		CyDmaTdSetAddress(LED_Brightness_DMA_TD, LO16((uint32)&(LED_Brightness_RAM[0])), LO16((uint32)LED_COM_PWM_COMPARE1_LSB_PTR));
		/* set the channels initial TD */
		CyDmaChSetInitialTd(LED_Brightness_DMA_Chan, LED_Brightness_DMA_TD);
		/* clear spurious queued requests */
		CyDmaChSetRequest(LED_Brightness_DMA_Chan, CPU_TERM_CHAIN);
		CyDmaChEnable(LED_Brightness_DMA_Chan, 1);
		CyDmaChEnable(LED_Brightness_DMA_Chan, 1);
		
		LED_COM_PWM_Start();
		
	#endif
}

void LED_Stop()
{
	LED_ClearDisplayAll(); /* clear the display ram to prevent LEDs from being driven while disabled */
	/* disable the DMA channels */
	CyDmaChSetRequest(LED_Segment_DMA_Chan, CPU_TERM_CHAIN);
	CyDmaChSetRequest(LED_Common_DMA_Chan, CPU_TERM_CHAIN);
	
	#if LED_PWM_Enable
		/* disable the PWM */
		LED_COM_PWM_Stop();
		CyDmaChSetRequest(LED_Brightness_DMA_Chan, CPU_TERM_CHAIN);
	#endif
	
	return;
}

/* matrix LED display APIs */

/* set the LED in the corresponding row and column.  Rows are the segments and the columns are the commons.  
Rows greater than 8 will wrap (row % 8) and columns greater than LED_Num_Commons will wrap (col % LED_Num_Commons) */
void LED_SetRC(uint8 row, uint8 col)
{
	LED_Segment_RAM[col % LED_Num_Commons] |= 1 << (row % 8);
	return;
}

/* clear the LED in the corresponding row and column.  Rows are the segments and the columns are the commons.  
Rows greater than 8 will wrap (row % 8) and columns greater than LED_Num_Commons will wrap (col % LED_Num_Commons) */
void LED_ClearRC(uint8 row, uint8 col)
{
	LED_Segment_RAM[col % LED_Num_Commons] &= ~(1 << (row % 8));
	return;
}

/* toggle the LED in the corresponding row and column.  Rows are the segments and the columns are the commons. 
Rows greater than 8 will wrap (row % 8) and columns greater than LED_Num_Commons will wrap (col % LED_Num_Commons) */
void LED_ToggleRC(uint8 row, uint8 col)
{
	LED_Segment_RAM[col % LED_Num_Commons] ^= 1 << (row % 8);
	return;
}

/* returns the state of the LED in the corresponding row and column.  Rows are the segments and the columns are the commons.  
Rows greater than 8 will wrap (row % 8) and columns greater than LED_Num_Commons will wrap (col % LED_Num_Commons) */
uint8 LED_GetRC(uint8 row, uint8 col)
{
	return ((LED_Segment_RAM[col % LED_Num_Commons] & (1 << (row % 8))) >> row % 8) & 0x01;
}

/* write directly to the correspinding display ram.  The display number will wrap at LED_Num_Commons (display % LED_Num_Commons) */
void LED_SetDisplayRAM(uint8 value, uint8 display)
{
	LED_Segment_RAM[display % LED_Num_Commons] = value;
	return;
}

/* Read the correspinding display ram.  The display number will wrap at LED_Num_Commons (display % LED_Num_Commons) */
uint8 LED_GetDisplayRAM(uint8 display)
{
	return LED_Segment_RAM[display % LED_Num_Commons];
}

/* clears the specified display.  if "display" is greater than the number of commons, the number will wrap (display % LED_Num_Commons) */
void LED_ClearDisplay(uint8 display)
{
	LED_Segment_RAM[display % LED_Num_Commons] = 0;
}

/* clears the entire display */
void LED_ClearDisplayAll(void)
{
	uint8 j;
	
	for(j = 0; j < LED_Num_Commons; j++)
	{
		LED_Segment_RAM[j] = 0;
	}
	return;
}

#if LED_Seg7_Support
	
	/* returns the value to be written into the LED_Segment_RAM[] in order to display the particular number */
	uint8 LED_DecodeNumber(uint8 input)
	{
		return LED_seg7_Table[(input & 0x0f)];
	}
	
	/* returns the value to be written into the LED_Segment_RAM[] in order to display the ascii alphabet character */
	uint8 LED_DecodeAlpha(char input)
	{
		return LED_seg7_Alpha_Table[((input >= 97) ? input - 97 : input - 65) % 26];
	}
	
	/* sets or clears the decimal point on "display" based on the value of "value".  If the LSb of value is set, the decimal point will be set
	if the LSb of "value" is clear, the decimal point will be cleared. */
	void LED_PutDecimalPoint(uint8 value, uint8 display)
	{
		LED_Segment_RAM[display % LED_Num_Commons] &= 0x7f; /* clear the DP */
		LED_Segment_RAM[display % LED_Num_Commons] |= ((value << 7) & 0x80); /* set the DP (if requested) */
		return;
	}
	
	/* returns the state of the decimal point for "display".  If the returned value is '1', the decimal point is set.  If the returned value is '0', the decimal point is not set */
	uint8 LED_GetDecimalPoint(uint8 display)
	{
		return (LED_Segment_RAM[display % LED_Num_Commons] >> 7) & 0x01;
	}
	
	/* writes the ascii character "value" to the display "display"  if "display" is greater than the number of commons, the number will wrap (display % LED_Num_Commons) */
	void LED_PutCharacter(char value, uint8 display)
	{
		if(value >= 97 && value <= 122) /* a-z */
		{
			LED_Segment_RAM[display % LED_Num_Commons] = LED_seg7_Alpha_Table[value - 97];
		}
		else if(value >= 65 && value <= 90) /* A-Z */
		{
			LED_Segment_RAM[display % LED_Num_Commons] = LED_seg7_Alpha_Table[value - 65];
		}
		else if(value >= 48 && value <= 57) /* 0-9 */
		{
			LED_Segment_RAM[display % LED_Num_Commons] = LED_seg7_Table[value - 48];
		}
		else if(value == 45) /* - */
		{
			LED_Segment_RAM[display % LED_Num_Commons] = 0x40;
		}
		else if(value == 46) /* . */
		{
			LED_Segment_RAM[display % LED_Num_Commons] = 0x80;
		}
		else if(value == 61) /* = */
		{
			LED_Segment_RAM[display % LED_Num_Commons] = 0x48;
		}
		else if(value == 95) /* _ */
		{
			LED_Segment_RAM[display % LED_Num_Commons] = 0x08;
		}
		else
		{
			LED_Segment_RAM[display % LED_Num_Commons] = 0;
		}
		return;
	}
	
	/* writes a string to the 7 segment display, starting with the the display "display".  if the string extends beyond LED_Num_Commons, then the string will be truncated */
	void LED_PutString(char * string, uint8 display)
	{
		uint8 j;
		
		j = 0;
		while((string[j] != 0) && (j < (LED_Num_Commons - display)))
		{
			LED_PutCharacter(string[j], display + j);
			j++;
		}
		return;
	}
	
	/* draws the specified digit 0-9 onto the the display "display". if "display" is greater than the number of commons, the number will wrap (display % LED_Num_Commons) */
	void LED_SetNumberDec(uint8 value, uint8 display)
	{
		LED_Segment_RAM[display % LED_Num_Commons] = LED_seg7_Table[value % 10];
		return;
	}
	
	/* draws the specified digit 0-F onto the the display "display". if "display" is greater than the number of commons, the number will wrap (display % LED_Num_Commons) */
	void LED_SetNumberHex(uint8 value, uint8 display)
	{
		LED_Segment_RAM[display % LED_Num_Commons] = LED_seg7_Table[value & 0x0f];
		return;
	}
	
	/* displays signed integer values up to 8 characters long */
	void LED_PutNumberInt(int32 value, uint8 display, uint8 digits)
	{
		uint8 j;
		int32 divisors[8] = {1,10,100,1000,10000,100000,1000000,10000000}; 
		int8 max_digits;
		
		if(value < 0) /* determine if the number needs a negative sign */
		{
			LED_PutCharacter( '-', display);
			display++;
			digits--;
			value = -value;
		}
		
		max_digits = (display > 8 ? 8 : digits);
		
		for(j = 0; j < max_digits; j++)
		{
			LED_SetNumberDec((value / divisors[max_digits - j-1]) % 10, display + j);
		}
		return;
	}
	
	/* displays hexadecimal values, up to 8 characters longs */
	void LED_PutNumberHex(uint32 value, uint8 display, uint8 digits)
	{
		uint8 j;
		int8 max_digits;
		
		max_digits = (display > 8 ? 8 : digits);
		
		for(j = 0; j < max_digits; j++)
		{
			LED_SetNumberHex(value >> ((max_digits-1)*4 - (j*4)) & 0x0f, display + j);
		}
		return;
	}
#endif

#if LED_PWM_Enable

	/* write directly to the correspinding brightness ram.  The display number will wrap at LED_Num_Commons (display % LED_Num_Commons) */
	void LED_SetBrightnessRAM(uint8 value, uint8 display)
	{
		LED_Brightness_RAM[display % LED_Num_Commons] = value;
		return;
	}

	/* Read the correspinding brightness ram.  The display number will wrap at LED_Num_Commons (display % LED_Num_Commons) */
	uint8 LED_GetBrightnessRAM(uint8 display)
	{
		return LED_Brightness_RAM[display % LED_Num_Commons];
	}
	
#endif

/* [] END OF FILE */
