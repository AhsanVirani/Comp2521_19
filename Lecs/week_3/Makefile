CC = gcc
CFLAGS = -g -Wall -Werror 

splayTree : splay_tree.o
	$(CC) -o splayTree splay_tree.o

tree : tree.o
	$(CC) -o tree tree.o

splay_tree.o : splay_tree.c tree.h
	$(CC)	$(CFLAGS) -c splay_tree.c

tree.o : tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

clean :
	rm -f*.o splay_tree tree  
