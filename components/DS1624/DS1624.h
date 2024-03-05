#pragma once

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/components/i2c/i2c.h"

class DS1624 : public Component {
public:
  void set_address(uint8_t address) { address_ = address; }

  void setup() override;
  void loop() override;

  float get_temperature() const { return temperature_; }
  bool is_valid() const { return temperature_valid_; }

protected:
  I2CComponent *i2c_;
  uint8_t address_;
  float temperature_{0.0};
  bool temperature_valid_{false};

  void init();
  float read_converted_value();
};
