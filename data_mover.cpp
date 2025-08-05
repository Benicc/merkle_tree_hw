#include "data_mover.h"

void data_mover(volatile uint32_t *input, int size, hls::stream<ap_uint<512>> &out, hls::stream<ap_uint<256>> &res,
    uint32_t *out_0,
    uint32_t *out_1,
    uint32_t *out_2,
    uint32_t *out_3,
    uint32_t *out_4,
    uint32_t *out_5,
    uint32_t *out_6,
    uint32_t *out_7) {
#pragma HLS INTERFACE m_axi     port=input offset=slave bundle=gmem
#pragma HLS INTERFACE axis port=out
#pragma HLS INTERFACE s_axilite port=return bundle=control
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=size bundle=control

#pragma HLS INTERFACE s_axilite port=out_0 bundle=control
#pragma HLS INTERFACE s_axilite port=out_1 bundle=control
#pragma HLS INTERFACE s_axilite port=out_2 bundle=control
#pragma HLS INTERFACE s_axilite port=out_3 bundle=control
#pragma HLS INTERFACE s_axilite port=out_4 bundle=control
#pragma HLS INTERFACE s_axilite port=out_5 bundle=control
#pragma HLS INTERFACE s_axilite port=out_6 bundle=control
#pragma HLS INTERFACE s_axilite port=out_7 bundle=control
#pragma HLS INTERFACE axis port=res

    int n_chunks = size / 16;
    // int n_rem_words = size % 16;

    //pack integers words into a packet
    //these words fill the 256 bit width
    for (int i = 0; i < n_chunks; i++) {
        ap_uint<512> packet = 0;
        for (int j = 0; j < 16; j++) {
            ap_uint<32> word = input[i * 16 + j];
            packet.range((j + 1) * 32 - 1, j * 32) = word;
        }
        out.write(packet);
    }

    ap_uint<256> val = res.read();

    *out_0 = (uint32_t)val.range(31, 0);
    *out_1 = (uint32_t)val.range(63, 32);
    *out_2 = (uint32_t)val.range(95, 64);
    *out_3 = (uint32_t)val.range(127, 96);
    *out_4 = (uint32_t)val.range(159, 128);
    *out_5 = (uint32_t)val.range(191, 160);
    *out_6 = (uint32_t)val.range(223, 192);
    *out_7 = (uint32_t)val.range(255, 224);
}

