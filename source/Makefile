# Makefile for searches

# Compiler:
CC=gcc

#  compiler options
CFLAGS=-c -Wextra

all: stockMarket

stockMarket: stock.o main.o linkedlist.o
	$(CC) stock.c main.c linkedlist.c -o stockMarket

main: main.o
	$(CC) $(CFLAGS) main.c

stock: stock.o
	$(CC) $(CFLAGS) stock.c
	
list: linkedlist.o
	$(CC) $(CFLAGS) linkedlist.c

clean:
	rm -rf *.o

