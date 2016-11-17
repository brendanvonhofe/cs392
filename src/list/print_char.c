#include "my.h"
#include "list.h"

void print_char(struct s_node* node) {
    if(node == NULL) {
        my_str("NULL");
        return;
    }

    my_char(*(char*)node->elem);
}
