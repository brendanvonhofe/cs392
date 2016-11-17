#include "my.h"

char* my_strcat(char* dst, char* src) {
    if(dst == NULL && src == NULL) return NULL;
    else if(dst == NULL) return NULL;
    else if(src == NULL) return dst;
    
    int i, j;
    for(i = my_strlen(dst), j = 0; src[j] != '\0'; i++, j++) {
        dst[i] = src[j];
    }
    dst[i] = '\0';
    return dst;
}
