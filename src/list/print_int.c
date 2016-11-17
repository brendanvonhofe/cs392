#include "my.h"
#include "list.h"

void print_int(struct s_node* node) {
    if(node == NULL) {
        my_str("NULL");
        return;
    }

    my_int(*(int*)node->elem);
}
