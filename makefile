
CC=c99
CFLAGS=-c -Wall

all: clean main
	./main

main: main.o sparse_graph.o dense_graph.o
	$(CC) -o main ./obj/*

main.o:
	$(CC) $(CFLAGS) main.c -o ./obj/main.o

sparse_graph.o:
	$(CC) $(CFLAGS) sparse_graph.c -o ./obj/sparse_graph.o

dense_graph.o:
	$(CC) $(CFLAGS) dense_graph.c -o ./obj/dense_graph.o


clean:
	rm -rf *.o main
	rm -rf ./obj/*
