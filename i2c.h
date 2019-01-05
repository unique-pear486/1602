/* 
 * File:   i2c.h
 * Author: unique-pear468
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef I2C_H
#define	I2C_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void i2cInit(void);
__bit i2cWrite(uint8_t address, uint8_t data);
uint8_t i2cRead(uint8_t address);

#endif	/* I2C_H */

