#define _BSD_SOURCE
#include "my.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 1024

void sig_handler(pid_t pid) {
    kill(pid, SIGKILL);
}

void execute(char *buf) {
    pid_t pid;
    char **vect = my_str2vect(buf);
    if((pid = fork()) < 0) {
        perror("fork");
    }
    if(pid == 0) {
        if(execvp(vect[0], vect) < 0) {
            perror("exec");
        }
        exit(0);
    }
    else {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {

    int running = 1;
    char *cur_dir;
    char *buf;
    int reads = 1;
    int rd_ind = 0;
    buf = (char *)malloc(BUFSIZE);
    memset(buf, 0, BUFSIZE);

    while(running) {
        rd_ind = 0;
        reads = 1;

        signal(SIGINT, sig_handler);

        cur_dir = getcwd(NULL, 0);
        my_str("MINISHELL: ");
        my_str(cur_dir);
        my_str(" $:");

        while(read(0, &buf[rd_ind], BUFSIZE) == BUFSIZE) {
            if(buf[(BUFSIZE*reads)-1] == '\n') break;
            reads++;
            rd_ind += BUFSIZE;
            void *new_ptr;
            if((new_ptr = realloc(buf, BUFSIZE * reads)) != NULL) {
                buf = new_ptr;
            }
            else {
                perror("realloc");
                exit(0);
            }
        }

        if(my_strcmp(buf, "exit\n") == 0) {
            exit(0);
        }
        else if(my_strcmp(buf, "help\n") == 0) {
            my_str("\ncd [directory]\nChanges the current working directory to [directory].\n\nexit\nExits the minishell.\n\nhelp\nPrints a help message listing the built in commands.\n\n");
        }
        else if(my_strncmp(buf, "cd ", 3) == 0) {
            char path[1024];
            for(int i = 3; buf[i] != ' ' && buf[i] != '\0'; i++) {
                path[i-3] = buf[i];
            }

            char *abs_path = my_strconcat(cur_dir, "/");
            my_strcat(abs_path, path);

            //get rid of pesky newline
            for(int i = 0; i < my_strlen(abs_path); i++) {
                if(abs_path[i] == '\n') {
                    abs_path[i] = 0;
                }
            }

            if(chdir(abs_path) < 0) {
                perror("Invalid path");
                my_str(abs_path);
                my_char('\n');
            }
        }
        else {
            execute(buf);
        }

        memset(buf, 0, BUFSIZE*reads);
    }
}
