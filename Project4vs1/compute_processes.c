#include "sig.h"

//Compute program
//send a ready command
//receive compute command
//send a done command
//receive a print command

class primes{
	public:
		void compute_primes(int);
		long long unsigned int lower_bound, upper_bound;
		long int total = 0;
};

//primes prime;

/* Signal handler for MYSIGNAL signal. */
void computeHandler (int sig) {
printf ("SIGUSR1 received.\n");
}

void primes::compute_primes(int id){
	//printf("into primes\n");
  int j, i, flag;
	//sleep(10);
	//printf("end sleep\n");
	upper_bound = (id+1) * INC;
	lower_bound = id * INC;
//	printf("upper%lu lower%lu, %lu\n", upper_bound, lower_bound, INC);

	for(i = lower_bound; i <= upper_bound; i++){ //for loop to determine the number of primes in range
			flag = 1;
			if(i==1 || i == 0) {continue;}
			for(j = 2; j <= i/2; j++){
				if( i % j == 0){
					flag = 0;
					break;
				}
			}
			if(flag == 1){
				total = total + 1;
				//printf("total: %lu \n", total);
			}
		}
		//printf("out of primes\n");
	}


int main (int argc, char *argv[]) {
	primes prime;
	int err;
	int id;
	int pid;
	struct sigaction action;

	sscanf(argv[0],"%d",&id);
	printf("(%d) compute: Child ID: %d, Parent ID: %d\n",id, getpid(), getppid());
	pid = getppid();
	/* Set compute signal handler. */
	action.sa_handler = (void(*)(int))computeHandler;
	sigemptyset (&action.sa_mask);
	action.sa_flags = 0;
	err = sigaction (COMPUTE_PRINT, &action, NULL);
	if (err == -1) {
		printf ("compute: Received error %d on sigaction.\n", errno);
		exit(4);
	}
	printf ("(%d) compute: Sending signal 1 to parent process.\n", id);
	sleep(id);
	err = kill(pid, READY_DONE);
	if (err == -1) {
		printf ("compute: Kill error: %d\n", errno);
		exit (4);
	}
	printf ("(%d) compute: Signal sent 1 .\n", id);
	err = pause();
	prime.compute_primes(id);
	printf ("(%d) compute: Sending signal 2 to parent process.\n", id);

	sleep(id);
	err = kill(pid, READY_DONE);
	if (err == -1) {
		printf ("compute: Kill error: %d\n", errno);
		exit (4);
	}
	printf ("(%d) compute: Signal 2 sent.\n", id);
	err = pause();
	printf("(%d) compute: For interval [%llu,%llu] Count = %lu\n", id, prime.lower_bound, prime.upper_bound, prime.total);
	printf ("(%d) compute: Complete.\n", id);
	exit (0);
}
