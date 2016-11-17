#include "my.h"
#include "list.h"

int count_s_nodes(struct s_node* head) {
    if(head == NULL) return 0;
    
    struct s_node *ptr = head;
    int count = 1;

    while(ptr->next != NULL) {
        ptr = ptr->next;
        count++;
    }

    return count;
}
