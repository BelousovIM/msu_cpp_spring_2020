CC=g++

all: test

test: main.o matrix.o
	$(CC) main.o matrix.o -o test

main.o: main.cxx functions.h
	$(CC) -c main.cxx 

matrix.o: matrix.cxx functions.h
	$(CC) -c matrix.cxx

clean:
	rm -rf *.o test
