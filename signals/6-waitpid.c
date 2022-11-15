#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

int ret;
void SIGCHLD_handler(int signum);

int child_caught = 0;

void fibonacci() {
    int a = 0, b = 1, res;
    printf("[%d] %d\n", getpid(), a);
    sleep(1);
    printf("[%d] %d\n", getpid(), b);
    for(int i = 2; i <= 15; i++) {
        sleep(1);
        res = a + b;
        printf("[%d] %d\n", getpid(), res);
        a = b;
        b = res;
    }

    printf("[%d] My Parent, %d, has abandoned me...\n", getpid(), getppid());

    exit(0);
}

void tables() {
    for(int i = 0; i < 10; i++) {
        printf("[%d] 2 * %d = %d\n", getpid(), i, 2 * i);
        sleep(1);
    }

    printf("[%d] My Parent, %d, has abandoned me...\n", getpid(), getppid());

    exit(0);
}

int main() {

    signal(SIGCHLD, SIGCHLD_handler);
    // Installing the handler
    
    // pid_t pid1, pid2;
    // (pid1 == fork()) && (pid2 == fork()); Why?

    pid_t pid1 = fork();

    if(pid1 == 0) {
        // First Child : Fibonacci
        fibonacci();
    } else if(pid1 == -1) {
        perror("fork #1");
        exit(0);
    } else {
        pid_t pid2 = fork();
        if(pid2 == 0) {
            // Second Child : Tables
            tables();
        } else if(pid2 == -1) {
            perror("fork #2");
            exit(0);
        } else {
            // Parent Process

            while(child_caught < 2) {
                // Someone should call the police...
            }
        }
    }
    
}

void SIGCHLD_handler(int signum) {
    // Parent wakes up and realizes it needs to take care of its child.
    int status;
    pid_t ret;
    
    ret = waitpid(-1, &status, WNOHANG);

    // ERROR HANDLING!!!
    if(ret == -1) {
        perror("wait");
        exit(0);
    }

    // What about multiple children. Signals are not queued!
    /*
      while((ret = waitpid(-1, &status, WNOHANG)) > 0) {}
    */
    // this is what happens when I run ``emacs 6-waitpid.c &``

    printf("[%d] I have taken care of my child, %d \n", getpid(), ret);

    child_caught++;
}
