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
        lcdWriteChar(0x57, 0, 1);
        __delay_ms(500);
        lcdWriteChar(0x58, 0, 1);
        __delay_ms(500);
        lcdWriteChar(0x59, 0, 1);
        __delay_ms(500);
        lcdWriteChar(0x5A, 0, 1);
        __delay_ms(500);
        
        lcdClear();
        
        __delay_ms(500);
        
    }
}