#include <project.h>
int i = 0;          //8bit counter container

int main()
{
    /* [] INITIALIZATION/STARTUP SEQUENCE */
    PWM_Start();    //Starts PWM1
    PWM2_Start();   //Starts PWM2
    clk_Start();    //Starts clock1
    clk2_Start();   //Starts clock2

    /* [] GLOBAL INTERUPTS & LOOPS */
    while(1)
    {
            /* [] APPLICATION SCRIPTS */
            // change the pwm compare value from 0 - 255 then back to 0
            
            for (i=0;i<255;i++){        //this brightens the LED incremently
                PWM_WriteCompare(i);
                CyDelay(5);
            }
            
            for (i=255;i>0;i--){        //this dims the LED incremently
                PWM_WriteCompare(i);
                CyDelay(5);
            }
    }
}

/* [] END OF FILE */
