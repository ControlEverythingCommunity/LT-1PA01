// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LT-1PA01
// This code is designed to work with the LT-1PA01_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class LT_1PA01
{
	public static void main(String args[]) throws Exception
	{
		// Create I2CBus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, LT_1PA01 I2C address is 0x44(68)
		I2CDevice device = bus.getDevice(0x44);

		// Select config0 register, 0x01(01)
		// Proximity enable, Sleep time = 100 ms
		device.write(0x01, (byte)0x28);
		// Select config1 register, 0x02(02)
		// Ambient Light Sensing enable, Range = 2000 lux
		device.write(0x02, (byte)0x07);

		// Read 3 bytes of data
		// proximity, luminance msb, luminance lsb
		byte[] data = new byte[3];
		device.read(0x0A, data, 0, 3);

		// Convert the data
		int proximity = (data[0] & 0xFF);
		int luminance = ((data[1] & 0xFF) * 256) + (data[2] & 0xFF);

		// Output data to screen
		System.out.printf("Ambient Light Luminance : %d lux %n", luminance);
		System.out.printf("Proximity of the Device : %d %n", proximity);
	}
}