SRC = my_char.c my_int.c my_str.c my_strlen.c my_num_base.c my_alpha.c \
my_digits.c my_strindex.c my_strrindex.c my_revstr.c my_strfind.c \
my_strrfind.c my_strcmp.c my_strncmp.c my_strcpy.c my_strncpy.c my_strcat.c \
my_strdup.c my_strconcat.c my_strnconcat.c my_atoi.c my_vect2str.c \
my_str2vect.c my_panic.c
OBJ = $(SRC:.c=.o)
CFLAGS += -I../../include -g -std=c99 -Wall -Werror -pedantic

all: $(OBJ)
		ar -rc ../../lib/libmy.a $^
		ranlib ../../lib/libmy.a

clean:
		rm -f $(OBJ)
		rm -f ../../lib/libmy.a

fclean:
		make clean
		rm -f ../../test/testmy

re:
		make fclean
		make all
