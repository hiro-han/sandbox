#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "Error.h"
#include "NEMAParser.h"
#include "SerialConnection.h"

int main() {
  std::ofstream ofs_all_log("all_log.txt");
  std::ofstream ofs_some_log("some_log.csv");

  ofs_some_log
      << "utc" << ","
      << "latitude" << ","
      << "latitude_direction" << ","
      << "longitude" << ","
      << "longitude_direction" << ","
      << "altitude" << ","
      << "ground_speed_kmh" << ","
      << "track" << ","
      << "quality" << ","
      << "status" << ","
      << "number_of_satellites" << ","
      << std::endl;

  SerialConnection serial;
  if (!serial.initialize("/dev/ttyUSB0", SerialConnection::kB9600)) {
    return 1;
  }
  sleep(1);

  NEMAParser::NEMAParser parser;
  NEMAParser::ErrorCode error;
  while (true) {
    usleep(1000000.f); // 100ms
    ofs_all_log << "-----START-----" << std::endl;
    std::istringstream ss(serial.receive('\n'));
    std::string buffer;
    while (std::getline(ss, buffer, '\n') ) {
     error = parser.parse(buffer);
    }
    if (error != NEMAParser::ErrorCode::kNoError) {
      ofs_all_log << "Error Code = " << (int)error << std::endl;
    }
    parser.getGPGGA().output(ofs_all_log);
    parser.getGPGLL().output(ofs_all_log);
    parser.getGPGSA().output(ofs_all_log);
    parser.getGPGSV().output(ofs_all_log);
    parser.getGPRMC().output(ofs_all_log);
    parser.getGPVTG().output(ofs_all_log);
    parser.getGPZDA().output(ofs_all_log);
    ofs_all_log << "-----END-----" << std::endl;

    ofs_some_log
        << std::setprecision(10)
        << parser.getGPGGA().time.utc << ","
        << parser.getGPGGA().latitude.decimal_degrees << ","
        << parser.getGPGGA().latitude_direction << ","
        << parser.getGPGGA().longitude.decimal_degrees << ","
        << parser.getGPGGA().longitude_direction << ","
        << parser.getGPGGA().altitude << ","
        << parser.getGPVTG().ground_speed_kmh << ","
        << parser.getGPVTG().track << ","
        << parser.getGPGGA().quality << ","
        << parser.getGPGSA().status << ","
        << parser.getGPGGA().number_of_satellites
        << std::endl;
  }
  return 0;
}

