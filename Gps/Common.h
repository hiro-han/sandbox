#ifndef COMMON_H_
#define COMMON_H_

#include <string>
#include <iostream>

namespace NEMAParser {
namespace Common {

inline float convertToFloat(const std::string &str) {
  if (str.empty()) {
    return 0.0;
  } else {
    return std::stof(str);
  }
}

inline int convertToInt(const std::string &str, const int base) {
  if (str.empty()) {
    return 0;
  } else {
    return std::stoi(str, nullptr, base);
  }
}

inline int convertToIntFromDecimal(const std::string &str) {
  if (str.empty()) {
    return 0;
  } else {
    return convertToInt(str, 10);
  }
}

inline int convertToIntFromHex(const std::string &str) {
  if (str.empty()) {
    return 0;
  } else {
    return convertToInt(str, 16);
  }
}

} // end of namespase Common
} // end of namespase NEMAParser

#endif // COMMON_H_
