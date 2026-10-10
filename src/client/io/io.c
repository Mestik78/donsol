#include "io.h"

enum Key read_input() {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();
    enum Key result = KEY_OTHER;

    switch (ch) {
        case '\n': result = KEY_ENTER; break;
        case ' ': result = KEY_ENTER; break;

        case 'k': result = KEY_UP; break;
        case 'j': result = KEY_DOWN; break;
        case 'l': result = KEY_RIGHT; break;
        case 'h': result = KEY_LEFT; break;

        case '\033':
            getchar();
            switch(getchar()) {
                case 'A': result = KEY_UP; break;
                case 'B': result = KEY_DOWN; break;
                case 'C': result = KEY_RIGHT; break;
                case 'D': result = KEY_LEFT; break;
            }
            break;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return result;
}
