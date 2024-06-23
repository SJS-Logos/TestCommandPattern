#include "TmscGetValueCommand.h"

TmscGetValueCommand::TmscGetValueCommand(const std::string& clssid, uint32_t instid,
  OnCompletedCallback callback)
  : clssid_(clssid), instid_(instid), callback_(callback) {}

std::unique_ptr<TmscGetValueCommand> TmscGetValueCommand::create(
  const std::string& clssid, uint32_t instid, OnCompletedCallback callback) {
  return std::unique_ptr<TmscGetValueCommand>(new TmscGetValueCommand(clssid, instid, callback));
}

uint32_t TmscGetValueCommand::instId_get() const {
  return instid_;
}

const char* TmscGetValueCommand::clssid_get() const
{
  return clssid_.c_str();
}

TmscGetValueCommand::OnCompletedCallback TmscGetValueCommand::callback_get() const
{
  return callback_;
}

void TmscGetValueCommand::incrementInstId() {
  ++instid_;
}
