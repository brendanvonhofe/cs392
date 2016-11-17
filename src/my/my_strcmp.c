#include "my.h"

int my_strcmp(char* a, char* b) {
    if(a == NULL && b == NULL) return 0;
    else if(a == NULL) return -1;
    else if(b == NULL) return 1;

    int i;
    for(i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
        if(a[i] == b[i]) continue;
        else return a[i] - b[i];
    }
    if(a[i] == '\0' && b[i] == '\0') return 0;
    else if(a[i] == '\0') return -b[i];
    else return a[i];
}
