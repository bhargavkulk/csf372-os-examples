#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
/*
  sigval_int
  sigval_ptr
 */
void signal_handler(int signum, siginfo_t *siginfo, void *ucontext) {
    printf("I got value %d\n", siginfo->si_int);
}

int main() {
    pid_t pid = getpid();
    struct sigaction act;

    printf("My PID is %d\n", pid);

    act.sa_sigaction = signal_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_RESTART;
    sigaction(SIGUSR1, &act, NULL);

    while (1) ;//sleep(100);
    return EXIT_SUCCESS;
}
