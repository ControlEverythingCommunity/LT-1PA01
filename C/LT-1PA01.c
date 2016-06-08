// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LT-1PA01
// This code is designed to work with the LT-1PA01_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, LT-1PA01 I2C address is 0x44(68)
	ioctl(file, I2C_SLAVE, 0x44);

	// Select config0 register(0x01)
	// Proximity enable, Sleep time = 100 ms(0x28)
	char config[2] = {0};
	config[0] = 0x01;
	config[1] = 0x28;
	write(file, config, 2);
	// Select config1 register(0x02)
	// Ambient Light Sensing enable, Range = 2000 lux(0x07)
	config[0] = 0x02;
	config[1] = 0x07;
	write(file, config, 2);
	sleep(1);

	// Read 3 bytes of data from register(0x0A)
	// proximity lsb, proximity msb
	char reg[1] = {0x0A} ;
	write(file, reg, 1);
	char data[3] = {0};
	if(read(file, data, 3) != 3)
	{
		printf("Erorr : Input/output Erorr \n");
	}
	else
	{
		// Convert the data
		int proximity = data[0];
		int luminance = (data[1] * 256 + data[2]);

		// Output data to screen
		printf("Ambient Light Luminance : %d lux \n", luminance);
		printf("Proximity of the Device : %d \n", proximity);
	}
}
