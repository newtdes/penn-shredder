#include <stdlib.h> // for atoi, exit, free, malloc, perror
#include <string.h> // for strlen, strtok

#include <unistd.h> // for alarm, execve, fork
#include <signal.h> // for kill, read, signal
#include <stdio.h> // for perror
#include <sys/types.h>
#include <sys/wait.h> // for wait
#include <errno.h> // used for error-handling
#include "handler.h"

#ifndef EC_NOKILL

void handler(int signum)
{
    if (signum == SIGALRM) {
		// const char timeout_msg[] = "Bwahaha ... tonight I dine on turtle soup\n";
		if (write(STDOUT_FILENO, CATCHPHRASE, strlen(CATCHPHRASE)) == -1){
			perror("Failed to write.");
		}	
		if (kill(pid, SIGKILL) == -1){
			perror("Failed to kill.");
		}
	}

    else if (signum == SIGINT)
    {

        if (pid == -99)
        {
            if (write(STDOUT_FILENO, "\n", strlen("\n")) == -1)
            {
                perror("Write Failed");
                exit(EXIT_FAILURE);
            }

            if (write(STDOUT_FILENO, PROMPT, strlen(PROMPT)) == -1)
            {
                perror("Cannot write");
                exit(EXIT_FAILURE);
            }


        }
        else
        {
            if (kill(pid, SIGKILL) == -1)
            {
                perror("Failed to kill");
            }
        }

        signal(SIGINT, handler);
    }

    else
    {
        exit(EXIT_SUCCESS);
    }
}

#endif

#ifdef EC_NOKILL

void handler(int signum)
{
    if (signum == SIGALRM) {
		// const char timeout_msg[] = "Bwahaha ... tonight I dine on turtle soup\n";
		if (write(STDOUT_FILENO, CATCHPHRASE, strlen(CATCHPHRASE)) == -1){
			perror("Failed to write.");
		}	
	}

    else if (signum == SIGINT)
    {
        if (pid == -99)
        {
            if (write(STDOUT_FILENO, "\n", strlen("\n")) == -1)
            {
                perror("Write Failed");
                exit(EXIT_FAILURE);
            }

            if (write(STDOUT_FILENO, PROMPT, strlen(PROMPT)) == -1)
            {
                perror("Cannot write");
                exit(EXIT_FAILURE);
            }


        }
        else
        {
            alarm(0);
        }

        signal(SIGINT, handler);
    }

    else
    {
        exit(EXIT_SUCCESS);
    }
}

#endif