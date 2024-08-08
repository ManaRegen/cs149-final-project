#include "../headers/structs.h"

Program init = {
    .instructions = {
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
        {'E', 0, ""}
    },
    .programSize = 16,
    .name = "init"
};

Program file_a = {
    .instructions = {
        {'S', 4, ""},
        {'A', 8, ""},
        {'D', 2, ""}
    },
    .programSize = 3,
    .name = "file_a";
};
