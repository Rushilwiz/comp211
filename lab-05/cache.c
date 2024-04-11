// PID: 730677144
// I pledge the COMP 211 honor code.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bit_utils.h"
#include "cache.h"
#include "memory.h"

/**
 * Global variables. The extern ones are initialized in memory.c and are
 * accessible via the extern keyword
 */

extern unsigned int* phy_memory;
extern unsigned int* block_location;
extern unsigned int addr_bits;
cache_line** cache;

int initialize_cache(unsigned int number_of_lines) {
    unsigned int line;

    // Allocate memory for the cache (array of cache lines).
    cache = malloc(sizeof(cache_line*) * number_of_lines);

    // For each cache line, allocate memory and initialize the cache line.
    if (cache != NULL) {
        for (line = 0; line < number_of_lines; line++) {
            cache[line] = (cache_line*)malloc(sizeof(cache_line));
            cache[line]->tag = EMPTY;
            cache[line]->hit_count = 0;
            cache[line]->block =
                malloc(sizeof(unsigned int) * (int)exp2(NUM_BLOCK_OFFSET_BITS));
        }
    } else {
        return FAIL;
    }

    return OK;
}

int cread(unsigned int cmf, unsigned int* hex_addr, bool* hit, bool* replace) {
    // Either the value at the requested hexadecimal address or FAIL
    int ret_val = FAIL;

    // Initialize these variables by
    // extracting the line (for DM, not FA), tag, and block offset bits from
    // hex_addr
    unsigned int line, tag, block_offset;

    // (Optional) Indicates a line that is open and thus usable
    int open_line;
    // (Optional) For DM, indicates the cache line that should be replaced
    int replace_line;

    // For FA, keeps track of LFU cache line
    int min_hit_cnt = (int)1E10;
    // For FA, keeps track of index of LFU cache line
    int min_line;

    // Variables that are passed by reference
    // Must indicate to the driver code whether there was a cache hit and
    // whether we had to overwrite and replace something
    *hit = false;
    *replace = false;

    if ((cmf == DM) && ((*hex_addr) < exp2(addr_bits))) {
        tag = bit_select(*hex_addr, addr_bits - 1, addr_bits - NUM_TAG_BITS_DM);
        line = bit_select(*hex_addr, addr_bits - NUM_TAG_BITS_DM - 1,
                          NUM_BLOCK_OFFSET_BITS);
        block_offset = bit_select(*hex_addr, NUM_BLOCK_OFFSET_BITS - 1, 0);

        if (cache[line]->tag == tag) {
            // hit
            *hit = true;
            cache[line]->hit_count++;
            ret_val = cache[line]->block[block_offset];
        } else {
            // miss
            if (cache[line]->tag == EMPTY) {
                open_line = line;
            } else {
                replace_line = line;
                *replace = true;
            }

            cache[line]->tag = tag;
            cache[line]->hit_count = 1;

            unsigned int mem_index =
                block_location[*hex_addr >> NUM_BLOCK_OFFSET_BITS];

            memcpy(cache[line]->block, phy_memory + mem_index,
                   sizeof(unsigned int) * (int)exp2(NUM_BLOCK_OFFSET_BITS));

            ret_val = cache[line]->block[block_offset];
        }

    } else if ((cmf == FA) && ((*hex_addr) < exp2(addr_bits))) {
        tag = bit_select(*hex_addr, addr_bits - 1, addr_bits - NUM_TAG_BITS_FA);
        block_offset = bit_select(*hex_addr, NUM_BLOCK_OFFSET_BITS - 1, 0);

        for (line = 0; line < NUM_LINES; line++) {
            if (cache[line]->tag == tag) {
                // hit
                *hit = true;
                cache[line]->hit_count++;
                ret_val = cache[line]->block[block_offset];
                break;
            }
        }

        if (!(*hit)) {
            for (line = 0; line < NUM_LINES; line++) {
                if (cache[line]->tag == EMPTY) {
                    replace_line = line;
                    break;
                }
            }

            if (line == NUM_LINES) {
                for (line = 0; line < NUM_LINES; line++) {
                    if (cache[line]->hit_count < min_hit_cnt) {
                        min_hit_cnt = cache[line]->hit_count;
                        min_line = line;
                    }
                }

                replace_line = min_line;
                *replace = true;
            }

            cache[replace_line]->tag = tag;
            cache[replace_line]->hit_count = 1;

            unsigned int mem_index =
                block_location[*hex_addr >> NUM_BLOCK_OFFSET_BITS];

            memcpy(cache[replace_line]->block, phy_memory + mem_index,
                   sizeof(unsigned int) * (int)exp2(NUM_BLOCK_OFFSET_BITS));

            ret_val = cache[replace_line]->block[block_offset];
        }
    }

    // Print state of cache after mapping algorithm is applied
    cprint();

    return ret_val;
}

void cprint() {
    unsigned int line;

    printf("\n---------------------------------------------\n");
    printf("line\ttag\tnum of hits\n");
    printf("---------------------------------------------\n");

    for (line = 0; line < NUM_LINES; line++) {
        if (cache[line]->tag == EMPTY) {
            printf("%d\t%d\t%d\n", line, cache[line]->tag,
                   cache[line]->hit_count);
        } else {
            printf("%d\t%02X\t%d\n", line, cache[line]->tag,
                   cache[line]->hit_count);
        }
    }
}
