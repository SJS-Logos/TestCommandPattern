#pragma once

#include "TmscFindInterfaceIdCommand.h"

 bool checkResult(session_error error, tms_result_t result, int conversionResult) {
    return error == SESS_OK && result == TMS_RES_OK && conversionResult == 0;
  }

 bool strequal(const std::string & s, const char* valueStr, size_t length)
  {
  if (s.length() != length) {
    return false;
  }
  else {
    return memcmp(s.c_str(), valueStr, length) == 0;
  }
}
