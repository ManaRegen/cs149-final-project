#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "../headers/queue.h"
#include "../headers/structs.h"
#include "../headers/q.h"
#include "../headers/p.h"
#include "../headers/u.h"
#include "../headers/t.h"
#include "../headers/files.h"
#include "../headers/globals.h"

static void initializePcbTable()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        pcbTable[i].processId = -1;
    }
}

int createProcess(int parentPid, Program program) {
    for (int i = 0; i < 99; i++) {
        if (pcbTable[i].processId == -1) {  // Find an unoccupied spot
            PcbEntry newProcess;

            // Assign the provided program to the new process
            newProcess.program = program;

            newProcess.processId = i;
            newProcess.parentProcessId = parentPid;  // Set parent PID
            newProcess.programCounter = 0;
            newProcess.value = 0;
            newProcess.priority = 0;  // Default priority
            newProcess.startTime = 0;  // Set when the process starts
            newProcess.timeUsed = 0;

            // Add the new process to the PCB table
            pcbTable[i] = newProcess;

            printf("Process %d created and added to PCB table at index %d.\n", i, i);
            return i;  // Return the new PID
        }
    }
    return -1;  // No available spot
}

static void loadContext(int processIndex)
{
    // Check if the process index is valid
    if (processIndex < 0 || processIndex >= MAX_PROCESSES)
    {
        printf("Invalid process index\n");
        return;
    }

    PcbEntry newProcess = pcbTable[processIndex];

    cpu.program = newProcess.program;
    cpu.programCounter = newProcess.programCounter;
    cpu.value = newProcess.value;
    cpu.timeSlice = 0; // Assuming the time slice needs to be initialized/reset
    cpu.timeSliceUsed = newProcess.timeUsed;

    runningState = processIndex;

    if (newProcess.startTime == 0)
    {
        newProcess.startTime = time;
    }

    printf("Process %d is now running.\n", newProcess.processId);
}

static void saveContext()
{
    if (runningState < 0 || runningState >= MAX_PROCESSES)
    {
        printf("Invalid running state\n");
        return;
    }

    // Save the current CPU context into the PCB
    pcbTable[runningState].programCounter = cpu.programCounter;
    pcbTable[runningState].value = cpu.value;
    pcbTable[runningState].timeUsed = cpu.timeSliceUsed;

    // Reset running state
    runningState = -1;

    printf("Context for process %d saved\n", pcbTable[runningState].processId);
}

static void initializePm()
{
    initializePcbTable();
    createProcess(0, init);
    loadContext(0);
    initializeQueue(&readyState);
    initializeQueue(&blockedState);
    printf("Process Manager has been initialized.\n");
}

void processManager(int command_fd[2], int response_fd[2])
{
    close(command_fd[1]);  // Close unused write end
    close(response_fd[0]); // close unused read end
    char command;
    char signal;

    initializePm();
    signal = 1;
    write(response_fd[1], &signal, sizeof(char));

    while (true)
    {
        read(command_fd[0], &command, 1);
        switch (command)
        {
        case 'Q':
            q();
            break;
        case 'U':
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