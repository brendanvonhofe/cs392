#include "my.h"
#include "list.h"

void* remove_node_at(struct s_node** head, int n) {
    if(head == NULL || *head == NULL) {
        my_str("Non-null arguments only. \n");
        return NULL;
    }
    if(n < 0) n = 0;

    struct s_node* ptr = *head;
    int i = 0;

    while(ptr->next != NULL && i < n) {
        ptr = ptr->next;
        i++;
    }

    void* ret = ptr->elem;

    if(ptr->next == NULL && ptr->prev == NULL) {
        *head = NULL;
        head = NULL;
    }
    else if(ptr->next == NULL) {
        ptr->prev->next = NULL;
    }
    else if(n == 0) {
        ptr->next->prev = NULL;
        *head = ptr->next;
    }
    else {
        ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
    }

    free(ptr);
    return ret;
}
