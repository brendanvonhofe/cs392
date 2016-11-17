#include "my.h"

int main() {
    char *str = (char *)my_malloc(4);
    str[0] = 'y';
    str[1] = 'e';
    str[2] = 'p';
    str[3] = '\0';
    my_str(str);
    my_char('\n');
}
