// PID: 730677144
// I pledge the COMP 211 honor code.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // convert a IEEE 754 single precision floating point number to a 32-bit
    // integer
    char input[33];
    char exponent[9];
    char mantissa[24];

    strncpy(input, argv[1], 32);
    input[32] = '\0';

    strncpy(exponent, input + 1, 8);
    strncpy(mantissa, input + 9, 23);

    int sign = (input[0] == '1') ? -1 : 1;

    long int exp = strtol(exponent, NULL, 2) - 127;

    float frac = 1.0;

    for (int i = 0; i < 23; i++) {
        if (mantissa[i] == '1') {
            frac += pow(2, -i - 1);
        }
    }

    float result = sign * frac * pow(2, exp);

    printf("%.4f\n", result);
}
