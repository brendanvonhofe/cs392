#include "../../include/my.h"

char **my_str2vect(char *str) {
    int word_count = 0;
    int word_length = 0;
    int longest_word = 0;
    char **vect;

    int i = 0;
    while(str[i] != '\0') {
        while(str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0') {
            word_length++;
            i++;
        }
        if(word_length > longest_word) longest_word = word_length;
        word_count++;
        word_length = 0;
        if(str[i] == '\0') break;
        while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
            i++;
        }
    }

    vect = (char **)malloc((word_count + 1) * sizeof(char *));
    for(int j = 0; j < word_count; j++) {
        vect[j] = (char*)malloc((longest_word + 1) * sizeof(char));
    }

    int k, x, y;
    k = 0; x = 0; y = 0;
    while(str[k] != '\0') {
        while(str[k] != ' ' && str[k] != '\t' && str[k] != '\n' && str[k] != '\0') {
            vect[x][y] = str[k];
            k++;
            y++;
        }
        if(str[k] == '\0') break;
        vect[x][y] = '\0';
        k++;
        x++;
        y = 0;
        while(str[k] == ' ' || str[k] == '\t' || str[k] == '\n') {
            k++;
        }
    }
    x++;
    vect[x] = NULL;
    return vect;
}
