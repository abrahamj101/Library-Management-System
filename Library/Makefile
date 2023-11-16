all: run-lib

run-lib: Library-main.o Library.o Record.o
	c++ -g -std=c++11 Library-main.o Library.o Record.o -o run-lib

Library.o: Library.cpp Library.h Record.h TemplatedDLList.h
	c++ -g -std=c++11 -c Library.cpp

Library-main.o: Library-main.cpp Library.h Record.h
	c++ -g -std=c++11 -c Library-main.cpp

Record.o: Record.cpp Record.h
	c++ -g -std=c++11 -c Record.cpp

DLList.o: DLList.cpp DLList.h
	c++ -g -std=c++11 -c DLList.cpp

DLList-main.o: DLList-main.cpp DLList.h
	c++ -g -std=c++11 -c DLList-main.cpp

clean:
	rm *.o run-lib
