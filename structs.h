#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char operation;
    int intArg;
    char stringArg[99];
} Instruction;

typedef struct {
    Instruction instructions[99];
    int programCounter;
    int value;
    int timeSlice;
    int timeSliceUsed;
} Cpu;

enum State {
    STATE_READY,
    STATE_RUNNING,
    STATE_BLOCKED
};

typedef struct {
    int processId;
    int parentProcessId;
    Instruction program[99];
    int programCounter;
    int value;
    int priority;
    State state;
    int startTime;
    int timeUsed;
} PcbEntry;

#endif // STRUCTS_H
