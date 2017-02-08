To create a 16-bit image for MK-II displays on MSP432 or TM4C123G
Jonathan Valvano, 8/28/2016
See BmpConvert.cpp for how it works
1) Create a bmp file
   width less than or equal to 128 pixels
   height less than or equal 128pixels
   save the image as a 24-bit bmp file
   store in same directory as BmpConvert16.exe
   remember the height and width
2) Execute BmpConvert16_MKII.exe
   Type the image name 
   E.g., if the file is b0.bmp, then type b0
   remember the height and width
3) Open the corresponding txt file, select all, copy
4) Open uVision compiler
   paste new image as a data constant into C code
5) Draw the image by calling BSP_LCD_DrawBitmap
   E.g., place a 11,10 image (width,height) at (50,70)
         BSP_LCD_DrawBitmap(50, 70, b0, 11, 10);
FYI: differences between ST7735 and MKII
ST7735R is 160 by 128
MKII    is 128 by 128
ST7735R is packed 5-bit blue, 6-bit green, 5-bit red
MKII    is packed 5-bit red,  6-bit green, 5-bit blue


