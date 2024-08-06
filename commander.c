#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/wait.h>
#include <unistd.h>
#include "processManager.h"


int main(int argc, char *argv[])
{
	

	//Hold process IDs
	pid_t pid;

	//Pipe file descriptors
	int pipe_fd[2];
	char command;

	//Setup pipe, read is fd[0] and write is fd[1]
	if (pipe(pipe_fd) == -1)
	{
		return 1;
	}

	//Fork child process
	pid = fork();

	//Error handling for child process creation
	if (pid < 0)
	{
		printf("Error creating child\n");
		return 1;
	}

	//Commander process
	if (pid > 0)
	{
		close(pipe_fd[0]);
		
		while (true)
		{
			//Prompt user
			printf("$ ");
			scanf("%c", &command);

			command = toupper(command);

			//Send command to process manager
			write(pipe_fd[1], &command, sizeof(char));
			
		}
		wait(NULL);
		close(pipe_fd[1]);
		exit(0);
	}

	//Process manager
	else
	{
		processManager(pipe_fd);
		exit(0);
	}

	//Debug
	printf("End of main\n");
}
