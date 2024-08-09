#include <stdbool.h>
#include "../headers/queue.h"   // Include for Queue related operations
#include "../headers/structs.h" // Include for PcbEntry
#include "../headers/operations.h"
#include "../headers/processController.h"
#include "../headers/scheduler.h"

static void executeCode()
{
    printf("Executing instruction: %d\n", cpu.programCounter);
    Instruction currentInstruction = cpu.program.instructions[cpu.programCounter];
    printf("Executing instruction: %c\n", currentInstruction.operation);

    cpu.programCounter++;
    cpu.timeSliceUsed++;

    switch (currentInstruction.operation)
    {
    case 'S':
        S(currentInstruction.intArg);
        break;
    case 'A':
        A(currentInstruction.intArg);
        break;
    case 'D':
        D(currentInstruction.intArg);
        break;
    case 'B':
        B();
        break;
    case 'E':
        E();
        break;
    case 'F':
        F(currentInstruction.intArg);
        break;
    case 'R':
        R(currentInstruction.stringArg);
        break;
    default:
        printf("Invalid operation on line %d. Please try again.\n", cpu.programCounter);
        break;
    }
}

void incrementTime()
{
    time++;
    scheduleProcess();
    printf("Running process %d\n", runningState);
    executeCode();
    checkTimeSlice(); 
}