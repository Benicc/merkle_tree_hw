#include <hls_stream.h>
#include <ap_int.h>

void dummy_hash(
    hls::stream<ap_uint<512>> &in,
    hls::stream<ap_uint<256>> &out
) {
#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=out
#pragma HLS INTERFACE ap_ctrl_none port=return

    ap_uint<256> dummy_result = 0;

    for (int i = 0; i < 1; i++) {
        ap_uint<512> data = in.read();
        // For dummy: XOR lower 256 bits of all packets
        dummy_result ^= data.range(255, 0);
    }

    // Write ONE final 256-bit dummy hash
    out.write(dummy_result);
}