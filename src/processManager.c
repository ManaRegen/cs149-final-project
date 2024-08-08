#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "../headers/queue.h"
#include "../headers/structs.h"
#include "../headers/q.h"
#include "../headers/p.h"
#include "../headers/u.h"
#include "../headers/t.h"
#include "../headers/files.h"
#include "../headers/globals.h"
#include "../headers/processController.h"

static void initializePm()
{
    initializePcbTable();
    createProcess(0, init);
    loadContext(0);
    initializeQueue(&readyState);
    initializeQueue(&blockedState);
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
            q();
            break;
        case 'U':
            u(blockedState, readyState);
            break;
        case 'P':
            p();
            break;
        case 'T':
            t(command_fd, response_fd);
            return;
        default:
            printf("Invalid command. Please try again.\n");
            break;
        }
        signal = 1;
        write(response_fd[1], &signal, sizeof(char));
    }
}