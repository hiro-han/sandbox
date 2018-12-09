#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "Error.h"
#include "NEMAParser.h"
#include "SerialConnection.h"

int main() {
  std::ofstream ofs("log.txt");

  SerialConnection serial;
  if (!serial.initialize("/dev/ttyUSB0", SerialConnection::kB9600)) {
    return 1;
  }
  sleep(1);

  NEMAParser::NEMAParser parser;
  NEMAParser::ErrorCode error;
  while (true) {
    usleep(100000.f); // 100ms
    ofs << "-----START-----" << std::endl;
    std::istringstream ss(serial.receive('\n'));
    std::string buffer;
    while (std::getline(ss, buffer, '\n') ) {
     error = parser.parse(buffer);
    }
    if (error != NEMAParser::ErrorCode::kNoError) {
      ofs << "Error Code = " << (int)error << std::endl;
    }
    parser.getGPGGA().output(ofs);
    parser.getGPGLL().output(ofs);
    parser.getGPGSA().output(ofs);
    parser.getGPGSV().output(ofs);
    parser.getGPRMC().output(ofs);
    parser.getGPVTG().output(ofs);
    parser.getGPZDA().output(ofs);
    ofs << "-----END-----" << std::endl;
  }
  return 0;
}

