// PID: 730677144
// I pledge the COMP 211 honor code.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int num = abs(atoi(argv[1]));
    char out[17] = "\0";

    if (num > 65535) {
        printf("not possible\n");
        return 0;
    }

    for (int i = 15; i >= 0; i--) {
        if (num >= (1 << i)) {
            out[15 - i] = '1';
            num -= (1 << i);
        } else {
            out[15 - i] = '0';
        }
    }

    if (argv[1][0] == '-') {
        for (int i = 0; i < 16; i++) {
            if (out[i] == '0') {
                out[i] = '1';
            } else {
                out[i] = '0';
            }
        }

        for (int i = 15; i >= 0; i--) {
            if (out[i] == '1') {
                out[i] = '0';
            } else {
                out[i] = '1';
                break;
            }
        }
    }

    printf("%s\n", out);

    return EXIT_SUCCESS;
}
