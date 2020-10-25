#include "sig.h"



/* Signal handler for MYSIGNAL signal. */
void readyDoneHandler (int sig) {
	/* Send signal to child. */
printf ("SIGUSR2 received.\n");
}


/* The purpose of this example program is
to demonstrate the use of signals. */
int main (int argc, char *argv[]) {
	int i = 0;
	pid_t cpid[MAXCP];
	pid_t result;
	int id[MAXCP];
	int err;
	char arg1[50];
	char arg2[50];
	int status;
	time_t start_time, stop_time;
	struct sigaction action;
	/* Start up child process. */
	//srand(time(NULL));
for(i = 0; i < MAXCP; i++){
  cpid[i] = fork ();
	// id[i] = (rand()% 30) + 1;
	id[i] = i+1;

	if (cpid[i] == -1) {
		printf ("controller: Error on fork, errno = %d\n", errno);
		exit (2);
	}
	else if (cpid[i] == 0) {
	/* Start child code.. */

		memset(arg1, 0, strlen(arg1));
		sprintf(arg1, "%d", id[i]);
		execl ("./compute", arg1, (char *)NULL);
	}
	else{
		printf("(%d) controller: Parent ID: %d, Child ID: %d\n",id[i], getppid(), cpid[i]);

	}
}

		/* Set ready/done signal handler. */
		action.sa_handler = (void(*)(int))readyDoneHandler;
		sigemptyset (&action.sa_mask);
		action.sa_flags = 0;
		err = sigaction (READY_DONE, &action, NULL);
		if (err == -1) {
			printf ("controller: Received error %d on sigaction.\n", errno);
			exit(4);
		}
	for(i = 0; i < MAXCP; i++){
		err = pause();
	}

	printf("controller: start time\n");
	//start_time = clock(); //gather start time
	time(&start_time);
	for(i = 0; i < MAXCP; i++){
		printf ("(%d) controller: Sending signal to child process.\n", id[i]);
		err = kill(cpid[i], COMPUTE_PRINT);
		if (err == -1) {
			printf ("controller: Kill error: %d\n", errno);
			exit (4);
		}
		printf ("(%d) controller: Signal sent.\n", id[i]);
	}



	for(i = 0; i < MAXCP; i++){
		err = pause();  //child sent DONE command
	}
	//stop_time = clock(); //gather stop time
	time(&stop_time);
	printf("controller: stop time\n");

	printf("controller: elapsed time = %f seconds\n", (float)(stop_time-start_time));///(float)CLOCKS_PER_SEC)*100000.0)));//display

	for(i = 0; i < MAXCP; i++){
		/* Send signal to child. */
		printf ("(%d) controller: Sending signal to child process.\n", id[i]);
		err = kill(cpid[i], COMPUTE_PRINT);						//tell child to print

		if (err == -1) {
			printf ("controller: Kill error: %d\n", errno);
			exit (4);
		}
		printf ("(%d) controller: Signal sent.\n", id[i]);
	}

		i = 0;
	  while(true){
	    cpid[i] = wait(&status);
	    if(cpid[i] == -1){
	      continue;
	    }
	    else{
	      printf ("controller: Child process %d completed.\n", cpid[i]);
				i++;
				if(i == MAXCP){
					break;
				}
	    }
	  }

	printf ("controller: Complete.\n");
	exit (0);

}
