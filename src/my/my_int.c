#include "my.h"

void my_int(int num) {
    if(num == 0) {
        my_char('0');
        return;
    }
    if(num > 0) {
        int div = 1;
        while(div < num && div < 1000000000) { //need to find a divisor so that
            div *= 10;                         //it prints the most significant
        }                                      //digit first
        if(div != 1000000000 && div != 1) div /= 10;
        while(div > 0) {
            my_char((num / div) + '0');
            num %= div;
            div /= 10;
        }
        return;
    }
    if(num < 0) {
        my_char('-');
        int div = -1;
        while(div > num && div > -1000000000) {
            div *= 10;
        }
        if(div != -1000000000 && div != -1) div /= 10;
        while(div < 0) {
            my_char((num / div) + '0');
            num %= div;
            div /= 10;
        }
        return;
    }
}
