#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <ctime>

namespace esphome {
namespace benq {

const int max_line_length = 80;
const int max_queue_size = 20;

class Benq;
class BenqCallback {
public:
  virtual void feed_command_back(std::string &data);
};

template <class T>
class BenqGeneric : public Component, public T, public BenqCallback {
public:

  void set_benq_parent(Benq *parent) { this->parent_ = parent; }
  void set_benq_command(std::string cmd) { this->command_ = cmd; }

protected:
  Benq *parent_;
  std::string command_;
};

class Benq : public PollingComponent, public uart::UARTDevice {
public:
  void loop() override;

  void update() override;
  void setup() override;
  void dump_config() override;
  void register_command(std::string cmd, BenqCallback* child);
  void send_command(std::string &cmd);
  void set_retry_timeout_value(uint8_t value) { this->retry_timeout_ = value; }

protected:

private:
  uint8_t retry_timeout_;
  std::map<std::string, BenqCallback*> cmd_list;
  std::string str;
  void write_to_uart(std::string cmd);
  int readline(int readch, char*buffer, int len);
  bool cmd_ready;
  std::time_t last_ready;
  std::queue<std::string> cmd_pump;
  char buffer[max_line_length];
  int pos;
};

}  // namespace benq
}  // namespace esphome
