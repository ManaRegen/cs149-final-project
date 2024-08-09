#include "../headers/structs.h"

Program init = {
    .instructions = {
        {'S', 100, ""},
        {'F', 1, ""},
        {'A', 10, ""},
        {'F', 0, ""},
        {'B', 0, ""},
        {'A', 10, ""},
        {'A', 0, ""}
    },
    .programSize = 4,
    .name = "init"
};

Program file_a = {
    .instructions = {
        {'S', 4, ""},
        {'A', 8, ""},
        {'D', 2, ""}
    },
    .programSize = 3,
    .name = "file_a"
};
