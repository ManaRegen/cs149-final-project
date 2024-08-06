#include "p.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern int time;

static void reporterProcess() { // to be completed
    printf("****************************************************************\n");
    printf("The current system state is as follows:\n");
    printf("****************************************************************\n\n");

    printf("CURRENT TIME: %d\n\n", time);

    printf("RUNNING PROCESSES: \n");


}

void p() {
    // Spawn a reporter process
                if (fork() == 0) {
                    reporterProcess();
                    exit(0);
                }
                wait(NULL);
}