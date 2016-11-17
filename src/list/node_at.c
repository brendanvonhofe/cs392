#include "my.h"
#include "list.h"

struct s_node* node_at(struct s_node* head, int n) {
    if(head == NULL) {
        my_str("Non-null arguments only. \n");
        return NULL;
    }
    if(n < 0) n = 0;

    struct s_node* ptr = head;

    while(n > 0 && ptr->next != NULL) {
        ptr = ptr->next;
        n--;
    }

    return ptr;
}
