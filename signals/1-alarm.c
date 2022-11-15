#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

bool not_alarmed = false;

int main() {

    // Stop whatever I am doing in 2 seconds
    int ret = alarm(2);

    // What does alarm return?
    // > man alarm
    

    while(!not_alarmed) {
        // While I am not alarmed I will loop
        printf("Stuck in loop.\n");
    }

    // Is this ever reached?
    printf("Not stuck in loop.\n");
}
