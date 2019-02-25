/*
 * Atmega328p_I2C_MASTER.c
 *
 * Created: 2/25/19 1:37:55 AM
 * Author : Ahmed El-Torky
 */ 

#define F_CPU 8000000ul
#include <avr/io.h>
#include <util/delay.h>

void i2c_start (void);
void i2c_write (unsigned char data);
unsigned char i2c_read (void);
void i2c_stop (void);

unsigned char slaveWriteAddress = 0b00000010; // SLA + R/W : slave address is 0000001 and write 0
unsigned char slaveReadAddress = 0b00000111; // SLA + R/W : slave address is 0000011 and read 1

int main(void)
{
	// I2C initialization as Master
	TWSR &= ~(1 << TWPS0) & ~(1 << TWPS1); // set prescaler to zero
	TWBR = 0x47; // SCL freq. is 50K for F_CPU = 8M
	
	unsigned char oldData = 0;
	
    while (1) 
    {
		unsigned char data;
		// read data from read slave
		i2c_start();
		i2c_write(slaveReadAddress);
		data = i2c_read();
		i2c_stop();

		if (data != oldData) {
			i2c_start();
			i2c_write(slaveWriteAddress);
			i2c_write(data);
			i2c_stop();
			oldData = data;
		}		
		
		_delay_ms(100);
    }
}

void i2c_start (void) {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

void i2c_write (unsigned char data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));	
}

unsigned char i2c_read (void) {
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

void i2c_stop (void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}
