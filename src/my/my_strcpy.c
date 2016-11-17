#include "my.h"

char* my_strcpy(char* dst, char* src) {
    if(dst == NULL || src == NULL) return NULL;
    int i;
    for(i = 0; src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return dst;
}
