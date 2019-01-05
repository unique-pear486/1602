/*
 * File:   lcd_i2c.c
 * Author: unique-pear468
 *
 * Created on January 5, 2019, 11:33 AM
 */


#include <xc.h>
#include "i2c.h"
#include "lcd_i2c.h"

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
    lcdSendCommand(0x33);
    __delay_ms(5);
    lcdSendNibble(0x30);
    __delay_ms(5);
    lcdSendNibble(0x20);
    __delay_ms(5);
    lcdSendCommand(0x28);
    lcdSendCommand(0x0C);
    lcdSendCommand(0x06);
    lcdSendCommand(0x01);
}

void lcdSendCommand(uint8_t command) {
    RS = 0x00;
    lcdSendNibble(command);
    lcdSendNibble(command << 4);
    __delay_ms(1);          // need to wait for previous command to finish, we just brute-force wait 1ms
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
    i2cWrite(LCD_ADDRESS, data);
}

void lcdBacklight() {
    BK = LCD_BACKLIGHT;
    lcdSendData(0);
}

void lcdNoBacklight() {
    BK = LCD_NOBACKLIGHT;
    lcdSendData(0);
}

void lcdWriteChar(uint8_t character, uint8_t x, uint8_t y) {
//    uint8_t a = 0x80;
//    if (y > 0) {
//        a = 0xC0;
//    }
//    a += x;
//    lcdSendCommand(a);
    lcdSendData(character);
}

void lcdClear(void) {
    lcdSendCommand(0x01);
}