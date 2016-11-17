#include "my.h"
#include "list.h"

void traverse_string(struct s_node* head) {
    if(head == NULL) {
        my_str("NULL");
        return;
    }


    while(head->next != NULL) {
        print_string(head);
        my_char(' ');
        head = head->next;
    }

    print_string(head);
}
