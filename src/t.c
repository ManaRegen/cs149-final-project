#include <stdio.h>
#include <unistd.h>

extern int totalTurnaround;
extern int completedProcessesCount;

void terminateProcessManager(int command_fd[2], int response_fd[2]) {
    // Print average turnaround time and terminate the system
    int avgTurnaround;
    char signal;

    if (completedProcessesCount == 0) {
        avgTurnaround = 0;
    } else {
        avgTurnaround = totalTurnaround / completedProcessesCount;
    }

    printf("Completed processes: %d\n", completedProcessesCount);
    printf("Average turnaround time: %d\n", avgTurnaround);
    printf("Terminating system.\n");

    close(command_fd[0]);
    close(response_fd[1]);

    signal = 'T';
    write(response_fd[1], &signal, sizeof(char));
}