// PID: 730677144
// I pledge the COMP 211 honor code.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char input[33];
    char output[33] = {'\0'};

    strncpy(input, argv[1], 32);
    input[32] = '\0';

    for (int i = 0; i < 32; i++)
        output[i] = (input[i] == '0') ? '1' : '0';

    output[32] = '\0';

    if (input[0] == '1') {
        int carry = 1;
        for (int i = 31; i >= 0 && carry; i--) {
            output[i] = (input[i] == '0') ? '1' : '0';
            if (input[i] == '0')
                carry = 0;
        }
    } else {
        int i = 31;
        while (input[i] == '0' && i >= 0) {
            output[i] = '0';
            i--;
        }

        output[i] = '1';
    }

    printf("%s\n", output);
    return EXIT_SUCCESS;
}