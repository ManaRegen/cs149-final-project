#include <stdbool.h>
#include <stdio.h>
#include "../headers/globals.h"
#include "../headers/processController.h"
#include "../headers/queue.h"

static int dequeueIfNotEmpty(Queue *queue)
{
    if (!isEmpty(queue))
    {
        int pid = peek(queue);
        dequeue(queue);
        return pid;
    }
    return -1;
}

static int getHighestPriorityProcess()
{
    int pid;

    pid = dequeueIfNotEmpty(&readyState[3]);
    if (pid != -1)
    {
        return pid;
    }

    pid = dequeueIfNotEmpty(&readyState[2]);
    if (pid != -1)
    {
        return pid;
    }

    pid = dequeueIfNotEmpty(&readyState[1]);
    if (pid != -1)
    {
        return pid;
    }

    pid = dequeueIfNotEmpty(&readyState[0]);
    if (pid != -1)
    {
        return pid;
    }

    return runningState;
}

void scheduleProcess()
{
    int highestPriorityProcess = getHighestPriorityProcess();
    printf("The highest priority process has pid %d.\n", highestPriorityProcess);
    if (highestPriorityProcess != runningState)
    {
        loadContext(highestPriorityProcess);
    }
}