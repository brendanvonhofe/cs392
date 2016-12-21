#include "my.h"
#include "list.h"

void* elem_at(struct s_node* head, int n) {
    if(head == NULL) {
        my_str("Non-null arguments only. \n");
        return NULL;
    }
    return node_at(head, n)->elem;
}
