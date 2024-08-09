#ifndef PROCESS_CONTROLLER_H
#define PROCESS_CONTROLLER_H

#include "structs.h"
#include "globals.h"

// Function prototypes
void initializePcbTable();
int createProcess(int parentPid, Program program);
void loadContext(int processIndex);
void saveContext();
void blockProcess(int pid);
void unblockProcess(); 
void terminateProcess();

#endif // PROCESS_CONTROLLER_H
