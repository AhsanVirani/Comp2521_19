# COMP2521 20T2 Assignment 1

CC=gcc
CFLAGS=-Wall -werror -g
OBJS=tw.o Dict.o stemmer.o

all : tw stem

tw : $(OBJS)

stem : stem.o stemmer.o

tw.o : tw.c Dict.h WFreq.h stemmer.h 

Dict.o : Dict.c Dict.h WFreq.h

stemmer.o : stemmer.c

stem.o : stem.c stemmer.h

clean :
	rm -f tw stem $(OBJS) stem.o core
