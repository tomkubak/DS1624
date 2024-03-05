#ifndef DS1624_H
#define DS1624_H

#include <Wire.h>
#include <esphome.h>

class DS1624 {
public:
  void setup();
  float readTemperature();
};

#endif
