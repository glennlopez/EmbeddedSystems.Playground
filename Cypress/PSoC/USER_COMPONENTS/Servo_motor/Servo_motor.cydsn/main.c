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

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint16 adc, compare;
    
    LCD_Start();
    ADC_Start();
    PWM_Start();
    
    

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
//        LCD_ClearDisplay();
        LCD_Start();
        
        adc = 0;
        ADC_StartConvert();
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
        ADC_StopConvert();
        adc = ADC_GetResult16();
        
        if(adc > 255)
        {
            if(adc == 0xFFFF) /* underflow correction */
            {
                adc = 0x00;
            }
            else
            adc = 0xFF; /* Overflow correction */
        }    
        
        LCD_Position(0,0);
        LCD_PrintHexUint8(adc);
                
        compare = (uint16)(1000 + ((float)((float)((float)adc / (float)255) * (float)1000)));
        LCD_Position(1,0);
        LCD_PrintDecUint16(compare);
        
        PWM_WriteCompare(compare);
        PWM_WritePeriod(compare + 39999);
    }
}

/* [] END OF FILE */
