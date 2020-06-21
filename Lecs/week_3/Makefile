CC = gcc
CFLAGS = -g -Wall -Werror

all : black

black : black.o tree.o splay_tree.o avl_tree.o
	$(CC) -o black black.o tree.o splay_tree.o avl_tree.o
 
black.o : black.c avl_tree.h
	$(CC) $(CFLAGS) -c black.c

tree.o : tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

splay_tree.o : splay_tree.c tree.h splay_tree.h
	$(CC)	$(CFLAGS) -c splay_tree.c


AvlTree.o : avl_tree.c splay_tree.h avl_tree.h
	$(CC) $(CFLAGS) -c avl_tree.c

clean :
	rm -f *.o black 
