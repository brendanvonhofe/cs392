#include "my.h"

char* my_strrfind(char* str, char c) {
    int i = my_strrindex(str, c);
    if(i == -1) return NULL;
    else return str + i;
}
