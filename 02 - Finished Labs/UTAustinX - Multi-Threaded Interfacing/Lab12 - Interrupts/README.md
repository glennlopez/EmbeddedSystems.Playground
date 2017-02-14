C12 Interupts
=================
Lab12_TuningFork

Learning Objectives
=================
An embedded system uses its input/output devices to interact with the external world. Input devices allow the computer to gather information and output devices can display information. Output devices also allow the computer to manipulate its environment. The tight-coupling between the computer and external world distinguishes an embedded system from a regular computer system. The challenge under most situations is that the software executes much faster than the hardware, e.g., it might take the software only 1 us to ask the hardware to clear the LCD, but the hardware might take 1 ms to complete the command. During this time, the software could execute tens of thousands of instructions. Therefore, the synchronization between the executing software and its external environment is critical for the success of an embedded system. This chapter presents general concepts about interrupts and specific details for the Cortex™-M microcontroller. We will then use periodic interrupts to cause a software task to be executed on a periodic basis. If a GPIO pin is configured as an input, it can also be armed to invoke an interrupt on falling edges, rising edges, or both falling and rising edges. Using interrupts allows the software to  respond quickly to changes in the external environment.

Learning Objectives
=================

* Appreciate the need to perform multiple tasks concurrently.
* Understand real-time performance measures such as bandwidth and latency.
* Learn how interrupts can be used to minimize latency.
* Study the basics of interrupt programming: arm, enable, trigger, vector, priority, acknowledge.
* Understand how to use SysTick to create periodic interrupts.
* Use SysTick to create sounds and spin motors.

[![IMAGE ALT TEXT](http://img.youtube.com/vi/?????/0.jpg)](http://www.youtube.com/watch?v=????? "Video Title")