#include "my.h"

int my_atoi(char *str) {
    if(str == NULL) return 0;
    int mul = 1;
    int val = 0;
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == 45) mul *= -1;
        else if(str[i] > 47 && str[i] < 58) {
            break;
        }
        i++;
    }

    while(str[i] != '\0') {
        if(str[i] < 48 || str[i] > 57) break;
        val *= 10;
        val += str[i] - 48;
        i++;
    }
    return val * mul;
}
