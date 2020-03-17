CC=g++

all: test

test: main.o parser.o
	$(CC) main.o parser.o -o test

main.o: main.cxx functions.h
	$(CC) -c main.cxx 

parser.o: parser.cxx functions.h
	$(CC) -c parser.cxx

clean:
	rm -rf *.o test
