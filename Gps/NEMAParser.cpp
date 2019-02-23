#include "NEMAParser.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace NEMAParser {

NEMAParser::NEMAParser() {
  // nop
}

NEMAParser::~NEMAParser() {
  // nop
}

ErrorCode NEMAParser::parse(const std::string &data) {
  if (data.size() < 4
      || data.front() != '$'
      || data.back() != '\r') {
    return ErrorCode::kFormatInvalid;
  }

  // 先頭の$, 末尾の\rを取り除いてsplit (\nはシリアルの受信時に削除されている)
  std::vector<std::string> splited_data = split(data.substr(1, data.size() - 2));
  // parse
  ErrorCode error = ErrorCode::kNoError;
  const std::string &type = splited_data.front();
  if (type == "GPGGA") {
    error = parseGPGGA(splited_data, gpgga_);
  } else if (type == "GPGLL") {
    error = parseGPGLL(splited_data, gpgll_);
  } else if (type == "GPGSA") {
    error = parseGPGSA(splited_data, gpgsa_);
  } else if (type == "GPGSV") {
    error = parseGPGSV(splited_data, gpgsv_);
  } else if (type == "GPRMC") {
    error = parseGPRMC(splited_data, gprmc_);
  } else if (type == "GPVTG") {
    error = parseGPVTG(splited_data, gpvtg_);
  } else if (type == "GPZDA") {
    error = parseGPZDA(splited_data, gpzda_);
  } else {
    error = ErrorCode::kUnsupportFormat;
  }

  return error;
}

std::vector<std::string> NEMAParser::split(const std::string &data) const {
  std::vector<std::string> splited_data;
  std::stringstream ss(data);
  std::string buffer;
  while (std::getline(ss, buffer, ',') ) {
    splited_data.push_back(buffer);
  }

  // split check sum
  std::string last = splited_data.back();
  splited_data.pop_back();
  ss.str("");
  ss.clear(std::stringstream::goodbit);
  ss << last;
  while (std::getline(ss, buffer, '*') ) {
    splited_data.push_back(buffer);
  }
  return splited_data;
}

ErrorCode NEMAParser::parseGPGGA(const std::vector<std::string> &data, GPGGA &gpgga) const {
  if (data.size() != gpgga_.data_num) {
    gpgga.reset();
    return ErrorCode::kGPGGAInvalid;
  }
  gpgga.time.set(data.at(1));
  gpgga.latitude.set(data.at(2));
  gpgga.latitude_direction                 = data.at(3);
  gpgga.longitude.set(data.at(4));
  gpgga.longitude_direction                = data.at(5);
  gpgga.quality                            = Common::convertToIntFromDecimal(data.at(6));
  gpgga.number_of_satellites               = Common::convertToIntFromDecimal(data.at(7));
  gpgga.horizontal_dilution_of_precision   = Common::convertToFloat(data.at(8));
  gpgga.altitude                           = Common::convertToFloat(data.at(9));
  gpgga.altitude_units                     = data.at(10);
  gpgga.undulation                         = Common::convertToFloat(data.at(11));
  gpgga.undulation_units                   = data.at(12);
  gpgga.age = Common::convertToFloat(data.at(13));
  gpgga.differential_station_ID            = data.at(14);
  gpgga.checksum                           = Common::convertToIntFromHex(data.at(15));
  return ErrorCode::kNoError;
}

ErrorCode NEMAParser::parseGPGLL(const std::vector<std::string> &data, GPGLL &gpgll) const {
  if (data.size() != gpgll.data_num) {
    gpgll.reset();
    return ErrorCode::kGPGLLInvalid;
  }
  gpgll.latitude.set(data.at(1));
  gpgll.latitude_direction          = data.at(2);
  gpgll.longitude.set(data.at(3));
  gpgll.longitude_direction         = data.at(4);
  gpgll.time.set(data.at(5));
  gpgll.status                      = data.at(6);
  gpgll.mode                        = data.at(7);
  gpgll.checksum                    = Common::convertToIntFromHex(data.at(8));
  return ErrorCode::kNoError;
}

ErrorCode NEMAParser::parseGPGSA(const std::vector<std::string> &data, GPGSA &gpgsa) const {
  if (data.size() != gpgsa.data_num) {
    gpgsa.reset();
    return ErrorCode::kGPGSAInvalid;
  }
  gpgsa.mode            = data.at(1);
  gpgsa.status          = Common::convertToIntFromDecimal(data.at(2));
  gpgsa.satellite_id_1  = Common::convertToIntFromDecimal(data.at(3));
  gpgsa.satellite_id_2  = Common::convertToIntFromDecimal(data.at(4));
  gpgsa.satellite_id_3  = Common::convertToIntFromDecimal(data.at(5));
  gpgsa.satellite_id_4  = Common::convertToIntFromDecimal(data.at(6));
  gpgsa.satellite_id_5  = Common::convertToIntFromDecimal(data.at(7));
  gpgsa.satellite_id_6  = Common::convertToIntFromDecimal(data.at(8));
  gpgsa.satellite_id_7  = Common::convertToIntFromDecimal(data.at(9));
  gpgsa.satellite_id_8  = Common::convertToIntFromDecimal(data.at(10));
  gpgsa.satellite_id_9  = Common::convertToIntFromDecimal(data.at(11));
  gpgsa.satellite_id_10 = Common::convertToIntFromDecimal(data.at(12));
  gpgsa.satellite_id_11 = Common::convertToIntFromDecimal(data.at(13));
  gpgsa.satellite_id_12 = Common::convertToIntFromDecimal(data.at(14));
  gpgsa.pdop            = Common::convertToFloat(data.at(15));
  gpgsa.hdop            = Common::convertToFloat(data.at(16));
  gpgsa.vdop            = Common::convertToFloat(data.at(17));
  gpgsa.checksum        = Common::convertToIntFromHex(data.at(18));
  return ErrorCode::kNoError;
}

ErrorCode NEMAParser::parseGPGSV(const std::vector<std::string> &data, GPGSV &gpgsv) const {
  if (data.size() != gpgsv.data_num) {
    gpgsv.reset();
    return ErrorCode::kGPGSAInvalid;
  }
  gpgsv.total_message_num       = Common::convertToIntFromDecimal(data.at(1));
  gpgsv.message_number          = Common::convertToIntFromDecimal(data.at(2));
  gpgsv.total_satellite_number  = Common::convertToFloat(data.at(3));
  gpgsv.satellite_number_1      = Common::convertToIntFromDecimal(data.at(4));
  gpgsv.elevation_1             = Common::convertToFloat(data.at(5));
  gpgsv.azimuth_1               = Common::convertToFloat(data.at(6));
  gpgsv.sn_1                    = Common::convertToFloat(data.at(7));
  gpgsv.satellite_number_2      = Common::convertToIntFromDecimal(data.at(8));
  gpgsv.elevation_2             = Common::convertToFloat(data.at(9));
  gpgsv.azimuth_2               = Common::convertToFloat(data.at(10));
  gpgsv.sn_2                    = Common::convertToFloat(data.at(11));
  gpgsv.satellite_number_3      = Common::convertToIntFromDecimal(data.at(12));
  gpgsv.elevation_3             = Common::convertToFloat(data.at(13));
  gpgsv.azimuth_3               = Common::convertToFloat(data.at(14));
  gpgsv.sn_3                    = Common::convertToFloat(data.at(15));
  gpgsv.satellite_number_4      = Common::convertToIntFromDecimal(data.at(16));
  gpgsv.elevation_4             = Common::convertToFloat(data.at(17));
  gpgsv.azimuth_4               = Common::convertToFloat(data.at(18));
  gpgsv.sn_4                    = Common::convertToFloat(data.at(19));
  gpgsv.checksum                = Common::convertToIntFromHex(data.at(20));
  return ErrorCode::kNoError;
}

ErrorCode NEMAParser::parseGPRMC(const std::vector<std::string> &data, GPRMC &gprmc) const {
  if (data.size() != gprmc.data_num) {
    gprmc.reset();
    return ErrorCode::kGPRMCInvalid;
  }
  gprmc.time.set(data.at(1));
  gprmc.status                       = data.at(2);
  gprmc.latitude.set(data.at(3));
  gprmc.latitude_direction           = data.at(4);
  gprmc.longitude.set(data.at(5));
  gprmc.longitude_direction          = data.at(6);
  gprmc.knots                        = Common::convertToFloat(data.at(7));
  gprmc.degrees                      = Common::convertToFloat(data.at(8));
  gprmc.date                         = data.at(9);
  gprmc.magnetic_variation           = Common::convertToFloat(data.at(10));
  gprmc.magnetic_variation_direction = data.at(11);
  gprmc.mode                         = data.at(12);
  gprmc.checksum                     = Common::convertToIntFromHex(data.at(13));
  return ErrorCode::kNoError;
}

ErrorCode NEMAParser::parseGPVTG(const std::vector<std::string> &data, GPVTG &gpvtg) const {
  if (data.size() != gpvtg.data_num) {
    gpvtg.reset();
    return ErrorCode::kGPVTGInvalid;
  }
  gpvtg.track               = Common::convertToFloat(data.at(1));
  gpvtg.track_mode          = data.at(2);
  gpvtg.magnetic_track      = Common::convertToFloat(data.at(3));
  gpvtg.magnetic_track_mode = data.at(4);
  gpvtg.ground_speed_knots  = Common::convertToFloat(data.at(5));
  gpvtg.knots               = data.at(6);
  gpvtg.ground_speed_kmh    = Common::convertToFloat(data.at(7));
  gpvtg.kmh                 = data.at(8);
  gpvtg.mode                = data.at(9);
  gpvtg.checksum            = Common::convertToIntFromHex(data.at(10));
  return ErrorCode::kNoError;
}

ErrorCode NEMAParser::parseGPZDA(const std::vector<std::string> &data, GPZDA &gpzda) const {
  if (data.size() != gpzda.data_num) {
    gpzda.reset();
    return ErrorCode::kGPZDAInvalid;
  }
  gpzda.time.set(data.at(1));
  gpzda.day                            = Common::convertToIntFromDecimal(data.at(2));
  gpzda.month                          = Common::convertToIntFromDecimal(data.at(3));
  gpzda.year                           = Common::convertToIntFromDecimal(data.at(4));
  gpzda.local_zone_hours_description   = Common::convertToIntFromDecimal(data.at(5));
  gpzda.local_zone_minutes_description = Common::convertToIntFromDecimal(data.at(6));
  gpzda.checksum                       = Common::convertToIntFromHex(data.at(7));
  return ErrorCode::kNoError;
}

} // end of namespase NEMAParser

