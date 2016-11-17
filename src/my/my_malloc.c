#define _BSD_SOURCE
#include <unistd.h>
#include <stdio.h>
#include "my.h"
#include "list.h"


struct s_node *node = NULL;
struct s_node **head = &node;


void *my_malloc(int size) {
    intptr_t new_size = (intptr_t)size;

    void *ret;
    if(*((int *)(ret = sbrk(new_size))) == -1) {
        perror("sbrk");
    }

    //append(new_node(ret, NULL, NULL), head);
        //debug_string(*head);

    return ret;
}

//incompleTE!
void free(void *ptr) {
    if(*head == NULL) {
        my_str("Error, no memory has been allocated by my_malloc yet.");
    }
    struct s_node *cursor = *head;

    while(cursor->next != NULL) {
        if(cursor->elem == ptr) {
        }
    }
}
