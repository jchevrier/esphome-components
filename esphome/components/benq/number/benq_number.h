#pragma once

#include "esphome/core/component.h"
#include "esphome/components/benq/benq.h"
#include "esphome/components/number/number.h"
#include "esphome/core/optional.h"

namespace esphome {
namespace benq {

class BenqNumber : public number::Number, public Component, public BenqCallback {
 public:
  void setup() override;
  void dump_config() override;
  void set_number_id(uint8_t number_id) { this->number_id_ = number_id; }

  void set_benq_command(std::string cmd) { this->command_ = cmd; }
  void feed_command_back(std::string data) override;
  void set_benq_parent(Benq *parent) { this->parent_ = parent; }

 protected:
  void control(float value) override;

  Benq *parent_;
  uint8_t number_id_{0};
  std::string command_;
};

}  // namespace benq
}  // namespace esphome

