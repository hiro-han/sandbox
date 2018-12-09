#ifndef SERIAL_CONNECTION_H_
#define SERIAL_CONNECTION_H_

#include <fcntl.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>

class SerialConnection {
 public:

  enum BaudRate {
    kB4800 = B4800,
    kB9600 = B9600,
    kB19200 = B19200,
    kB38400 = B38400
   };

  SerialConnection();
  virtual ~SerialConnection();
  bool initialize(const std::string &device, const BaudRate &baudrate);
  bool send(const std::string &str);
  std::string receive(const bool wait=true, const char terminate='\0');

 private:
  static const int kError;

  termios old_settings_;
  termios current_settings_;
  int port_;
};

#endif // SERIAL_CONNECTION_H_
