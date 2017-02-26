CC=gcc
CFLAGS=-lncurses

all:
	$(CC) -o terminal-clock terminal-clock.c $(CFLAGS)
