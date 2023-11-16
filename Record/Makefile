all: record

record: Record.o main.o
	c++ -g -std=c++11 Record.o main.o -o record

Record.o: Record.cpp Record.h
	c++ -g -std=c++11 -c Record.cpp

main.o: main.cpp Record.h
	c++ -std=c++11 -c main.cpp

clean:
	rm *.o record
