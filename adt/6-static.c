#include <stdio.h>

void increment_and_print() {
    static int i = 0;

    i += 1;
    printf("%d\n", i);
}

int main() {
    for (int i = 0; i < 5; i++) {
        increment_and_print();
    }
}