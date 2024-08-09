#include <stdbool.h>
#include <stdio.h>
#include "../headers/globals.h"
#include "../headers/processController.h"
#include "../headers/queue.h"

static int getFrontIfNotEmpty(Queue *queue)
{
    if (!isEmpty(queue))
    {
        int pid = peek(queue);
        return pid;
    }
    return -1;
}

static int getHighestPriorityProcess()
{
    int pid;

    pid = getFrontIfNotEmpty(&readyState[3]);
    if (pid != -1)
    {
        return pid;
    }

    pid = getFrontIfNotEmpty(&readyState[2]);
    if (pid != -1)
    {
        return pid;
    }

    pid = getFrontIfNotEmpty(&readyState[1]);
    if (pid != -1)
    {
        return pid;
    }

    pid = getFrontIfNotEmpty(&readyState[0]);
    if (pid != -1)
    {
        return pid;
    }

    return runningState;
}

void scheduleProcess()
{
    int highestPriorityPid = getHighestPriorityProcess();
    if (highestPriorityPid == runningState)
    {
        return; // No higher priority process to schedule or the same process should continue
    }

    PcbEntry highPriorityCandidate = pcbTable[highestPriorityPid];
    PcbEntry currentProcess = pcbTable[runningState];

    // Check if the new candidate has a higher priority
    if (highPriorityCandidate.priority > currentProcess.priority || runningState == -1)
    {
        dequeue(&readyState[highPriorityCandidate.priority]); // Dequeue based on the process's priority queue
        loadContext(highestPriorityPid);                      // Load context of the higher priority process
        printf("Switching to process %d.\n", highestPriorityPid);
    }
    else
    {
        printf("Continuing with the current process %d.\n", runningState);
    }
}

void checkTimeSlice()
{
    if (cpu.timeSliceUsed >= cpu.timeSlice)
    {
        PcbEntry running = pcbTable[runningState];
        int pid = getFrontIfNotEmpty(&readyState[running.priority]);
            if (pid != -1)
            {
                saveContext();
            }
    }
}