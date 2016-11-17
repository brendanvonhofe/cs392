#include "my.h"

int my_revstr(char* str) {
    int len = my_strlen(str);
    char temp;
    int i, j;
    for(i = 0, j= (len-1); i < len / 2; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    return len;
}
