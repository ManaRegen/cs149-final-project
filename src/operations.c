#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../headers/queue.h"
#include "../headers/structs.h"
#include <string.h>
#include "../headers/globals.h"
#include "../headers/processController.h"
#include "../headers/files.h"

// Set CPU value to n
void S(int n)
{
    cpu.value = n;
}

// Add n to CPU value
void A(int n)
{
    cpu.value += n;
}

// Subtract n from CPU value
void D(int n)
{
    cpu.value -= n;
}

// Take the PCB of the currently running process to add it to the blocked queue, store the CPU PC in the PCB's PC, store the CPU's value in the PCB's value, and change runningState to -1
void B()
{
    blockProcess(runningState);
}

// Terminate the process
void E()
{
    terminateProcess();
}

// Create a new process
void F(int n)
{
    createProcess(runningState, cpu.program);
    cpu.programCounter += n;
}

// Replace the program of the process with filename and set the program counter to the first instruction of filename
void R(char *filename)
{
    Program *newProgram = NULL;

    if (strcmp(filename, "init") == 0)
    {
        newProgram = &init;
    }

    else if (strcmp(filename, "file_a") == 0)
    {
        newProgram = &file_a;
    }

    else if (strcmp(filename, "file_b") == 0)
    {
        newProgram = &file_b;
    }

    else if (strcmp(filename, "file_c") == 0)
    {
        newProgram = &file_c;
    }

    else if (strcmp(filename, "file_d") == 0)
    {
        newProgram = &file_d;
    }

    if (newProgram == NULL)
    {
        printf("Error: Program with filename %s not found\n", filename);
        return;
    }

    cpu.program = *newProgram;
    cpu.programCounter = 0;

    // pcbTable[runningState].program = filename;
    // pcbTable[runningState].programCounter = 0;
}