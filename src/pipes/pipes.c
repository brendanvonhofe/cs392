#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../../include/my.h"
#include <strings.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        my_str("Usage error; please provide message to be piped\n");
        exit(0);
    }

    char *str = my_vect2str(argv + 1);
    int fd[2];
    int fd2[2];
    pid_t pid;
    pid_t pid2;
    char buffer[100];
    char buffer2[100];
    bzero(buffer, 100);
    bzero(buffer2, 100);


    if(pipe(fd) < 0) {
        my_str("pipe error \n");
        exit(0);
    }
    if((pid = fork()) < 0) {
        my_str("fork error \n");
        exit(0);
    }
    else if(pid > 0) {
        close(fd[0]);
        write(fd[1], str, my_strlen(str));
        my_str("Parent: ");
        my_str(str);
        my_char('\n');
        close(fd[1]);
        wait(0);
    }
    else {
        close(fd[1]);
        read(fd[0], buffer, 100);
        my_str("Child: ");
        my_str(buffer);
        my_char('\n');
        close(fd[0]);

        if(pipe(fd2) < 0) {
            my_str("pipe2 error \n");
            exit(0);
        }
        if((pid2 = fork()) < 0) {
            my_str("fork2 error \n");
            exit(0);
        }
        else if(pid2 > 0) {
            close(fd2[0]);
            write(fd2[1], buffer, my_strlen(buffer));
            wait(0);
            close(fd2[1]);
        }
        else {
            close(fd2[1]);
            read(fd2[0], buffer2, 100);
            my_str("Grandchild: ");
            my_str(buffer2);
            my_char('\n');
            close(fd2[0]);
        }
    }
    return 0;
}
