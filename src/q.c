#include "../headers/queue.h"   // Include for Queue related operations
#include "../headers/structs.h" // Include for PcbEntry
#include "../headers/instructions.h"

extern Queue readyState;
extern int runningState;
extern int time;
extern Cpu cpu;

static void contextSwitchIn()
{ // selects process from the top of the readyState queue to run
    // Update runningState and readyState
    if (!isEmpty(&readyState))
    {
        runningState = readyState.front;
        dequeue(&readyState);
    }
    
}

static void executeCode() {
    int currentLine = cpu.programCounter;
    Instruction currentInstruction = cpu.program[currentLine];

    char op = currentInstruction.operation;
    int intArg = currentInstruction.intArg;
    char stringArg[] = currentInstruction.stringArg;

    switch (op)
        {
        case 'S':
            S(intArg);
            break;
        case 'A':
            A(intArg);
            break;
        case 'D':
            D(intArg);
            break;
        case 'B':
            B();
            break;            
        case 'E':
            E();
            break;
        case 'F':
            F();
            break;
        case 'R':
            R(char filename[])
            break;
        default:
            printf("Invalid operation on line %d. Please try again.\n", currentLine);
            break;
        }
}

void q()
{
    // Execute the next instruction of the running process
    if (runningState == -1)
    {
        contextSwitchIn();
    }
    time++;
}