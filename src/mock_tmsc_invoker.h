#pragma once

#include "mock_tmsc.h"
#include "TmscGetvalueCommand.h"

class mock_tmsc_invoker {
public:
  static void execute(TmscGetValueCommand& command)
  {
    tmsc_get_value(command.clssid_get(), command.instId_get(), staticCallback, static_cast<void*>(&command));
  }

private:
  static void staticCallback(session_error error, tms_result_t result, const tlv_t* value, void* reqCtxt) {
    TmscGetValueCommand* self = static_cast<TmscGetValueCommand*>(reqCtxt);
    TmscGetValueCommand::OnCompletedCallback cb = self->callback_get();
    cb(error, result, value);
  }
};
