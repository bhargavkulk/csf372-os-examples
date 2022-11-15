#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

bool not_alarmed = false;

void alarm_handler(int signum) {
    // The signal number of the the signal for which this handler was called is
    // passed as the argument to the signal handler.
    printf("[%d] Ring Ring Ring Ring Ring\n", signum);
    not_alarmed = true;
}

int main() {

    signal(SIGALRM, alarm_handler);
    // signal(int signum, void (* signal_handler)(int))
    // signal tells the OS to call the function alarm_handler whenever the
    // calling process recieves the SIGALRM signal.
    
    alarm(2); // Does the word asynchronous ring any bells?

    while(!not_alarmed) {
        printf("Stuck in loop.\n");
    }

    // Now do I reach this part?
    printf("Not stuck in loop.\n");
}
