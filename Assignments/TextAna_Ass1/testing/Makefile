# COMP2521 20T2 Assignment 1

CC=gcc
CFLAGS=-Wall -g
OBJS=testDict.o Dict.o stemmer.o Queue.o

all : testDict

testDict : $(OBJS)

stem : stem.o stemmer.o

testDict.o : testDict.c Dict.h WFreq.h stemmer.h 

Dict.o : Dict.c Dict.h WFreq.h Queue.h

stemmer.o : stemmer.c

stem.o : stem.c stemmer.h

Queue.o : Queue.c Queue.h

clean :
	rm -f tw stem $(OBJS) stem.o core
