// PID: 730677144
// I pledge the COMP 211 honor code.

#include <stdio.h>
#include <stdlib.h>

int main() {
    int lines[100];
    int total, chars, cur, c;

    total = 0;
    chars = 0;
    cur = 0;

    while ((c = getchar()) != EOF) {
        chars++;

        if (c == '\n') {
            chars = 0;
            cur++;
            putchar(c);
        } else if (chars > 50) {
            if (total == 0 || lines[total - 1] != cur) {
                lines[total] = cur;
                total++;
            }

            chars = 1;
            putchar('\n');
            putchar(c);
        } else {
            putchar(c);
        }
    }

    printf("\nTotal lines over 50 chars: %d\n", total);
    printf("Offending lines: ");
    for (int i = 0; i < total; i++) {
        printf("%d, ", lines[i]);
    }
    printf("\n");
    return 0;
}
