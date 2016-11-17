#include "my.h"

void my_num_base(int num, char* alphabet) {
    if(alphabet == NULL || my_strlen(alphabet) == 0) {
        my_str("Please input a non-empty string, yo");
        return;
    }

    if(num == 0) my_char('0');

    long my_num = (long)num;

    if(my_strlen(alphabet) == 1) {
        while(num-- > 0) {
            my_str(alphabet);
        }
        my_char('\n');
        return;
    }

    if(num < 0) {
        my_char('-');
        my_num = ((long)num) * -1;
    }

    char digits[32];
    int ct = 0;
    long base = (long)my_strlen(alphabet);
    while(my_num > 0) {
        digits[ct++] = alphabet[my_num % base];
        my_num /= base;
    }
    while(--ct > -1) {
        my_char(digits[ct]);
    }
    my_char('\n');
}
