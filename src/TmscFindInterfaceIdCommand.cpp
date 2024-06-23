#pragma once

#include "TmscFindInterfaceIdCommand.h"
#include <iostream>

static
bool checkResult(session_error error, tms_result_t result, int conversionResult) {
  return error == SESS_OK && result == TMS_RES_OK && conversionResult == 0;
}

// Compare a std::string and a const char* which is not zero terminated
static
bool strequal(const std::string& s, const char* valueStr, size_t length)
{
  if (s.length() != length) {
    return false;
  }
  else {
    return memcmp(s.c_str(), valueStr, length) == 0;
  }
}

TmscFindInterfaceIdCommand::TmscFindInterfaceIdCommand(
  const std::string& interfaceName,
  std::function<void(bool ok, int interfaceIndex)> callback,
  uint32_t maxNoOfInterfaces)
  : interfaceName_(interfaceName), callback_(callback), maxNoOfInterfaces_(maxNoOfInterfaces) {

  command_ = TmscGetValueCommand::create(
    OID_IP_NAME, 0,
    [this](session_error error, tms_result_t result, const tlv_t* value) {
      const char* valueStr = nullptr;
      size_t length = 0;
      if (!checkResult(error, result, tmsc_tlvval_to_str8(value, &valueStr, &length))) {
        std::cout << "Problems in return value\n";
        callback_(false, 0);
      }
      else if ( strequal( interfaceName_, valueStr, length) ) {
        std::cout << "Found match\n";
        callback_(true, command_->getInstId());
      }
      else {
        command_->incrementInstId();
        if (command_->getInstId() < maxNoOfInterfaces_) {
          execute();
        }
        else {
          std::cout << "No more interfaces\n";
          callback_(false, 0);
        }
      }
    }
  );
}

void TmscFindInterfaceIdCommand::execute() {
  std::cout << "Try " << command_->getInstId() << "\n";
  command_->execute();
}
