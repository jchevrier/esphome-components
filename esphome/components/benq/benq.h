#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include <string>
#include <map>
#include <vector>

namespace esphome {
namespace benq {

class Benq;
class BenqCallback {
public:
  virtual void feed_command_back(std::string data);
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
  void send_command(std::string cmd);
  int readline(int readch, char*buffer, int len);
  
 protected:
  void write_to_uart(std::string cmd);
  std::map<std::string, BenqCallback*> cmd_list;
  std::string str;
};

}  // namespace benq
}  // namespace esphome
