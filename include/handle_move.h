#include <stdbool.h>

#ifndef HANDLE_MOVE_H
#define HANDLE_MOVE_H

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
};

void handle_move(enum direction dir, int x, int y);

#endif