CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=graph_list.o List.o

all : graph_list

graph_list : $(OBJS)

graph_list.o : graph_list.c graph_list.h List.h

List.o : List.c List.h Item.h

clean:
	rm -f graph_list
