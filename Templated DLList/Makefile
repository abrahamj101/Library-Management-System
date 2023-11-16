all: run-tdll

run-tdll: TDLList-main.o 
	c++ -std=c++14 TDLList-main.o -o run-tdll

TDLList-main.o: TDLList-main.cpp TemplatedDLList.h
	c++ -std=c++14 -c TDLList-main.cpp

clean:
	rm *.o run-tdll
