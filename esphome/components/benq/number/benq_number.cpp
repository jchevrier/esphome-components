#include "benq_number.h"
#include "esphome/core/log.h"

namespace esphome {
namespace benq {

static const char *const TAG = "benq.number";

void BenqNumber::feed_command_back(std::string &data) {
  if (data.empty())
    return;

  char* ptr;
  float val = strtof(data.c_str(), &ptr);
  if ((*ptr) != '\0')
    return;
  this->publish_state(val);
}

void BenqNumber::control(float value) {
  auto myCmd = this->command_ + "=" + std::to_string(int(value));
  this->parent_->send_command(myCmd);
}
void BenqNumber::setup() {
  parent_->register_command(this->command_, this);
}
void BenqNumber::dump_config() {
  LOG_NUMBER(" ", "Benq projector number", this);
}
}  // namespace Benq
}  // namespace esphome
