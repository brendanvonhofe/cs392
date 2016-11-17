#include "my.h"
#include "list.h"

void* remove_node(struct s_node** node) {
    if(node == NULL || *node == NULL) {
        my_str("Non-null arguments only. \n");
        return NULL;
    }

    void* ret = (*node)->elem;
    struct s_node* ptr = *node;

    if(ptr->prev != NULL && ptr->next != NULL) {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
    }
    else if(ptr->prev != NULL) {
        ptr->prev->next = NULL;
        *node = NULL;
    }
    else if(ptr->next != NULL) {
        ptr->next->prev = NULL;
        *node = ptr->next;
    }
    else {
        *node = NULL;
    }

    free(ptr);
    return ret;
}
