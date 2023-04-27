#include <stdio.h>
#include <pthread.h>

void *hello(void *input) {
    printf("%s\n", (char *)input);
    pthread_exit(NULL);
}

int main(void) {
    pthread_t tid;
    pthread_create(&tid, NULL, hello, "hello world");
    pthread_join(tid, NULL);
    pthread_exit(NULL);
    return 0;
}