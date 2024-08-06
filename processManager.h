#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "queue.h"
#include "structs.h"

void processManager(int command_fd[2], int response_fd[2]);

#endif // PROCESS_MANAGER_H
