/*
 * File:   lcd_i2c.c
 * Author: unique-pear468
 *
 * Created on January 5, 2019, 11:33 AM
 */


#include <xc.h>
#include "i2c.h"
#include "lcd_i2c.h"

// Command for LCD
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for backlight Control
#define LCD_BACKLIGHT   0x08
#define LCD_NOBACKLIGHT 0x00

// Bits
#define En      0b00000100
#define Rw      0b00000010
#define Rs      0b00000001

// LCD globals
static uint8_t RS;
static uint8_t BK;

// private functions
void lcdSendCommand(uint8_t);
void lcdSendData(uint8_t);
void lcdSendNibble(uint8_t);
inline void lcdExpanderWrite(uint8_t);

void lcd_initialize() {
    BK = LCD_BACKLIGHT;
    
    i2cInit();
    __delay_ms(50);         // need to wait at least 37ms from 5V rail
    lcdSendCommand(0x33);   // Complicated bit to transition to 4-bit mode
    __delay_ms(5);
    lcdSendNibble(0x30);
    __delay_ms(5);
    lcdSendNibble(0x20);
    __delay_ms(5);
    lcdSendCommand(0x28);   // Set 4-bit, 2 line, 5x8 Characters
    lcdSendCommand(0x0C);   // Turn the display on, cursor and blink off
    lcdSendCommand(0x06);   // Left-to-right, static display (moving cursor)
    lcdClear();             // Clear the screen
}

void lcdSendCommand(uint8_t command) {
    RS = 0x00;
    lcdSendNibble(command);
    lcdSendNibble(command << 4);
}

void lcdSendData(uint8_t command) {
    RS = Rs;
    lcdSendNibble(command);
    lcdSendNibble(command << 4);
}

void lcdSendNibble(uint8_t data) {
    uint8_t d = data & 0xF0;
    d |= BK;
    d |= RS;
    lcdExpanderWrite(d);
    lcdExpanderWrite(d | En);
    __delay_us(1);              // line must be held high > 450ns
    lcdExpanderWrite(d & ~En);
    __delay_us(50);             // command need >37us to settle
};

void lcdExpanderWrite(uint8_t data) {
    // initiate the I2C write
    i2cWriteByte(LCD_ADDRESS, data);
}

void lcdBacklight() {
    BK = LCD_BACKLIGHT;
    lcdSendData(0);
}

void lcdNoBacklight() {
    BK = LCD_NOBACKLIGHT;
    lcdSendData(0);
}

void lcdSetCursor(uint8_t x, uint8_t y) {
    // DRAM Layout
    //
    // Before shifting:
    // |=================|==============================|
    // |Display Position | 01 | 02 | 03 | ... | 15 | 16 |
    // |=================|==============================|
    // |  DRAM Position  | 00 | 01 | 02 | ... | 0E | 0F |
    // |                 | 40 | 41 | 42 | ... | 4E | 4F |
    // |=================|==============================|
    //
    // After left shift:
    // |=================|==============================|
    // |Display Position | 01 | 02 | 03 | ... | 15 | 16 |
    // |=================|==============================|
    // |  DRAM Position  | 01 | 02 | 03 | ... | 0F | 10 |
    // |                 | 41 | 42 | 43 | ... | 4F | 50 |
    // |=================|==============================|
    //
    // After right shift:
    // |=================|==============================|
    // |Display Position | 01 | 02 | 03 | ... | 15 | 16 |
    // |=================|==============================|
    // |  DRAM Position  | 27 | 00 | 01 | ... | 0D | 0E |
    // |                 | 67 | 40 | 41 | ... | 4D | 4E |
    // |=================|==============================|

    uint8_t cmd = 0x80;     // Set DRAM address
    if (y > 0) {
        cmd |= 0x40;         // Second row starts at 0x40
    }
    cmd += x;
    lcdSendCommand(cmd);
}

void lcdWriteChar(uint8_t character) {

    lcdSendData(character);
}

void lcdClear(void) {
    lcdSendCommand(LCD_CLEARDISPLAY);
    __delay_ms(1);
}

void lcdWriteString(unsigned char *str) {
    while(*str != 0) {
        lcdWriteChar(*str);
        str++; 
    }
}

void lcdLoadCustomChar(uint8_t location, uint8_t data[]) {
    lcdSendCommand(LCD_SETCGRAMADDR | (location << 3));   //
    for (int i=0; i<8; i++) {
        lcdSendData(data[i]);
    }
}