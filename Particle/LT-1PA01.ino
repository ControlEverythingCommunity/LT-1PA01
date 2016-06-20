// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LT-1PA01
// This code is designed to work with the LT-1PA01_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// LT-1PA01 I2C address is 0x44(68)
#define Addr 0x44

int proximity = 0;
int luminance = 0;

void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "LT-1PA01");
  Particle.variable("proximity", proximity);
  Particle.variable("luminance", luminance);

  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select config0 register, 0x01(01)
  Wire.write(0x01);
  // Proximity enable, Sleep time = 100 ms
  Wire.write(0x28);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select config1 register, 0x02(02)
  Wire.write(0x02);
  // Ambient Light Sensing enable, Range = 2000 lux
  Wire.write(0x07);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[3];

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x0A);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 3 bytes of data
  Wire.requestFrom(Addr, 3);

  // Read 3 bytes of data
  if (Wire.available() == 3)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
  }

  // Convert the data
  proximity = data[0];
  luminance = data[1] * 256 + data[2];

  // Output data to dashboard
  Particle.publish("Proximity of the Device : ", String(proximity));
  delay(1000);
  Particle.publish("Ambient Light Luminance : ", String(luminance));
  delay(1000);
}
