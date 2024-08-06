#include "../headers/q.h"
#include "../headers/queue.h"   // Include for Queue related operations
#include "../headers/structs.h" // Include for PcbEntry

extern Queue readyState;
extern int runningState;

void runProcess()
{ // selects process from the top of the readyState queue to run
    // Update runningState and readyState
    if (!isEmpty(&readyState))
    {
        runningState = readyState.front;
        dequeue(&readyState);
    }
}

void q()
{
    // Execute the next instruction of the running process
    if (runningState == -1)
    {
        runProcess();
    }
}