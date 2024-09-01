#pragma once

#include "esphome/core/component.h"
#include "esphome/components/benq/benq.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace benq {

class BenqSwitch : public BenqGeneric<switch_::Switch> {
 public:
  //TODO
  void setup() override;
  void dump_config() override;
  void set_switch_id(uint8_t switch_id) { this->switch_id_ = switch_id; }
  void set_on_value(std::string on) { this->on_ = on; }
  void set_off_value(std::string off) { this->off_ = off; }
  void feed_command_back(std::string &data) override;
  void set_repeat_off_value(bool repeat) { this->repeat_off_ = repeat; }

 protected:
  void write_state(bool state) override;

  uint8_t switch_id_{0};
  std::string on_, off_;
  bool repeat_off_;
};

}  // namespace benq
}  // namespace esphome
