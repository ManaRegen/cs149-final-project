#include "../headers/structs.h"

Program init = {
    .instructions = {
        {'S', 100, ""},
        {'F', 1, ""},
        {'A', 10, ""},
        {'F', 1, ""},
        {'R', 0, "file_d"},
        {'R', 0, "file_a"},
        {'E', 0, ""}
    },
    .programSize = 7,
    .name = "init"
};

Program file_a = {
    .instructions = {
        {'S', 4, ""},
        {'A', 8, ""},
        {'B', 2, ""},
        {'R', 0, "file_b"},
        {'E', 0, ""}
    },
    .programSize = 5,
    .name = "file_a"
};

Program file_b = {
    .instructions = {
        {'S', 50, ""},
        {'A', 20, ""},
        {'D', 5, ""},
        {'F', 2, ""},
        {'B', 0, ""},
        {'R', 0, "file_c"},
        {'E', 0, ""}
    },
    .programSize = 7,
    .name = "file_b"
};

Program file_c = {
    .instructions = {
        {'S', 200, ""},
        {'D', 50, ""},
        {'F', 1, ""},
        {'A', 30, ""},
        {'R', 0, "file_d"},
        {'B', 0, ""},
        {'E', 0, ""}
    },
    .programSize = 7,
    .name = "file_c"
};

Program file_d = {
    .instructions = {
        {'S', 10, ""},
        {'A', 40, ""},
        {'F', 3, ""},
        {'D', 20, ""},
        {'A', 10, ""},
        {'B', 0, ""},
        {'E', 0, ""}
    },
    .programSize = 7,
    .name = "file_d"
};
