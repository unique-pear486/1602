/*
 * File:   i2c.c
 * Author: unique-pear486
 *
 * Created on 5 January 2019, 2:55 PM
 */


#include <xc.h>
#include "i2c.h"

void i2cInit() {
    // Set SDA and SCL to inputs
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    
    // Set the registers
    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP High Speed; UA dontupdate; CKE disabled; D_nA lastbyte_address; 
    SSP1STAT = 0x00;
    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM I2C Master, FOSC/(4* (SSPADD+1)); SSPOV no_overflow; 
    SSP1CON1 = 0x28;
    // GCEN disabled; ACKSTAT not_received; ACKDT acknowledge; ACKEN idle; RCEN idle; PEN idle; RSEN idle, SEN idle;
    SSP1CON2 = 0x00;
    // ACKTIM ackseq; SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x00;
    // SSPADD 32Mhz / ((0x4F + 1) * 4) = 100kHz; 
    SSP1ADD = 0x4F;

    // Clear interrupt bits
    PIR1bits.SSP1IF = 0;
    PIR2bits.BCL1IF = 0;
    
}

__bit i2cWriteByte(uint8_t address, uint8_t data) {
    static __bit err = 0;
    // Reset interrupt
    PIR1bits.SSP1IF = 0;
    
    // Send start bit
    SSP1CON2bits.SEN = 1;
    
    // Wait for it to complete, then send the address
    while (PIR1bits.SSP1IF != 1) {}
    
    PIR1bits.SSP1IF = 0;
    SSP1BUF = address << 1;
    
    // Wait for it to complete, then check if ACK'ed
    while (PIR1bits.SSP1IF != 1) {}
    
    if (SSP1CON2bits.ACKSTAT == 1) {
        // There was no acknowledge; reset and abort
        SSP1CON2bits.ACKSTAT = 0;
        PIR1bits.SSP1IF = 0;
        
        err = 1;
        goto STOP;
    }
    
    SSP1CON2bits.ACKSTAT = 0;
    PIR1bits.SSP1IF = 0;
    
    SSP1BUF = data;
    while (PIR1bits.SSP1IF != 1) {}
    if (SSP1CON2bits.ACKSTAT == 1) {
        // There was no acknowledge; reset and abort
        SSP1CON2bits.ACKSTAT = 0;
        err = 1;
    }
    
STOP:
    // Send Stop bit and return error status
    PIR1bits.SSP1IF = 0;    
    SSP1CON2bits.PEN = 1;
    while (PIR1bits.SSP1IF != 1) {}
    return err;
}

__bit i2cWrite(uint8_t address, uint8_t n, uint8_t *data) {    
    static __bit err = 0;
    // Reset interrupt
    PIR1bits.SSP1IF = 0;
    
    // Send start bit
    SSP1CON2bits.SEN = 1;
    
    // Wait for it to complete, then send the address
    while (PIR1bits.SSP1IF != 1) {}
    
    PIR1bits.SSP1IF = 0;
    SSP1BUF = address << 1;
    
    // Wait for it to complete, then check if ACK'ed
    while (PIR1bits.SSP1IF != 1) {}
    
    if (SSP1CON2bits.ACKSTAT == 1) {
        // There was no acknowledge; reset and abort
        SSP1CON2bits.ACKSTAT = 0;
        PIR1bits.SSP1IF = 0;
        
        err = 1;
        goto STOP;
    }
    
    // Send data
    while(n > 0) {
        SSP1CON2bits.ACKSTAT = 0;
        PIR1bits.SSP1IF = 0;

        SSP1BUF = *data;
        while (PIR1bits.SSP1IF != 1) {}
        if (SSP1CON2bits.ACKSTAT == 1) {
            // There was no acknowledge; reset and abort
            SSP1CON2bits.ACKSTAT = 0;
            err = 1;
            goto STOP;
        }
        data++;
        n--;
    }
    
STOP:
    // Send Stop bit and return error status
    PIR1bits.SSP1IF = 0;    
    SSP1CON2bits.PEN = 1;
    while (PIR1bits.SSP1IF != 1) {}
    return err;
}

uint8_t i2cReadByte(uint8_t address) {
    return 0;
}
