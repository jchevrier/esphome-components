#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include <string>
#include <map>
#include <vector>

namespace esphome {
namespace benq {

typedef void(*cmd_cb)(std::string);

class BenqCallback {
public:
  virtual void feed_command_back(std::string data);
};

class Benq : public PollingComponent, public uart::UARTDevice {
 public:
  void loop() override;

  void update() override;
  void setup() override;
  void dump_config() override;
  void register_command(std::string cmd, BenqCallback* child);
  void send_command(std::string cmd);
  int readline(int readch, char*buffer, int len);
  
 protected:
  void write_to_uart(std::string cmd);
  std::map<std::string, BenqCallback*> cmd_list;
  std::string str;
};

}  // namespace benq
}  // namespace esphome
