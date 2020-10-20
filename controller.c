#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "sig.h"


/* Signal handler for MYSIGNAL signal. */
void sigHandler (int sig) {
printf ("csig: Signal received.\n");
}


main (int argc, char *argv[]) {
	int err;
	struct sigaction action;
	/* Set signal handler. */
	action.sa_handler = (void(*)(int))sigHandler;
	sigemptyset (&action.sa_mask);
	action.sa_flags = 0;
	err = sigaction (MYSIGNAL, &action, NULL);
	
	if (err == -1) {
		printf ("csig: Received error %d on sigaction.\n", errno);
		exit(4);
	}
	
	/* Wait for signal. */
	printf ("csig: About to pause.\n");
	err = pause();
	printf ("csig: Complete.\n");
	exit (0);
}