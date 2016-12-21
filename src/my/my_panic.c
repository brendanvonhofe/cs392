#include "my.h"

void my_panic(char* str, int n) {
    my_str(str);
    exit(n);
}
