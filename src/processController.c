#include <stdio.h>
#include "../headers/globals.h"
#include "../headers/structs.h"

void initializePcbTable()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        pcbTable[i].processId = -1;
    }
}

int createProcess(int parentPid, Program program)
{
    for (int i = 0; i < 99; i++)
    {
        if (pcbTable[i].processId == -1)
        { // Find an unoccupied spot
            PcbEntry newProcess;

            // Assign the provided program to the new process
            newProcess.program = program;
            newProcess.processId = i;
            newProcess.parentProcessId = parentPid; // Set parent PID
            newProcess.programCounter = 0;
            newProcess.value = 0;
            newProcess.priority = 0;  // Default priority
            newProcess.startTime = time; // Set when the process starts
            newProcess.timeUsed = 0;

            // Add the new process to the PCB table
            pcbTable[i] = newProcess;

            printf("Process %d created and added to PCB table at index %d.\n", i, i);
            return i; // Return the new PID
        }
    }
    return -1; // No available spot
}

void loadContext(int processIndex)
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

void saveContext()
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
