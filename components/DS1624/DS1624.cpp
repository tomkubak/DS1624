#include "DS1624.h"
#include <Wire.h>

static const char *TAG = "ds1624";

void DS1624::setup() {
  i2c_ = App.get_component<I2CComponent>();
  if (!i2c_) {
    ESP_LOGW(TAG, "I2C not found!");
    return;
  }
}

void DS1624::loop() {
  if (!i2c_) {
    ESP_LOGW(TAG, "I2C not found!");
    return;
  }

  if (!_initialized) {
    init();
  }

  temperature_ = read_converted_value();
  temperature_valid_ = true; // Assuming always valid
  ESP_LOGD(TAG, "Temperature: %.2f °C", temperature_);

  delay(1000); // Adjust delay as needed
}

void DS1624::init() {
  // Start I2C communication on default SCK, SDA ports for I2C master
  Wire.begin();

  // Configure sensor
  Wire.beginTransmission(address_);
  // Command "Access config"
  Wire.write(0xAC);
  // lsb of configuration register is ONESHOT bit. Set it to zero to enable continuous conversion
  Wire.write(0x00);
  Wire.endTransmission();

  // Minimum time needed to store the configuration is 10ms
  // So wait for 100ms
  delay(100);

  // Set initialization flag
  _initialized = true;

  // Start conversion
  Wire.beginTransmission(address_);
  Wire.write(0xEE);
  Wire.endTransmission();
}

float DS1624::read_converted_value() {
  uint8_t msw = 0;
  uint8_t lsw = 0;

  // Request to read last converted temperature value
  Wire.beginTransmission(address_);
  Wire.write(0xAA);
  Wire.requestFrom(address_, (uint8_t)2);

  // Read most significant word
  if (Wire.available()) {
    msw = Wire.read();
  }

  // Read least significant word
  if (Wire.available()) {
    lsw = Wire.read();
  }

  // End transmission
  Wire.endTransmission();

  // If negative temperature, apply two's complement
  if (msw & 0x80) {
    msw = ~msw + 0x01;
    lsw = ~lsw + 0x01;
  }

  // Decimal part of the temperature is stored on 4 most significant bits
  // of the lsw value, so shift right 4 bits
  lsw >>= 4;

  // Convert to float and handle negative numbers
  float temperature = (float)msw;
  temperature += ((float)lsw) / 16.0;
  return temperature;
}
