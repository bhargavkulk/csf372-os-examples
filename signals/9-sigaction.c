#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// Making a C-c handler with sigaction

bool looping = true;

void handler(int signum) {
	printf("No u.\n");
	looping = false;
}

int main() {
	struct sigaction act;
	act.sa_handler = &handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;

	int ret = sigaction(SIGINT, &act, NULL);
	// the third argument saves the previous handler
	// into the reference given, we dont need that so
	// pass NULL

	if(ret == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	while(looping) {
		printf("looping.\n");
	}

	printf("C-c handler\n");

	act.sa_handler = SIG_DFL;
	ret = sigaction(SIGINT, &act, NULL);
	if(ret == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	while(true) {
		printf("back to normal.\n");
	}

	return 0;
}
