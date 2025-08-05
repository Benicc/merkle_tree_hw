#include <cstdint>
#include <ap_int.h>
#include <hls_stream.h>

void data_mover(volatile uint32_t *input, int size, hls::stream<ap_uint<512>> &out);