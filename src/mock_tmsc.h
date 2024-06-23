#pragma once
#include <cstdint>

#define MAX_NO_OF_INTERFACES 4
#define OID_IP_NAME ""


enum session_error {
  SESS_OK
};
enum tms_result_t {
  TMS_RES_OK
};


struct tlv_t {
};

int tmsc_tlvval_to_str8(const tlv_t* ptlv_value, const char** p_value, size_t* p_value_len);

typedef void (*tmsc_get_value_cb)(session_error error, enum tms_result_t result, const tlv_t* value, void* req_ctxt);

void tmsc_get_value(const char* clssid, uint32_t instid, tmsc_get_value_cb cb, void* req_ctxt);

