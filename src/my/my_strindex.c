#include "my.h"

int my_strindex(char* str, char key) {
    if(str == NULL || key == '\0') {
        my_str("Please input a valid string and character. \n");
        return -1;
    }
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == key) return i;
    }
    return -1;
}
