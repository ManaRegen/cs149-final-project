#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
#include "structs.h"

int totalTurnaround = 0;
int completedProcessesCount = 0;

Queue readyState;
Queue blockedState;
int runningState = -1;
int time = 0;

PcbEntry pcbTable[99];

static void runProcess();
static void blockProcess();
static void unblockProcess();
static void reporterProcess();

void processManager(int command_fd[2], int response_fd[2]) {
    //Initialize the queue
    initializeQueue(&readyState);

    //Loop to add all processes to the readyState queue
    for (int i = 0; i < 99; i++)
    {
        enqueue(&readyState, pcbTable[i].processId);
    }

    close(command_fd[1]); // Close unused write end
    close(response_fd[0]); // close unused read end
    char command;
    
    while (true) {
        read(command_fd[0], &command, sizeof(command));
        switch (command) {
            case 'Q':
                // Execute the next instruction of the running process

                if (runningState == -1) {
                    runProcess();
                }
                break;
            case 'U':
                // Unblock the first process in the blocked queue

                break;
            case 'P':
                // Spawn a reporter process
                if (fork() == 0) {
                    reporterProcess();
                    exit(0);
                }
                break;
            case 'T':
                // Print average turnaround time and terminate the system
                int avgTurnaround;
                if (completedProcessesCount == 0) {
                    avgTurnaround = 0;
                } else {
                    avgTurnaround = totalTurnaround / completedProcessesCount;
                }
                printf("Average turnaround time: %d\n", avgTurnaround);
                printf("Terminating system.\n");
                close(command_fd[0]);
                close(response_fd[1]);

                
                return;
            default:
                printf("Invalid command. Please try again.\n");
                break;
        }
        char signal = 1;
        write(response_fd[1], &signal, sizeof(char));
    }

}

static void runProcess() { // selects process from the top of the readyState queue to run
    //Update runningState and readyState
    if (!isEmpty(&readyState))
    {
        runningState = readyState.front;
        dequeue(&readyState);
    }
    
}

static void blockProcess() {

}

static void unblockProcess() {

}

static void reporterProcess() { // to be completed
    printf("****************************************************************\n");
    printf("The current system state is as follows:\n");
    printf("****************************************************************\n\n");

    printf("CURRENT TIME: %d\n\n", time);

    printf("RUNNING PROCESSES: \n");


}

