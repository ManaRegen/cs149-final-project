#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "../headers/queue.h"
#include "../headers/structs.h"
#include "../headers/q.h"
#include "../headers/p.h"
#include "../headers/t.h"
#include "../headers/files.h"
#include "../headers/globals.h"
#include "../headers/processController.h"

static void initializePm()
{
    initializePcbTable();
    createProcess(-1, init);
    loadContext(0);
    initializeQueue(&blockedState);

    for (int i = 0; i < 4; i++)
    {
        initializeQueue(&readyState[i]);
    }
    
    printf("Process Manager has been initialized.\n");
}

void processManager(int command_fd[2], int response_fd[2])
{
    close(command_fd[1]);  // Close unused write end
    close(response_fd[0]); // close unused read end
    char command;
    char signal;

    initializePm();
    signal = 1;
    write(response_fd[1], &signal, sizeof(char));

    while (true)
    {
        read(command_fd[0], &command, 1);
        switch (command)
        {
        case 'Q':
            incrementTime();
            break;
        case 'U':
            unblockProcess(); 
            break;
        case 'P':
            printReport();
            break;
        case 'T':
            terminateProcessManager(command_fd, response_fd);
            return;
        default:
            printf("Invalid command. Please try again.\n");
            break;
        }
        signal = 1;
        write(response_fd[1], &signal, sizeof(char));
    }
}