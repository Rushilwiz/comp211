/**
 * Test/runner file for bit_utils.c
 * Run the tests here with `make test_all`, `make test_mask`, etc.
 * This file is not meant to be run directly
 *
 * You may write tests and debug here, but note when submitting, all
 * changes you make will not be kept. So, you may add tests, but you should
 * not remove any.
 * To see the hex representation of an int, use format specifier %x
 */
#include "bit_utils.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr,
                "test.c requires at least one argument to select the function "
                "to test\n");
        return EXIT_FAILURE;
    }
    char* fun_name = argv[1];
    if (strcmp("mask", fun_name) == 0) {
        assert(mask(0x00F7, 0x000F) == 0x0007);
        assert(mask(0x07e081aa, 0xF0FF) == 0x80aa);
        assert(mask(0x07e081aa, 0xFFFFFFFF) == 0x7e081aa);
    } else if (strcmp("set", fun_name) == 0) {
        assert(set(0x00F7, 0x000F) == 0x00FF);
        assert(set(0xf70000aa, 0x0abcF0) == 0xf70abcfa);
        assert(set(0xdeadbeef, 0x00000000) == 0xdeadbeef);
    } else if (strcmp("inverse", fun_name) == 0) {
        assert(inverse(0x00F7, 0x000F) == 0x00F8);
        assert(inverse(0xf73123aa, 0xc0FFF0) == 0xf7f1dc5a);
        assert(inverse(0xf73123aa, 0x00000000) == 0xf73123aa);
    } else if (strcmp("bit_select", fun_name) == 0) {
        assert(bit_select(0xE7E7, 3, 0) == 0x7);
        assert(bit_select(0xE7E7, 7, 0) == 0xE7);
        assert(bit_select(0xE7E7, 6, 1) == 0x33);
        assert(bit_select(0x07654321, 7, 4) == 2);
        assert(bit_select(0x00F0, 6, 4) == 7);
        assert(bit_select(0xF, 3, 3) == 1);
        assert(bit_select(0xF1111111, 31, 31) == 1);
    } else if (strcmp("barrel_shift", fun_name) == 0) {
        assert(barrel_shift(0x00F0FFFF, 16) == 0xFFFF00F0);
        assert(barrel_shift(0xdeadbeef, 12) == 0xeefdeadb);
    } else {
        fprintf(stderr, "function name invalid\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
