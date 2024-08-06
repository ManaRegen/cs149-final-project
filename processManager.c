#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "queue.h"
#include "structs.h"
#include "q.h"
#include "p.h"
#include "u.h"
#include "t.h"

int totalTurnaround = 0;
int completedProcessesCount = 0;

Queue readyState;
Queue blockedState;
int runningState = -1;
int time = 0;

PcbEntry pcbTable[99];

static void blockProcess();
static void reporterProcess();

void processManager(int command_fd[2], int response_fd[2])
{
    // Initialize the queue
    initializeQueue(&readyState);

    // Loop to add all processes to the readyState queue
    for (int i = 0; i < 99; i++)
    {
        enqueue(&readyState, pcbTable[i].processId);
    }

    close(command_fd[1]);  // Close unused write end
    close(response_fd[0]); // close unused read end
    char command;
    char signal;

    while (true)
    {
        read(command_fd[0], &command, 1);
        switch (command) {
            case 'Q':
                q();
                break;
            case 'U':
                // Unblock the first process in the blocked queue
                u();
                break;
            case 'P':
                p();
                break;
            case 'T':
                t(command_fd, response_fd);
                return;
            default:
                printf("Invalid command. Please try again.\n");
                break;
        }
        signal = 1;
        write(response_fd[1], &signal, sizeof(char));
    }
}