CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=testHeap.o heaps.o

all : testHeap

testHeap : $(OBJS)

testHeap.o : testHeap.c heaps.h

heaps.o : heaps.c heaps.h

clean:
	rm -f heaps.o testHeap
