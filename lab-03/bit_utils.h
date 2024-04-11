// Do not edit this header file!

#include "assert.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define SIZE sizeof(unsigned int) * 8

// Returns num after mask has been applied.
unsigned int mask(unsigned int num, unsigned int bits);

// Returns num after bits have been set.
unsigned int set(unsigned int num, unsigned int bits);

// Returns num after bits have been inversed.
unsigned int inverse(unsigned int num, unsigned int bits);

// Returns the bits in the number from startbit to
// end bit (including startbit and endbit);
unsigned int bit_select(unsigned int num,
                        unsigned int startbit,
                        unsigned int endbit);

// Returns value of num circularly shifted to the right by
// shamt (shift amount) positions. The bits that are shifted
// out of the right end are put back in at the left end.
// For example, barrel_shift(0x00F0FFFF, 16) is 0xFFFF00F0
unsigned int barrel_shift(unsigned int num, unsigned int shamt);
