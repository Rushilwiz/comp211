// Do not edit this file

#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>

// Return values

#define OK 0
#define FAIL -1

// Cache mapping functions

#define DM 1  // Direct Mapping
#define FA 2  // Fully Associative

// Simulation parameters

#define NUM_LINE_BITS 3
#define NUM_TAG_BITS_DM 3
#define NUM_TAG_BITS_FA 6
// exp2(NUM_LINE_BITS)
#define NUM_LINES (1 << NUM_LINE_BITS)

// If cache_line->tag is EMPTY, then the cache line is considered empty
#define EMPTY -1

/**
 * See cache.c initialize_cache() function to see how this struct is used
 */
typedef struct {
    int tag;
    int hit_count;
    unsigned int* block;
} cache_line;

/**
 * Initializes the cache array.
 *
 * Each element in the cache array is a cache_line struct.
 *
 * Parameters:
 *  number_of_lines: number of lines in the cache
 * Return:
 *  OK (success) | FAIL (error)
 */
int initialize_cache(unsigned int number_of_lines);

/**
 * Reads the cache and returns the byte at the specified physical memory address
 * location.
 *
 * Note that hit and replace are passed by reference (pointers). You must set
 * these values correctly to indicate to the driver function whether there was a
 * cache hit and whether there was a replacement. These two variables behave as
 * "return values" even though they are parameters.
 *
 * Parameters:
 *  cmf: cache mapping function, either DM or FA
 *  hex_addr: memory address pointer
 *  hit: set to true on cache hit, false on cache miss
 *  replace: set to true if a cache replacement was performed, false otherwise
 * Return:
 *  byte value at specified memory location (success) | FAIL (error)
 */
int cread(unsigned int cmf, unsigned int* hex_addr, bool* hit, bool* replace);

/**
 * Displays the cache, for debugging purposes
 *
 * Parameters:
 *  none
 * Return:
 *  void
 */
void cprint();

#endif  // CACHE_H
