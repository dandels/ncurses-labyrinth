#include <stdio.h>
#include <locale.h>
#include <ncurses.h>

int inputloop();
int handlemovement(int y, int x);
int drawmap();
int x = 1;
int y = 1;
WINDOW *win;

int main() {
    // Recommended by man page
    setlocale(LC_ALL, "");

    initscr();

    // Needs testing. Is it necessary to check for this?
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color.\n");
        return 1;
    }

    // These dimensions are somewhat arbitrary, but they have to be bigger than the map we use
    win = newwin(36, 72, 0, 0);

    // Read a character at a time without waiting for newline or carriage return
    cbreak();

    // Don't print keypresses
    noecho();

    // Don't translate return key into newline
    nonl();

    // Don't flush tty driver queue contents if an interrupt key is pressed, as it messes up the screen contents
    intrflush(win, FALSE);

    // Enable use of the keypad
    keypad(win, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    // Enable scrolling if moving past the terminal edge.
    //idlok(win, TRUE);
    //scrollok(win, TRUE);

    drawmap("map.txt");
    box(win, '|', '-');

    inputloop();

    // Must be called before exiting so our terminal doesn't behave weirdly
    endwin();
    return 0;
}

int drawmap(char *filename) {
    wmove(win, 0, 0);
    FILE *fp;
    int c;
    fp = fopen(filename, "r");
    while (1) {
        c = fgetc(fp);
        if (feof(fp)) {
            break;
        }
        switch (c) {
            case '<':
            case '>':
            case '^':
            case 'v':
                wattron(win, COLOR_PAIR(1));
                wprintw(win, "%c", c);
                wattroff(win, COLOR_PAIR(1));
                break;
            default:
                 wprintw(win, "%c", c);
                 break;
        }
    }
    fclose(fp);
    wmove(win, y, x);
}

int inputloop() {
    for (;;) {
        int next_y = y;
        int next_x = x;
        int keypress = wgetch(win);
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
        wrefresh(win);
    }

    return 0;
}

int handlemovement (int next_y, int next_x) {
    int nextchar = mvwinch(win, next_y, next_x);
    // The int to compare has a different value depending on the color of the character, 
    // so we use the int values as a workaround
    switch (nextchar) {
        // >
        case 318:
            if (next_x > x)  {
                x = next_x;
            }
            break;
        // <
        case 316:
            if (next_x < x) {
                x = next_x;
            }
            break;
        // v
        case 374:
            if (next_y > y) {
                y = next_y;
            }
            break;
        // ^
        case 350:
            if (next_y < y) {
                y = next_y;
            }
            break;
        case ' ':
            x = next_x;
            y = next_y;
            break;
        default:
            // Debug function for getting the code of the char we run into
            // wprintw(win, "%d", nextchar);
            break;
    }
    wmove(win, y, x);
    return 0;
}
