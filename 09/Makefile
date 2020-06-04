CC=g++

all: test

test: main.o sort.o
	$(CC) main.o sort.o -o test -std=c++14 -pthread

main.o: main.cxx sort.h
	$(CC) -c main.cxx -std=c++14

sort.o: sort.cxx sort.h
	$(CC) -c sort.cxx -std=c++14

clean:
	rm -rf *.o test

