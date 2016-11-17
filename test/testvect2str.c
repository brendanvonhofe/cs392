#include "../include/my.h"

int main() {
    char *vect[4];
    vect[0] = "hello";
    vect[1] = "world";
    vect[2] = "man";
    vect[3] = NULL;
    my_str(my_vect2str(vect));
    my_char('\n');
}
