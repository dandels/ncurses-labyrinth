#include <stdio.h>
#include <locale.h>
#include <ncurses.h>

int inputloop();
int handlemovement(int y, int x);
int drawmap();
int x = 1;
int y = 1;

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

    drawmap("map.txt");
    box(stdscr, '|', '-');
    inputloop();

    // Must be called before exiting so our terminal doesn't behave weirdly
    endwin();
    return 0;
}

int drawmap(char *filename) {
    FILE *fp;
    int c;
    fp = fopen(filename, "r");
    while (1) {
        c = fgetc(fp);
        if (feof(fp)) {
            break;
        }
        printw("%c", c);
    }
    fclose(fp);
}


int inputloop() {
    for (;;) {
        int next_x = x;
        int next_y = y;
        int keypress = getch();
        switch (keypress) {
            case 'q':
                return 0;
            case 'h':
            case KEY_LEFT:
                next_x--;
                break;
            case 'j':
            case KEY_DOWN:
                next_y++;
                break;
            case 'k':
            case KEY_UP:
                next_y--;
                break;
            case 'l':
            case KEY_RIGHT:
                next_x++;
                break;
        }
        handlemovement(next_y, next_x);
        refresh();
    }

    return 0;
}

int handlemovement (int next_y, int next_x) {
    char nextchar = mvinch(next_y, next_x);
    if (nextchar == ' ') {
        x = next_x;
        y = next_y;
        return 0;
    }
    move(y,x);
}
