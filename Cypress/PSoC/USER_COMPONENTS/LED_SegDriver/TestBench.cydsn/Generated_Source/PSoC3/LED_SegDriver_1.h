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

#ifndef LED_SegDriver_1_LED_API
#define LED_SegDriver_1_LED_API

#include <device.h>

#define LED_SegDriver_1_Com_Drive 0
#define LED_SegDriver_1_Seg_Drive 1
#define LED_SegDriver_1_Seg7_Support 1
#define LED_SegDriver_1_PWM_Enable	0
#define LED_SegDriver_1_Num_Commons 4
#define LED_SegDriver_1_External_PWM_Clk 0
#define LED_SegDriver_1_External_Refresh_Clk 0

extern uint8 LED_SegDriver_1_Segment_RAM[8];

#if LED_SegDriver_1_PWM_Enable
	/* data array for the PWM */
	extern uint8 LED_SegDriver_1_Brightness_RAM[8];
#endif

void LED_SegDriver_1_Start();
void LED_SegDriver_1_Stop();

/* matrix LED display APIs */
void LED_SegDriver_1_SetRC(uint8 row, uint8 col);
void LED_SegDriver_1_ClearRC(uint8 row, uint8 col);
void LED_SegDriver_1_ToggleRC(uint8 row, uint8 col);
uint8 LED_SegDriver_1_GetRC(uint8 row, uint8 col);
void LED_SegDriver_1_SetDisplayRAM(uint8 value, uint8 display);
uint8 LED_SegDriver_1_GetDisplayRAM(uint8 display);
void LED_SegDriver_1_ClearDisplay(uint8 display);
void LED_SegDriver_1_ClearDisplayAll(void);

#if LED_SegDriver_1_Seg7_Support
	/* number 0 - 15 to 7 segment decoder table */
	extern uint8 LED_SegDriver_1_seg7_Table[16];
	extern uint8 LED_SegDriver_1_seg7_Alpha_Table[26];
	
	uint8 LED_SegDriver_1_DecodeNumber(uint8 input);
	uint8 LED_SegDriver_1_DecodeAlpha(char input);
	void LED_SegDriver_1_PutDecimalPoint(uint8 value, uint8 display);
	uint8 LED_SegDriver_1_GetDecimalPoint(uint8 display);
	void LED_SegDriver_1_PutCharacter(char value, uint8 display);
	void LED_SegDriver_1_PutString(char * string, uint8 display);
	void LED_SegDriver_1_SetNumberDec(uint8 value, uint8 display);
	void LED_SegDriver_1_SetNumberHex(uint8 value, uint8 display);
	void LED_SegDriver_1_PutNumberInt(int32 value, uint8 display, uint8 digits);
	void LED_SegDriver_1_PutNumberHex(uint32 value, uint8 display, uint8 digits);
#endif



#if LED_SegDriver_1_PWM_Enable
	/* write directly to the correspinding brightness ram.  The display number will wrap at LED_SegDriver_1_Num_Commons (display % LED_SegDriver_1_Num_Commons) */
	void LED_SegDriver_1_SetBrightnessRAM(uint8 value, uint8 display);
	/* Read the correspinding brightness ram.  The display number will wrap at LED_SegDriver_1_Num_Commons (display % LED_SegDriver_1_Num_Commons) */
	uint8 LED_SegDriver_1_GetBrightnessRAM(uint8 display);	
#endif

#endif

//[] END OF FILE
