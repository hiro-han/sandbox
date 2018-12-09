#include <stdio.h>
#include <string>
#include "SerialConnection.h"

int main(int argc, char* argv[]) {
  std::string device;
  if (argc == 2) {
    device = argv[1];
  } else if (argc == 1) {
    device = "/dev/ttyACM0";
  } else {
    std::cout << "invalid args" << std::endl;
    return 1;
  }

  SerialConnection serial;
  if (!serial.initialize(device, SerialConnection::kB9600)) {
    return 1;
  }

  sleep(1);
  while (true) {
    std::cout << "Please Input..." << std::endl;
    std::string input_str;
    getline(std::cin, input_str);
    if (input_str.empty()) {
      std::cout << "End " << std::endl;
      break;
    }

    if (serial.send(input_str)) {
      std::cout << "Send : " << input_str << std::endl;
    } else {
      std::cout << "Send Error"  << std::endl;
    }
    usleep(100000);
    std::string receive_str = serial.receive('r');
    std::cout << "Receive :" <<  receive_str << std::endl;
  }

  return 0;
}

