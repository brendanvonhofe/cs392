#include "my.h"

char *my_strconcat(char* a, char* b) {
    if(a == NULL && b == NULL) return NULL;

    char *ab;
    int i;

    if(b == NULL) {
        ab = (char*)malloc((my_strlen(a) + 1) * sizeof(char));
        for(i = 0; a[i] != '\0'; i++) {
            ab[i] = a[i];
        }
        ab[i] = '\0';
    }
    else if(a == NULL) {
        ab = (char*)malloc((my_strlen(b) + 1) * sizeof(char));
        for(i = 0; b[i] != '\0'; i++) {
            ab[i] = b[i];
        }
        ab[i] = '\0';
    }
    else {
        int j;
        ab = (char*)malloc((my_strlen(a) + my_strlen(b) + 1) * sizeof(char));
        for(i = 0; a[i] != '\0'; i++) {
            ab[i] = a[i];
        }
        for(j = 0; b[j] != '\0'; i++, j++) {
            ab[i] = b[j];
        }
        ab[i] = '\0';
    }
    return ab;
}
