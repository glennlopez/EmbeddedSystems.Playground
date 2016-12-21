/* ========================================
 *
 * The following firmware was developed by Cypress Semiconductor
 * This work is licensed under a Creative Commons Attribution 3.0 Unported License.
 * 
 * http://creativecommons.org/licenses/by/3.0/deed.en_US
 * 
 * You are free to:
 * -To Share — to copy, distribute and transmit the work 
 * -To Remix — to adapt the work 
 * -To make commercial use of the work
 *
 * ========================================
 */

/* ========================================
 * CY8CKIT-042 LED RGB Driver Module
 * This module was designed to drive the RGB LEDs on the KIT-042 with pleasing
 * colors. This module requires that three 16- or 8-bit PWMs be placed and named
 * PWM_R, PWM_G, and PWM_B. Their outputs should be inverted because the LEDs on
 * the kit are sunk by the PSoC 4 GPIOs. LEDs are on P1[6], P0[2], P0[3] (RGB).
 * The PWMs should be clocked at a rate such that the output frequency is 45 Hz
 * or greater to avoid weird blinking.
 * ========================================
 */

#ifndef LED_RGB_H
#define LED_RGB_H

#include <device.h>

/* Maximum type sizes for variable and PWM duty cycle scaling */
#define UINT16_MAX              65535
#define UINT8_MAX               255

/* PWM resolution, in case someone wants to use 8 bit */
#define LED_RGB_PWM_RESOLUTION  16              

/* Constants for LED identification     */
#define LED_RED                 1u
#define LED_GREEN               2u
#define LED_BLUE                3u

/* Hue defines for easy color switching */
#define LED_RGB_HUE_RED         (uint16) 0
#define LED_RGB_HUE_ORANGE      (uint16) (((uint32)UINT16_MAX) * 1 / 12)
#define LED_RGB_HUE_YELLOW      (uint16) (((uint32)UINT16_MAX) * 2 / 12)
#define LED_RGB_HUE_YELLOWGREEN (uint16) (((uint32)UINT16_MAX) * 3 / 12)
#define LED_RGB_HUE_GREEN       (uint16) (((uint32)UINT16_MAX) * 4 / 12)
#define LED_RGB_HUE_TURQOISE    (uint16) (((uint32)UINT16_MAX) * 5 / 12)
#define LED_RGB_HUE_CYAN        (uint16) (((uint32)UINT16_MAX) * 6 / 12)
#define LED_RGB_HUE_BLUE        (uint16) (((uint32)UINT16_MAX) * 7 / 12)
#define LED_RGB_HUE_VIOLET      (uint16) (((uint32)UINT16_MAX) * 8 / 12)
#define LED_RGB_HUE_PURPLE      (uint16) (((uint32)UINT16_MAX) * 9 / 12)
#define LED_RGB_HUE_MAGENTA     (uint16) (((uint32)UINT16_MAX) * 10 / 12)
#define LED_RGB_HUE_SCARLET     (uint16) (((uint32)UINT16_MAX) * 11 / 12)

/* Defines to chop the UINT8 range up into 6 neat pieces for the color gamut */
#define UINT16_1_6TH_MAX        (uint16) (((uint32)UINT16_MAX) * 1 / 6)
#define UINT16_2_6TH_MAX        (uint16) (((uint32)UINT16_MAX) * 2 / 6)
#define UINT16_3_6TH_MAX        (uint16) (((uint32)UINT16_MAX) * 3 / 6)
#define UINT16_4_6TH_MAX        (uint16) (((uint32)UINT16_MAX) * 4 / 6)
#define UINT16_5_6TH_MAX        (uint16) (((uint32)UINT16_MAX) * 5 / 6)

/* Function prototypes */
void LED_RGB_Start(void);
void LED_RGB_Stop(void);
void LED_RGB_DCWrite(uint8 LED_Color, uint16 LED_NewDutyCycle);
void LED_RGB_SetColorRGB(uint16 redIntensity, uint16 greenIntensity, uint16 blueIntensity);
void LED_RGB_SetColorCircle(uint16 hue);
void LED_RGB_SetColorCircleHSV(uint16 hue, uint16 saturation, uint16 value);

#endif

//[] END OF FILE
