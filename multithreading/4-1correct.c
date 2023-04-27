#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS	8

char *messages[NUM_THREADS];
long taskids[NUM_THREADS];
pthread_t threads[NUM_THREADS];

void *print_hello(void *threadid) {
    long *taskid = (long *)threadid;
    sleep(1);
    printf("Thread %ld: %s\n", *taskid, messages[*taskid]);
    free(taskid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    messages[0] = "English: Hello World!";
    messages[1] = "French: Bonjour, le monde!";
    messages[2] = "Spanish: Hola al mundo";
    messages[3] = "Klingon: Nuq neH!";
    messages[4] = "German: Guten Tag, Welt!"; 
    messages[5] = "Russian: Zdravstvuyte, mir!";
    messages[6] = "Japan: Sekai e konnichiwa!";
    messages[7] = "Latin: Orbis, te saluto!";

    for(int t = 0; t < NUM_THREADS; t++) {
        long *arg = malloc(sizeof(long));
        *arg = t;
        printf("Creating thread %d\n", t);
        int rc = pthread_create(
            &threads[t], 
            NULL, 
            print_hello, 
            (void *) arg
        );
    }

    for(int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    pthread_exit(NULL);
}
