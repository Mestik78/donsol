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

    if (ch == '\n')
        result = KEY_ENTER;

    else if (ch == '\033') {
        getchar();
        switch(getchar()) {
            case 'A': result = KEY_UP; break;
            case 'B': result = KEY_DOWN; break;
            case 'C': result = KEY_RIGHT; break;
            case 'D': result = KEY_LEFT; break;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return result;
}
