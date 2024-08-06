#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{
    char operation;
    int intArg;
    char stringArg[99];
} Instruction;

typedef struct
{
    int *program;
    int programCounter;
    int value;
    int timeSlice;
    int timeSliceUsed;
} Cpu;

typedef struct
{
    int processId;
    int parentProcessId;
    Instruction program[99];
    int programCounter;
    int value;
    int priority;
    int startTime;
    int timeUsed;
} PcbEntry;

#endif // STRUCTS_H
