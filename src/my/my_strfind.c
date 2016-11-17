#include "my.h"

char* my_strfind(char* str, char c) {
    int i = my_strindex(str, c);
    if(i == -1) return NULL;
    else return str + i;
}
