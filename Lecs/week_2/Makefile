# Makefile for Tree ADT

CC = gcc
CFLAGS = -g -Wall -Werror

tree_output : tree_partition.o
	$(CC) -o tree_output tree_partition.o

tree_partiton.o : tree_partition.c tree_partition.h
	$(CC) $(CFLAGS) -c tree_partition.c

clean : rm -f *.o tree_output
