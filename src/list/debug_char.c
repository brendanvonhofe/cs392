#include "my.h"
#include "list.h"

void debug_char(struct s_node* head) {
    if(head == NULL) {
        my_str("NULL");
        return;
    }

    while(head->next != NULL) {
        my_char('(');
        print_char(head->prev);
        my_str(" <- ");
        print_char(head);
        my_str(" -> ");
        print_char(head->next);
        my_str(") ");

        head = head->next;
    }

    my_char('(');
    print_char(head->prev);
    my_str(" <- ");
    print_char(head);
    my_str(" -> ");
    print_char(head->next);
    my_str(") ");
}
