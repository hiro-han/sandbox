#ifndef ERROR_H_
#define ERROR_H_

namespace NEMAParser {

enum class ErrorCode {
  kNoError         = 0,
  kFormatInvalid   = 1,
  kUnsupportFormat = 2,
  kGPGGAInvalid    = 3,
  kGPRMCInvalid    = 4,
  kGPGLLInvalid    = 5,
  kGPGSAInvalid    = 6,
  kGPGSVInvalid    = 7,
  kGPVTGInvalid    = 8,
  kGPZDAInvalid    = 9,
};

} // end of namespase NEMAParser

#endif // ERROR_H_
