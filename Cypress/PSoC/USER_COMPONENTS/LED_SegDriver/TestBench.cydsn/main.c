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
#include <device.h>
#include <string.h>

void sparkles(void);

CYCODE char four_score[] = ".     Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.  Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this. But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth.     ";
// 1484
//CYCODE char four_score[] = "  0123456789abcdefghijklmnopqrstuvwxyz.-=_   ";
void main()
{
	char snippet[5];
	int8 j = 0;
	
	LED_Start();
	
    while(1)
	{
		j %= 1482;
		memmove(&snippet[0], &four_score[j], 4);
		snippet[4] = 0;
		LED_ClearDisplayAll();
		LED_PutString(snippet, 0);
		while(Button_Read() > 0);
		CyDelay(350);
		j++;
	}
}

void sparkles(void)
{
	LED_Segment_RAM[0] += 5; 
	LED_Segment_RAM[1] +=3;
	LED_Segment_RAM[2] +=7;
	LED_Segment_RAM[3] +=1;
    
	LED_Brightness_RAM[0] -= 15;
	LED_Brightness_RAM[1] -= 13;
	LED_Brightness_RAM[2] -= 17;
	LED_Brightness_RAM[3] -= 11;
	CyDelay(25);
}

/* [] END OF FILE */
