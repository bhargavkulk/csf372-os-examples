#include <stdio.h>

// Try compiling this program like this:
// gcc 2-main.c
// you should see an error, because add is not defined just declared!

// compile 2-main.c and 2-add.c together!
// gcc 2-main.c 2-add.c

int add(int a, int b);

int main() {
    printf("%d\n", add(1, 1));
}