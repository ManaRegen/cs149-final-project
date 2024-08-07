#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../headers/queue.h"
#include "../headers/structs.h"
#include <string.h>

Cpu cpu;
extern int runningState;
extern Queue blockedState;
extern PcbEntry pcbTable[99];
extern int time;

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
void F()
{
    //Get the next free PCB index
    for (int i = 0; i < 99; i++) 
    {
        if (pcbTable[i].processId == -1) 
        { 
            pcbTable[i].parentProcessId = pcbTable[runningState].processId;
            memcpy(pcbTable[i].program, pcbTable[runningState].program, sizeof(Instruction) * 99);
            pcbTable[i].programCounter = pcbTable[runningState].programCounter + 1;
            pcbTable[i].value = pcbTable[runningState].value;
            pcbTable[i].priority = pcbTable[runningState].priority;
        }
    }
}

//Replace the program of the process with filename and set the program counter to the first instruction of filename
void R(char filename)
{
    //pcbTable[runningState].program = filename;
    //pcbTable[runningState].programCounter = 0;
}