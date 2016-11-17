#include "my.h"
#include "list.h"

void add_elem(void* elem, struct s_node** head) {
    if(head == NULL || elem == NULL || *head == NULL) {
        my_str("Non-null arguments only. \n");
        return;
    }

    struct s_node *node = new_node(elem, *head, NULL);
    (*head)->prev = node;
    *head = node;
}
