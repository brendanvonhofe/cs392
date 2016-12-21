#define _POSIX_C_SOURCE 200809L
#include <ncurses.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include "my.h"
#include "list.h"


#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

int ch, initrow, initcol, row, col, cursy, cursx, cli, cbi, running, ctrlW, keyUp, keyDown, y, x, promptLen;
char* cur_line;
char* clipboard;
char cur_dir[PATH_MAX];
struct s_node* tmp;
struct s_node** head;
struct s_node* hist_ptr;
WINDOW* win;

void printPrompt() {
        getcwd(cur_dir, sizeof cur_dir);

        init_pair(1, COLOR_GREEN, -1);
        init_pair(2, COLOR_RED, -1);
        init_pair(3, COLOR_BLACK, -1);

        attron(COLOR_PAIR(2));
        printw("nsminishell");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(3));
        printw(":");
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(1));
        printw("~");
        printw(cur_dir);
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(3));
        printw("$ ");
        attroff(COLOR_PAIR(3));

        refresh();

        promptLen = 16 + strlen(cur_dir);

}

void del_line(WINDOW* win) {
        getyx(win, cursy, cursx);
        for(; cursx >= promptLen-1; cursx--) {
                delch();
                move(cursy, cursx-1);
        }
        move(cursy, cursx+1);
}

void reverseString(char* str) {
        int i = 0;
        int j = strlen(str) - 1;
        char tmp = str[j];

        while(i < j) {
                str[j] = str[i];
                str[i] = tmp;
                i++; j--;
        }
}

void shiftRight(char* str) {
    for(int i = strlen(str)-1; i >= 0; i--) {
        str[i+1] = str[i];
    }
    str[0] = ' ';
}

void processCmd(char** cmd) {
    if(cmd[0] == NULL) return;
    if(strcmp(cmd[0], "exit") == 0) {
        running = 0;
        endwin();

        FILE* history = fopen("/home/brendan/.nsmshistory", "w");

        if((*head)->next == NULL) {
            exit(0);
        }

        struct s_node* node = (*head)->next;

        while(node != NULL) {
            fputs(node->elem, history);
            fputc('\n', history);
            node = node->next;
        }

        exit(0);
        fclose(history);
    }
    else if(strcmp(cmd[0], "help") == 0) {
        printw("\ncd [directory]\nChanges the current working directory to [directory].\n\nexit\nExits the minishell.\n\nhelp\nPrints a help message listing the built in commands.");
    }
    else if(strcmp(cmd[0], "cd") == 0) {
        if(cmd[1] == NULL) {
            getyx(win, cursy, cursx);
            mvprintw(cursy+1, 0, "Invalid arguments.");
        }
        else if(chdir(cmd[1]) < 0) {
            getyx(win, cursy, cursx);
            mvprintw(cursy+1, 0, "Invalid path: %s/%s", cur_dir, cmd[1]);
        }
    }
}

void processInput() {
        if(ch == 21) { // CTRL-U
            if(ctrlW == 0) {
                strcpy(clipboard, cur_line);
                memset(cur_line, 0, 1024);
                cli = 0;
                del_line(win);
            }
            else {
                for(int i = 0; i < cli; i++) {
                    shiftRight(clipboard);
                }
                for(int i = 0; cur_line[i] != 0; i++) {
                    clipboard[i] = cur_line[i];
                }
                cli = 0;
                memset(cur_line, 0, 1024);
                del_line(win);
            }
        }
        else if(ch == 23) { // CTRL-W
                getyx(win, cursy, cursx);

                if(ctrlW == 0) {
                    memset(clipboard, 0, 1024);
                    cbi = 0;
                    if(cli > 0) {
                        cli--;
                        x--;
                    }
                    while(cur_line[cli] == ' ' && cli >= 0) {
                        cli--;
                        x--;
                    }
                    while(cur_line[cli] != ' ' && cli >= 0) {
                        cli--;
                        x--;
                    }
                    cli++;
                    x++;
                    int tmpcli = cli;
                    while(cur_line[cli] != 0) {
                        clipboard[cbi] = cur_line[cli];
                        cur_line[cli] = 0;
                        cli++;
                        cbi++;
                    }
                    cli = tmpcli;
                }
                else {
                    cbi = 0;
                    if(cli > 0) {
                        cli--;
                        x--;
                    }
                    while(cur_line[cli] == ' ' && cli >= 0) {
                        cli--;
                        x--;
                        shiftRight(clipboard);
                    }
                    while(cur_line[cli] != ' ' && cli >= 0) {
                        cli--;
                        x--;
                        shiftRight(clipboard);
                    }
                    cli++;
                    x++;
                    int tmpcli = cli;
                    while(cur_line[cli] != 0) {
                        clipboard[cbi] = cur_line[cli];
                        cur_line[cli] = 0;
                        cli++;
                        cbi++;
                    }
                    cli = tmpcli;
                }

                del_line(win);
                move(cursy, promptLen-1);
                printw(cur_line);
                ctrlW = 1;
        }
        else if (ch == 25) { // CTRL-Y
                printw(clipboard);
                strcpy(&(cur_line[cli]), clipboard);
                cli = strlen(cur_line);
                x = strlen(cur_line);
        }
        else if(ch == 12) { // CTRL-L
                clear();
                printPrompt();
                printw(cur_line);
        }
        else if(ch == 1) { // CTRL-A
                getyx(win, cursy, cursx);
                move(cursy, promptLen);
        }
        else if(ch == 5) { // CTRL-E
                getyx(win, cursy, cursx);
                move(cursy, promptLen+strlen(cur_line));
        }
        else if(ch == 2) { // CTRL-B
                endwin();
                debug_string(*head);
                exit(0);
        }
        else if(ch == KEY_DOWN) {
                if(hist_ptr->next != NULL && hist_ptr != *head) {
                    hist_ptr = hist_ptr->next;
                    del_line(win);
                    printw(hist_ptr->elem);
                    strcpy(cur_line, hist_ptr->elem);
                }
                else {
                    del_line(win);
                    memset(cur_line, 0, 1024);
                }
        }
        else if(ch == KEY_UP) {
                if(keyUp == 0) {
                    hist_ptr = *head;
                    for(; hist_ptr->next != NULL; hist_ptr = hist_ptr->next) {}
                    del_line(win);
                    printw(hist_ptr->elem);
                    strcpy(cur_line, hist_ptr->elem);
                }
                else {
                    if(hist_ptr->prev != NULL && hist_ptr->prev != *head) {
                        hist_ptr = hist_ptr->prev;
                        del_line(win);
                        printw(hist_ptr->elem);
                        strcpy(cur_line, hist_ptr->elem);
                    }
                }

                keyUp = 1;
        }
        else if(ch == KEY_BACKSPACE) {
                getyx(win, cursy, cursx);
                if(cursx > promptLen-1) {
                        x--;
                        mvdelch(cursy, cursx-1); // 51
                }
                if(cli > 0) {
                    cli--;
                    cur_line[cli] = 0;
                }
        }
        else if(ch == KEY_LEFT) {
                getyx(win, cursy, cursx);
                if(cursx > promptLen-1) {
                        move(cursy, cursx-1);
                        x--;
                }
        }
        else if(ch == KEY_RIGHT) {
                getyx(win, cursy, cursx);
                if(cursx < promptLen + strlen(cur_line)-1) {
                        move(cursy, cursx+1);
                        x++;
                }
        }
        else if(ch == '\n') { // enter
                //store prev command in the linked list and clear buffer
                char* command = malloc(1024);
                strcpy(command, cur_line);
                if(command[0] != 0) {
                        struct s_node* node = new_node(command, NULL, NULL);
                        append(node, head);
                }

                char** cmd = malloc(32*sizeof(char*));
                for(int i = 0; i < 32; i++) {
                    cmd[i] = malloc(1024);
                    memset(cmd[i], 0, 1024);
                }
                cmd = my_str2vect(cur_line);

                processCmd(cmd);

                // for (char **c = cmd; *c != NULL; c++)
                    // free(*c);
                // free(cmd);

                memset(cur_line, 0, 1024);
                cli = 0;

                printw("\n");
                getyx(win, cursy, cursx);
                // cursy++;
                cursx = 0;
                move(cursy, cursx);
                printPrompt();
                y++;
                x = 0;
        }
        else if(ch >= 32 && ch <= 126) {
                getyx(win, cursy, cursx);
                shiftRight(&(cur_line[x]));
                cur_line[x] = ch;
                cli++;
                insch(ch);
                move(cursy, cursx+1);
                x++;
        }

        if(ch != 23) {
                ctrlW = 0;
        }
        if(ch != KEY_UP) {
            keyUp = 0;
        }
}

void debug() {
    getyx(win, cursy, cursx);
    getmaxyx(stdscr, initrow, initcol);
    for(int i = 0; i < cursx; i++) {
        mvdelch(initrow-1, i);
    }
    for(int i = 0; i < cursx; i++) {
        mvdelch(initrow-2, i);
    }

    move(initrow-2, 0);
    for (struct s_node *h = *head; h != NULL; h = h->next) {
        printw("%s ", (char*)h->elem);
    }


    mvprintw(initrow-1, 0, "Cur_Line: %s, Clipboard: %s, Hist_Ptr: %s, x: %d, y: %d", cur_line, clipboard, (char*)(hist_ptr->elem), x, y);
    move(cursy, cursx);
}

void loadHistory() {
    char* lineptr = malloc(1024);
    memset(lineptr, 0, 1024);
    size_t n = 1024;
    char path[PATH_MAX];
    strcpy(path, getenv("HOME"));
    strcat(path, "/.nsmshistory");
    FILE* history = fopen(path, "r");

    while(getline(&lineptr, &n, history) != -1) {
        char* str = malloc(1024);
        lineptr[strlen(lineptr)-1] = 0;
        strcpy(str, lineptr);
        append(new_node(str, NULL, NULL), head);
        memset(lineptr, 0, 1024);
    }
    fclose(history);
}

int main() {

        win = initscr();
        keypad(stdscr, TRUE);
        scrollok(stdscr, TRUE);
        cbreak();
        noecho();
        start_color();
        assume_default_colors(COLOR_BLACK, COLOR_WHITE);

        cursy = 0; cursx = 0; cli = 0; cbi = 0; running = 1; ctrlW = 0; keyUp = 0; keyDown = 0; y = 0; x = 0;
        cur_line = malloc(1024);
        clipboard = malloc(1024);
        tmp = new_node("", NULL, NULL);
        head = &tmp;
        hist_ptr = *head;


        memset(cur_line, 0, 1024);
        memset(clipboard, 0, 1024);
        getmaxyx(stdscr, initrow, initcol);

        while(tmp->next != NULL) {
                tmp = tmp->next;
        }

        printPrompt();
        loadHistory();
        //debug();

        while(running) {
                getmaxyx(stdscr, row, col);
                if(row != initrow || col != initcol) {
                        refresh();
                }


                ch = getch();
                processInput();
                //debug();
        }


        endwin();
        return 0;
}
