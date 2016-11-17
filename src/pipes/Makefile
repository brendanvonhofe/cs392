TARGET = pipes
SRC = pipes.c
OBJ = $(SRC:.c=.o)
CFLAGS += -I../../include -g -std=c99 -Wall -Werror -pedantic
LDFLAGS += -L../../lib
LDLIBS += -lmy

all:$(TARGET)

$(TARGET): $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f pipes

re: fclean all
