#ifndef GPS_SENTENCES_H_
#define GPS_SENTENCES_H_

#include <string>

namespace NEMAParser {

struct Sentence {
  Sentence(const std::string &_type, const int _data_num)
    : type(_type),
      data_num(_data_num) {}
  virtual ~Sentence() {}

  virtual void output(std::ostream &stream) const {return;}
  virtual void reset() = 0;

  bool equalType(const std::string &_type) {return type == _type;}

  const std::string type;
  const int data_num;
};


//$GPGGA - Global Positioning System Fix Data
struct GPGGA : Sentence {
  GPGGA() : Sentence("GPGGA", 16) {
    reset();
  }

  void output(std::ostream &stream) const {
    stream << "--------------------GPGGA START--------------------" << std::endl;
    stream << "time                                    = " << time                                    << std::endl;
    stream << "latitude                                = " << latitude                                << std::endl;
    stream << "latitude_compass_direction              = " << latitude_compass_direction              << std::endl;
    stream << "longitude                               = " << longitude                               << std::endl;
    stream << "longitude_compass_direction             = " << longitude_compass_direction             << std::endl;
    stream << "fix_type                                = " << fix_type                                << std::endl;
    stream << "number_of_satellites                    = " << number_of_satellites                    << std::endl;
    stream << "horizontal_dilution_of_precision        = " << horizontal_dilution_of_precision        << std::endl;
    stream << "altitude                                = " << altitude                                << std::endl;
    stream << "altitude_units                          = " << altitude_units                          << std::endl;
    stream << "height_of_geoid                         = " << height_of_geoid                         << std::endl;
    stream << "height_of_geoid_units                   = " << height_of_geoid_units                   << std::endl;
    stream << "time_since_last_differential_correction = " << time_since_last_differential_correction << std::endl;
    stream << "differential_station_ID                 = " << differential_station_ID                 << std::endl;
    stream << "checksum                                = " << checksum                                << std::endl;
    stream << "--------------------GPGGA END--------------------" << std::endl;
  }

  void reset() {
    time = 0.0f;
    latitude = 0.0f;
    latitude_compass_direction = "";
    longitude = 0.0f;
    longitude_compass_direction = "";
    fix_type = 0;
    number_of_satellites = 0;
    horizontal_dilution_of_precision = 0.0f;
    altitude = 0.0f;
    altitude_units = "";
    height_of_geoid = 0.0f;
    height_of_geoid_units = "";
    time_since_last_differential_correction = 0.0f;
    differential_station_ID = "";
    checksum = 0;
  }

  float time;
  float latitude;
  std::string latitude_compass_direction;
  float longitude;
  std::string longitude_compass_direction;
  int fix_type;
  int number_of_satellites;
  float horizontal_dilution_of_precision;
  float altitude;
  std::string altitude_units;
  float height_of_geoid;
  std::string height_of_geoid_units;
  float time_since_last_differential_correction;
  std::string differential_station_ID;
  int checksum;
};

//$GPGLL - Geographic position, latitude / longitude
struct GPGLL : Sentence {
  GPGLL() : Sentence("GPGLL", 9) {}

  void output(std::ostream &stream) const {
    stream << "--------------------GPGLL START--------------------" << std::endl;
    stream << "latitude                             = " << latitude                             << std::endl;
    stream << "latitude_compass_direction           = " << latitude_compass_direction           << std::endl;
    stream << "longitude                            = " << longitude                            << std::endl;
    stream << "longitude_compass_direction          = " << longitude_compass_direction          << std::endl;
    stream << "utc                                  = " << utc                                  << std::endl;
    stream << "status                               = " << status                               << std::endl;
    stream << "mode                                 = " << mode                                 << std::endl;
    stream << "checksum                             = " << checksum                             << std::endl;
    stream << "--------------------GPGLL END--------------------" << std::endl;
  }

  void reset() {
    latitude = 0.0f;
    latitude_compass_direction = "";
    longitude = 0.0f;
    longitude_compass_direction = "";
    utc = "";
    status = "";
    mode = "";
    checksum = 0;
  }

  float latitude;
  std::string latitude_compass_direction;
  float longitude;
  std::string longitude_compass_direction;
  std::string utc;
  std::string status;
  std::string mode;
  int checksum;
};

//$GPGSA - GPS DOP and active satellites
struct GPGSA : Sentence {
  GPGSA() : Sentence("GPGSA", 19) {}

  void output(std::ostream &stream) const {
    stream << "--------------------GPGSA START--------------------" << std::endl;
    stream << "mode            = " << mode            << std::endl;
    stream << "status          = " << status          << std::endl;
    stream << "satellite_id_1  = " << satellite_id_1  << std::endl;
    stream << "satellite_id_2  = " << satellite_id_2  << std::endl;
    stream << "satellite_id_3  = " << satellite_id_3  << std::endl;
    stream << "satellite_id_4  = " << satellite_id_4  << std::endl;
    stream << "satellite_id_5  = " << satellite_id_5  << std::endl;
    stream << "satellite_id_6  = " << satellite_id_6  << std::endl;
    stream << "satellite_id_7  = " << satellite_id_7  << std::endl;
    stream << "satellite_id_8  = " << satellite_id_8  << std::endl;
    stream << "satellite_id_9  = " << satellite_id_9  << std::endl;
    stream << "satellite_id_10 = " << satellite_id_10 << std::endl;
    stream << "satellite_id_11 = " << satellite_id_11 << std::endl;
    stream << "satellite_id_12 = " << satellite_id_12 << std::endl;
    stream << "pdop            = " << pdop            << std::endl;
    stream << "hdop            = " << hdop            << std::endl;
    stream << "vdop            = " << vdop            << std::endl;
    stream << "checksum        = " << checksum        << std::endl;
    stream << "--------------------GPGSA END--------------------" << std::endl;
  }

  void reset() {
    mode = "";
    status = 0;
    satellite_id_1 = 0;
    satellite_id_2 = 0;
    satellite_id_3 = 0;
    satellite_id_4 = 0;
    satellite_id_5 = 0;
    satellite_id_6 = 0;
    satellite_id_7 = 0;
    satellite_id_8 = 0;
    satellite_id_9 = 0;
    satellite_id_10 = 0;
    satellite_id_11 = 0;
    satellite_id_12 = 0;
    pdop = 0.0f;
    hdop = 0.0f;
    vdop = 0.0f;
    checksum = 0;
  }

  std::string mode;
  int status;
  int satellite_id_1;
  int satellite_id_2;
  int satellite_id_3;
  int satellite_id_4;
  int satellite_id_5;
  int satellite_id_6;
  int satellite_id_7;
  int satellite_id_8;
  int satellite_id_9;
  int satellite_id_10;
  int satellite_id_11;
  int satellite_id_12;
  float pdop;
  float hdop;
  float vdop;
  int checksum;
};

//$GPGSV - GPS Satellites in view
struct GPGSV : Sentence {
  GPGSV() : Sentence("GPGSV", 21) {
    reset();
  }

  void output(std::ostream &stream) const {
    stream << "--------------------GPGSV START--------------------" << std::endl;
    stream << "total_message_num      = " << total_message_num      << std::endl;
    stream << "message_number         = " << message_number         << std::endl;
    stream << "total_satellite_number = " << total_satellite_number << std::endl;
    stream << "satellite_number_1     = " << satellite_number_1     << std::endl;
    stream << "elevation_1            = " << elevation_1            << std::endl;
    stream << "azimuth_1              = " << azimuth_1              << std::endl;
    stream << "sn_1                   = " << sn_1                   << std::endl;
    stream << "satellite_number_2     = " << satellite_number_2     << std::endl;
    stream << "elevation_2            = " << elevation_2            << std::endl;
    stream << "azimuth_2              = " << azimuth_2              << std::endl;
    stream << "sn_2                   = " << sn_2                   << std::endl;
    stream << "satellite_number_3     = " << satellite_number_3     << std::endl;
    stream << "elevation_3            = " << elevation_3            << std::endl;
    stream << "azimuth_3              = " << azimuth_3              << std::endl;
    stream << "sn_3                   = " << sn_3                   << std::endl;
    stream << "satellite_number_4     = " << satellite_number_4     << std::endl;
    stream << "elevation_4            = " << elevation_4            << std::endl;
    stream << "azimuth_4              = " << azimuth_4              << std::endl;
    stream << "sn_4                   = " << sn_4                   << std::endl;
    stream << "--------------------GPGSV END--------------------" << std::endl;
  }

  void reset() {
    total_message_num = 0;
    message_number = 0;
    total_satellite_number = 0;
    satellite_number_1 = 0;
    elevation_1 = 0.f;
    azimuth_1 = 0.f;
    sn_1 = 0.f;
    satellite_number_2 = 0;
    elevation_2 = 0.f;
    azimuth_2 = 0.f;
    sn_2 = 0.f;
    satellite_number_3 = 0;
    elevation_3 = 0.f;
    azimuth_3 = 0.f;
    sn_3 = 0.f;
    satellite_number_4 = 0;
    elevation_4 = 0.f;
    azimuth_4 = 0.f;
    sn_4 = 0.f;
    checksum = 0;
  }

  int total_message_num;
  int message_number;
  int total_satellite_number;
  int satellite_number_1;
  float elevation_1;
  float azimuth_1;
  float sn_1;
  int satellite_number_2;
  float elevation_2;
  float azimuth_2;
  float sn_2;
  int satellite_number_3;
  float elevation_3;
  float azimuth_3;
  float sn_3;
  int satellite_number_4;
  float elevation_4;
  float azimuth_4;
  float sn_4;
  int checksum;
};

//$GPRMC - Recommended minimum specific GPS/Transit data
struct GPRMC : Sentence {
  GPRMC() : Sentence("GPRMC", 14) {
    reset();
  }

  void output(std::ostream &stream) const {
    stream << "--------------------GPRMC START--------------------" << std::endl;
    stream << "utc_time                             = " << utc_time                             << std::endl;
    stream << "status                               = " << status                               << std::endl;
    stream << "latitude                             = " << latitude                             << std::endl;
    stream << "latitude_compass_direction           = " << latitude_compass_direction           << std::endl;
    stream << "longitude                            = " << longitude                            << std::endl;
    stream << "longitude_compass_direction          = " << longitude_compass_direction          << std::endl;
    stream << "knots                                = " << knots                                << std::endl;
    stream << "degrees                              = " << degrees                              << std::endl;
    stream << "utc_date                             = " << utc_date                             << std::endl;
    stream << "magnetic_variatio_degrees            = " << magnetic_variatio_degrees            << std::endl;
    stream << "magnetic_variatio_degrees_direction  = " << magnetic_variatio_degrees_direction  << std::endl;
    stream << "mode                                 = " << mode                                 << std::endl;
    stream << "checksum                             = " << checksum                             << std::endl;
    stream << "--------------------GPRMC END--------------------" << std::endl;
  }

  void reset() {
    utc_time = "";
    status = "";
    latitude = 0.f;
    latitude_compass_direction = "";
    longitude = 0.f;
    longitude_compass_direction = "";
    knots = 0.f;
    degrees = 0.f;
    utc_date = "";
    magnetic_variatio_degrees = 0.f;
    magnetic_variatio_degrees_direction = "";
    mode = "";
    checksum = 0;
  }

  std::string utc_time;
  std::string status;
  float latitude;
  std::string latitude_compass_direction;
  float longitude;
  std::string longitude_compass_direction;
  float knots;
  float degrees;
  std::string utc_date;
  float magnetic_variatio_degrees;
  std::string magnetic_variatio_degrees_direction;
  std::string mode;
  int checksum;
};

//$GPVTG - Track made good and ground speed
struct GPVTG : Sentence {
  GPVTG() : Sentence("GPVTG", 11) {
    reset();
  }

  void output(std::ostream &stream) const {
    stream << "--------------------GPVTG START--------------------" << std::endl;
    stream << "track               = " << track               << std::endl;
    stream << "track_mode          = " << track_mode          << std::endl;
    stream << "magnetic_track      = " << magnetic_track      << std::endl;
    stream << "magnetic_track_mode = " << magnetic_track_mode << std::endl;
    stream << "ground_speed_knots  = " << ground_speed_knots  << std::endl;
    stream << "knots               = " << knots               << std::endl;
    stream << "ground_speed_kmh    = " << ground_speed_kmh    << std::endl;
    stream << "kmh                 = " << kmh                 << std::endl;
    stream << "mode                = " << mode                << std::endl;
    stream << "checksum            = " << checksum            << std::endl;
    stream << "--------------------GPVTG END--------------------" << std::endl;
  }

  void reset() {
    track = 0.f;
    track_mode = "";
    magnetic_track = 0.f;
    magnetic_track_mode = "";
    ground_speed_knots = 0.f;
    knots = "";
    ground_speed_kmh = 0.f;
    kmh = "";
    mode = "";
    checksum = 0;
  }

  float track;
  std::string track_mode;
  float magnetic_track;
  std::string magnetic_track_mode;
  float ground_speed_knots;
  std::string knots;
  float ground_speed_kmh;
  std::string kmh;
  std::string mode;
  int checksum;
};

//$GPZDA - Date & Time
struct GPZDA : Sentence {
  GPZDA() : Sentence("GPZDA", 8) {
    reset();
  }

  void output(std::ostream &stream) const {
    stream << "--------------------GPZDA START--------------------" << std::endl;
    stream << "utc                            = " << utc                            << std::endl;
    stream << "day                            = " << day                            << std::endl;
    stream << "month                          = " << month                          << std::endl;
    stream << "year                           = " << year                           << std::endl;
    stream << "local_zone_hours_description   = " << local_zone_hours_description   << std::endl;
    stream << "local_zone_minutes_description = " << local_zone_minutes_description << std::endl;
    stream << "checksum                       = " << checksum                       << std::endl;
    stream << "--------------------GPZDA END--------------------" << std::endl;
  }

  void reset() {
    utc = "";
    day = 0;
    month = 0;
    year = 0;
    local_zone_hours_description = 0;
    local_zone_minutes_description = 0;
    checksum = 0;
  }

  std::string utc;
  int day;
  int month;
  int year;
  int local_zone_hours_description;
  int local_zone_minutes_description;
  int checksum;
};

} // end of namespase NEMAParser
#endif // GPS_SENTENCES_H_
