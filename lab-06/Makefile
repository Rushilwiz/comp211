CC=gcc
CFLAGS=-c -Wall -Werror -g

all: main

main: task.o schedule.o main.o
	$(CC) task.o schedule.o main.o -o main -lm

task.o: task.c
	$(CC) $(CFLAGS) task.c
	
schedule.o: schedule.c
	$(CC) $(CFLAGS) schedule.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

run: main
	./main

clean:
	/bin/rm -f main *.o 
