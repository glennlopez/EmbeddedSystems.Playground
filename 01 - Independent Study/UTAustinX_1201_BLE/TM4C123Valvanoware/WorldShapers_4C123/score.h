// score.h
// Jonathan Valvano 
// draws score on bottom of screen
// May 1, 2016
// **********Score_OutHorizontal*******************
// draw score on screen horizonally as 4-digit number
// font is 5 wide-6 high Courier bold yellow on black
// Input: n is between 0 and 9999
//        x     horizontal position of the bottom left corner of the image, columns from the left edge
//        y     vertical position of the bottom left corner of the image, rows from the top edge
// Output: none
void Score_OutHorizontal(uint32_t n, int16_t x, int16_t y);

// **********Score_OutVertical*******************
// draw score on screen vertically as 4-digit number
// font is 6 wide-5 high Courier bold yellow on black
// Input: n is between 0 and 9999
//        x     horizontal position of the bottom left corner of the image, columns from the left edge
//        y     vertical position of the bottom left corner of the image, rows from the top edge
// Output: none
void Score_OutVertical(uint32_t n, int16_t x, int16_t y);
