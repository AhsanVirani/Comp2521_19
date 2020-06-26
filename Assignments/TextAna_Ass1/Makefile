
CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=testDict.o

all : testDict

testDict : testDict.o Dict.o stemmer.o
	$(CC) -o testDict testDict.o Dict.o stemmer.o

testDict.o : dictionary.c Dict.h WFreq.h 
	$(CC) $(CFLAGS) -c testDict.c

Dict.o : dictionary.c Dict.h WFreq.h stemmer.h
	$(CC) $(CFLAGS) -c dictionary.c

stemmer.o : stemmer.c stemmer.h
	$(CC) $(CFLAGS) -c stemmer.c

clean :
	rm -f testDict
