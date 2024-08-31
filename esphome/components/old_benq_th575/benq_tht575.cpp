#include "benq_th575.h"
#include "esphome/core/log.h"
#include <cinttypes>

namespace esphome {
namespace th575 {

static const char *const TAG = "th575";



void TH575::loop() {
}

void TH575::update() {
  // this->flush();
  // this->write_byte(TH575_READ_COMMAND);
  // this->write_byte(TH575_FULL_PACKET);
}

void TH575::setup() {
  this->flush();
}

void TH575::dump_config() {  // NOLINT(readability-function-cognitive-complexity)
  ESP_LOGCONFIG(TAG, "TH575:");
  LOG_SENSOR("", "Hours", this->lamphours_);
  LOG_NUMBER("", "Volume", this->volume_);
  LOG_SWITCH("", "Power", this->onoff_);
}

void Volume::control(float volume) {};
}  // namespace th575
}  // namespace esphome
