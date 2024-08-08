#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "queue.h"
#include "structs.h"


// CPU structure
extern Cpu cpu;

// External variables
extern int runningState;
extern Queue blockedState;
extern PcbEntry pcbTable[99];
extern int time;

// Function prototypes
void S(int n);    // Set CPU value to n
void A(int n);    // Add n to CPU value
void D(int n);    // Subtract n from CPU value
void B();         // Block the running process
void E();         // Terminate the process
void F();         // Create a new process
void R(char *filename); // Replace the program of the process with filename

#endif // OPERATIONS_H
