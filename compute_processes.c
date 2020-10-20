#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "sig.h"
/* The purpose of this example program is
to demonstrate the use of signals. */
main (int argc, char *argv[]) {
	pid_t cpid;
	pid_t result;
	int err;
	int status;
	/* Start up child process. */
	cpid = fork ();
	if (cpid == -1) {
		printf ("psig: Error on fork, errno = %d\n", errno);
		exit (2);
	}
	else if (cpid == 0) {
	/* Start child code.. */
		execl ("./controller", "controller", (char *)NULL);
	}
	else {
		/* Delay for a while to ensure that the child process
		has issued its pause request. */
		sleep (1);
		/* Send signal to child. */
		printf ("psig: Sending signal to child process.\n");
		err = kill(cpid, MYSIGNAL);
		
		if (err == -1) {
			printf ("psig: Kill error: %d\n", errno);
			exit (4);
		}
		
		printf ("psig: Signal sent.\n");
		/* Wait for termination of all child processes. */
		result = waitpid (-1, &status, 0);
		
		if (result == -1) {
			printf ("psig: No child process\n");
		}
		
		printf ("psig: Child process completed.\n");
	}
	
	printf ("psig: Complete.\n");
	exit (0);
}