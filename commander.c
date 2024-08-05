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
	pthread_t pid;

	//Pipe file descriptors
	int pipe_fd[2];
	char read_msg[2];
	char command[2];

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
		while (true)
		{
			//Prompt user
			printf("$ ");
			scanf("%s", command);

			for (int i = 0; command[i] != '\0'; i++)
			{
				command[i] = toupper(command[i]);
			}

			//Send command to process manager
			close(pipe_fd[0]);
			write(pipe_fd[1], command, strlen(command) + 1);	
			close(pipe_fd[1]);

			//Wait for manager to terminate
			wait(NULL);
		}
		
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
