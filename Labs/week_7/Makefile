# COMP2521 20T2 ... lab07

CC	= gcc
CFLAGS  = -Wall -Werror -g

.PHONY: all
all: travel

travel:		travel.o Graph.o Queue.o
travel.o:	travel.c Graph.h
Graph.o:	Graph.c Graph.h Queue.h
Queue.o:	Queue.c Queue.h Item.h

.PHONY: clean
clean:
	-rm -f travel travel.o Graph.o Queue.o

.PHONY: give
give: Graph.c
	give cs2521 lab07 $^
