TARGET = lab6
CFLAGS += -I../../../include -g -std=c99 -Wall -Werror -pedantic
LDFLAGS += -L../../../lib -pthread
LDLIBS += -llist -lmy

all: $(TARGET)

clean:
	$(RM) $(TARGET)

fclean: clean

re: fclean all
