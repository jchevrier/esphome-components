#include "benq_number.h"
#include "esphome/core/log.h"

namespace esphome {
namespace benq {

static const char *const TAG = "benq.number";

void BenqNumber::feed_command_back(std::string data) {
  ESP_LOGD(TAG, "data: %s", data.c_str());
  if (data.empty())
    return;

  char* ptr;
  float val = strtof(data.c_str(), &ptr);
  if ((*ptr) != '\0')
    return;
  this->publish_state(val);
}

void BenqNumber::control(float value) {
  parent_->send_command(command_ + "=" + std::to_string(value));
}
void BenqNumber::setup() {
  parent_->register_command(this->command_, this);
}
void BenqNumber::dump_config() {
  LOG_NUMBER(" ", "Benq projector number", this);
}
}  // namespace Benq
}  // namespace esphome
