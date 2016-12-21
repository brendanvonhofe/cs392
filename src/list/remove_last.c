#include "my.h"
#include "list.h"

void* remove_last(struct s_node** node) {
    if(node == NULL || *node == NULL) {
        my_str("Non-null arguments only. \n");
        return NULL;
    }

    struct s_node* ptr = *node;

    while(ptr->next != NULL) {
        ptr = ptr->next;
    }

    if(ptr->prev != NULL) {
        ptr->prev->next = NULL;
    }
    else {
        *node = NULL;
        node = NULL;
    }

    void* ret = ptr->elem;

    free(ptr);
    return ret;
}
