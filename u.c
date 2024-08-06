#include "queue.h"

void u(Queue blockedState, Queue readyState)
{
    int index = peek(&blockedState);
    dequeue(&blockedState);
    enqueue(&readyState, index);
}