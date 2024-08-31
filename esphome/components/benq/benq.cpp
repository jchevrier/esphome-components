#include "benq.h"
#include "esphome/core/log.h"
#include <cctype>
#include <ctime>
#include <string>
#include <queue>


namespace esphome {
namespace benq {

static const char *const TAG = "benq";
static volatile bool cmd_ready;
static std::time_t last_ready;
static std::queue<std::string> cmd_pump;

int Benq::readline(int readch, char *buffer, int len) {
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\n':
      case '\r': // Return on CR or newline
        buffer[pos] = 0; // Just to be sure, set last character 0
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      case '*':
      case '#':
      case '>':
        cmd_ready = true;
        last_ready = std::time(nullptr);
        break;
      default:
        if ((pos < len-1) && ( readch < 127 )) { // Filter on <127 to make sure it is a character
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
        else
        {
          buffer[pos] = 0; // Just to be sure, set last character 0
          rpos = pos;
          pos = 0;  // Reset position index ready for next time
          return rpos;
        }
        break;
    }
  }
  // No end of line has been found, so return -1.
  return -1;
}

void Benq::update() {
  for (auto const& component: this->cmd_list) {
    auto name = component.first;
    cmd_pump.push(name + "=?");
  }
}
void Benq::loop() {
  const int max_line_length = 80;
  static char buffer[max_line_length];
  if (cmd_ready && cmd_pump.size() >0) {
    std::string myCmd = cmd_pump.front();
    this->write_to_uart(myCmd);
    cmd_pump.pop();
    cmd_ready = false;
  }
  while (available()) {
    if(readline(read(), buffer, max_line_length) > 0) {
      ESP_LOGI(TAG,"Got message: %s", buffer);
      std::string str = buffer;
      auto equal_pos = str.find('=');
      if (equal_pos == std::string::npos)
        continue;
      std::string cmd = str.substr(0, equal_pos);
      std::transform(cmd.begin(), cmd.end(), cmd.begin(),
                     [](unsigned char c){ return std::tolower(c); });
      std::string data = str.substr(equal_pos+1, str.size());
      ESP_LOGI(TAG,"Got cmd: %s, data: %s", cmd.c_str(), data.c_str());
      if ((data.compare("?") == 0) || (data.compare("+") ==0) || (data.compare("-") == 0)){
        continue;
      }
      auto search = cmd_list.find(cmd);
      if (search != cmd_list.end() && search->second != nullptr) {
        search->second->feed_command_back(data);
      }
    }
  }
  if ((!cmd_ready) && (std::difftime(last_ready, std::time(nullptr)) > 10.0 ))
  {
    cmd_ready = true;
    last_ready = std::time(nullptr);
  }
}

void Benq::setup() {
  this->flush();
  cmd_ready=true;
}

void Benq::dump_config() {  // NOLINT(readability-function-cognitive-complexity)
  ESP_LOGCONFIG(TAG, "Benq:");
}
void Benq::register_command(std::string cmd, BenqCallback *cb) {
  this->cmd_list[cmd] = cb; 
}

void Benq::send_command(std::string cmd) {
  // cmd_pump.push(std::string("\r*") + cmd + std::string("#\r"));
  cmd_pump.push(cmd);
}

void Benq::write_to_uart(std::string cmd) {
  ESP_LOGD(TAG, "Sending: %s", cmd.c_str());
  this->write_str("\r*");
  for (auto &c : cmd) {
    this->write_byte(c);
  }
  this->write_str("#\r");
  this->flush();
}

}  // namespace Benq
}  // namespace esphome
