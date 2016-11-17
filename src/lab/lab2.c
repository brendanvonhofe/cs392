#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFSIZE 3

int main() {
    char buf[BUFSIZE];
    int key = 5;
    int encrypted = open("encrypted.txt", O_RDONLY);
    int solution = open("solution.txt", O_WRONLY);
    int n = 1;
    while(n != 0) {
        n = read(encrypted, buf, BUFSIZE);
        printf("%d", n);
        for(int i = 0; i < n; i++) {
            if(buf[i] != '!' && buf[i] != ' ') {
                if(buf[i] >= 'a') {
                    if(buf[i] - key < 'a') {
                        buf[i] = 'z' - (key - (buf[i] - 'a') - 1);
                    }
                    else {
                        buf[i] -= key;
                    }
                }
                else {
                    if(buf[i] - key < 'A') {
                        buf[i] = 'Z' - (key - (buf[i] - 'A') - 1);
                    }
                    else {
                        buf[i] -= key;
                    }
                }
            }
        }
        //char writer[n];
        //for(int j = 0; j < n; j++) {
        //    writer[j] = buf[j];
        //}
        write(solution, buf, n);
        // n = read(encrypted, buf, BUFSIZE);
        key += 2;
    }
    close(encrypted);
    close(solution);
    return 0;
}
