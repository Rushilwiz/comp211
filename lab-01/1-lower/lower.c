// PID: 730677144
// I pledge the COMP 211 honor code.

#include <stdio.h>
#include <stdlib.h>

int main() {
    char c;
    while ((c = getchar()) != EOF) {
        if (64 < c && c < 91)
            c += 32;
        putchar(c);
    }
}
