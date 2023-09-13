#include <stdlib.h> // for atoi, exit, free, malloc, perror
#include <string.h> // for strlen, strtok

#include <unistd.h> // for alarm, execve, fork
#include <signal.h> // for kill, read, signal
#include <stdio.h> // for perror
#include <sys/types.h>
#include <sys/wait.h> // for wait
#include <errno.h> // used for error-handling
#include "handler.h"
#include "setTimer.h"

#define MAX_COMMAND_LENGTH 4096

#ifndef EC_NOKILL
pid_t pid; 

int main(int argc, char* argv[])
{
    int time;
    if (argv[1] != NULL)
    {
        time = atoi(argv[1]);
    }

    else
    {
        time = 0;
    }

    while (1)
    {
        pid = -99;
        if (write(STDOUT_FILENO, PROMPT, strlen(PROMPT)) == -1)
        {
            perror("Cannot write");
            exit(EXIT_FAILURE);
        }
        signal(SIGINT, handler);

        
        char buff[MAX_COMMAND_LENGTH + 1];
        int num_read = read(STDIN_FILENO, buff, MAX_COMMAND_LENGTH);
        buff[num_read] = '\0';
        if (num_read == 0)
            exit(EXIT_FAILURE); // handling the first case of Ctrl + D
        
        if (num_read == 1)
            continue;
        
        else if (num_read == -1)
        {
            perror("Cannot read");
        }
        signal(SIGINT, handler);
        char* envp[] = {NULL};

        char* tokens[MAX_COMMAND_LENGTH];
        char* token;

        int count = 0;

        char delimiter[] = " \t\n";

        token = strtok(buff, delimiter);
        if (token == NULL)
        {
            continue;
        }

        while (token != NULL && count < MAX_COMMAND_LENGTH)
        {
            tokens[count] = token;
            ++count;
            token = strtok(NULL, delimiter);
        }

        tokens[count] = NULL;
        
        pid = fork();
        if (pid == 0)
        {
            int err = execve(tokens[0], tokens, envp);

            if (err < 0)
            {
                perror("Error");
            }
            exit(EXIT_FAILURE);

        }

        else if (pid < 0)
        {
            perror("Fork Failure");
            exit(EXIT_FAILURE);
        }

        else
        {
            setTimer(time);
            if (wait(NULL) == -1)
            {
                perror("Wait failed!");
            }

            // reset alarm
            alarm(0);
            pid = 0;
        }
    }
}
#endif


#ifdef EC_NOKILL
pid_t pid; 

void handler(int signum);

int main(int argc, char* argv[])
{
    int time;
    if (argv[1] != NULL)
    {
        time = atoi(argv[1]);
    }

    else
    {
        time = 0;
    }

    while (1)
    {
        pid = -99;
        if (write(STDOUT_FILENO, PROMPT, strlen(PROMPT)) == -1)
        {
            perror("Cannot write");
            exit(EXIT_FAILURE);
        }
        signal(SIGINT, handler);

        char buff[MAX_COMMAND_LENGTH + 1];
        int num_read = read(STDIN_FILENO, buff, MAX_COMMAND_LENGTH);
        buff[num_read] = '\0';
        if (num_read == 0)
            exit(EXIT_FAILURE); // handling the first case of Ctrl + D
        
        if (num_read == 1)
            continue;
        
        else if (num_read == -1)
        {
            perror("Cannot read");
        }


        signal(SIGINT, handler);
        char* envp[] = {NULL};
        // printf("Check value here\n");
        char* tokens[MAX_COMMAND_LENGTH];
        char* token;

        int count = 0;

        char delimiter[] = " \t\n";

        token = strtok(buff, delimiter);
        if (token == NULL)
        {
            continue;
        }

        while (token != NULL && count < MAX_COMMAND_LENGTH)
        {
            tokens[count] = token;
            ++count;
            token = strtok(NULL, delimiter);
        }


        tokens[count] = NULL;


        
        pid = fork();
        if (pid == 0)
        {
            alarm(time);
            int err = execve(tokens[0], tokens, envp);

            if (err < 0)
            {
                // printf("Line 75\n");
                perror("Error");
            }
            exit(EXIT_FAILURE);

        }

        else if (pid < 0)
        {
            perror("Fork Failure");
            exit(EXIT_FAILURE);
        }

        else
        {

            int status;
            wait(&status);

            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)
            {
                if (write(STDOUT_FILENO, CATCHPHRASE, strlen(CATCHPHRASE)) == -1)
                {
                    perror("Failed to write");
                }
            }

            pid = 0;
        }
    }
}

#endif
