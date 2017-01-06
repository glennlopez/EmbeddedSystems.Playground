<h1>CC3100GetWeather_4C123 Example</h1>

<!--##### README BEGIN #####-->
Simple starter file
This application will fetch weather data from openweathermap.org
It will request weather by sending "GET /data/2.5/weather?q=Austin%20Texas&units=metric HTTP/1.1\r\nUser-Agent: Keil\r\nHost:api.openweathermap.org\r\nAccept: */*\r\n\r\n"

With all the buzz about the Internet of Things (IoT), we all have considered adding wireless connectivity to our embedded system lab. However, a flood of worries may hold us back, such as cost, complexity, and inertia.  This example explains to create a smart object.

Why. With the proliferation of embedded systems and the pervasiveness of the internet, it is only natural to connect the two. IoT is the combination of embedded systems, which have sensors to collect data and actuators to affect the surrounding, and the internet, which provides for ubiquitous remote and secure communication. Traditional education on wireless communication focuses on the theory of communication, which is appropriate for those engineers destined to develop new channels and maintain existing ones. However, it is likely for the embedded system engineer to be asked to connect devices to the internet.  Therefore, we should add wireless connectivity to our students’ toolbox so they will be competitive in the job market.

Pedagogical Shift. I am a strong advocate of bottom-up education, which means we start with the basics, teach a topic until the student has full grasp, and then encapsulate and use that topic as we move to teach a higher-level topic. In order to connect to the internet, our device must implement a plethora of details to be fully compatible. The only way to add wireless to an existing embedded system lab is to violate the bottom up rule “students must understand everything about the devices they use” and provide them a working “black box” with which they can experiment. More specifically, we will purchase a hardware/software solution (called an internet stack) that is internet ready, and we will provide a rich set of example solutions to teach how the internet works at the component level. Students will modify and combine these examples to design systems. This purchase-and-use design process is prevalent in industry, so it will be beneficial for students to be exposed to both bottom-up and component-level design processes.

How. The approach for implementing a smart object over wifi is to begin with a hardware/software platform that implements IEEE801.11 wifi. The CC3100BOOST is a boosterpack that can be used with the MSP430 LaunchPad, the MSP432 LaunchPad, the TM4C123 LaunchPad, the TM4C1294 LaunchPad, or with a CC31XXEMUBOOST emulation module. The CC3100BOOST implements the internet stack with a combination of hardware and software components. Software in the LaunchPad preforms system calls to the CC3100BOOST to affect wireless communication. I didn’t use the CC31XXEMUBOOST emulation module because I didn’t want or need to reprogram the CC3100 boosterpack. In this example student use one EK-TM4C123-GXL LaunchPad that fetches weather data from the internet

\ValvanoWareTM4C123
  CC3100GetWeather_4C123
  CC3100
  CC3100_docs
  driverlib
  inc
  utils


To get the getWeather project to run, the first set of steps involve hardware devices:
0) First, you will need to configure a wireless access point as unencrypted, WEP or WPA. 
You will need the name of the AP. In the starter project you will notice my AP was called valvano.
You will set these three lines to specify the parameters of the AP.  
#define SSID_NAME  "valvano"         /* Access point name to connect to. */
#define SEC_TYPE   SL_SEC_TYPE_WPA
#define PASSKEY    "calvin50"        /* Password in case of secure AP */
The SEC_TYPE can be SL_SEC_TYPE_OPEN SL_SEC_TYPE_WPA or SL_SEC_TYPE_WEP

1) If you have a Nokia 5110 LCD display, interface it to port A as described in the Nokia5110.c file. 

2) If you do not have a Nokia 5110 LCD, it will also output to the UART. The UART transmits to the PC at 115200 bits/sec, no flow control

The system should fetch weather data, the green LED toggles for each received communication. Push SW1 or SW2 to get a weather update.
If it doesn't work, use the debugger to see where it is stuck. 
The second set of changes changing "Austin Texas" to your city, 
and if you wish you can change "metric" to "imperial"

For more information see Chapter 11 in Embedded Systems: Real-Time Interfacing to ARM Cortex-M Microcontrollers, 2015, ISBN: 978-1463590154, http://users.ece.utexas.edu/~valvano/arm/outline.htm 

Jonathan Valvano 9/13/2015
<!--##### README END #####-->


