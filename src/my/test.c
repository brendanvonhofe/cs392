#include "my_str2vect.c"
#include "my_str.c"
#include "my_char.c"

int main() {
    char *str = "hello world";
    char **vect = my_str2vect(str);
    for(int i = 0; vect[i] != NULL; i++) {
        my_str(vect[i]);
        my_str(", ");
    }
    my_char('\n');
}
