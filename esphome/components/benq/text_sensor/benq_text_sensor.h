#pragma once

#include "esphome/core/component.h"
#include "esphome/components/benq/benq.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace benq {

class BenqTextSensor : public text_sensor::TextSensor, public Component, public BenqCallback {
 public:
  void setup() override;
  void dump_config() override;
  void set_sensor_id(uint8_t sensor_id) { this->sensor_id_ = sensor_id; }
  void feed_command_back(std::string data) override;
  void set_benq_parent(Benq *parent) { this->parent_ = parent; }
  void set_benq_command(std::string cmd) { this->command_ = cmd; }

 protected:
  Benq *parent_;
  uint8_t sensor_id_{0};
  std::string command_;
};

}  // namespace benq
}  // namespace esphome
