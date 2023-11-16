all: run-dll

run-dll: DLList.o DLList-main.o
	c++ -g -std=c++14 DLList.o DLList-main.o -o run-dll

DLList.o: DLList.cpp DLList.h
	c++ -g -std=c++14 -c DLList.cpp

DLList-main.o: 

clean:
	rm *.o run-dll
