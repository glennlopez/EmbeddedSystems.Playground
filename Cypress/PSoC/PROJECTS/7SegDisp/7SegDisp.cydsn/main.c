#include <project.h>
int i;

/*****************************************************************************\
 * Function:    Count
 * Input:       int j
 * Description: 
 *   Takes intiger from count(_) and puts it into switch(_)
\*****************************************************************************/
void count (int j)
    {
        switch(j)
        {
            case 0:{binReg_Write(0x09);
            break;}
           
            case 1:{binReg_Write(0x08);
            break;}
            
            case 2:{binReg_Write(0x07);
            break;} 
            
            case 3:{binReg_Write(0x06);
            break;}
            
            case 4:{binReg_Write(0x05);
            break;}
            
            case 5:{binReg_Write(0x04);
            break;}
           
            case 6:{binReg_Write(0x03);
            break;}
            
            case 7:{binReg_Write(0x02);
            break;} 
            
            case 8:{binReg_Write(0x01);
            break;}
            
            case 9:{binReg_Write(0x00);
            break;}          
        }
    }


/*****************************************************************************\
 * Function:   Main Function
 * Description: 
 *      This is the main function
\*****************************************************************************/ 
int main()
{
    //ADC Results
    uint16 ADCResults;
    
    //Enables Global Interupts
    CyGlobalIntEnable;
    
    //Initializes ADC API 
    ADC_Start();
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    
    //Infinite Loop (LIKE AN ARDUINO)
    for(;;) 
    {
        //Put ADC Results into "ADCResults" & Puts it into "count(_)"
        ADCResults = ADC_GetResult16(0);
        count(ADCResults / 220);
        CyDelay(50);
        
        /*------------------ DEBUG LOOP FOR TESTING 7 SEGMENT DISPLAY -----------
        for(i=0;i<=9;i++) //this for loop adds +1 to variable i
        {
            count(i); //takes the value of i and puts it in "count( )" function
            CyDelay(1000); // delays the next code to excecute
        }
        -----------------------------------------------------------------------*/

    }     
}