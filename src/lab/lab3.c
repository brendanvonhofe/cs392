#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pid_t pid;
int is_alive = 1;

void ctrl_z() {
    kill(pid, SIGUSR1);
    alarm(10);
}

void dead_baby() {
    is_alive = 0;
    alarm(10);
}

void ctrl_c() {
    if(is_alive) {
        kill(pid, SIGUSR2);
    }
    else {
        printf("Goodbye! \n");
        exit(0);
    }
    alarm(10);
}

void diediedie() {
    kill(pid, SIGKILL);
    exit(0);
}

void cigreceived() {
    printf("Signal Received! \n");
    alarm(10);
}

void childexit() {
    exit(0);
}

void fuckoff() {
    alarm(10);
}

int main() {
    alarm(10);
    pid = fork();

    if(pid == -1) {
        printf("get fuckd");
    }
    else if(pid == 0) { //child
        signal(SIGUSR1, cigreceived);
        signal(SIGUSR2, childexit);
        signal(SIGINT, fuckoff);
        signal(SIGTSTP, fuckoff);
        while(1) {
            pause();
        }
    }
    else {
        signal(SIGTSTP, ctrl_z);
        signal(SIGCHLD, dead_baby);
        signal(SIGINT, ctrl_c);
        signal(SIGALRM, diediedie);
        while(1) {
            pause();
        }
    }
}
