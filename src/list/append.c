#include "my.h"
#include "list.h"

void append(struct s_node* node, struct s_node** head) {
    if(node == NULL || node->elem == NULL) {
        my_str("Non-null arguments only. PLEASEEE");
        return;
    }
    if(node->prev != NULL || node->next != NULL) {
        my_str("Looks like your trying to add a node that already exists in the list");
        return;
    }
    if(*head == NULL || head == NULL) {
        *head = node;
        return;
    }

    struct s_node* ptr = *head;
    while(ptr->next != NULL) {
        ptr = ptr->next;
    }

    ptr->next = node;
    node->prev = ptr;
}
