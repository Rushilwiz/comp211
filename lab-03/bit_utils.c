// PID: 730677144
// I pledge the COMP 211 honor code.

/**
 * DO NOT define a main function in this file!
 * This file is intended to be a library file, so a main function here
 * will conflict with the main function in test.c (our "runner" file)
 * To test your functions, write tests in test.c
 */

#include "bit_utils.h"

unsigned int mask(unsigned int num, unsigned int bits) {
    return num & bits;
}

unsigned int set(unsigned int num, unsigned int bits) {
    return num | bits;
}

unsigned int inverse(unsigned int num, unsigned int bits) {
    return num ^ bits;
}

unsigned int bit_select(unsigned int num,
                        unsigned int startbit,
                        unsigned int endbit) {
    unsigned int shifted = num >> endbit;
    unsigned int bit_count = startbit - endbit + 1;
    unsigned int mask = (1 << bit_count) - 1;
    return shifted & mask;
}

unsigned int barrel_shift(unsigned int num, unsigned int shamt) {
    const unsigned int bit_width = sizeof(unsigned int) * 8;

    shamt %= bit_width;

    if (shamt == 0) {
        return num;
    }
    unsigned int right_part = num >> shamt;
    unsigned int left_part = num << (bit_width - shamt);

    return right_part | left_part;
}
