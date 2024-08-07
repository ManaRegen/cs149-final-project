#include "../headers/structs.h"
#include <stdio.h>

Instruction init[] = {
    {'S', 1000, ""},
    {'A', 19, ""},
    {'A', 20, ""},
    {'D', 53, ""},
    {'A', 55, ""},
    {'F', 1, ""},
    {'R', 0, "file_a"},
    {'F', 1, ""},
    {'R', 0, "file_b"},
    {'F', 1, ""},
    {'R', 0, "file_c"},
    {'F', 1, ""},
    {'R', 0, "file_d"},
    {'F', 1, ""},
    {'R', 0, "file_e"},
    {'E', 0, ""}};

Instruction file_a[] = {
    {'S', 4, ""},
    {'A', 8, ""},
    {'D', 2, ""}
};    
