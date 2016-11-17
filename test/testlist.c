#include "../include/list.h"
#include "../include/my.h"

#define TEST(code) { \
    my_str(#code); \
    my_str(": "); \
    code; }

//~~~~~~~~~~~~~TEST ADDING A NODE THAT ALREADY EXISTS
// IF THERES A DOUBLE POINTER THERES A REASON

int main() {
    my_str("~~~~~~~~~~TESTING~~~~~~~~~~~");
    my_char('\n');


    struct s_node *first= new_node("first", NULL, NULL);
    struct s_node *second = new_node("second", NULL, NULL);
    struct s_node *third = new_node("third", NULL, NULL);
    struct s_node *fourth = new_node("fourth", NULL, NULL);
    struct s_node *fifth = new_node("fifth", NULL, NULL);
    struct s_node *sixth = new_node("sixth", NULL, NULL);
    struct s_node *shitbird= new_node("shitbird", NULL, NULL);
    struct s_node *shitstorm = new_node("shitstorm", NULL, NULL);
//    struct s_node *shithead = new_node("shithead", NULL, NULL);
    struct s_node *head = third;

    debug_string(head);
    my_char('\n');
    TEST(add_node(first, &head));
    my_char('\n');
    debug_string(head);
    my_char('\n');
    TEST(add_node_at(second, &head, 1));
    my_char('\n');
    debug_string(head);
    my_char('\n');
    TEST(append(fourth, &head));
    my_char('\n');
    debug_string(head);
    my_char('\n');
    TEST(add_node_at(fifth, &head, 10));
    my_char('\n');
    debug_string(head);
    my_char('\n');
    TEST(add_node_at(sixth, &head, 5));
    my_char('\n');
    debug_string(head);
    my_char('\n');
    TEST(add_node_at(shitstorm, &head, -5));
    my_char('\n');
    debug_string(head);
    my_char('\n');

    TEST(add_node(NULL, NULL));
    my_char('\n');
    TEST(add_node(shitbird, NULL));
    my_char('\n');
    TEST(add_node(NULL, &head));
    my_char('\n');
    TEST(add_node_at(NULL, NULL, 4));
    my_char('\n');
    TEST(add_node_at(shitbird, NULL, 2));
    my_char('\n');
    TEST(add_node_at(NULL, &head, 2));
    my_char('\n');

    TEST(remove_node(&third));
    my_char('\n');
    debug_string(head);
    my_char('\n');
    TEST(remove_node(&shitstorm));
    my_char('\n');
    debug_string(head);
    my_char('\n');
    TEST(remove_last(&head));
    my_char('\n');
    debug_string(head);
    my_char('\n');
    TEST(remove_node_at(&head, 2));
    my_char('\n');
    debug_string(head);
    my_char('\n');




/*
    TEST(my_int(count_s_nodes(head)));
    my_char('\n');
    TEST(my_str(node_at(head, 0)->elem));
    my_char('\n');
    TEST(my_str(elem_at(head, 0)));
    my_char('\n');
    TEST(print_int(node_at(head, 0)));
    my_char('\n');
    TEST(print_char(node_at(head, 0)));
    my_char('\n');
    TEST(print_string(node_at(head, 0)));
    my_char('\n');
    TEST(traverse_int(head));
    my_char('\n');
    TEST(traverse_char(head));
    my_char('\n');
    TEST(traverse_string(head));
    my_char('\n');
    TEST(debug_int(head));
    my_char('\n');
    TEST(debug_char(head));
    my_char('\n');
    TEST(debug_string(head));
    my_char('\n');
    */
    TEST(empty_list(&head));
}
