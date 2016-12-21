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

#ifndef LED_LED_API
#define LED_LED_API

#include <device.h>

#define LED_Com_Drive 0
#define LED_Seg_Drive 1
#define LED_Seg7_Support 1
#define LED_PWM_Enable	1
#define LED_Num_Commons 4
#define LED_External_PWM_Clk 0
#define LED_External_Refresh_Clk 0

extern uint8 LED_Segment_RAM[8];

#if LED_PWM_Enable
	/* data array for the PWM */
	extern uint8 LED_Brightness_RAM[8];
#endif

void LED_Start();
void LED_Stop();

/* matrix LED display APIs */
void LED_SetRC(uint8 row, uint8 col);
void LED_ClearRC(uint8 row, uint8 col);
void LED_ToggleRC(uint8 row, uint8 col);
uint8 LED_GetRC(uint8 row, uint8 col);
void LED_SetDisplayRAM(uint8 value, uint8 display);
uint8 LED_GetDisplayRAM(uint8 display);
void LED_ClearDisplay(uint8 display);
void LED_ClearDisplayAll(void);

#if LED_Seg7_Support
	/* number 0 - 15 to 7 segment decoder table */
	extern uint8 LED_seg7_Table[16];
	extern uint8 LED_seg7_Alpha_Table[26];
	
	uint8 LED_DecodeNumber(uint8 input);
	uint8 LED_DecodeAlpha(char input);
	void LED_PutDecimalPoint(uint8 value, uint8 display);
	uint8 LED_GetDecimalPoint(uint8 display);
	void LED_PutCharacter(char value, uint8 display);
	void LED_PutString(char * string, uint8 display);
	void LED_SetNumberDec(uint8 value, uint8 display);
	void LED_SetNumberHex(uint8 value, uint8 display);
	void LED_PutNumberInt(int32 value, uint8 display, uint8 digits);
	void LED_PutNumberHex(uint32 value, uint8 display, uint8 digits);
#endif



#if LED_PWM_Enable
	/* write directly to the correspinding brightness ram.  The display number will wrap at LED_Num_Commons (display % LED_Num_Commons) */
	void LED_SetBrightnessRAM(uint8 value, uint8 display);
	/* Read the correspinding brightness ram.  The display number will wrap at LED_Num_Commons (display % LED_Num_Commons) */
	uint8 LED_GetBrightnessRAM(uint8 display);	
#endif

#endif

//[] END OF FILE
