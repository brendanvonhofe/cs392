#include "my.h"
#include "list.h"

void print_string(struct s_node* node) {
    if(node == NULL) {
        my_str("NULL");
        return;
    }

    my_str((char*)node->elem);
}
