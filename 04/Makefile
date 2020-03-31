CC=g++

all: test

test: main.o
	$(CC) main.o -o test

main.o: main.cxx functions.h
	$(CC) -c main.cxx 

clean:
	rm -rf *.o test
