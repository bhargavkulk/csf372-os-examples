#include <stdio.h>

int get_global();

extern int global;

int main() {
    int val = get_global();
    printf("%d\n", val);

    global += 500;

    val = get_global();
    printf("%d\n", val);
}