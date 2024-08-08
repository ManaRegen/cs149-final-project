#include <stdbool.h>
#include <stdio.h>
#include "../headers/globals.h"
#include "../headers/processController.h"
#include "../headers/queue.h"

static int dequeueIfNotEmpty(Queue *queue)
{
    if (!isEmpty(queue))
    {
        peek(queue);
        dequeue(queue);
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
    if (highestPriorityProcess != runningState)
    {
        loadContext(highestPriorityProcess);
    }
}