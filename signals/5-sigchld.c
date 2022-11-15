#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

int ret;
void SIGCHLD_handler(int signum);

int main() {

    signal(SIGCHLD, SIGCHLD_handler);
    // Installing the handler
    
    pid_t pid = fork();

    int a, b;
    a = b = 1;

    switch(pid) {
    case -1:
        perror("fork: ");
        exit(0);
    case 0:
        // Child Process
        // The child is doing some computationally intensive process, in this
        // case calculating Fibonacci numbers.
        printf("[%d] %d\n[%d] %d\n", getpid(), a, getpid(), b);
        for(int i = 2; i <= 10; i++) {
            sleep(1);
            int res = a + b;
            printf("[%d] %d\n", getpid(), res);
            a = b;
            b = res;
            
        }

        printf("[%d] My parent, %d, has abandoned me...\n", getpid(), getppid());
        exit(0);
    default:
        // Parent Process
        // Parent does not want to "wait" for the child process, because it has
        // its own things to do.

        while(true) {
            // A case of negligence...
        }
        
    }
}

void SIGCHLD_handler(int signum) {
    // Parent wakes up and realizes it needs to take care of its child.
    int status;
    pid_t ret = wait(&status);
    if(ret == -1) {
        perror("wait: ");
        exit(0);
    }

    printf("[%d] I have taken care of my child, %d \n", getpid(), ret);

    exit(0);
}
