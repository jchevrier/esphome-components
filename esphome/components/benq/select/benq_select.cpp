#include "benq_select.h"
#include "esphome/core/log.h"

namespace esphome {
namespace benq {

static const char *const TAG = "benq.select";

void BenqSelect::feed_command_back(std::string data) {
  ESP_LOGD("benq", "data: %s", data.c_str());
  this->publish_state(data);
}
void BenqSelect::setup() {
  parent_->register_command(this->command_, this);
}
void BenqSelect::dump_config() {
  LOG_SELECT(TAG, "Benq select", this);
}
}  // namespace Benq
}  // namespace esphome
