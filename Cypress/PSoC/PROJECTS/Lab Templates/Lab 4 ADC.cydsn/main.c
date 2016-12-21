#include <device.h>
#include <LED_RGB.h>

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint16 ADCResult;
    LED_RGB_Start();
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    
    Change1; /* Replace this line with the ADC Start code */
    
    for(;;)
    {
        /* Place your application code here. */
        Change2; /* Replace this line with the ADC Get Result API */
        LED_RGB_SetColorRGB(ADCResult * (65535 / 2048), 0, 0);
        CyDelay(10);
    }
}

/* [] END OF FILE */
