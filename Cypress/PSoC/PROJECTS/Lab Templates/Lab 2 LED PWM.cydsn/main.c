#include <device.h>

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint16 PWMCompare;
    Change1; /* Replace this line with the PWM start API */

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        PWMCompare = PWMCompare + 1;
        if( PWMCompare >= 1000 )
            PWMCompare = 0;
        Change2; /* Replace this line with the PWM write compare API */
        CyDelay(1);
    }
}

/* [] END OF FILE */
