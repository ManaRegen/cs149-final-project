#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char operation;
    int intArg;
    char stringArg[99];
} Instruction;

typedef struct {
    Instruction instructions[99];
    int programSize;
} Program;

typedef struct
{
    Program program;
    int programCounter;
    int value;
    int timeSlice;
    int timeSliceUsed;
} Cpu;

typedef struct {
    int processId;
    int parentProcessId;
    Program program;
    int programCounter;
    int value;
    int priority;
    int startTime;
    int timeUsed;
} PcbEntry;

#endif // STRUCTS_H
