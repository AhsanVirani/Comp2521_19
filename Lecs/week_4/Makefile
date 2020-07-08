CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=test.o graph.o

all : test

test : $(OBJS)

test.o : test.c graph.h

graph.o : graph.c graph.h

clean:
	rm -f graph
