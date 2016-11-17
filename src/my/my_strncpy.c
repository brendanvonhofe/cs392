#include "my.h"

char* my_strncpy(char* dst, char* src, int n) {
    if(dst == NULL || src == NULL) return NULL;
    int i;
    for(i = 0; src[i] != '\0' && i < n; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return dst;
}
