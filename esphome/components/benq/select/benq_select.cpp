#include "benq_select.h"
#include "esphome/core/log.h"

namespace esphome {
namespace benq {

static const char *const TAG = "benq.select";

void BenqSelect::feed_command_back(std::string &data) {
  this->publish_state(data);
}
void BenqSelect::setup() {
  this->parent_->register_command(this->command_, this);
}
void BenqSelect::control(const std::string &value) {
  auto myCmd = this->command_ + "=" + value;
  this->parent_->send_command(myCmd);
};
void BenqSelect::dump_config() {
  LOG_SELECT(TAG, "Benq select", this);
}
}  // namespace Benq
}  // namespace esphome
