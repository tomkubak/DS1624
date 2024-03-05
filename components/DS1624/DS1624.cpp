#include "DS1624.h"

void DS1624::setup() {
  Wire.begin();
}

float DS1624::readTemperature() {
  Wire.beginTransmission(0x48);
  Wire.write(0xAA); // Command to start temperature conversion
  Wire.endTransmission();
  delay(20); // Wait for conversion to finish

  Wire.beginTransmission(0x48);
  Wire.write(0xAA); // Command to read temperature
  Wire.endTransmission();
  
  Wire.requestFrom(0x48, 2); // Request 2 bytes of temperature data
  if (Wire.available() >= 2) {
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    int16_t rawTemperature = (msb << 8) | lsb;
    if (rawTemperature & 0x8000) {
      rawTemperature = -(~rawTemperature + 1);
    }
    return rawTemperature * 0.0625; // Each bit represents 0.0625 degrees Celsius
  }
  return -1000; // Return an invalid value if reading failed
}
