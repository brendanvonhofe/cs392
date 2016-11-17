#include "my.h"
#include "list.h"

void add_node_at(struct s_node *node, struct s_node **head, int n) {
    if(node == NULL || head == NULL || node->elem == NULL || *head == NULL) {
        my_str("Non-null arguments only. \n");
        return;
    }
    if(node->prev != NULL || node->next != NULL) {
        my_str("Looks like your trying to add a node that already exists in the list");
        return;
    }
    if(n < 0) n = 0;

    struct s_node* ptr = *head;
    int i = 0;
    while(ptr->next != NULL && i < n - 1) {
        ptr = ptr->next;
        i++;
    }

    if(n == 0) {
        node->next = ptr;
        ptr->prev = node;
        *head = node;
    }
    else if(ptr->next == NULL) {
        node->next = ptr->next;
        node->prev = ptr;
        ptr->next = node;
    }
    else {
        node->next = ptr->next;
        node->prev = ptr;
        ptr->next->prev = node;
        ptr->next = node;
    }
}
