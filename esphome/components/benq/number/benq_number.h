#pragma once

#include "esphome/core/component.h"
#include "esphome/components/benq/benq.h"
#include "esphome/components/number/number.h"
#include "esphome/core/optional.h"

namespace esphome {
namespace benq {

class BenqNumber : public BenqGeneric<number::Number> {
 public:
  void setup() override;
  void dump_config() override;
  void set_number_id(uint8_t number_id) { this->number_id_ = number_id; }
  void feed_command_back(std::string &data) override;

 protected:
  void control(float value) override;

  uint8_t number_id_{0};
};

}  // namespace benq
}  // namespace esphome

