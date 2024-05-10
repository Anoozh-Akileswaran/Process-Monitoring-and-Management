# To run, enter: make all

all: APIComplete

APIComplete: main.o dining.o philosopher.o
	gcc -o diningphilosophers main.o dining.o philosopher.o -lpthread

main.o: main.c dp.h
	gcc -lpthread -c main.c -lpthread

dining.o: dining.c dp.h
	gcc -lpthread -c dining.c -lpthread

philosopher.o: philosopher.c dp.h
	gcc -lpthread -c philosopher.c -lpthread
