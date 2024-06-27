#pragma once

#include <functional>
#include <memory>
#include <string>
#include <iostream>

#include "mock_tmsc.h"
#include "TmscGetValueCommand.h"

template <class invoker>
class TmscFindInterfaceIdOperation {
public:
  using TmscFindInterfaceCallback = std::function<void(bool ok, int interfaceIndex)>;

  TmscFindInterfaceIdOperation() = default;
  ~TmscFindInterfaceIdOperation() = default;

  void action(const std::string& interfaceName, TmscFindInterfaceCallback onCompletedCallback)
  {
    onCompletedCallback_ = onCompletedCallback;
    interfaceName_ = interfaceName;

    auto onGetCommandCompleted = [this](session_error error, tms_result_t result, const tlv_t* value) {
      const char* valueStr = nullptr;
      size_t length = 0;
      if (!checkResult(error, result, tmsc_tlvval_to_str8(value, &valueStr, &length))) {
        std::cout << "Problems in return value\n";
        onCompletedCallback_(false, 0);
      }
      else if (strequal(interfaceName_, valueStr, length)) {
        std::cout << "Found match\n";
        onCompletedCallback_(true, command_->instId_get());
      }
      else {
        command_->incrementInstId();
        if (command_->instId_get() < MAX_NO_OF_INTERFACES) {
          invoker::execute(*command_);
        }
        else {
          std::cout << "No more interfaces\n";
          onCompletedCallback_(false, 0);
        }
      }
      };
    command_ = TmscGetValueCommand::create(OID_IP_NAME, 0, onGetCommandCompleted);
    invoker::execute(*command_);
  }

private:
  static bool checkResult(session_error error, tms_result_t result, int conversionResult) {
    return error == SESS_OK && result == TMS_RES_OK && conversionResult == 0;
  }

  static bool strequal(const std::string& s, const char* valueStr, size_t length)
  {
    if (s.length() != length) {
      return false;
    }
    else {
      return memcmp(s.c_str(), valueStr, length) == 0;
    }
  }

  std::unique_ptr<TmscGetValueCommand> command_;
  std::string interfaceName_;
  TmscFindInterfaceCallback onCompletedCallback_;
};
