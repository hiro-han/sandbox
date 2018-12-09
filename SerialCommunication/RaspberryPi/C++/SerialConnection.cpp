#include "SerialConnection.h"

const int SerialConnection::kError = -1;

SerialConnection::SerialConnection() : port_(kError) {
  // nop
}

SerialConnection::~SerialConnection() {
  if (port_ != kError) {
    tcsetattr(port_, TCSANOW, &old_settings_);
    close(port_);
  }
}

bool SerialConnection::initialize(const std::string &device, const BaudRate &rate) {
  port_ = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
  if (port_ == kError) {
    std::cout << "Device open error. device : \"" << device << "\""<< std::endl;
    return false;
  }

  if (tcgetattr(port_, &old_settings_) == kError) {
    std::cout << "tcgetattr error."<< std::endl;
    close(port_);
    return false;
  }

  current_settings_ = old_settings_;

  if ((cfsetispeed(&current_settings_, rate) == kError) || (cfsetospeed(&current_settings_, rate) == kError)) {
    std::cout << "cfsetispeed or cfsetospeed error."<< std::endl;
    close(port_);
    return false;
  }

  current_settings_.c_iflag = IGNPAR;
  current_settings_.c_oflag = 0;
  current_settings_.c_lflag = 0;
  current_settings_.c_cflag= (CS8 | CLOCAL | CREAD);

  if (tcsetattr(port_, TCSANOW, &current_settings_) == kError) {
    std::cout << "tcsetattr error."<< std::endl;
    close(port_);
    return false;
  }

  return true;
}

bool SerialConnection::send(const std::string &str) {
  size_t send_size = str.size() + 1;
  char send_char[send_size];
  str.copy(send_char, str.size());
  send_char[str.size()] = '\0';
  return write(port_, send_char, send_size) == send_size;
}

std::string SerialConnection::receive(const bool wait, const char terminate) {
  std::string receive_str;
  bool receving = false;
  char receive_char;
  while (true) {
    int read_size = read(port_, &receive_char, 1);
    if (read_size > 0) {
      receving = true;
      receive_str.append(1, receive_char);
      if (receive_char == terminate) {
        break;
      }
    } else {
      if (!wait || receving) {
        break;
      }
    }
  }
  return receive_str;
}


