#ifndef VEC_H
#define VEC_H

#include <stddef.h>

struct vector {
    size_t count;
    size_t capacity;
    int *arr;
};

typedef struct vector vec_t;

void vec_init(vec_t *vec);
void vec_destroy(vec_t *vec);

void vec_append(vec_t *vec, int value);
int vec_get(vec_t *vec, size_t index);
void vec_set(vec_t *vec, size_t index, int value);

#endif