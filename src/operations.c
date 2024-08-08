#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../headers/queue.h"
#include "../headers/structs.h"
#include <string.h>
#include "../headers/globals.h"
#include "../headers/processController.h"

//Set CPU value to n
void S(int n)
{
    cpu.value = n;
}

//Add n to CPU value
void A(int n)
{
    cpu.value += n;
}

//Subtract n from CPU value
void D(int n)
{
    cpu.value -= n;
}

//Take the PCB of the currently running process to add it to the blocked queue, store the CPU PC in the PCB's PC, store the CPU's value in the PCB's value, and change runningState to -1
void B()
{
    enqueue(&blockedState, runningState);
    //pcbTable[runningState].state = STATE_BLOCKED
    pcbTable[runningState].programCounter = cpu.programCounter;
    runningState = -1;
}

//Terminate the process
void E()
{
    pcbTable[runningState].timeUsed = (time + 1) - pcbTable[runningState].startTime;
    //terminatedProcesses++;
    runningState = -1;
}

//Create a new process
void F(int n)
{
    createProcess(runningState, cpu.program);
    cpu.programCounter += n;
}

//Replace the program of the process with filename and set the program counter to the first instruction of filename
void R(char *filename)
{
    //pcbTable[runningState].program = filename;
    //pcbTable[runningState].programCounter = 0;
}