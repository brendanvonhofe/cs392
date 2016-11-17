#include "my.h"

void my_alpha() {
    unsigned short int let = 'A';
    while(let <= 'Z') {
        my_char(let++);
    }
    my_char('\n');
}
