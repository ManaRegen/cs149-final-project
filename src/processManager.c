#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../headers/queue.h"
#include "../headers/structs.h"
#include "../headers/q.h"
#include "../headers/p.h"
#include "../headers/u.h"
#include "../headers/t.h"
#include "../headers/files.h"

int totalTurnaround = 0;
int completedProcessesCount = 0;

Queue readyState;
Queue blockedState;
int runningState;
int time = 0;

PcbEntry pcbTable[99];

static void blockProcess();
static void reporterProcess();

void initializePm()
{
    PcbEntry initProcess = {
        .processId = 0,
        .parentProcessId = 0,
        .program = {0},
        .programCounter = 0,
        .value = 100,
        .priority = 1,
        .startTime = 0,
        .timeUsed = 0};

    // copy the init array to the program field
    for (int i = 0; i < 16 / sizeof(init[0]); i++)
    {
        initProcess.program[i] = init[i];
    }

    Cpu cpu = {
        .program = &initProcess.program,
        .programCounter = 0,
        .timeSlice = 5, // what is a time slice
        .timeSliceUsed = 0,
    };

    pcbTable[0] = initProcess;
    runningState = 0;
}

void processManager(int command_fd[2], int response_fd[2])
{
    // Initialize the queue
    initializePm();
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
        switch (command)
        {
        case 'Q':
            q();
            break;
        case 'U':
            // Unblock the first process in the blocked queue
            u(blockedState, readyState);
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
