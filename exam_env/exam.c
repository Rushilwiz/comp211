#include <stdio.h>
#include <stdlib.h>

int main() {
    short a = -3;
    int b = (int) a;
    unsigned short c = (unsigned short) a;
    unsigned int d = (unsigned int) c;

    // The "h" modifier here tells printf that
    // a is a short. Otherwise the value would
    // be treated like an int.
    printf("%hx\n", a);
    printf("%x\n", b);
    printf("%hx\n", c);
    printf("%x\n", d);

    return EXIT_SUCCESS;
}

