#include <device.h>
#include <LED_RGB.h>

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint16 CapSensePosition;
    LED_RGB_Start();
    CyGlobalIntEnable;
    Change1; /* Replace this line with the Capsense and UART initialization code */
     
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        CapSense_1_UpdateEnabledBaselines();
        CapSense_1_ScanEnabledWidgets();
        while(CapSense_1_IsBusy() != 0);
        Change2; /* Replace this line with the Capsense slider position read API */
        LED_RGB_SetColorCircle(255 * CapSensePosition);
        Change3; /* Replace this line with the UART Put Char API */        
        CyDelay(10);
    }
}

/* [] END OF FILE */
