#include <stdio.h>
#include "../headers/globals.h"
#include "../headers/structs.h"

void addToReadyQueue(int pid)
{
    PcbEntry p = pcbTable[pid];
    int prio = p.priority;
    enqueue(&readyState[prio], pid);
}

static void configureRoot(PcbEntry newProcess)
{
    newProcess.programCounter = 0;
    newProcess.value = 0;
    newProcess.priority = 0;
}

static void configureNonRoot(PcbEntry newProcess, int parentPid)
{
    PcbEntry parent = pcbTable[parentPid];
    newProcess.programCounter = parent.programCounter + 1;
    newProcess.value = parent.value;
    newProcess.priority = parent.priority;
    addToReadyQueue(newProcess.processId);
}

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
        if (pcbTable[i].processId == -1) // find an unoccupied spot
        {
            PcbEntry newProcess;
            newProcess.processId = i;
            newProcess.parentProcessId = parentPid;
            newProcess.program = program;
            newProcess.startTime = time;
            newProcess.timeUsed = 0;

            if (parentPid == -1)
            {
                configureRoot(newProcess);
            }
            else
            {
                configureNonRoot(newProcess, parentPid);
            }

            // Add the new process to the PCB table
            pcbTable[i] = newProcess;

            printf("Process %d created and added to PCB table at index %d.\n", i, i);
            return i; // Return the new PID
        }
    }
    return -1; // No available spot
}

static int getTimeSlice(PcbEntry p)
{
    int prio = p.priority;
    switch (prio)
    {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 8;
    default:
        printf("Process %d is assigned an invalid priority.\n", p.processId);
        return -1;
    }
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

    cpu.timeSliceUsed = newProcess.timeUsed;
    cpu.timeSlice = getTimeSlice(newProcess);
    if (cpu.timeSlice == -1)
    {
        printf("Error setting time slice for process %d.\n", processIndex);
        return;
    }

    runningState = processIndex;

    printf("Process %d is now running.\n", newProcess.processId);
}

static void setPriority(PcbEntry p)
{
    if (cpu.timeSliceUsed = cpu.timeSlice)
    {
        p.priority--;
        p.priority = p.priority < 0 ? 0 : p.priority;
    }
    else
    {
        p.priority++;
        p.priority = p.priority < 0 ? 0 : p.priority;
    }
}

void saveContext()
{
    if (runningState < 0 || runningState >= MAX_PROCESSES)
    {
        printf("Invalid running state\n");
        return;
    }

    // Save the current CPU context into the PCB
    PcbEntry currentProcess = pcbTable[runningState];
    currentProcess.programCounter = cpu.programCounter;
    currentProcess.value = cpu.value;
    currentProcess.timeUsed = cpu.timeSliceUsed;

    setPriority(currentProcess);

    // Reset running state
    runningState = -1;

    printf("Context for process %d saved\n", currentProcess.processId);
}



void blockProcess(int pid)
{
    saveContext();
    enqueue(&blockedState, pid);
}
