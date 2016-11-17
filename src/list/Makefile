SRC = new_node.c add_node.c add_elem.c append.c add_note_at.c remove_node.c \
remove_last.c remove_node_at.c count_s_nodes.c empty_list.c node_at.c \
elem_at.c print_int.c print_char.c print_string.c traverse_int.c \
traverse_char.c traverse_string.c debug_int.c debug_char.c debug_string.c
OBJ = $(SRC:.c=.o)
CFLAGS += -I../../include -g -std=c99 -Wall -Werror -pedantic

all: $(OBJ)
		ar -rc ../../lib/liblist.a $^
		ranlib ../../lib/liblist.a

clean:
		rm -f $(OBJ)
		rm -f ../../lib/liblist.a

fclean:
		make clean
		rm -f ../../test/testlist
re:
		make fclean
		make all
