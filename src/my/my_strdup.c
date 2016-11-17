#include "my.h"

char *my_strdup(char *src) {
    if(src == NULL) return NULL;
    char *dst = (char*)malloc((my_strlen(src) + 1) * sizeof(char));
    int i;
    for(i = 0; src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return dst;
}
