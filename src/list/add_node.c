#include "my.h"
#include "list.h"

void add_node(struct s_node* node, struct s_node** head) {
    if(node == NULL || node->elem == NULL || head == NULL || *head == NULL) {
        my_str("Non-null arguments only. \n");
        return;
    }
    if(node->prev != NULL || node->next != NULL) {
        my_str("Looks like your trying to add a node that already exists in the list");
        return;
    }


    (*head)->prev = node;
    node->next = *head;
    *head = node;
}
