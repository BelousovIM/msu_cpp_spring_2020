CC=g++

all: test

test: main.o BigInt.o
	$(CC) main.o BigInt.o -o test

main.o: main.cxx functions.h
	$(CC) -c main.cxx 

BigInt.o: BigInt.cxx functions.h
	$(CC) -c BigInt.cxx

clean:
	rm -rf *.o test
