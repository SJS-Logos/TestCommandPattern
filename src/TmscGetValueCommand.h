#pragma once

#include "mock_tmsc.h"

#include <memory>
#include <functional>
#include <string>

class TmscGetValueCommand {
public:
  using OnCompletedCallback =std::function<void(session_error error, tms_result_t result, const tlv_t* value)>;

  static std::unique_ptr<TmscGetValueCommand> create(
    const std::string& clssid,
    uint32_t instid,
    OnCompletedCallback callback);

  ~TmscGetValueCommand() = default;

  uint32_t instId_get() const;
  const char* clssid_get() const;
  OnCompletedCallback callback_get() const;

  void incrementInstId();

  template <typename invoker>
    void execute() { invoker::execute(this); }

private:
  TmscGetValueCommand(const std::string& clssid, uint32_t instid, OnCompletedCallback callback);

  const std::string clssid_;
  uint32_t instid_;
  OnCompletedCallback callback_;
};
