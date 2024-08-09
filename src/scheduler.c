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
    PcbEntry currentProcess = pcbTable[runningState];
    PcbEntry highPriorityCandidate = pcbTable[getHighestPriorityProcess()];
    int highestPriorityPid = (highPriorityCandidate.priority > currentProcess.priority) ? highPriorityCandidate.priority : currentProcess.priority;

    printf("The highest priority process has pid %d.\n", highestPriorityPid);
    if (highestPriorityPid != runningState)
    {
        PcbEntry highestProcess = pcbTable[highestPriorityPid];
        dequeue(&readyState[highestProcess.priority]);
        loadContext(highestPriorityPid);
    }
}