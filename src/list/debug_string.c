#include "my.h"
#include "list.h"

void debug_string(struct s_node* head) {
    if(head == NULL) {
        my_str("NULL");
        return;
    }

    while(head->next != NULL) {
        my_char('(');
        print_string(head->prev);
        my_str(" <- ");
        print_string(head);
        my_str(" -> ");
        print_string(head->next);
        my_str(") ");

        head = head->next;
    }

    my_char('(');
    print_string(head->prev);
    my_str(" <- ");
    print_string(head);
    my_str(" -> ");
    print_string(head->next);
    my_str(") ");
}
