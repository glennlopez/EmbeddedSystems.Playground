
PREPARATION
=================

You will need a LaunchPad.  Run the Lab9 starter file in the simulator and on the real board just to make sure the configurations are correct. The graders should run, but return scores of 0.

STARTER PROJECT
=================

Lab9_FunctionalDebugging

PURPOSE
=================

In Lab09 you will learn about time delays, arrays and functional debugging. The data you collect will be physical proof that the system operates within specifications.

SYSTEM REQUIREMENTS
=================

The Lab9 starter project is the same as C9_Debugging example but includes the connections to the Lab9 grader. You will make three changes.

First, make the LED flash at 10 Hz. In other words, invert the output every 0.05 seconds.

Second, make the LED flash if either switch SW1 or SW2 are pressed (this means either PF4 or PF0 is 0).  This means toggle if just SW1 is pressed, just SW2 is pressed or both switches are pressed.

Third, record PortF bits 4,1,0 every time the input changes or the output changes. For example, if your system detects a change in either PF4 or PF0 input, record PortF bits 4,1,0. If your system causes a change in PF1, record PortF bits 4,1,0. In order for the grading engine to see/grade your data, please leave the debugging array defined exactly as it is in the starter project.

Remember to reset the program before grading so the grader can watch you enter data into the buffers.

[![IMAGE ALT TEXT](http://img.youtube.com/vi/fzIaC0JLg7Y/0.jpg)](http://www.youtube.com/watch?v=fzIaC0JLg7Y "Video Title")

