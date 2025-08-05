#include <ap_int.h>
#include <cstdint>
#include <hls_stream.h>

void dummy_hash(hls::stream<ap_uint<256>> &in_stream, int size, uint32_t *out_0, 
    uint32_t *out_1, uint32_t *out_2, uint32_t *out_3, uint32_t *out_4,
    uint32_t *out_5, uint32_t *out_6, uint32_t *out_7);