// PID: 730677144
// I pledge the COMP 211 honor code.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int num = atoi(argv[1]);

    if (num < -32768 || num > 32767) {
        printf("not possible\n");
        return 0;
    }

    if (argv[1][0] == '-') {
        printf("1");
        num = -num;
    } else {
        printf("0");
    }

    for (int i = 14; i >= 0; i--) {
        if (num >= (1 << i)) {
            printf("1");
            num -= (1 << i);
        } else {
            printf("0");
        }
    }

    printf("\n");
    return EXIT_SUCCESS;
}
