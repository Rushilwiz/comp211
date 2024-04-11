// PID: 730677144
// I pledge the COMP 211 honor code.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bit_utils.h"
#include "memory.h"

// Global variables

unsigned int* phy_memory;
unsigned int* block_location;
unsigned int addr_bits;

int number_of_blocks(unsigned int addr_bits,
                     unsigned int num_block_offset_bits) {
    if (addr_bits < num_block_offset_bits || num_block_offset_bits <= 0 ||
        addr_bits <= 0)
        return FAIL;

    return exp2(addr_bits - num_block_offset_bits);
}

int read_memory_file(char* file_name) {
    int addr_cnt = 0;

    FILE* fhnd;
    fhnd = fopen(file_name, "r");

    if (fhnd != NULL) {
        phy_memory = malloc(sizeof(unsigned int) * MAX_SIZE);

        int fscanf_rv;

        // For each line, increment total address count and store value in
        // phy_memory.
        while ((fscanf_rv = fscanf(fhnd, "%x\n", &phy_memory[addr_cnt])) != EOF)
            addr_cnt++;

        phy_memory[addr_cnt] = '\0';
        fclose(fhnd);
    } else {
        // If fopen didn't work, no addresses of physical memory were counted.
        addr_cnt = FAIL;
        fprintf(stderr, "Error: Could not open file %s\n", file_name);
    }

    if (MEM_DEBUG)
        printf("Number of bytes read: %d\n", addr_cnt);

    if (addr_cnt != FAIL)
        return ceil(log2(addr_cnt));
    else
        return FAIL;
}

void initialize_block_pointers(unsigned int num_blocks,
                               unsigned int num_block_offset_bits) {
    int i;

    /**
     * Here, we create a mapping to the starting addresses of each block.
     * Blocks are groupings of physical memory into chunks.
     * For example, if num_block_offset_bits is 3, then each block is size 2^3.
     * The block locations would be [0, 8, 16, 24, ...]
     */

    block_location = malloc(sizeof(unsigned int) * num_blocks);

    for (i = 0; i < num_blocks; i++) {
        block_location[i] = i * exp2(num_block_offset_bits);

        if (MEM_DEBUG)
            printf("starting block address (base-16) %02X (%d base-10)\n",
                   block_location[i], block_location[i]);
    }
}
