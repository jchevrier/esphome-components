#include "benq_switch.h"
#include "esphome/core/log.h"

namespace esphome {
namespace benq {

static const char *const TAG = "benq.switch";

void BenqSwitch::write_state(bool state) {
  auto new_state = state ? this->on_ : this->off_;

  std::transform(new_state.begin(), new_state.end(), new_state.begin(),
                 [](unsigned char c){ return std::tolower(c); });
  std::string cmd = this->command_ + "=" + new_state ;
  parent_->send_command(cmd);
  if(!state && this->repeat_off_) {
    parent_->send_command(cmd);
  }
}

void BenqSwitch::feed_command_back(std::string data) {
  ESP_LOGD("benq", "data: %s", data.c_str());
  if(data.compare(this->on_) == 0) {
    this->publish_state(true);
  }
  if(data.compare(this->off_) == 0) {
    this->publish_state(false);
  }
}
void BenqSwitch::setup() {
  parent_->register_command(this->command_, this);
}
void BenqSwitch::dump_config() {
  LOG_SWITCH(TAG, "Benq switch", this);
}
}  // namespace Benq
}  // namespace esphome
