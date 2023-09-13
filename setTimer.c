#include <stdlib.h> // for atoi, exit, free, malloc, perror
#include <string.h> // for strlen, strtok

#include <unistd.h> // for alarm, execve, fork
#include <signal.h> // for kill, read, signal
#include <stdio.h> // for perror
#include <sys/types.h>
#include <sys/wait.h> // for wait
#include <errno.h> // used for error-handling
#include "setTimer.h"
#include "handler.h"

#ifndef EC_NOKILL

void setTimer(int time){
	if (signal(SIGALRM, handler) == SIG_ERR){
		perror("Signal error");
	}
	alarm(time);
    // printf("setTimer\n");
}

#endif