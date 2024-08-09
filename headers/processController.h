#ifndef PROCESS_CONTROLLER_H
#define PROCESS_CONTROLLER_H

#include "structs.h"
#include "globals.h"

// Function prototypes
void initializePcbTable();
int createProcess(int parentPid, Program program);
void loadContext(int processIndex);
void saveContext();
void addToReadyQueue(int pid);
void blockProcess(int pid);
void unblockProcess(); 

#endif // PROCESS_CONTROLLER_H
