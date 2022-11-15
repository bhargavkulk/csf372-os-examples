#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// signal, kill and pause are quite rudimentary and don't really allow
// fine-tuned control of signal handling. Also the forced asynchronosity
// of signal handler causes a lot of problems (race conditions). Many times
// before a critical section we may have to disable(SIG_IGN) a bunch of signals
// so we aren't disturbed in the critical section. And if we disable(SIG_IGN) we
// lose all the signals that reached us during the critical section. There
// should be some facility to block a set of signals before a critical section
// and then go through them all at the end. This and much more (like
// synchronosly waiting for specific signals) are implemented in a new group of
// system functions.

sigset_t set, old_set;
int ret;

int main() {
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGUSR1);

    ret = sigprocmask(SIG_BLOCK, &set, &old_set);
    // A signal that is blocked is one that is not delivered. While it is
    // blocked and not delivered, it said to be pending.

    // ERROR HANDLING!!!
    if(ret != 0) {
        perror("sigprocmask");
    }

    pid_t pid = fork();

    if(pid == -1) {
        perror("fork");
        exit(0);
    } else if(pid == 0) {
        // CHILD PROCESS
        int signum;
        while(true) {
            ret = sigwait(&set, &signum);
            if(ret != 0) {
                printf("sigwait");
                exit(0);
            }
            
            printf("[%d] Child got signal %d.\n", getpid(), signum);
            // THIS IS MY SIGNAL HANDLER!!
            // It is not at all asynchronous.
            // It is completely synchronous.
        }
    } else {
        pause();
    }
    
} 
