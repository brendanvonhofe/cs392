#include "my.h"
#include "list.h"

void* elem_at(struct s_node* head, int n) {
    return node_at(head, n)->elem;
}
