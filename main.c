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
    lcd_initialize(); 
    TRISAbits.TRISA5 = 0;
    
    while(1) {
        lcdBacklight();
        LATAbits.LATA5 = 1;
        __delay_ms(500);
        lcdNoBacklight();
        LATAbits.LATA5 = 0;
        __delay_ms(500);        
    }
//    // Write hello
//    lcdWriteString("Hello");
//
//    // rotate through the characters on the second line
//    int i = 0x20;
//    while (1) {
//        lcdWriteChar(i++, 0, 1);
//        if (i >= 0x80) { i=0; }
//        
//        __delay_ms(1000);
//        
//    }
}