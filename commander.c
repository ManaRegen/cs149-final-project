#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>



int main(int argc, char *argv[])
{
	

	//Hold process IDs
	pthread_t pid;

	//Pipe file descriptors
	int pipe_fd[2];
	char read_msg[1];
	char command[1];

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

	//Parent process
	if (pid > 0)
	{
		while (true)
		{
			//Prompt user
			printf("$");
			scanf("%s", command);

			//Send command to process manager
			close(pipe_fd[0]);
			write(pipe_fd[1], command, strlen(command) + 1);	
			close(pipe_fd[1]);

			//Wait for manager to terminate
			wait(NULL);
		}
		
	}

	//Child process
	else
	{
		//Read command from commander process
		read(pipe_fd[0], read_msg, strlen(read_msg) + 1);
		printf("This is the process manager, here's the command from the commander process:  %s\n", read_msg);
		exit(0);
	}

	//Debug
	printf("End of main\n");
}
