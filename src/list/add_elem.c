#include "my.h"
#include "list.h"

void add_elem(void* elem, struct s_node** head) {
    if(head == NULL || elem == NULL) {
        my_str("Non-null arguments only. \n");
        return;
    }
    if(*head == NULL) {
        struct s_node *node = new_node(elem, *head, NULL);
        *head = node;
    }
    else {
        struct s_node *node = new_node(elem, *head, NULL);
        (*head)->prev = node;
        *head = node;
    }
}
