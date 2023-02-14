#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "vec.h"

#define INITIAL_CAPACITY 8

void vec_init(vec_t *vec) {
    assert(vec != NULL);

    vec->count = 0;
    vec->capacity = INITIAL_CAPACITY;
    vec->arr = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    if(vec->arr == NULL) {
        perror("malloc");
        exit(1);
    }
}

void vec_destroy(vec_t *vec) {
    assert(vec != NULL);
    assert(vec->arr != NULL);

    free(vec->arr);
}

int vec_get(vec_t *vec, size_t index) {
    assert(vec != NULL);
    assert(vec->arr != NULL);
    assert(index < vec->count);
    
    return vec->arr[index];
}

void vec_set(vec_t *vec, size_t index, int value) {
    assert(vec != NULL);
    assert(vec->arr != NULL);
    assert(index < vec->count);

    vec->arr[index] = value;
}

void vec_append(vec_t *vec, int value) {
    assert(vec != NULL);
    assert(vec->arr != NULL);

    if (vec->count < vec->capacity) {
        vec->arr[vec->count] = value;
        vec->count += 1;
        return;
    }

    vec->arr = (int *) realloc(vec->arr, vec->capacity * 2 * sizeof(int));
    if(vec->arr == NULL) {
        perror("realloc");
        exit(1);
    }
    vec->capacity *= 2;
    vec_append(vec, value);
}