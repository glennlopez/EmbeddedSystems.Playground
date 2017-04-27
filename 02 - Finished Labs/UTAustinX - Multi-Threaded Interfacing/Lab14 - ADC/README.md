C14 ADC and Data Acquisition
=================
In this lab I will design a distance meter. A linear slide potentiometer converts distance into resistance (0 ? R ? 10 k?). My software will use the 12-bit ADC built into the microcontroller. The ADC will be sampled at 40 Hz using SysTick interrupts. I will write a C function that converts the ADC sample into distance, with units of 0.001 cm. That data stream will be passed from the ISR into the main program using a mailbox, and the main program will output the data on a display. The display is optional.


Learning Objectives
=================
In this chapter we will focus on input devices that we use to gather information about the world. More specifically, we present a technique for the system to measure analog inputs using an analog to digital converter (ADC). We will use periodic interrupts to sample the ADC at a fixed rate. We will then combine sensors, the ADC, software, PWM output and motor interfaces to implement intelligent control on our robot car.

![https://raw.githubusercontent.com/glennlopez/EmbeddedSystems.Playground/master/05%20-%20WikiAssets/Fig10_02DAS.jpg](https://raw.githubusercontent.com/glennlopez/EmbeddedSystems.Playground/master/05%20-%20WikiAssets/Fig10_02DAS.jpg)

* Develop a means for a digital computer to sense its analog world.
* Review digitization: Quantization, range, precision and resolution.
* Extend the Nyquist Theorem to cases the ADC is used to sense information.
* Study the basics of transducers: conversion of physical to electrical.
* Use an optical sensor to measure distance to an object.


Learning/Referance material
=================