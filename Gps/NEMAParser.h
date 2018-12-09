#ifndef NEMA_PARSER_H_
#define NEMA_PARSER_H_

#include <string>
#include <vector>
#include "Common.h"
#include "Error.h"
#include "GpsSentences.h"

namespace NEMAParser {

class NEMAParser {
 public:
  NEMAParser();
  virtual ~NEMAParser();
  ErrorCode parse(const std::string &data);

  GPGGA getGPGGA() const {return gpgga_;}
  GPGLL getGPGLL() const {return gpgll_;}
  GPGSA getGPGSA() const {return gpgsa_;}
  GPGSV getGPGSV() const {return gpgsv_;}
  GPRMC getGPRMC() const {return gprmc_;}
  GPVTG getGPVTG() const {return gpvtg_;}
  GPZDA getGPZDA() const {return gpzda_;}

 private:
  std::vector<std::string> split(const std::string &data) const;
  ErrorCode parseGPGGA(const std::vector<std::string> &data, GPGGA &gpgga) const;
  ErrorCode parseGPGLL(const std::vector<std::string> &data, GPGLL &gpgll) const;
  ErrorCode parseGPGSA(const std::vector<std::string> &data, GPGSA &gpgsa) const;
  ErrorCode parseGPGSV(const std::vector<std::string> &data, GPGSV &gpgsv) const;
  ErrorCode parseGPRMC(const std::vector<std::string> &data, GPRMC &gprmc) const;
  ErrorCode parseGPVTG(const std::vector<std::string> &data, GPVTG &gpvtg) const;
  ErrorCode parseGPZDA(const std::vector<std::string> &data, GPZDA &gpzda) const;

  GPGGA gpgga_;
  GPGLL gpgll_;
  GPGSA gpgsa_;
  GPGSV gpgsv_;
  GPRMC gprmc_;
  GPVTG gpvtg_;
  GPZDA gpzda_;
};
} // end of namespase NEMAParser

#endif // NEMA_PARSER_H_
