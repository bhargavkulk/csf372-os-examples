#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int ret;

void child_handler(int signum) {
    printf("[%d] Handled.\n", getpid());
    printf("[%d] Sending signal to %d.\n", getpid(), getppid());
    sleep(1);
    kill(getppid(), SIGUSR2);
}

void parent_handler(int signum) {
    printf("[%d] Handled.\n", getpid());
}

int main() {
    pid_t pid = fork();

    switch(pid) {
    case -1:
        // ERROR HANDLING!!!
        perror("fork: ");
        exit(0);
    case 0:
        // Child Process
        signal(SIGUSR1, child_handler);
        // SIGUSR1 and SIGUSR2 are two signals that don't have any OS-specific
        // use. They are left for you to use for any purpose in your
        // applications.

        printf("[%d] Waiting for parent.\n", getpid());
        pause();
        // pause makes the calling process to sleep until it recives a signal
        // that either terminates it or calles a signal handling function.
        // as always: man pause
        break;
    default:
        // Parent Process
        signal(SIGUSR2, parent_handler);

        printf("[%d] Sending signal to %d.\n", getpid(), pid);
        sleep(1);
        ret = kill(pid, SIGUSR1);
        // kill(pid_t pid, int signum)
        // kill is used to send a specified signal to a process or a group of
        // processes.
        // if pid > 0, kill sends signum to that pid (if it exists)
        // if pid == 0, kill sends signum to all processes that have the same
        //              group id as the calling process
        // if pid == -1, kill sends signum to all processes it can send signals
        //               to
        // if pid < -1, kill sends signum to all processes whose group id is
        //              -pid

        // ERROR HANDLING!!!
        if(ret == -1) {
            perror("kill: ");
            exit(0);
        }
                             
        printf("[%d] Waiting for response from %d.\n", getpid(), pid);
        pause();
    }
}
