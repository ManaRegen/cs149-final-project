#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../headers/structs.h"
#include "../headers/globals.h"

static void listQueueMembers(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
    }
    else
    {
        for (int i = q->front + 1; i < q->rear; i++)
        {
            PcbEntry runningP = pcbTable[q->items[i]];
            printf("PID: %d, PPID: %d, Priority: %d, Value: %d, Start Time: %d, CPU Time Used: %d\n",
                   runningP.processId, runningP.parentProcessId, runningP.priority, runningP.value, runningP.startTime, runningP.timeUsed);
        }
        printf("\n");
    }
}

static void reporterProcess()
{ // to be completed
    printf("\n*****************************************************************************************\n");
    printf("The current system state is as follows:\n");
    printf("*****************************************************************************************\n\n");

    printf("CURRENT TIME: %d\n\n", time);

    if (runningState == -1)
    {
        printf("There is currently no process running.\n");
    }
    else
    {
        PcbEntry runningP = pcbTable[runningState];
        printf("RUNNING PROCESS: \n");
        printf("PID: %d, PPID: %d, Priority: %d, Value: %d, Start Time: %d, CPU Time Used: %d\n\n",
               runningP.processId, runningP.parentProcessId, runningP.priority, cpu.value, runningP.startTime, cpu.timeSliceUsed);
    }
    printf("READY PROCESSES: \n");
    printf("\nPRIORITY 3: \n");
    listQueueMembers(&readyState[3]);
    printf("\nPRIORITY 2: \n");
    listQueueMembers(&readyState[2]);
    printf("\nPRIORITY 1: \n");
    listQueueMembers(&readyState[1]);
    printf("\nPRIORITY 0: \n\n");
    listQueueMembers(&readyState[0]);
    printf("\nBLOCKED PROCESSES: \n\n");
    listQueueMembers(&blockedState);

    printf("\n*****************************************************************************************\n\n");

    return;
}

void printReport()
{
    // Spawn a reporter process
    if (fork() == 0)
    {
        reporterProcess();
        exit(0);
    }
    wait(NULL);
}