CC=g++

all: test

test: main.o
	$(CC) -o test main.o --std=c++17 -pthread

main.o: main.cxx functions.h
	$(CC) -c main.cxx --std=c++17

clean:
	rm -rf *.o test
