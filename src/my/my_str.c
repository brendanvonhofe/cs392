#include "../../include/my.h"

void my_str(char* str) {
    if(str == NULL || str[0] == '\0') {
    }
    else {
        int i = 0;
        char letter = str[i];
        while(letter != '\0') {
            letter = str[i];
            my_char(letter);
            i = i + 1;
        }
    }
}
