/*
 * Atmega328p_I2C_Slave_Read.c
 *
 * Created: 2/25/19 1:25:51 PM
 * Author : Ahmed El-Torky
 */ 

#define F_CPU 8000000ul

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char slaveAddress = 0b00000110; // slave address is 0000011 and doesn't accept the general call


int main(void)
{
	DDRD = 0x00; // set port D as input port
	// I2C initialization as Slave
	TWAR = slaveAddress; // write slave address into slave address register
	TWCR |= (1 << TWIE); // enable i2c interrupt
	sei(); // set global interrupt
	TWCR |= (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // start i2c and wait to addressed by the master 
	
    while (1) 
    {
		// polling technique
		/*
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		while (!(TWCR & (1 << TWINT)));
		TWDR = PIND;
		TWCR = (1 << TWINT) | (1 << TWEN);
		while (!(TWCR & (1 << TWINT)));
		*/
    }
}

ISR (TWI_vect) {
	TWDR = PIND;
	TWCR |= (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
}