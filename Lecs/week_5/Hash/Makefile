CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=testHash.o hash.o

all : testHash

testHash : $(OBJS)

testHash.o : testHash.c hash.h

hash.o : hash.c hash.h

clean:
	rm -f hash.o testHash
