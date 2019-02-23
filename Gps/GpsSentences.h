#ifndef GPS_SENTENCES_H_
#define GPS_SENTENCES_H_

#include <iomanip>
#include <string>
#include "Common.h"

namespace NEMAParser {

struct LatLong {
  LatLong () : degrees(0.f), minutes(0.f), decimal_degrees(0.f) {}

  virtual ~LatLong() {}

  void reset() {
    degrees = 0.f;
    minutes = 0.f;
    decimal_degrees = 0.f;
  }

  void set(const std::string &value) {
    degrees = Common::convertToFloat(value.substr(0, value.find(".")-2));
    minutes = Common::convertToFloat(value.substr(value.find(".")-2));
    if (degrees >= 0.f) {
      decimal_degrees = degrees + minutes / 60.f;
    } else {
      decimal_degrees = degrees - minutes / 60.f;
    }
  }

  float degrees;
  float minutes;
  float decimal_degrees;
};

struct Time {
  Time () : hours(0.f), minutes(0.f), seconds(0.f), utc("") {}

  virtual ~Time() {}

  void reset() {
    hours = 0.f;
    minutes = 0.f;
    seconds = 0.f;
    utc = "";
  }

  void set(const std::string &value) {
    const std::string str_hours = value.substr(0, 2);
    const std::string str_minutes = value.substr(2, 2);
    const std::string str_seconds = value.substr(4);
    hours = Common::convertToFloat(str_hours);
    minutes = Common::convertToFloat(str_minutes);
    seconds = Common::convertToFloat(str_seconds);
    utc = str_hours + ":" + str_minutes + ":" + str_seconds;
  }

  float hours;
  float minutes;
  float seconds;
  std::string utc;
};

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
    stream << std::setprecision(10);
    stream << "--------------------GPGGA START--------------------" << std::endl;
    stream << "time                              = " << time.utc                         << std::endl;
    stream << "latitude                          = " << latitude.decimal_degrees         << std::endl;
    stream << "latitude_direction                = " << latitude_direction               << std::endl;
    stream << "longitude                         = " << longitude.decimal_degrees        << std::endl;
    stream << "longitude_direction               = " << longitude_direction              << std::endl;
    stream << "quality                           = " << quality                          << std::endl;
    stream << "number_of_satellites              = " << number_of_satellites             << std::endl;
    stream << "horizontal_dilution_of_precision  = " << horizontal_dilution_of_precision << std::endl;
    stream << "altitude                          = " << altitude                         << std::endl;
    stream << "altitude_units                    = " << altitude_units                   << std::endl;
    stream << "undulation                        = " << undulation                       << std::endl;
    stream << "undulation_units                  = " << undulation_units                 << std::endl;
    stream << "age                               = " << age                              << std::endl;
    stream << "differential_station_ID           = " << differential_station_ID          << std::endl;
    stream << "checksum                          = " << checksum                         << std::endl;
    stream << "--------------------GPGGA END--------------------" << std::endl;
  }

  void reset() {
    time.reset();
    latitude.reset();
    latitude_direction = "";
    longitude.reset();
    longitude_direction = "";
    quality = 0;
    number_of_satellites = 0;
    horizontal_dilution_of_precision = 0.0f;
    altitude = 0.0f;
    altitude_units = "";
    undulation = 0.0f;
    undulation_units = "";
    age = 0.0f;
    differential_station_ID = "";
    checksum = 0;
  }

  Time time;                               // utc
  LatLong latitude;                        // lat
  std::string latitude_direction;          // N or S
  LatLong longitude;                       // long
  std::string longitude_direction;         // E or W
  int quality;                             // 0~9
  int number_of_satellites;                // number of satellites in use
  float horizontal_dilution_of_precision;  // horizontal dilution of precision
  float altitude;                          // altitude
  std::string altitude_units;              // altitude unit : M = meter
  float undulation;                        // undulation
  std::string undulation_units;            // undulation unit : M = meter
  float age;                               // age of correction data (in seconds)
  std::string differential_station_ID;     // differential station ID
  int checksum;                            // check sum
};

//$GPGLL - Geographic position, latitude / longitude
struct GPGLL : Sentence {
  GPGLL() : Sentence("GPGLL", 9) {
    reset();
  }

  void output(std::ostream &stream) const {
    stream << std::setprecision(10);
    stream << "--------------------GPGLL START--------------------" << std::endl;
    stream << "latitude                             = " << latitude.decimal_degrees   << std::endl;
    stream << "latitude_compass_direction           = " << latitude_direction         << std::endl;
    stream << "longitude                            = " << longitude.decimal_degrees  << std::endl;
    stream << "longitude_compass_direction          = " << longitude_direction        << std::endl;
    stream << "utc                                  = " << time.utc                   << std::endl;
    stream << "status                               = " << status                     << std::endl;
    stream << "mode                                 = " << mode                       << std::endl;
    stream << "checksum                             = " << checksum                   << std::endl;
    stream << "--------------------GPGLL END--------------------" << std::endl;
  }

  void reset() {
    latitude.reset();
    latitude_direction = "";
    longitude.reset();
    longitude_direction = "";
    time.reset();
    status = "";
    mode = "";
    checksum = 0;
  }

  LatLong latitude;                 // lat
  std::string latitude_direction;   // N or S
  LatLong longitude;                // long
  std::string longitude_direction;  // E or W
  Time time;                        // utc
  std::string status;               // data status : A = Data valid, V = Data invalid
  std::string mode;                 // mode
  int checksum;                     // check sum
};

//$GPGSA - GPS DOP and active satellites
struct GPGSA : Sentence {
  GPGSA() : Sentence("GPGSA", 19) {}

  void output(std::ostream &stream) const {
    stream << std::setprecision(10);
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

  std::string mode;    // mode MA  : A = Automatic 2D/3D M = Manual, forced to operate in 2D or 3D
  int status;          // mode 123 : 1 = Fix not available; 2 = 2D; 3 = 3D
  int satellite_id_1;  // PRN numbers of satellites
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
  float pdop;           // position dilution of precision
  float hdop;           // horizontal dilution of precision
  float vdop;           // vertical dilution of precision
  int checksum;         // check sum
};

//$GPGSV - GPS Satellites in view
struct GPGSV : Sentence {
  GPGSV() : Sentence("GPGSV", 21) {
    reset();
  }

  void output(std::ostream &stream) const {
    stream << std::setprecision(10);
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

  int total_message_num;       // total number of messages
  int message_number;          // message number
  int total_satellite_number;  // total number of satellites in view
  int satellite_number_1;      // satellite PRN number
  float elevation_1;           // elevation : degrees, 90 maximum
  float azimuth_1;             // azimuth, degrees True, 000 to 359
  float sn_1;                  // SNR (C/No) 00-99 dB, null when not tracking
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
  int checksum;                // check sum
};

//$GPRMC - Recommended minimum specific GPS/Transit data
struct GPRMC : Sentence {
  GPRMC() : Sentence("GPRMC", 14) {
    reset();
  }

  void output(std::ostream &stream) const {
    stream << "--------------------GPRMC START--------------------" << std::endl;
    stream << "utc                                  = " << time.utc                      << std::endl;
    stream << "status                               = " << status                        << std::endl;
    stream << "latitude                             = " << latitude.decimal_degrees      << std::endl;
    stream << "latitude_compass_direction           = " << latitude_direction            << std::endl;
    stream << "longitude                            = " << longitude.decimal_degrees     << std::endl;
    stream << "longitude_compass_direction          = " << longitude_direction           << std::endl;
    stream << "knots                                = " << knots                         << std::endl;
    stream << "degrees                              = " << degrees                       << std::endl;
    stream << "utc_date                             = " << date                          << std::endl;
    stream << "magnetic_variatio_degrees            = " << magnetic_variation            << std::endl;
    stream << "magnetic_variatio_degrees_direction  = " << magnetic_variation_direction  << std::endl;
    stream << "mode                                 = " << mode                          << std::endl;
    stream << "checksum                             = " << checksum                      << std::endl;
    stream << "--------------------GPRMC END--------------------" << std::endl;
  }

  void reset() {
    time.reset();
    status = "";
    latitude.reset();
    latitude_direction = "";
    longitude.reset();
    longitude_direction = "";
    knots = 0.f;
    degrees = 0.f;
    date = "";
    magnetic_variation = 0.f;
    magnetic_variation_direction = "";
    mode = "";
    checksum = 0;
  }

  Time time;                                 // utc
  std::string status;                        // position status : A = data valid, V = data invalid)
  LatLong latitude;                          // lat
  std::string latitude_direction;            // N or S
  LatLong longitude;                         // long
  std::string longitude_direction;           // E or W
  float knots;                               // speed over ground, knots
  float degrees;                             // track made good, degrees True
  std::string date;                          // utc data
  float magnetic_variation;                  // magnetic variation, degrees
  std::string magnetic_variation_direction;  // Magnetic variation direction : E or W
  std::string mode;                          // mode
  int checksum;                              // check sum
};

//$GPVTG - Track made good and ground speed
struct GPVTG : Sentence {
  GPVTG() : Sentence("GPVTG", 11) {
    reset();
  }

  void output(std::ostream &stream) const {
    stream << std::setprecision(10);
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

  float track;                      // track made good, degrees True
  std::string track_mode;           // True track indicator
  float magnetic_track;             // Track made good, degrees Magnetic
  std::string magnetic_track_mode;  // magnetic track indicator
  float ground_speed_knots;         // speed over ground, knots
  std::string knots;                // nautical speed indicator (N = Knots)
  float ground_speed_kmh;           // speed, kilometres/hour
  std::string kmh;                  // speed indicator (K = km/hr)
  std::string mode;                 // positioning system mode indicator
  int checksum;                     // check sum
};

//$GPZDA - Date & Time
struct GPZDA : Sentence {
  GPZDA() : Sentence("GPZDA", 8) {
    reset();
  }

  void output(std::ostream &stream) const {
    stream << std::setprecision(10);
    stream << "--------------------GPZDA START--------------------" << std::endl;
    stream << "utc                            = " << time.utc                       << std::endl;
    stream << "day                            = " << day                            << std::endl;
    stream << "month                          = " << month                          << std::endl;
    stream << "year                           = " << year                           << std::endl;
    stream << "local_zone_hours_description   = " << local_zone_hours_description   << std::endl;
    stream << "local_zone_minutes_description = " << local_zone_minutes_description << std::endl;
    stream << "checksum                       = " << checksum                       << std::endl;
    stream << "--------------------GPZDA END--------------------" << std::endl;
  }

  void reset() {
    time.reset();
    day = 0;
    month = 0;
    year = 0;
    local_zone_hours_description = 0;
    local_zone_minutes_description = 0;
    checksum = 0;
  }

  Time time;                           // utc
  int day;                             // day
  int month;                           // month
  int year;                            // year
  int local_zone_hours_description;    // local zone description
  int local_zone_minutes_description;  // local zone minutes description
  int checksum;                        // check sum
};

} // end of namespase NEMAParser
#endif // GPS_SENTENCES_H_
