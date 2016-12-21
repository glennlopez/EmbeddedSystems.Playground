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
#include <project.h>

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */

        LEDR_Write(0);
        CyDelay(500);
        LEDR_Write(1);
        CyDelay(500);
        
        LEDG_Write(0);
        CyDelay(500);
        LEDG_Write(1);
        CyDelay(500);
        
        LEDB_Write(0);
        CyDelay(500);
        LEDB_Write(1);
        CyDelay(500);

    }
}

/* [] END OF FILE */
