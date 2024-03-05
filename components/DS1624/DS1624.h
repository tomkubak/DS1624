#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ds1624 {

class DS1624 : public sensor::Sensor, public Component {
 public:
  void setup() override;
  void update() override;
  
 protected:
  float readTemperature();
};

}  // namespace ds1624
}  // namespace esphome
