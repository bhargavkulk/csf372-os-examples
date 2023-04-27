#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

struct args {
    int a;
    int b;
};

void *sum_thread (void *_args) {
    struct args *args = (struct args *) _args;
    
    int *ret = malloc(sizeof(int));
    *ret = args->a + args->b;
    pthread_exit((void *) ret);
}

int main() {
    pthread_t child;

    struct args *args = malloc(sizeof (struct args));
    args->a = 5;
    args->b = 8;

    pthread_create(&child, NULL, sum_thread, args);

    /* Wait for thread to finish and retrieve the void* into sum */
    void *sum = NULL;
    pthread_join (child, &sum);
    printf ("%d + %d = %d\n", args->a, args->b, *(int *)sum);

    /* Clean up the struct instance */
    free(args);
    free(sum);

    return 0;
}


