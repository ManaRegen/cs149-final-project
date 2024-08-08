#include "../headers/structs.h"
#include "../headers/queue.h"

#define MAX_PROCESSES 99

int time = 0;
Cpu cpu;
PcbEntry pcbTable[MAX_PROCESSES];

Queue readyState[4];
Queue blockedState;
int runningState;

int totalTurnaround;
int completedProcessesCount;