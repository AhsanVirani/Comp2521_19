CC=gcc
CFLAGS=-Wall -Werror -g
LDFLAGS=

number_seq : number_seq.o
	gcc -o number_seq number_seq.o

number_seq.o : number_seq.c
	gcc -c number_seq.o number_seq.c

clean	:
	rm number_seq.o

vclean:
	rm number_seq number_seq.o
