#pragma once

#include "./mock_tmsc.h"

#include <memory>
#include <functional>
#include <string>

class TmscGetValueCommand {
public:
  static std::unique_ptr<TmscGetValueCommand> create(
    const std::string& clssid,
    uint32_t instid,
    std::function<void(session_error error, tms_result_t result, const tlv_t* value)> callback);

  ~TmscGetValueCommand() = default;

  void execute();
  uint32_t getInstId() const;
  void incrementInstId();

private:
  TmscGetValueCommand(const std::string& clssid, uint32_t instid,
    std::function<void(session_error error, tms_result_t result, const tlv_t* value)> callback);

  static void staticCallback(session_error error, tms_result_t result, const tlv_t* value, void* reqCtxt);

  const std::string clssid_;
  uint32_t instid_;
  std::function<void(session_error error, tms_result_t result, const tlv_t* value)> callback_;
};
