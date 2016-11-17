#include <ncurses.h>
#include <curses.h>
#include <string.h>
#include <signal.h>


int row, col, max_col, num_cols, selected, running, ch, col_num, row_num;

int get_largest_str(char *strs[], int n) {
    if(n < 2) return 0;
    int largest = 0;
    for(int i = 1; i < n; i++) {
        if(strlen(strs[i]) > largest) {
            largest = strlen(strs[i]);
        }
    }
    return largest;
}

void print_highlighted(char *strings[], int n, int highlights[]) {
    for(int i = 1; i < n; i++) {
        if(highlights[i] == 1) {
            printf("%s ", strings[i]);
        }
    }
    printf("\n");
}

void suppress() {
    return;
}

void redraw_screen(char *strings[], int n, int highlights[]) {
    clear();
    int counter = 0;
    col_num = 0; row_num = 0;
    for(int i = 1; i < n; i++) {
        if(selected == i && highlights[i] == 1) {
            attrset(A_STANDOUT | A_UNDERLINE);
        }
        else if(selected == i) {
            attrset(A_UNDERLINE);
        }
        else if(highlights[i] == 1) {
            attrset(A_STANDOUT);
        }
        else {
            attrset(A_NORMAL);
        }

        mvprintw(row_num, col_num, strings[i]);
        row_num++;

        counter++;
        if(counter >= row) {
            col_num += max_col;
            row_num = 0;
            counter = 0;
        }
    }
    refresh();
}

int main(int argc, char *argv[]) {

    int highlights[argc];
    max_col = get_largest_str(argv, argc);
    max_col++; //space between columns
    selected = 1;
    running = 1;
    for(int i = 0; i < argc; i++) {
        highlights[i] = 0;
    }

    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    raw();
    noecho();

    while(running) {
        clear();
        getmaxyx(stdscr, row, col);

        if(max_col != 0) {
            num_cols = col/max_col;
        }
        else {
            num_cols = 0;
        }

        redraw_screen(argv, argc, highlights);

        if(num_cols * row < argc-1) {
            clear();
            printw("Please enlarge the window.");
            refresh();
        }

        ch = getch();
        if(ch == 27) {
            endwin();
            running = 0;
        }
        else if(ch == 32) {
            if(highlights[selected] == 0) {
                highlights[selected] = 1;
                selected++;
            }
            else {
                highlights[selected] = 0;
            }
        }
        else if(ch == KEY_RIGHT) {
            selected += row;
            if(selected >= argc) {
                selected = argc-1;
            }
        }
        else if(ch == KEY_LEFT) {
            selected -= row;
            if(selected < 1) {
                selected = 1;
            }
        }
        else if(ch == KEY_UP) {
            selected--;
        }
        else if(ch == KEY_DOWN) {
            selected++;
        }
        else if(ch == '\n') {
            endwin();
            running = 0;
            print_highlighted(argv, argc, highlights);
        }

        if(selected >= argc) {
            selected = 1;
        }
        else if(selected < 1) {
            selected = argc-1;
        }

    }

    return 0;
}
