#include <cstdlib>
#include <cstdint>
#include <cassert>
#include "xil_printf.h"
#include "xil_cache.h"
#include "xil_types.h"
#include "xparameters.h"
#include "xdata_mover.h"
// #include "xdummy_hash.h"
// #include "xmerkle_tree.h"

#define SIZE 16//262144
#define ALIGNMENT 4096

void* malloc_aligned(std::size_t size, std::size_t alignment) {
    void* original = std::malloc(size + alignment - 1 + sizeof(void*));
    if (!original) return nullptr;

    uintptr_t raw = reinterpret_cast<uintptr_t>(original) + sizeof(void*);
    uintptr_t aligned = (raw + alignment - 1) & ~(alignment - 1);

    // Store original pointer just before the aligned pointer
    reinterpret_cast<void**>(aligned)[-1] = original;

    return reinterpret_cast<void*>(aligned);
}

void free_aligned(void* ptr) {
    if (ptr) {
        std::free(reinterpret_cast<void**>(ptr)[-1]);
    }
}


int main() {
    xil_printf("Loading data...");
    // malloc input buffer
    // uint32_t* input_buffer = static_cast<uint32_t*>(malloc_aligned(SIZE * sizeof(uint32_t), ALIGNMENT));
    uint32_t *input_buffer = (uint32_t *)aligned_alloc(ALIGNMENT, SIZE * sizeof(uint32_t));
    // uint32_t *input_buffer = (uint32_t *)malloc(SIZE * sizeof(uint32_t));
    xil_printf("%016x", (u64)(UINTPTR)input_buffer);
    assert(((u64)(UINTPTR)input_buffer) % ALIGNMENT == 0);
    // static uint32_t input_buffer[8] __attribute__((aligned(64)));
    // init with random data
    // memset(input_buffer, 0, SIZE * sizeof(uint32_t));
    for (int i = 0; i < SIZE; i++) {
        input_buffer[i] = i + 1;
    }

    xil_printf("Pushing Data...");
    
    // flush cache to mem
    // look for how to flush cache in ARM
    Xil_DCacheFlushRange((UINTPTR)input_buffer, SIZE * sizeof(uint32_t));
    
    // set data loader base address (2 calls to set)
    xil_printf("Initializing Data Loader\r\n");
    XData_mover data_mover;
    XData_mover_Initialize(&data_mover, XPAR_DATA_MOVER_0_BASEADDR);
    // set size
    XData_mover_Set_size(&data_mover, SIZE);
    //set buffer
    XData_mover_Set_input_r(&data_mover, (u64)(UINTPTR)input_buffer);
    // start data loader
    XData_mover_Start(&data_mover);
    
    
    // set num of leaves for hasher
    // start hasher
    // wait hasher
    xil_printf("Waiting for data mover\r\n");
    while (!XData_mover_IsDone(&data_mover));

    
    // // Read return value directly from registers
    // xil_printf("Reading return value directly from registers:\r\n");

    // UINTPTR base = XPAR_DUMMY_HASH_0_BASEADDR;
    // for (int i = 0; i < 8; i++) {
    //     uint32_t word = Xil_In32(base + 0x10 + i * 4);
    //     xil_printf("Return word[%d] = %08x\r\n", i, word);
    // }

    
    // read return value of hasher
    // uint32_t hash_result_0 = XDummy_hash_Get_out_0(&dummy_hash);
    // uint32_t hash_result_1 = XDummy_hash_Get_out_1(&dummy_hash);
    // uint32_t hash_result_2 = XDummy_hash_Get_out_2(&dummy_hash);
    // uint32_t hash_result_3 = XDummy_hash_Get_out_3(&dummy_hash);
    // uint32_t hash_result_4 = XDummy_hash_Get_out_4(&dummy_hash);
    // uint32_t hash_result_5 = XDummy_hash_Get_out_5(&dummy_hash);
    // uint32_t hash_result_6 = XDummy_hash_Get_out_6(&dummy_hash);
    // uint32_t hash_result_7 = XDummy_hash_Get_out_7(&dummy_hash);
 
    uint32_t hash_result_0 = XData_mover_Get_out_0(&data_mover);
    uint32_t hash_result_1 = XData_mover_Get_out_1(&data_mover);
    uint32_t hash_result_2 = XData_mover_Get_out_2(&data_mover);
    uint32_t hash_result_3 = XData_mover_Get_out_3(&data_mover);
    uint32_t hash_result_4 = XData_mover_Get_out_4(&data_mover);
    uint32_t hash_result_5 = XData_mover_Get_out_5(&data_mover);
    uint32_t hash_result_6 = XData_mover_Get_out_6(&data_mover);
    uint32_t hash_result_7 = XData_mover_Get_out_7(&data_mover);
    xil_printf("Hash result = 0x");
    xil_printf("%08x ", hash_result_7);
    xil_printf("%08x ", hash_result_6);
    xil_printf("%08x ", hash_result_5);
    xil_printf("%08x ", hash_result_4);
    xil_printf("%08x ", hash_result_3);
    xil_printf("%08x ", hash_result_2);
    xil_printf("%08x ", hash_result_1);
    xil_printf("%08x ", hash_result_0);

    xil_printf("\r\n");
    

    //free memory
    free(input_buffer);

    return 0;
}