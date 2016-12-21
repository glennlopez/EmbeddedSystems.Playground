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

#ifndef `$INSTANCE_NAME`_LED_API
#define `$INSTANCE_NAME`_LED_API

#include <device.h>

#define `$INSTANCE_NAME`_Com_Drive `$Com_Drive`
#define `$INSTANCE_NAME`_Seg_Drive `$Seg_Drive`
#define `$INSTANCE_NAME`_Seg7_Support `$Seg7_Support`
#define `$INSTANCE_NAME`_PWM_Enable	`$PWM_Enable`
#define `$INSTANCE_NAME`_Num_Commons `$Num_Commons`
#define `$INSTANCE_NAME`_External_PWM_Clk `$External_PWM_Clk`
#define `$INSTANCE_NAME`_External_Refresh_Clk `$External_Refresh_Clk`

extern uint8 `$INSTANCE_NAME`_Segment_RAM[8];

#if `$INSTANCE_NAME`_PWM_Enable
	/* data array for the PWM */
	extern uint8 `$INSTANCE_NAME`_Brightness_RAM[8];
#endif

void `$INSTANCE_NAME`_Start();
void `$INSTANCE_NAME`_Stop();

/* matrix LED display APIs */
void `$INSTANCE_NAME`_SetRC(uint8 row, uint8 col);
void `$INSTANCE_NAME`_ClearRC(uint8 row, uint8 col);
void `$INSTANCE_NAME`_ToggleRC(uint8 row, uint8 col);
uint8 `$INSTANCE_NAME`_GetRC(uint8 row, uint8 col);
void `$INSTANCE_NAME`_SetDisplayRAM(uint8 value, uint8 display);
uint8 `$INSTANCE_NAME`_GetDisplayRAM(uint8 display);
void `$INSTANCE_NAME`_ClearDisplay(uint8 display);
void `$INSTANCE_NAME`_ClearDisplayAll(void);

#if `$INSTANCE_NAME`_Seg7_Support
	/* number 0 - 15 to 7 segment decoder table */
	extern uint8 `$INSTANCE_NAME`_seg7_Table[16];
	extern uint8 `$INSTANCE_NAME`_seg7_Alpha_Table[26];
	
	uint8 `$INSTANCE_NAME`_DecodeNumber(uint8 input);
	uint8 `$INSTANCE_NAME`_DecodeAlpha(char input);
	void `$INSTANCE_NAME`_PutDecimalPoint(uint8 value, uint8 display);
	uint8 `$INSTANCE_NAME`_GetDecimalPoint(uint8 display);
	void `$INSTANCE_NAME`_PutCharacter(char value, uint8 display);
	void `$INSTANCE_NAME`_PutString(char * string, uint8 display);
	void `$INSTANCE_NAME`_SetNumberDec(uint8 value, uint8 display);
	void `$INSTANCE_NAME`_SetNumberHex(uint8 value, uint8 display);
	void `$INSTANCE_NAME`_PutNumberInt(int32 value, uint8 display, uint8 digits);
	void `$INSTANCE_NAME`_PutNumberHex(uint32 value, uint8 display, uint8 digits);
#endif



#if `$INSTANCE_NAME`_PWM_Enable
	/* write directly to the correspinding brightness ram.  The display number will wrap at `$INSTANCE_NAME`_Num_Commons (display % `$INSTANCE_NAME`_Num_Commons) */
	void `$INSTANCE_NAME`_SetBrightnessRAM(uint8 value, uint8 display);
	/* Read the correspinding brightness ram.  The display number will wrap at `$INSTANCE_NAME`_Num_Commons (display % `$INSTANCE_NAME`_Num_Commons) */
	uint8 `$INSTANCE_NAME`_GetBrightnessRAM(uint8 display);	
#endif

#endif

//[] END OF FILE
