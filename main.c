#include <stdio.h>
#include <locale.h>
#include <ncurses.h>

int inputloop();
int handlemovement(char keypress);
int checkmovement(int y, int x);
int x = 0;
int y = 0;

int main() {
    // Necessary functions as per man page
    setlocale(LC_ALL, "");
    initscr();

    // To get character-at-a-time input without echoing (most interactive, screen oriented programs want this), 
    // the following sequence should be used:
    cbreak();
    noecho();

    // Most programs would additionally use the sequence:
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    inputloop();

    // Must be called before exiting so our terminal doesn't behave weirdly
    endwin();
    return 0;
}

int inputloop() {
    for (;;) {
        char input = (char)getch();
        switch (input) {
            case 'h':
            case 'j':
            case 'k':
            case 'l':
                //mvaddstr(15, 15, "Hello, world!");
                handlemovement(input);
                break;
            case 'q':
                return 0;
            default:
                break;
        }
    }
    return 0;
}

int handlemovement(char keypress) {
    int new_x = x;
    int new_y = y;
    switch (keypress) {
        case 'h':
            new_x--;
            break;
        case 'j':
            new_y++;
            break;
        case 'k':
            new_y--;
            break;
        case 'l':
            new_x++;
            break;
    }
    if (checkmovement(new_y, new_x)) {
        printw("a");
        move(y,x);
        refresh();
    }
    return 0;
}

int checkmovement (int new_y, int new_x) {
    char nextchar = mvinch(new_y, new_x);
    if (nextchar == 'a') {
        return 0;
    } else {
        x = new_x;
        y = new_y;
        return 1;
    }
}
