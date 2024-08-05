#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
#include "structs.h"

int totalTurnaround;
int completedProcessesCount;

Queue readyState;
Queue blockedState;
int runningState = -1;
int time = 0;

PcbEntry pcbTable[99];

static void runProcess();
static void blockProcess();
static void unblockProcess();
static void reporterProcess();

void processManager(int pipe_fd[2]) {
    close(pipe_fd[1]); // Close unused write end
    char command;
    
    while (read(pipe_fd[0], &command, sizeof(command)) > 0) {
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

                int avgTurnaround = totalTurnaround / completedProcessesCount;
                printf("Average turnaround time: %d\n", avgTurnaround);
                printf("Terminating system.\n");

                return;
            default:
                printf("Invalid command. Please try again.\n");
                break;
        }
    }

}

static void runProcess() { // selects process from the top of the readyState queue to run

}

static void blockProcess() {

}

static void unblockProcess() {

}

static void reporterProcess() {
    printf("****************************************************************\n");
    printf("The current system state is as follows:\n");
    printf("****************************************************************\n\n");

    printf("CURRENT TIME: %d\n\n", time);

    printf("RUNNING PROCESSES: \n");


}

