#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

struct args {
    int a;
    int b;
    int sum;
};

void *sum_thread(void *_args) {
    struct args *args = (struct args *) _args;

    args->sum = args->a + args->b;
    pthread_exit (NULL);
}

int main() {
    pthread_t child;

    struct args *args = malloc(sizeof (struct args));
    args->a = 5;
    args->b = 8;

    pthread_create (&child, NULL, sum_thread, args);
    pthread_join (child, NULL);
    printf ("%d + %d = %d\n", args->a, args->b, args->sum);
    free (args);

    return 0;
}