CC = gcc
CFLAGS = -Wall -Wextra

all: clean

clean: clean.c
	$(CC) $(CFLAGS) -o clean clean.c

clean_exec: clean
	./clean
