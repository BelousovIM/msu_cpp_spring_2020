CC=g++

all: test

test: main.o alloc.o
	$(CC) main.o alloc.o -o test

main.o: main.cxx
	$(CC) -c main.cxx

alloc.o: alloc.cxx
	$(CC) -c alloc.cxx

clean:
	rm -rf *.o test
