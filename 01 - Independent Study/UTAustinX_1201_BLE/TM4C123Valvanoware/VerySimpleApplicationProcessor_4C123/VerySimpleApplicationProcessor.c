// VerySimpleApplicationProcessor.c
// Runs on any computer
// Test of the CC2650 simple network processor.
// To port this program to a different processor, 
//     re-write GPIO.c, UART0.c, and UART1.c for that processor.
// This file should contain nothing hardware specific and require no significant changes.
// Daniel Valvano and Jonathan Valvano
// July 19, 2016
// This version automatically dumps all SNP communcication to the UART0 for debugging

/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
   ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
   ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

//------------See AP.c for details of hardware connections to CC2650--------------------
//------------See LaunchPad.c for details of switches and LEDs--------------------------

#include <stdint.h>
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/AP.h"
#include "../inc/UART0.h"
#include "../inc/LaunchPad.h"
//--------------------------------------------------
// 1. Initialize GATT (add services, characteristics, CCCD’s, etc.). See Section 9.5.
// 2. Initialize GAP (advertisement data, connection parameters, etc.). See Section 9.3.
// 3. Advertise and optionally wait for a connection. See Section 9.4.
// 4. Respond to GATT requests and send notifications / indications as desired. See Section 9.6

//----------------very simple application processor-----------
// first characteristic is called "Data" and is a read/write parameter exchanged with the phone
uint8_t Data;        // read/write parameter
uint16_t Handle1;    // number associated with this characteristic
// second characteristic is called "Switches" and is a read only parameter that returns switch value (0-3)
uint16_t Handle2;    // number associated with this characteristic
// third characteristic is called "LEDs" and is a write-only parameter that sets the LED (0-7)
uint16_t Handle3;    // number associated with this characteristic
// fourth characteristic is called "Count" and is a local counter sent periodically to the phone
uint8_t Count;
uint16_t Handle4;    // number associated with this characteristic
uint16_t CCCDhandle; // number associated with this CCCD, Client Characteristic Configuration Descriptor
uint16_t CCCDvalue;  // 0 means inactive, 1 means please notify

#define RECVSIZE 128
extern uint8_t RecvBuf[RECVSIZE];

const uint8_t NPI_GetStatusMsg[] =   {SOF,0x00,0x00,0x55,0x06,0x53};
const uint8_t NPI_GetVersionMsg[] =  {SOF,0x00,0x00,0x35,0x03,0x36};
const uint8_t NPI_AddServiceMsg[] = {
  SOF,3,0x00,     // length = 3
  0x35,0x81,      // SNP Add Service
  0x01,           // Primary Service
  0xF0,0xFF,      // UUID
  0xB9};          // FCS (calculated by AP_SendMessageResponse)

const uint8_t NPI_RegisterMsg[] = {   
  SOF,0x00,0x00,  // length = 0
  0x35,0x84,      // SNP Register Service
  0x00};          // FCS (calculated by AP_SendMessageResponse)

// call Set Advertisement twice 0, 2
const uint8_t NPI_SetAdvertisementMsg[] = {   
  SOF,11,0x00,    // length = 11
  0x55,0x43,      // SNP Set Advertisement Data
  0x01,           // Not connected Advertisement Data
  0x02,0x01,0x06, // GAP_ADTYPE_FLAGS,DISCOVERABLE | no BREDR
  0x06,0xFF,      // length, manufacturer specific
  0x0D ,0x00,     // Texas Instruments Company ID
  0x03,           // TI_ST_DEVICE_ID
  0x00,           // TI_ST_KEY_DATA_ID
  0x00,           // Key state
  0xEE};          // FCS (calculated by AP_SendMessageResponse)

const uint8_t NPI_GATTSetDeviceNameMsg[] = {   
  SOF,18,0x00,    // length = 18
  0x35,0x8C,      // SNP Set GATT Parameter (0x8C)
  0x01,           // Generic Access Service
  0x00,0x00,      // Device Name
  'S','h','a','p','e',' ','t','h','e',' ','W','o','r','l','d',
  0x77};          // FCS (calculated by AP_SendMessageResponse)


const uint8_t NPI_SetAdvertisementDataMsg[] = {   
  SOF,27,0x00,    // length = 27
  0x55,0x43,      // SNP Set Advertisement Data
  0x00,           // Scan Response Data
  16,0x09,        // length, type=LOCAL_NAME_COMPLETE
  'S','h','a','p','e',' ','t','h','e',' ','W','o','r','l','d',
// connection interval range
  0x05,           // length of this data
  0x12,           // GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE
  0x50,0x00,      // DEFAULT_DESIRED_MIN_CONN_INTERVAL
  0x20,0x03,      // DEFAULT_DESIRED_MAX_CONN_INTERVAL
// Tx power level
  0x02,           // length of this data
  0x0A,           // GAP_ADTYPE_POWER_LEVEL
  0x00,           // 0dBm
  0x77};          // FCS (calculated by AP_SendMessageResponse)
  
const uint8_t NPI_StartAdvertisementMsg[] = {   
  SOF,14,0x00,    // length = 14
  0x55,0x42,      // SNP Start Advertisement
  0x00,           // Connectable Undirected Advertisements
  0x00,0x00,      // Advertise infinitely.
  0x64,0x00,      // Advertising Interval (100 * 0.625 ms=62.5ms)
  0x00,           // Filter Policy RFU
  0x00,           // Initiator Address Type RFU
  0x00,0x01,0x00,0x00,0x00,0xC5, // RFU
  0x02,           // Advertising will restart with connectable advertising when a connection is terminated
  0xBB};          // FCS (calculated by AP_SendMessageResponse)

uint8_t NPI_ReadConfirmationMsg[] = {   
  SOF,0x08,0x00,  // length = 8 (7+data length, filled in dynamically)
  0x55,0x87,      // SNP Characteristic Read Confirmation (0x87)
  0x00,           // Success
  0x00,0x00,      // handle of connection always 0
  0x00,0x00,      // Handle of the characteristic value attribute being read (filled in dynamically
  0x00,0x00,      // offset, ignored, assumes small chucks of data
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // actual data (filled in dynamically)
  0x00};          // FCS (calculated by AP_SendMessageResponse)

uint8_t NPI_WriteConfirmationMsg[] = {   
  SOF,0x03,0x00,  // length = 3
  0x55,0x88,      // SNP Characteristic Write Confirmation
  0x00,           // Success
  0x00,0x00,      // handle of connection always 0
  0xDE};          // FCS (calculated by AP_SendMessageResponse)

uint8_t NPI_CCCDUpdatedConfirmationMsg[] = {   
  SOF,0x03,0x00,  // length = 3
  0x55,0x8B,      // SNP CCCD Updated Confirmation (0x8B)
  0x00,           // Success
  0x00,0x00,      // handle of connection always 0
  0xDD};          // FCS (calculated by AP_SendMessageResponse)

uint8_t NPI_SendNotificationIndicationMsg[] = {   
  SOF,0x07,0x00,  // length = 7 to 14 depending on data size
  0x55,0x89,      // SNP Send Notification Indication (0x89))
  0x00,0x00,      // handle of connection always 0
  0x00,0x00,      // Handle of the characteristic value attribute to notify / indicate (filled in dynamically
  0x00,           // RFU
  0x01,           // Indication Request type
  0x00,0,0,0,0,0,0,0, // 1 to 8 bytes of data filled in dynamically
  0xDD};      // FCS (calculated by AP_SendMessageResponse)

void OutValue(char *label,uint32_t value){ 
  UART0_OutString(label);
  UART0_OutUHex(value);
}

const uint8_t NPI_AddCharValue1[] = {   
  SOF,0x08,0x00,  // length = 8
  0x35,0x82,      // SNP Add Characteristic Value Declaration
  0x03,           // GATT Read+Write Permission
  0x0A,0x00,      // GATT Read+Write Properties
  0x00,           // RFU
  0x00,0x02,      // Maximum length of the attribute value=512
  0xF1,0xFF,      // UUID
  0xBA};          // FCS (calculated by AP_SendMessageResponse)
const uint8_t NPI_AddCharDescriptor1[] = {   
  SOF,11,0x00,    // length = 11
  0x35,0x83,      // SNP Add Characteristic Descriptor Declaration
  0x80,           // User Description String
  0x01,           // GATT Read Permissions
  0x05,0x00,      // Maximum Possible length of the user description string
  0x05,0x00,      // Initial length of the user description string
  'D','a','t','a',0, // Initial user description string
  0x0C};          // FCS (calculated by AP_SendMessageResponse)

const uint8_t NPI_AddCharValue2[] = {   
  SOF,0x08,0x00,  // length = 8
  0x35,0x82,      // SNP Add Characteristic Value Declaration
  0x01,           // GATT Read Permission
  0x02,0x00,      // GATT Read Properties
  0x00,           // RFU
  0x00,0x02,      // Maximum length of the attribute value=512
  0xF2,0xFF,      // UUID
  0xB3};          // FCS (calculated by AP_SendMessageResponse)
const uint8_t NPI_AddCharDescriptor2[] = {   
  SOF,15,0x00,    // length = 15
  0x35,0x83,      // SNP Add Characteristic Descriptor Declaration
  0x80,           // User Description String
  0x01,           // GATT Read Permissions
  0x09,0x00,      // Maximum Possible length of the user description string
  0x09,0x00,      // Initial length of the user description string
  'S','w','i','t','c','h','e','s',0, // Initial user description string
  0x0F};          // FCS (calculated by AP_SendMessageResponse)

const uint8_t NPI_AddCharValue3[] = {   
  SOF,0x08,0x00,  // length = 8
  0x35,0x82,      // SNP Add Characteristic Value Declaration
  0x02,           // GATT Write Permission
  0x08,0x00,      // GATT Write Properties
  0x00,           // RFU
  0x00,0x02,      // Maximum length of the attribute value=512
  0xF3,0xFF,      // UUID
  0xBB};          // FCS (calculated by AP_SendMessageResponse)
const uint8_t NPI_AddCharDescriptor3[] = {   
  SOF,11,0x00,    // length = 11
  0x35,0x83,      // SNP SNP Add Characteristic Descriptor Declaration
  0x80,           // User Description String
  0x01,           // GATT Read Permissions
  0x05,0x00,      // Maximum Possible length of the user description string
  0x05,0x00,      // Initial length of the user description string
  'L','E','D','s',0, // Initial user description string
  0x0E};          // FCS (calculated by AP_SendMessageResponse)

const uint8_t NPI_AddCharValue4[] = {   
  SOF,0x08,0x00,  // length = 8
  0x35,0x82,      // SNP Add Characteristic Value Declaration
  0x00,           // GATT no read, no Write Permission
  0x10,0x00,      // GATT notification Properties
  0x00,           // RFU
  0x00,0x02,      // Maximum length of the attribute value=512
  0xF4,0xFF,      // UUID
  0xA6};          // FCS (calculated by AP_SendMessageResponse)
const uint8_t NPI_AddCharDescriptor4[] = {   
  SOF,12,0x00,    // length = 12
  0x35,0x83,      // SNP Add Characteristic Descriptor Declaration
  0x84,           // User Description String+CCCD
  0x03,           // CCCD parameters read+write
  0x01,           // GATT Read Permissions
  0x06,0x00,      // Maximum Possible length of the user description string
  0x06,0x00,      // Initial length of the user description string
  'C','o','u','n','t',0, // Initial user description string
  0x0E};          // FCS (calculated by AP_SendMessageResponse)

int main(void){ volatile int r1; uint16_t h; uint32_t time=0;
  uint8_t responseNeeded;
  DisableInterrupts();
  Clock_InitFastest();  // processor running at max speed
  UART0_Init();         // debugging output
  LaunchPad_Init();     // switches and LEDs
  EnableInterrupts();
  UART0_OutString("\n\rVery Simple Application Processor\n\r");
  UART0_OutString("\n\rReset CC2650");
  r1 = AP_Init();  // debugging enabled with compiler flag APDEBUG in AP.c
  EnableInterrupts();

  UART0_OutString("\n\rGATT Set DeviceName");
  r1=AP_SendMessageResponse((uint8_t*)NPI_GATTSetDeviceNameMsg,RecvBuf,RECVSIZE);
  
  UART0_OutString("\n\rNPI_GetStatus");
  r1=AP_SendMessageResponse((uint8_t*)NPI_GetStatusMsg,RecvBuf,RECVSIZE);
  UART0_OutString("\n\rNPI_GetVersion");
  r1=AP_SendMessageResponse((uint8_t*)NPI_GetVersionMsg,RecvBuf,RECVSIZE); 
    
  UART0_OutString("\n\rAdd service");
  r1=AP_SendMessageResponse((uint8_t*)NPI_AddServiceMsg,RecvBuf,RECVSIZE); 
  //---------------Characteristic1 is read/write 8 bits---------
  Data = 1;
  UART0_OutString("\n\rAdd CharValue1");
  r1=AP_SendMessageResponse((uint8_t*)NPI_AddCharValue1,RecvBuf,RECVSIZE);
  Handle1 = (RecvBuf[7]<<8)+RecvBuf[6]; // handle for this characteristic
  UART0_OutString("\n\rAdd CharDescriptor1");
  r1=AP_SendMessageResponse((uint8_t*)NPI_AddCharDescriptor1,RecvBuf,RECVSIZE);
  //-----------Characteristic2 is read only 8 bits-------------
  UART0_OutString("\n\rAdd CharValue2");
  r1=AP_SendMessageResponse((uint8_t*)NPI_AddCharValue2,RecvBuf,RECVSIZE);
  Handle2 = (RecvBuf[7]<<8)+RecvBuf[6]; // handle for this characteristic
  UART0_OutString("\n\rAdd CharDescriptor2");
  r1=AP_SendMessageResponse((uint8_t*)NPI_AddCharDescriptor2,RecvBuf,RECVSIZE);
  //-----------Characteristic3 is write only 8 bits----------
  UART0_OutString("\n\rAdd CharValue3");
  r1=AP_SendMessageResponse((uint8_t*)NPI_AddCharValue3,RecvBuf,RECVSIZE);
  Handle3 = (RecvBuf[7]<<8)+RecvBuf[6]; // handle for this characteristic
  UART0_OutString("\n\rAdd CharDescriptor3");
  r1=AP_SendMessageResponse((uint8_t*)NPI_AddCharDescriptor3,RecvBuf,RECVSIZE);
  //-----------Characteristic4 is notify 8 bits-------------
  Count = 0;
  UART0_OutString("\n\rAdd CharValue4");
  r1=AP_SendMessageResponse((uint8_t*)NPI_AddCharValue4,RecvBuf,RECVSIZE);
  Handle4 = (RecvBuf[7]<<8)+RecvBuf[6]; // handle for this characteristic
  UART0_OutString("\n\rAdd CharDescriptor4");
  r1=AP_SendMessageResponse((uint8_t*)NPI_AddCharDescriptor4,RecvBuf,RECVSIZE);
  CCCDhandle = (RecvBuf[8]<<8)+RecvBuf[7]; // handle for this CCCD
  CCCDvalue = 0;
  //------------Register Service------------
  UART0_OutString("\n\rRegister service");
  r1=AP_SendMessageResponse((uint8_t*)NPI_RegisterMsg,RecvBuf,RECVSIZE);
  //--------------Advertise----------
  UART0_OutString("\n\rSetAdvertisement1");
  r1=AP_SendMessageResponse((uint8_t*)NPI_SetAdvertisementMsg,RecvBuf,RECVSIZE);
  UART0_OutString("\n\rSetAdvertisement2");
  r1=AP_SendMessageResponse((uint8_t*)NPI_SetAdvertisementDataMsg,RecvBuf,RECVSIZE);
  UART0_OutString("\n\rStartAdvertisement");
  r1=AP_SendMessageResponse((uint8_t*)NPI_StartAdvertisementMsg,RecvBuf,RECVSIZE);
  UART0_OutString("\n\rGetStatus");
  r1=AP_SendMessageResponse((uint8_t*)NPI_GetStatusMsg,RecvBuf,RECVSIZE);

  while(1){
    time++;
    if(AP_RecvStatus()){
      if(AP_RecvMessage(RecvBuf,RECVSIZE)==APOK){
        AP_EchoReceived(APOK);        
        if((RecvBuf[3]==0x55)&&(RecvBuf[4]==0x88)){// SNP Characteristic Write Indication (0x88)
          h = (RecvBuf[8]<<8)+RecvBuf[7]; // handle for this characteristic
          responseNeeded = RecvBuf[9];
          // process possible write indications
          if(h == Handle1){      // Handle1 could be write
            Data = RecvBuf[12];
            OutValue("\n\rWrite Data=",RecvBuf[12]);
          }else if(h == Handle3){// Handle3 could be write
            OutValue("\n\rWrite LED=",RecvBuf[12]);
            LaunchPad_Output(RecvBuf[12]&0x07);
          }
          if(responseNeeded){
            AP_SendMessage(NPI_WriteConfirmationMsg);
            AP_EchoSendMessage(NPI_WriteConfirmationMsg);
          }
        }
        if((RecvBuf[3]==0x55)&&(RecvBuf[4]==0x87)){// SNP Characteristic Read Indication (0x87)
          h = (RecvBuf[8]<<8)+RecvBuf[7]; // handle for this characteristic
          // process possible read indications
          if(h == Handle1){      // Handle1 could be read
            NPI_ReadConfirmationMsg[12] = Data;
            OutValue("\n\rRead Data=",NPI_ReadConfirmationMsg[12]);
          }else if(h == Handle2){// Handle2 could be read
            NPI_ReadConfirmationMsg[12] = LaunchPad_Input();
            OutValue("\n\rRead Switch=",NPI_ReadConfirmationMsg[12]);
          }
          NPI_ReadConfirmationMsg[8] = RecvBuf[7]; // handle
          NPI_ReadConfirmationMsg[9] = RecvBuf[8];
          AP_SendMessage(NPI_ReadConfirmationMsg);
          AP_EchoSendMessage(NPI_ReadConfirmationMsg);
        }
        if((RecvBuf[3]==0x55)&&(RecvBuf[4]==0x8B)){// SNP CCCD Updated Indication (0x8B)
          h = (RecvBuf[8]<<8)+RecvBuf[7]; // handle for this characteristic
          responseNeeded = RecvBuf[9];
          if(CCCDhandle == h){
            CCCDvalue = (RecvBuf[11]<<8)+RecvBuf[10];
          }
          if(responseNeeded){
            AP_SendMessage(NPI_CCCDUpdatedConfirmationMsg);
            AP_EchoSendMessage(NPI_CCCDUpdatedConfirmationMsg);
          }
        }        
      }
    }
    if(time>4000000){
      time = 0;
      Count++;
      if(CCCDvalue){      
        NPI_SendNotificationIndicationMsg[7] = Handle4&0x0FF; // handle
        NPI_SendNotificationIndicationMsg[8] = Handle4>>8; 
        NPI_SendNotificationIndicationMsg[11] = Count;
        OutValue("\n\rSend Count=",Count);
        r1=AP_SendMessageResponse(NPI_SendNotificationIndicationMsg,RecvBuf,RECVSIZE);
      }
    }
  }
}



