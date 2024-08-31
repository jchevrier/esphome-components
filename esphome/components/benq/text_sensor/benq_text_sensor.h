#pragma once

#include "esphome/core/component.h"
#include "esphome/components/benq/benq.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace benq {

class BenqTextSensor : public BenqGeneric<text_sensor::TextSensor> {
 public:
  void setup() override;
  void dump_config() override;
  void set_sensor_id(uint8_t sensor_id) { this->sensor_id_ = sensor_id; }
  void feed_command_back(std::string data) override;

 protected:
  uint8_t sensor_id_{0};
};

}  // namespace benq
}  // namespace esphome
