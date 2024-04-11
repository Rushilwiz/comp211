CC=gcc
CFLAGS=-c -Wall -g #-std=c11

all: main

main: memory.o cache.o bit_utils.o main.o
	$(CC) memory.o cache.o bit_utils.o main.o -o main -lm

memory.o: memory.c
	$(CC) $(CFLAGS) memory.c

cache.o: cache.c
	$(CC) $(CFLAGS) cache.c
	
bit_utils.o: bit_utils.c
	$(CC) $(CFLAGS) bit_utils.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	/bin/rm -f main *.o *.gz

run: main memory.txt
	./main memory.txt
