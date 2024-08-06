#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../headers/processManager.h"

int main(int argc, char *argv[])
{

	// Hold process IDs
	pid_t pid;

	// Pipe file descriptors
	int command_fd[2];	// used for sending commands to process manager
	int response_fd[2]; // used for to process manager to indicate that it has completed executing a command
	char command;

	// Setup pipe, read is fd[0] and write is fd[1]
	if (pipe(command_fd) == -1)
	{
		return 1;
	}

	if (pipe(response_fd) == -1)
	{
		return 1;
	}

	// Fork child process
	pid = fork();

	// Error handling for child process creation
	if (pid < 0)
	{
		printf("Error creating child\n");
		return 1;
	}

	// Commander process
	if (pid > 0)
	{
		close(command_fd[0]);
		close(response_fd[1]);

		while (true)
		{
			// Prompt user
			printf("$ ");
			scanf(" %c", &command);

			command = toupper(command);
			printf("Received command: '%c'\n", command); // debug
			char response;

			// Send command to process manager
			write(command_fd[1], &command, sizeof(char));
			read(response_fd[0], &response, sizeof(char));
			if (command == 'T')
			{
				break;
			}
		}
		wait(NULL);
		close(command_fd[1]);
		close(response_fd[0]);
		exit(0);
	}

	// Process manager
	else
	{
		processManager(command_fd, response_fd);
		exit(0);
	}

	// Debug
	printf("End of main\n");
}
