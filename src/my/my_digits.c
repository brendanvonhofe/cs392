#include "my.h"

void my_digits() {
    unsigned short int digit = '0';
    while(digit <= '9') {
        my_char(digit++);
    }
    my_char('\n');    
}
