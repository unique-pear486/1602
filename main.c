/**
  Main Source File

  File Name:
    main.c

  Summary:
    This is a test program that displays "Hello World" on a 16x2 Character
    display, connected over I2C

  Description:
 
*/

#include "mcc_generated_files/mcc.h"
#include "lcd_i2c.h"

const uint8_t SYM_C[8]      = {0x1F, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x1F};
const uint8_t SYM_L[8]      = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x1F};
const uint8_t SYM_BACK_L[8] = {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x1F, 0x1F};
const uint8_t SYM_r[8]      = {0x1F, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
const uint8_t SYM_BACK_r[8] = {0x1F, 0x1F, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03};
const uint8_t SYM_L_LINE[8] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
const uint8_t SYM_R_LINE[8] = {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03};
const uint8_t SYM_R_BRAC[8] = {0x18, 0x1C, 0x06, 0x06, 0x06, 0x06, 0x1C, 0x18};
const uint8_t SYM_SLASH[8]  = {0x01, 0x03, 0x07, 0x0F, 0x1E, 0x1C, 0x18, 0x10};
const uint8_t SYM_BSLASH[8] = {0x10, 0x18, 0x1C, 0x1E, 0x0F, 0x07, 0x03, 0x01};
const uint8_t SYM_TOP_BOT[8] = {0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F};
const uint8_t SYM_BOT[8]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x1E};

void draw_blue(void) {
    // Program characters needed
    lcdLoadCustomChar(0, SYM_C);
    lcdLoadCustomChar(1, SYM_R_BRAC);
    lcdLoadCustomChar(2, SYM_L_LINE);
    lcdLoadCustomChar(3, SYM_R_LINE);
    lcdLoadCustomChar(4, SYM_L);
    lcdLoadCustomChar(5, SYM_BOT);
    lcdLoadCustomChar(6, SYM_BACK_L);
    lcdLoadCustomChar(7, SYM_TOP_BOT);

    // Write line one
    lcdSetCursor(4, 0);
    lcdWriteChar(0x00);
    lcdWriteChar(0x01);
    lcdWriteChar(0x02);
    lcdSetCursor(8, 0);
    lcdWriteChar(0x02);
    lcdWriteChar(0x03);
    lcdWriteChar(0x00);
    lcdWriteChar(0x07);

    // Write line two
    lcdSetCursor(4, 1);
    lcdWriteChar(0x00);
    lcdWriteChar(0x01);
    lcdWriteChar(0x04);
    lcdWriteChar(0x05);
    lcdWriteChar(0x04);
    lcdWriteChar(0x06);
    lcdWriteChar(0x00);
    lcdWriteChar(0x07);
}

void draw_white(void) {
    // Program characters needed
    lcdLoadCustomChar(0, SYM_C);
    lcdLoadCustomChar(1, SYM_L_LINE);
    lcdLoadCustomChar(2, SYM_R_LINE);
    lcdLoadCustomChar(3, SYM_TOP_BOT);
    lcdLoadCustomChar(4, SYM_r);
    lcdLoadCustomChar(5, SYM_BACK_r);
    lcdLoadCustomChar(6, SYM_BSLASH);
    lcdLoadCustomChar(7, SYM_SLASH);
    

    // Write line one
    lcdSetCursor(3, 0);
    lcdWriteChar(0x01);
    lcdWriteChar(0x02);
    lcdWriteChar(0x01);
    lcdWriteChar(0x02);
    lcdWriteChar(0x02);
    lcdWriteChar(0x01);
    lcdWriteChar(0x05);
    lcdWriteChar(0x04);
    lcdWriteChar(0x00);
    lcdWriteChar(0x03);

    // Write line two
    lcdSetCursor(3, 1);
    lcdWriteChar(0x07);
    lcdWriteChar(0x06);
    lcdWriteChar(0x04);
    lcdWriteChar(0x05);
    lcdWriteChar(0x02);
    lcdWriteChar(0x01);
    lcdWriteChar(0x02);
    lcdWriteChar(0x01);
    lcdWriteChar(0x00);
    lcdWriteChar(0x03);
}

void main(void) {
    // initialize the device
    SYSTEM_Initialize();
    __delay_ms(100);
    lcd_initialize(); 
    TRISAbits.TRISA5 = 0;
    
    /*
    while(1) {
        lcdBacklight();
        LATAbits.LATA5 = 1;
        __delay_ms(500);
        lcdNoBacklight();
        LATAbits.LATA5 = 0;
        __delay_ms(500);        
    }
    */
    // Write hello
    //lcdWriteString("Hello");

    // rotate through the characters on the second line
    int i = 0;
    while (1) {
        lcdSetCursor(0,0);
        lcdWriteString("Ready?");
        __delay_ms(500);
        lcdWriteChar('.');
        __delay_ms(500);
        lcdWriteChar('.');
        __delay_ms(500);
        lcdWriteChar('.');
        __delay_ms(500);
        lcdClear();
        draw_blue();        
        __delay_ms(500);
        lcdClear();
        draw_white();
        __delay_ms(500);
        lcdClear();
        __delay_ms(5000);
        
    }
}