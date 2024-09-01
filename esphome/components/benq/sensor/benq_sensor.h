#pragma once

#include "esphome/core/component.h"
#include "esphome/components/benq/benq.h"
#include "esphome/components/sensor/sensor.h"

#include <vector>

namespace esphome {
namespace benq {

class BenqSensor : public BenqGeneric<sensor::Sensor> {
 public:
  void setup() override;
  void dump_config() override;
  void feed_command_back(std::string &data) override;

  void set_sensor_id(uint8_t sensor_id) { this->sensor_id_ = sensor_id; }


 protected:
  uint8_t sensor_id_;
};

}  // namespace benq
}  // namespace esphome
