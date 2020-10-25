#ifndef SIG_H
#define SIG_H


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
using namespace std;



#define READY_DONE  SIGUSR2
#define COMPUTE_PRINT SIGUSR1
#define MAXCP 2
#define INC 100000


#endif
