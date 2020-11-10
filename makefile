
CC = g++
CFLAGS = -g -Wall -Weffc++ -std=c++11
LFLAGS = -L/usr/lib

all: run

run: bin/main.o bin/Graph.o
	@echo 'Building target: run'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/run bin/main.o $(LFLAGS)
	@echo 'Finished building target: run'
	@echo ' '

bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

bin/Graph.o: include/Graph.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Graph.o include/Graph.cpp

clean:
	rm -f bin/*


