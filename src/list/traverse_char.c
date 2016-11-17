#include "my.h"
#include "list.h"

void traverse_char(struct s_node* head) {
    if(head == NULL) {
        my_str("NULL");
        return;
    }


    while(head->next != NULL) {
        print_char(head);
        my_char(' ');
        head = head->next;
    }

    print_char(head);
}
