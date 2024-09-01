#include "benq_text_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace benq {

static const char *const TAG = "benq.text_sensor";

void BenqTextSensor::setup() {
  parent_->register_command(this->command_, this);
}

void BenqTextSensor::feed_command_back(std::string &data) {
  this->publish_state(data);
}
void BenqTextSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Benq Text Sensor:");
  ESP_LOGCONFIG(TAG, "  Text Sensor has datapoint ID %u", this->sensor_id_);
}

}  // namespace benq
}  // namespace esphome
