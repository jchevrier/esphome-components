#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/select/select.h"
#include "esphome/components/number/number.h"

namespace esphome {
namespace th575 {

class TuyaSelect : public select::Select, public Component {
 public:
  void setup() {};
  void dump_config() {};

  void set_select_id(uint8_t select_id) { this->select_id_ = select_id; }
  // void set_select_mappings(std::vector<uint8_t> mappings) { this->mappings_ = std::move(mappings); }

 protected:
   void control(const std::string &value) {};

  uint8_t select_id_;
  std::vector<uint8_t> mappings_;
};

class DemoSensor : public sensor::Sensor, public PollingComponent {
 public:
  void update() override {
    float val = random_float();
    bool increasing = this->get_state_class() == sensor::STATE_CLASS_TOTAL_INCREASING;
    if (increasing) {
      float base = std::isnan(this->state) ? 0.0f : this->state;
      this->publish_state(base + val * 10);
    } else {
      if (val < 0.1) {
        this->publish_state(NAN);
      } else {
        this->publish_state(val * 100);
      }
    }
  }
};
class DemoSwitch : public switch_::Switch, public Component {
 public:
  void setup() override {
    bool initial = random_float() < 0.5;
    this->publish_state(initial);
  }

 protected:
  void write_state(bool state) override { this->publish_state(state); }
};

class TH575 : public PollingComponent, public uart::UARTDevice {
 public:
  void loop() override;

  void update() override;
  void setup() override;
  void dump_config() override;
  
  void set_lamphours_sensor(sensor::Sensor *lamphours) {lamphours_ = lamphours;}
  void set_volume_number(number::Number *volume) {volume_ = volume;}
  void set_onoff_switch(switch_::Switch *onoff) {onoff_ = onoff;}

 protected:
  sensor::Sensor *lamphours_{nullptr};
  number::Number *volume_{nullptr};
  switch_::Switch *onoff_{nullptr};
};
class Volume: public number::Number, public Component {
 public:
  Volume() = default;

 protected:
  void control(float volume) override;
};

}  // namespace th575
}  // namespace esphome
