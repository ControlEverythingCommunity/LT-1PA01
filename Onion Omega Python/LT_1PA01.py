# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# LT-1PA01
# This code is designed to work with the LT-1PA01_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# LT-1PA01 address, 0x44(68)
# Select config0 register, 0x01(01)
#		0x28(40)	Proximity enable, Sleep time = 100 ms
i2c.writeByte(0x44, 0x01, 0x28)
# LT-1PA01 address, 0x44(68)
# Select config1 register, 0x02(02)
#		0x07(07)	Ambient Light Sensing enable, Range = 2000 lux
i2c.writeByte(0x44, 0x02, 0x07)

time.sleep(0.5)

# LT-1PA01 address, 0x44(68)
# Read data back from 0x0A(10), 3 bytes
# proximity, luminance MSB, luminance LSB
data = i2c.readBytes(0x44, 0x0A, 3)

# Convert the data
proximity = data[0]
luminance = data[1] * 256 + data[2]

# Output data to screen
print "Ambient Light Luminance : %d lux" %luminance
print "Proximity of the Device : %d" %proximity
