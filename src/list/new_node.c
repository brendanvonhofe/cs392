#include "my.h"
#include "list.h"

struct s_node* new_node(void* elem, struct s_node* next, struct s_node* previous) {
    struct s_node *node = malloc(sizeof(struct s_node));
    node->elem = elem;
    node->prev = previous;
    node->next = next;
    return node;
}
