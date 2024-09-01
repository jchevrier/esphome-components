#include "esphome/core/log.h"
#include "benq_sensor.h"
#include <system_error>

namespace esphome {
namespace benq {

static const char *const TAG = "benq.sensor";

void BenqSensor::setup() {
  parent_->register_command(this->command_, this);
}

void BenqSensor::feed_command_back(std::string &data) {
  if (data.empty())
    return;

  char* ptr;
  float val = strtof(data.c_str(), &ptr);
  if ((*ptr) != '\0')
    return;
  this->publish_state(val);
}
void BenqSensor::dump_config() {
  LOG_SENSOR("", "Benq sensor", this);
  ESP_LOGCONFIG(TAG, "  Sensor has datapoint ID %u", this->sensor_id_);
}

}  // namespace benq
}  // namespace esphome
