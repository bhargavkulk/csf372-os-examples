#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void int_handler(int signum) {
    printf("no.\n");
}

int main() {
    // I have the very important task of summing up the first 10 numbers.
    // I can't have the user stop me by pressing C-c.

    // How does C-c stop execution? C-c raises the SIGINT signal, whose default
    // action is to stop execution of the recieving program.

    int sum = 0;

    // To not allow C-c to stop my execution, I will simply ask the OS to ignore
    // it for me.

    signal(SIGINT, SIG_IGN);
    // SIG_IGN stands for ignore

    for(int i = 1; i <= 10; i++) {
        printf("sum = %d\n", (sum = sum + i));
        sleep(1);
    }

    // I can also re-register signal handlers
    signal(SIGINT, int_handler);
        
    for(int i = 11; i <= 20; i++) {
        printf("sum = %d\n", (sum = sum + i));
        sleep(1);
    }

    // As I dont think addition over 20 is as important I don't care about C-c
    // stopping me as much. So I wan't SIGINT to do what it used to do.

    void (* ret)(int) = signal(SIGINT, SIG_DFL);

    // ERROR CHECKING IS VERY IMPORTANT!!!
    // Use man to check what happens when the signal function does not work as
    // it should.

    // signal usually returns a pointer to the signum's previous signal
    // handler. If there is an error, it returns the special SIG_ERR handler
    // So we must check if ret == SIG_ERROR

    if(ret == SIG_ERR) {
        perror("signal: ");
        // What does perror do? man perror
        
        exit(0);
    }

    for(int i = 21; i <= 30; i++) {
        printf("sum = %d\n", (sum = sum + i));
        sleep(1);
    }
}
