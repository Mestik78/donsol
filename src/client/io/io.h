#ifndef IO_H
#define IO_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

enum Key {
    KEY_OTHER,

    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,

    KEY_ENTER
};

enum Key read_input();

#endif
