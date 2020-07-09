CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=test.o graph.o Queue.o Stack.o

all : test

test : $(OBJS)

test.o : test.c graph.h

graph.o : graph.c graph.h Queue.h Stack.h

Queue.o : Queue.c Queue.h Item.h

Stack.o : Stack.c Stack.h Item.h

clean:
	rm -f graph
