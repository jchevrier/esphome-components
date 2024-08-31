#pragma once

#include "esphome/core/component.h"
#include "esphome/components/benq/benq.h"
#include "esphome/components/select/select.h"

#include <vector>

namespace esphome {
namespace benq {

class BenqSelect : public select::Select, public Component, public BenqCallback {
 public:
  void setup() override;
  void dump_config() override;
  void set_benq_parent(Benq *parent) { this->parent_ = parent; }
  void set_optimistic(bool optimistic) { this->optimistic_ = optimistic; }
  void set_select_id(uint8_t select_id) { this->select_id_ = select_id; }
  void set_select_mappings(std::vector<std::string> mappings) { this->mappings_ = std::move(mappings); }
  void feed_command_back(std::string data) override;
  void set_benq_command(std::string cmd) { this->command_ = cmd; }

 protected:
  //TODO
  // void control(const std::string &value) override;
  void control(const std::string &value) {};

  Benq *parent_;
  bool optimistic_ = false;
  uint8_t select_id_;
  std::string command_;
  std::vector<std::string> mappings_;
};

}  // namespace benq
} // namespace esphome
