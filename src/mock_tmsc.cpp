#include "mock_tmsc.h"
#include <thread>
#include <chrono>

void tmsc_get_value(const char* clssid, uint32_t instid, tmsc_get_value_cb cb, void* req_ctxt) {
  // Create a thread to simulate the delay and callback invocation
  std::thread([=]() {
    // Simulate a delay of 100 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Invoke the callback after the delay
    cb(SESS_OK, TMS_RES_OK, nullptr, req_ctxt);
    }).detach(); // Detach the thread to allow it to run independently
}

int tmsc_tlvval_to_str8(const tlv_t* ptlv_value, const char** p_value, size_t* p_value_len) {
  static int numberOfTries = 0;
  if (numberOfTries < 3) {
    *p_value = "";
    *p_value_len = 0;
  }
  else {
    *p_value = "hello";
    *p_value_len = 5;
  }
  numberOfTries++;
  return 0;
}

