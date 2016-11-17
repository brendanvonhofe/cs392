#include "my.h"

int my_strncmp(char* a, char* b, int n) {
    if(a == NULL && b == NULL) return 0;
    else if(a == NULL) return -1;
    else if(b == NULL) return 1;

    int i;
    for(i = 0; i < n; i++) {
        if(a[i] == '\0' || b[i] == '\0') {
            i++;
            break;
        }
        if(a[i] == b[i]) continue;
        else return a[i] - b[i];
    }
    i--;
    if(b[i] == a[i]) return 0;
    else if(a[i] == '\0') return ((b[i]) * -1);
    else return a[i];
}
