#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	pid_t pid;
    union sigval sv;

    if (argc < 2 || (pid = atoi(argv[1])) < 0) exit(EXIT_FAILURE);
    sv.sival_int = 69;
    printf("sender: sending %d to PID %d\n", sv.sival_int, pid);
    sigqueue(pid, SIGUSR1, sv);
    return EXIT_SUCCESS;
}
