#pragma once

#include "esphome/core/component.h"
#include "esphome/components/benq/benq.h"
#include "esphome/components/sensor/sensor.h"

#include <vector>

namespace esphome {
namespace benq {

class BenqSensor : public Component, public sensor::Sensor, public BenqCallback {
 public:
  void setup() override;
  void dump_config() override;
  void feed_command_back(std::string data) override;
  void set_benq_command(std::string cmd) { this->command_ = cmd; }

  void set_sensor_id(uint8_t sensor_id) { this->sensor_id_ = sensor_id; }

  void set_benq_parent(Benq *parent) { this->parent_ = parent; }

 protected:
  Benq *parent_;
  uint8_t sensor_id_;
  std::string command_, on_, off_;
};

}  // namespace benq
}  // namespace esphome
