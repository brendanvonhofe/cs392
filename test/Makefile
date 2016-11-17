CFLAGS = -g -Wall -Werror -pedantic -std=c99 -I ../include
LDLIBS = -L../lib -llist -lmy

check: testmalloc
		./testmalloc

clean:
		rm -f ./testmalloc
