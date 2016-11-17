#include "my.h"

int my_strrindex(char* str, char key) {
    if(str == NULL || key == '\0') {
        my_str("Please input a valid string and character. \n");
        return -1;
    }
    int let;
    for(int i = my_strlen(str) - 1; i >= 0; i--) {
        let = str[i];
        if(let == key) return i;
    }
    return -1;
}
