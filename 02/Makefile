CC=g++

all: test

test: main.o parser.o
	$(CC) main.o parser.o -o test

main.o: main.cxx 
	$(CC) -c main.cxx 

parser.o: parser.cxx
	$(CC) -c parser.cxx

clean:
	rm -rf *.o test
