# COMP2521 20T2 Assignment 1

CC=gcc
CFLAGS=-DWall -Dwerror -g

testDict : testDict.o Dict.o stemmer.o
	$(CC) -o testDict testDict.o Dict.o stemmer.o

Dict.o : Dict.c Dict.h WFreq.h
	$(CC) $(CFLAGS) -c Dict.c

stemmer.o : stemmer.c stemmer.h
	$(CC) $(CFLAGS) -c stemmer.c

clean :
	rm -f testDict
