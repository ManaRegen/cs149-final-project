#ifndef GLOBALS_H
#define GLOBALS_H

#include "structs.h"
#include "queue.h"

#define MAX_PROCESSES 99

extern int time;
extern Cpu cpu;
extern PcbEntry pcbTable[];

extern Queue readyState;
extern Queue blockedState;
extern int runningState;

extern int totalTurnaround;
extern int completedProcessesCount;

#endif // GLOBALS_H
