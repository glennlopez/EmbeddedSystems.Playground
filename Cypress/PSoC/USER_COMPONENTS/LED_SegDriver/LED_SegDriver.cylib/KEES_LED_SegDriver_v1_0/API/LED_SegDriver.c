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

#include "`$INSTANCE_NAME`.h"

/* variables */

#if `$INSTANCE_NAME`_Seg7_Support
	/* number 0 - 15 to 7 segment decoder table */
	uint8 `$INSTANCE_NAME`_seg7_Table[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
	uint8 `$INSTANCE_NAME`_seg7_Alpha_Table[26] = {0x77,0x7C,0x58,0x5E,0x79,0x71,0x3d,0x74,0x10,0x1e,0x76,0x38,0x55,0x54,0x5c,0x73,0x67,0x50,0x6d,0x78,0x1c,0x1c,0x1d,0x76,0x6e,0x5b};
#endif

/* storage for the display buffer */
uint8 `$INSTANCE_NAME`_Segment_RAM[8] = {0, 0, 0, 0, 0, 0, 0, 0};

/* data array for the common control register */
uint8 `$INSTANCE_NAME`_Common_RAM[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

#if `$INSTANCE_NAME`_PWM_Enable
	/* data array for the PWM */
	uint8 `$INSTANCE_NAME`_Brightness_RAM[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
#endif

static uint8 `$INSTANCE_NAME`_Segment_DMA_Chan;
static uint8 `$INSTANCE_NAME`_Segment_DMA_TD;

static uint8 `$INSTANCE_NAME`_Common_DMA_Chan;
static uint8 `$INSTANCE_NAME`_Common_DMA_TD;

#if `$INSTANCE_NAME`_PWM_Enable
	static uint8 `$INSTANCE_NAME`_Brightness_DMA_Chan;
	static uint8 `$INSTANCE_NAME`_Brightness_DMA_TD;
#endif

/* Defines */

/* DMA Configuration for `$INSTANCE_NAME`_Segment_DMA */
#define `$INSTANCE_NAME`_Segment_DMA_BYTES_PER_BURST 1
#define `$INSTANCE_NAME`_Segment_DMA_REQUEST_PER_BURST 1
#define `$INSTANCE_NAME`_Segment_DMA_SRC_BASE (CYDEV_SRAM_BASE)
#define `$INSTANCE_NAME`_Segment_DMA_DST_BASE (CYDEV_SRAM_BASE)

/* DMA Configuration for `$INSTANCE_NAME`_Common_DMA */
#define `$INSTANCE_NAME`_Common_DMA_BYTES_PER_BURST 1
#define `$INSTANCE_NAME`_Common_DMA_REQUEST_PER_BURST 1
#define `$INSTANCE_NAME`_Common_DMA_SRC_BASE (CYDEV_SRAM_BASE)
#define `$INSTANCE_NAME`_Common_DMA_DST_BASE (CYDEV_SRAM_BASE)

#if `$INSTANCE_NAME`_PWM_Enable
	/* DMA Configuration for `$INSTANCE_NAME`_Brightness_DMA */
	#define `$INSTANCE_NAME`_Brightness_DMA_BYTES_PER_BURST 1
	#define `$INSTANCE_NAME`_Brightness_DMA_REQUEST_PER_BURST 1
	#define `$INSTANCE_NAME`_Brightness_DMA_SRC_BASE (CYDEV_SRAM_BASE)
	#define `$INSTANCE_NAME`_Brightness_DMA_DST_BASE (CYDEV_SRAM_BASE)
#endif

/* allocates Transaction descriptors for the DMA channels, and configures each DMA channel
optionally starts the PWM*/
void `$INSTANCE_NAME`_Start()
{
	static uint8 `$INSTANCE_NAME`_InitVar = 0; /* The `$INSTANCE_NAME`_InitVar ensures that the TDs are only allocated once */
	
	if(`$INSTANCE_NAME`_InitVar == 0)
	{
		/* allocate TDs */
		`$INSTANCE_NAME`_Segment_DMA_TD = CyDmaTdAllocate();
		`$INSTANCE_NAME`_Common_DMA_TD = CyDmaTdAllocate();
		#if `$INSTANCE_NAME`_PWM_Enable
			`$INSTANCE_NAME`_Brightness_DMA_TD = CyDmaTdAllocate();
		#endif
		
		`$INSTANCE_NAME`_InitVar = 1;
	}
	
	#ifndef `$INSTANCE_NAME`_RAM_1_ctrl_reg__REMOVED /* removes this code if the control register is optimized out, this prevents build errors if nothing is connected to the `$INSTANCE_NAME` compnent */
		/* Segment DMA configuration
		Set DMA channels Bytes per burst, requests per burst, and upper 16 bits of source and destination */
		`$INSTANCE_NAME`_Segment_DMA_Chan = `$INSTANCE_NAME`_Segment_DMA_DmaInitialize(`$INSTANCE_NAME`_Segment_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_Segment_DMA_REQUEST_PER_BURST, HI16(`$INSTANCE_NAME`_Segment_DMA_SRC_BASE), HI16(`$INSTANCE_NAME`_Segment_DMA_DST_BASE));
		/* Configure the TD to transfer `$INSTANCE_NAME`_Num_Commons bytes total, chain to itself, increment source address (read throught the segment ram array) and issue a NRQ on completion */
		CyDmaTdSetConfiguration(`$INSTANCE_NAME`_Segment_DMA_TD, `$INSTANCE_NAME`_Num_Commons , `$INSTANCE_NAME`_Segment_DMA_TD, `$INSTANCE_NAME`_Segment_DMA__TD_TERMOUT_EN | TD_INC_SRC_ADR);
		/* Configure the TD to grab from the Segment_RAM array and write it into the RAM_1 control register */
		CyDmaTdSetAddress(`$INSTANCE_NAME`_Segment_DMA_TD, LO16((uint32)&(`$INSTANCE_NAME`_Segment_RAM[0])), LO16((uint32)&`$INSTANCE_NAME`_RAM_1_Control));
		/* set the channels initial TD */
		CyDmaChSetInitialTd(`$INSTANCE_NAME`_Segment_DMA_Chan, `$INSTANCE_NAME`_Segment_DMA_TD);
		/* clear spurious queued requests */
		CyDmaChSetRequest(`$INSTANCE_NAME`_Segment_DMA_Chan, CPU_TERM_CHAIN);
		CyDmaChEnable(`$INSTANCE_NAME`_Segment_DMA_Chan, 1);
		CyDmaChEnable(`$INSTANCE_NAME`_Segment_DMA_Chan, 1);
	#endif
	
	#ifndef `$INSTANCE_NAME`_RAM_2_ctrl_reg__REMOVED /* removes this code if the control register is optimized out, this prevents build errors if nothing is connected to the `$INSTANCE_NAME` compnent */
		/* Common DMA configuration
		Set DMA channels Bytes per burst, requests per burst, and upper 16 bits of source and destination */
		`$INSTANCE_NAME`_Common_DMA_Chan = `$INSTANCE_NAME`_Common_DMA_DmaInitialize(`$INSTANCE_NAME`_Common_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_Common_DMA_REQUEST_PER_BURST, HI16(`$INSTANCE_NAME`_Common_DMA_SRC_BASE), HI16(`$INSTANCE_NAME`_Common_DMA_DST_BASE));
		/* Configure the TD to transfer `$INSTANCE_NAME`_Num_Commons bytes total, chain to itself, increment source address (read throught the common ram array) and issue a NRQ on completion */
		CyDmaTdSetConfiguration(`$INSTANCE_NAME`_Common_DMA_TD, `$INSTANCE_NAME`_Num_Commons , `$INSTANCE_NAME`_Common_DMA_TD, `$INSTANCE_NAME`_Common_DMA__TD_TERMOUT_EN | TD_INC_SRC_ADR);
		/* Configure the TD to grab from the Common_RAM array and write it into the RAM_2 control register */
		CyDmaTdSetAddress(`$INSTANCE_NAME`_Common_DMA_TD, LO16((uint32)&(`$INSTANCE_NAME`_Common_RAM[0])), LO16((uint32)&`$INSTANCE_NAME`_RAM_2_Control));
		/* set the channels initial TD */
		CyDmaChSetInitialTd(`$INSTANCE_NAME`_Common_DMA_Chan, `$INSTANCE_NAME`_Common_DMA_TD);
		/* clear spurious queued requests */
		CyDmaChSetRequest(`$INSTANCE_NAME`_Common_DMA_Chan, CPU_TERM_CHAIN);
		CyDmaChEnable(`$INSTANCE_NAME`_Common_DMA_Chan, 1);
		CyDmaChEnable(`$INSTANCE_NAME`_Common_DMA_Chan, 1);
	#endif

	#if `$INSTANCE_NAME`_PWM_Enable

		/* Brightness DMA configuration
		Set DMA channels Bytes per burst, requests per burst, and upper 16 bits of source and destination */
		`$INSTANCE_NAME`_Brightness_DMA_Chan = `$INSTANCE_NAME`_Brightness_DMA_DmaInitialize(`$INSTANCE_NAME`_Brightness_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_Brightness_DMA_REQUEST_PER_BURST, HI16(`$INSTANCE_NAME`_Brightness_DMA_SRC_BASE), HI16(`$INSTANCE_NAME`_Brightness_DMA_DST_BASE));
		/* Configure the TD to transfer `$INSTANCE_NAME`_Num_Commons bytes total, chain to itself, increment source address (read throught the brightness ram array) and issue a NRQ on completion */
		CyDmaTdSetConfiguration(`$INSTANCE_NAME`_Brightness_DMA_TD, `$INSTANCE_NAME`_Num_Commons , `$INSTANCE_NAME`_Brightness_DMA_TD, `$INSTANCE_NAME`_Brightness_DMA__TD_TERMOUT_EN | TD_INC_SRC_ADR);
		/* Configure the TD to grab from the Brightness_RAM array and write it into the PWM Duty Cycle register */
		CyDmaTdSetAddress(`$INSTANCE_NAME`_Brightness_DMA_TD, LO16((uint32)&(`$INSTANCE_NAME`_Brightness_RAM[0])), LO16((uint32)`$INSTANCE_NAME`_COM_PWM_COMPARE1_LSB_PTR));
		/* set the channels initial TD */
		CyDmaChSetInitialTd(`$INSTANCE_NAME`_Brightness_DMA_Chan, `$INSTANCE_NAME`_Brightness_DMA_TD);
		/* clear spurious queued requests */
		CyDmaChSetRequest(`$INSTANCE_NAME`_Brightness_DMA_Chan, CPU_TERM_CHAIN);
		CyDmaChEnable(`$INSTANCE_NAME`_Brightness_DMA_Chan, 1);
		CyDmaChEnable(`$INSTANCE_NAME`_Brightness_DMA_Chan, 1);
		
		`$INSTANCE_NAME`_COM_PWM_Start();
		
	#endif
}

void `$INSTANCE_NAME`_Stop()
{
	`$INSTANCE_NAME`_ClearDisplayAll(); /* clear the display ram to prevent LEDs from being driven while disabled */
	/* disable the DMA channels */
	CyDmaChSetRequest(`$INSTANCE_NAME`_Segment_DMA_Chan, CPU_TERM_CHAIN);
	CyDmaChSetRequest(`$INSTANCE_NAME`_Common_DMA_Chan, CPU_TERM_CHAIN);
	
	#if `$INSTANCE_NAME`_PWM_Enable
		/* disable the PWM */
		`$INSTANCE_NAME`_COM_PWM_Stop();
		CyDmaChSetRequest(`$INSTANCE_NAME`_Brightness_DMA_Chan, CPU_TERM_CHAIN);
	#endif
	
	return;
}

/* matrix LED display APIs */

/* set the LED in the corresponding row and column.  Rows are the segments and the columns are the commons.  
Rows greater than 8 will wrap (row % 8) and columns greater than `$INSTANCE_NAME`_Num_Commons will wrap (col % `$INSTANCE_NAME`_Num_Commons) */
void `$INSTANCE_NAME`_SetRC(uint8 row, uint8 col)
{
	`$INSTANCE_NAME`_Segment_RAM[col % `$INSTANCE_NAME`_Num_Commons] |= 1 << (row % 8);
	return;
}

/* clear the LED in the corresponding row and column.  Rows are the segments and the columns are the commons.  
Rows greater than 8 will wrap (row % 8) and columns greater than `$INSTANCE_NAME`_Num_Commons will wrap (col % `$INSTANCE_NAME`_Num_Commons) */
void `$INSTANCE_NAME`_ClearRC(uint8 row, uint8 col)
{
	`$INSTANCE_NAME`_Segment_RAM[col % `$INSTANCE_NAME`_Num_Commons] &= ~(1 << (row % 8));
	return;
}

/* toggle the LED in the corresponding row and column.  Rows are the segments and the columns are the commons. 
Rows greater than 8 will wrap (row % 8) and columns greater than `$INSTANCE_NAME`_Num_Commons will wrap (col % `$INSTANCE_NAME`_Num_Commons) */
void `$INSTANCE_NAME`_ToggleRC(uint8 row, uint8 col)
{
	`$INSTANCE_NAME`_Segment_RAM[col % `$INSTANCE_NAME`_Num_Commons] ^= 1 << (row % 8);
	return;
}

/* returns the state of the LED in the corresponding row and column.  Rows are the segments and the columns are the commons.  
Rows greater than 8 will wrap (row % 8) and columns greater than `$INSTANCE_NAME`_Num_Commons will wrap (col % `$INSTANCE_NAME`_Num_Commons) */
uint8 `$INSTANCE_NAME`_GetRC(uint8 row, uint8 col)
{
	return ((`$INSTANCE_NAME`_Segment_RAM[col % `$INSTANCE_NAME`_Num_Commons] & (1 << (row % 8))) >> row % 8) & 0x01;
}

/* write directly to the correspinding display ram.  The display number will wrap at `$INSTANCE_NAME`_Num_Commons (display % `$INSTANCE_NAME`_Num_Commons) */
void `$INSTANCE_NAME`_SetDisplayRAM(uint8 value, uint8 display)
{
	`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = value;
	return;
}

/* Read the correspinding display ram.  The display number will wrap at `$INSTANCE_NAME`_Num_Commons (display % `$INSTANCE_NAME`_Num_Commons) */
uint8 `$INSTANCE_NAME`_GetDisplayRAM(uint8 display)
{
	return `$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons];
}

/* clears the specified display.  if "display" is greater than the number of commons, the number will wrap (display % `$INSTANCE_NAME`_Num_Commons) */
void `$INSTANCE_NAME`_ClearDisplay(uint8 display)
{
	`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = 0;
}

/* clears the entire display */
void `$INSTANCE_NAME`_ClearDisplayAll(void)
{
	uint8 j;
	
	for(j = 0; j < `$INSTANCE_NAME`_Num_Commons; j++)
	{
		`$INSTANCE_NAME`_Segment_RAM[j] = 0;
	}
	return;
}

#if `$INSTANCE_NAME`_Seg7_Support
	
	/* returns the value to be written into the `$INSTANCE_NAME`_Segment_RAM[] in order to display the particular number */
	uint8 `$INSTANCE_NAME`_DecodeNumber(uint8 input)
	{
		return `$INSTANCE_NAME`_seg7_Table[(input & 0x0f)];
	}
	
	/* returns the value to be written into the `$INSTANCE_NAME`_Segment_RAM[] in order to display the ascii alphabet character */
	uint8 `$INSTANCE_NAME`_DecodeAlpha(char input)
	{
		return `$INSTANCE_NAME`_seg7_Alpha_Table[((input >= 97) ? input - 97 : input - 65) % 26];
	}
	
	/* sets or clears the decimal point on "display" based on the value of "value".  If the LSb of value is set, the decimal point will be set
	if the LSb of "value" is clear, the decimal point will be cleared. */
	void `$INSTANCE_NAME`_PutDecimalPoint(uint8 value, uint8 display)
	{
		`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] &= 0x7f; /* clear the DP */
		`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] |= ((value << 7) & 0x80); /* set the DP (if requested) */
		return;
	}
	
	/* returns the state of the decimal point for "display".  If the returned value is '1', the decimal point is set.  If the returned value is '0', the decimal point is not set */
	uint8 `$INSTANCE_NAME`_GetDecimalPoint(uint8 display)
	{
		return (`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] >> 7) & 0x01;
	}
	
	/* writes the ascii character "value" to the display "display"  if "display" is greater than the number of commons, the number will wrap (display % `$INSTANCE_NAME`_Num_Commons) */
	void `$INSTANCE_NAME`_PutCharacter(char value, uint8 display)
	{
		if(value >= 97 && value <= 122) /* a-z */
		{
			`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = `$INSTANCE_NAME`_seg7_Alpha_Table[value - 97];
		}
		else if(value >= 65 && value <= 90) /* A-Z */
		{
			`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = `$INSTANCE_NAME`_seg7_Alpha_Table[value - 65];
		}
		else if(value >= 48 && value <= 57) /* 0-9 */
		{
			`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = `$INSTANCE_NAME`_seg7_Table[value - 48];
		}
		else if(value == 45) /* - */
		{
			`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = 0x40;
		}
		else if(value == 46) /* . */
		{
			`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = 0x80;
		}
		else if(value == 61) /* = */
		{
			`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = 0x48;
		}
		else if(value == 95) /* _ */
		{
			`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = 0x08;
		}
		else
		{
			`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = 0;
		}
		return;
	}
	
	/* writes a string to the 7 segment display, starting with the the display "display".  if the string extends beyond `$INSTANCE_NAME`_Num_Commons, then the string will be truncated */
	void `$INSTANCE_NAME`_PutString(char * string, uint8 display)
	{
		uint8 j;
		
		j = 0;
		while((string[j] != 0) && (j < (`$INSTANCE_NAME`_Num_Commons - display)))
		{
			`$INSTANCE_NAME`_PutCharacter(string[j], display + j);
			j++;
		}
		return;
	}
	
	/* draws the specified digit 0-9 onto the the display "display". if "display" is greater than the number of commons, the number will wrap (display % `$INSTANCE_NAME`_Num_Commons) */
	void `$INSTANCE_NAME`_SetNumberDec(uint8 value, uint8 display)
	{
		`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = `$INSTANCE_NAME`_seg7_Table[value % 10];
		return;
	}
	
	/* draws the specified digit 0-F onto the the display "display". if "display" is greater than the number of commons, the number will wrap (display % `$INSTANCE_NAME`_Num_Commons) */
	void `$INSTANCE_NAME`_SetNumberHex(uint8 value, uint8 display)
	{
		`$INSTANCE_NAME`_Segment_RAM[display % `$INSTANCE_NAME`_Num_Commons] = `$INSTANCE_NAME`_seg7_Table[value & 0x0f];
		return;
	}
	
	/* displays signed integer values up to 8 characters long */
	void `$INSTANCE_NAME`_PutNumberInt(int32 value, uint8 display, uint8 digits)
	{
		uint8 j;
		int32 divisors[8] = {1,10,100,1000,10000,100000,1000000,10000000}; 
		int8 max_digits;
		
		if(value < 0) /* determine if the number needs a negative sign */
		{
			`$INSTANCE_NAME`_PutCharacter( '-', display);
			display++;
			digits--;
			value = -value;
		}
		
		max_digits = (display > 8 ? 8 : digits);
		
		for(j = 0; j < max_digits; j++)
		{
			`$INSTANCE_NAME`_SetNumberDec((value / divisors[max_digits - j-1]) % 10, display + j);
		}
		return;
	}
	
	/* displays hexadecimal values, up to 8 characters longs */
	void `$INSTANCE_NAME`_PutNumberHex(uint32 value, uint8 display, uint8 digits)
	{
		uint8 j;
		int8 max_digits;
		
		max_digits = (display > 8 ? 8 : digits);
		
		for(j = 0; j < max_digits; j++)
		{
			`$INSTANCE_NAME`_SetNumberHex(value >> ((max_digits-1)*4 - (j*4)) & 0x0f, display + j);
		}
		return;
	}
#endif

#if `$INSTANCE_NAME`_PWM_Enable

	/* write directly to the correspinding brightness ram.  The display number will wrap at `$INSTANCE_NAME`_Num_Commons (display % `$INSTANCE_NAME`_Num_Commons) */
	void `$INSTANCE_NAME`_SetBrightnessRAM(uint8 value, uint8 display)
	{
		`$INSTANCE_NAME`_Brightness_RAM[display % `$INSTANCE_NAME`_Num_Commons] = value;
		return;
	}

	/* Read the correspinding brightness ram.  The display number will wrap at `$INSTANCE_NAME`_Num_Commons (display % `$INSTANCE_NAME`_Num_Commons) */
	uint8 `$INSTANCE_NAME`_GetBrightnessRAM(uint8 display)
	{
		return `$INSTANCE_NAME`_Brightness_RAM[display % `$INSTANCE_NAME`_Num_Commons];
	}
	
#endif

/* [] END OF FILE */
