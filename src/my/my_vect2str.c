#include "my.h"

char *my_vect2str(char **x) {
    if(x == NULL || *x == NULL) {
        my_str("vect2str null argument");
        return NULL;
    }
    else if(x[1] == NULL) {
        return x[0];
    }

    char *space = " ";
    int i = 2;
    char* ptr = x[i];
    char* str = my_strconcat(x[0], my_strconcat(space, x[1]));

    while(ptr != NULL) {
        ptr = my_strconcat(space, ptr);
        str = my_strconcat(str, ptr);
        i++;
        ptr = x[i];
    }

    return str;

}
