#ifndef DS1624_H
#define DS1624_H

#include "esphome.h"

class MyDS1624Sensor : public PollingComponent, public Sensor {
 public:
  MyDS1624Sensor() : PollingComponent(15000) {}

  void setup() override {
    Wire.begin();
  }

  void update() override {
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
      float temperature = convertTemperature(msb, lsb);
      publish_state(temperature);
    }
  }

  float convertTemperature(uint8_t msb, uint8_t lsb) {
    int16_t rawTemperature = (msb << 8) | lsb;
    if (rawTemperature & 0x8000) {
      rawTemperature = -(~rawTemperature + 1);
    }
    return rawTemperature * 0.0625; // Each bit represents 0.0625 degrees Celsius
  }
};

#endif
