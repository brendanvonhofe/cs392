#include "my.h"

int my_strlen(char* str) {
    if(str == NULL) return -1;
    int len = 0;
    char letter = str[len];
    while(letter != '\0') {
        len += 1;
        letter = str[len];
    }
    return len;
}
