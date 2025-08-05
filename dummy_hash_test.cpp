#include <hls_stream.h>
#include <ap_int.h>
#include "dummy_hash.h"
// #include <cstdlib.h>

#define TEST_SIZE 8

int main() {
    uint32_t input_data[TEST_SIZE];

    // Initialize input data
    for (int i = 0; i < TEST_SIZE; ++i) {
        input_data[i] = i + 1;
    }

    hls::stream<ap_uint<256>> out_stream;

    ap_uint<256> packet = 0;
    for (int i = 0; i < TEST_SIZE; i++) {
        ap_uint<32> word = i + 1;
        packet.range((i + 1) * 32 - 1, i * 32) = word;
        std::cout << "packet word[" << packet << "] = 0x" << (uint32_t) word << "\n";
    }
    out_stream.write(packet);

    uint32_t out_0 = 0; 
    uint32_t out_1 = 0; 
    uint32_t out_2 = 0; 
    uint32_t out_3 = 0; 
    uint32_t out_4 = 0; 
    uint32_t out_5 = 0; 
    uint32_t out_6 = 0; 
    uint32_t out_7 = 0; 
    dummy_hash(out_stream, TEST_SIZE, &out_0, &out_1, &out_2, &out_3, &out_4, &out_5, &out_6, &out_7);

    std::cout << "Result0: " << out_0 << "\r\n";
    std::cout << "Result1: " << out_1 << "\r\n";
    std::cout << "Result2: " << out_2 << "\r\n";
    std::cout << "Result3: " << out_3 << "\r\n";
    std::cout << "Result4: " << out_4 << "\r\n";
    std::cout << "Result5: " << out_5 << "\r\n";
    std::cout << "Result6: " << out_6 << "\r\n";
    std::cout << "Result7: " << out_7 << "\r\n";
    // while (!out_stream.empty()) {
    //     ap_uint<256> packet = out_stream.read();
    //     for (int i = 0; i < 8; i++) {
    //         ap_uint<32> word = packet.range((i + 1) * 32 - 1, i * 32);
    //         std::cout << "  Word[" << i << "]: " << word << std::endl;
    //     }
    // }

    return 0;
}