#include "DS1624.h"
#include <Wire.h>

namespace esphome {
namespace ds1624 {

void DS1624::setup() {
  Wire.begin(); // Inicializace I2C
}

void DS1624::update() {
  float temperature = readTemperature();
  publish_state(temperature);
}

float DS1624::readTemperature() {
  Wire.beginTransmission(0x48); // Adresa čipu DS1624 na I2C sběrnici
  Wire.write(0xAA); // Příkaz pro spuštění konverze teploty
  Wire.endTransmission();
  delay(20); // Čekání na dokončení konverze

  Wire.beginTransmission(0x48);
  Wire.write(0xAA); // Příkaz pro čtení teploty
  Wire.endTransmission();
  
  Wire.requestFrom(0x48, 2); // Požadavek na čtení 2 bytů teplotních dat
  if (Wire.available() >= 2) {
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    int16_t raw_temperature = (msb << 8) | lsb;
    if (raw_temperature & 0x8000) {
      raw_temperature = -(~raw_temperature + 1);
    }
    return raw_temperature * 0.0625; // Každý bit reprezentuje 0.0625 stupně Celsia
  }
  return NAN; // Pokud se nepodaří přečíst teplotu, vrátíme NAN
}

}  // namespace ds1624
}  // namespace esphome
