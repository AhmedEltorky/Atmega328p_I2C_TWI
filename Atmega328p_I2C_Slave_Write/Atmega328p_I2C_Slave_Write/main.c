/*
 * Atmega328p_I2C_Slave_Write.c
 *
 * Created: 2/25/19 3:39:31 PM
 * Author : Ahmed El-Torky
 */ 

#define F_CPU 8000000ul
#include <avr/io.h>

unsigned char slaveAddress = 0b00000010; // slave address is 0000011 and doesn't accept the general call


int main(void)
{
	DDRD = 0xFF; // set port D as output
	// I2C initialization as Slave
	TWAR = slaveAddress;  // write slave address into slave address register
	
    while (1) 
    {
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // start i2c and enable acknowledge 
		while (!(TWCR & (1 << TWINT))); // wait for master addressing
		
		TWCR = (1 << TWINT) | (1 << TWEN); // start i2c
		while (!(TWCR & (1 << TWINT))); // wait for master data
		PORTD = ~TWDR; // write data to port D
    }
}
