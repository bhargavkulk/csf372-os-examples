#include <stdio.h>
#include "vec.h"

void print_vec(vec_t *vec) {
    for (int i = 0; i < vec->count; i++) {
        int val = vec_get(vec, i);
        printf("%d ", val);
    }
    printf("\n");
}

int main() {
    vec_t vec;
    vec_init(&vec);

    for (int i = 0; i < 10; i++) {
        vec_append(&vec, i * 10);
    }

    print_vec(&vec);

    vec_set(&vec, 5, 400);

    print_vec(&vec);

    vec_destroy(&vec);
}