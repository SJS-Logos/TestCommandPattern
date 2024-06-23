#include "TmscGetValueCommand.h"

TmscGetValueCommand::TmscGetValueCommand(const std::string& clssid, uint32_t instid,
  std::function<void(session_error error, tms_result_t result, const tlv_t* value)> callback)
  : clssid_(clssid), instid_(instid), callback_(callback) {}

std::unique_ptr<TmscGetValueCommand> TmscGetValueCommand::create(
  const std::string& clssid, uint32_t instid, std::function<void(session_error error, tms_result_t result, const tlv_t* value)> callback) {
  return std::unique_ptr<TmscGetValueCommand>(new TmscGetValueCommand(clssid, instid, callback));
}

void TmscGetValueCommand::execute() {
  tmsc_get_value(clssid_.c_str(), instid_, staticCallback, static_cast<void*>(this));
}

uint32_t TmscGetValueCommand::getInstId() const {
  return instid_;
}

void TmscGetValueCommand::incrementInstId() {
  ++instid_;
}

void TmscGetValueCommand::staticCallback(session_error error, tms_result_t result, const tlv_t* value, void* reqCtxt) {
  auto* self = static_cast<TmscGetValueCommand*>(reqCtxt);
  self->callback_(error, result, value);
}
