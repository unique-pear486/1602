/* 
 * File:   lcd_i2c.h
 * Author: unique-pear468
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_I2C_H
#define	LCD_I2C_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

// I2C address of the LCD
#define LCD_ADDRESS     0x27
#define PIC_ADDRESS     0x02
#define _XTAL_FREQ      32000000

/**
    @Summary
        Initialises the lcd screen at given address

    @Description
        This sets the screen options to 4-bit mode, turns on the backlight,
        and clears and resets the screen

    @Preconditions
        None

    @Returns
        void

     @Example
        <code>
            lcd_initialize();
            lcdWriteString("Hello");

            uint8_t i = 0x20;
            while(1) {
                lcdWriteChar(i++, 0, 1);
                if(i >= 0x80) { i=0; }
                __delay_ms(1000)
        </code>

*/

void lcd_initialize(void);

/**
    @Summary
        Writes character to screen at point

    @Description
        Writes character to the screen at x, y.

    @Preconditions
        None

    @Param
        character - The character to write. 0x00-0x08 are custom characters,
            0x20-0x79 are ascii characters
    @Param
        x - The x location of the screen to write to. Range [0-15]
  
    @Param
        y - The y location of the screen to write to. Range [0-1]

    @Returns
        void

     @Example
        <code>
            See lcd_initialize()
        </code>

*/

void lcdWriteChar(uint8_t character, uint8_t x, uint8_t y);
//void lcdWriteChar(uint8_t character);

/**
    @Summary
        Writes a string to screen at point

    @Description
        Writes NULL-terminated string to the screen at x, y.

    @Preconditions
        None

    @Param
        string - The string to write.

    @Param
        x - The x location of the screen to write to. Range [0-15]
  
    @Param
        y - The y location of the screen to write to. Range [0-1]

    @Returns
        void

     @Example
        <code>
            See lcd_initialize()
        </code>

*/
void lcdWriteString(unsigned char *str, uint8_t x, uint8_t y);
//void lcdWriteString(unsigned char *str);

void lcdBacklight(void);
void lcdNoBacklight(void);

void lcdClear(void);

#endif	/* LCD_I2C_H */

