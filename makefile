
CC = g++
CFLAGS = -g -Wall -Weffc++ -std=c++11
LFLAGS = -L/usr/lib

all: run

run: bin/main.o bin/Graph.o bin/Session.o bin/Agent.o bin/Tree.o
	@echo 'Building target: run'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/run bin/main.o bin/Graph.o bin/Session.o bin/Agent.o bin/Tree.o $(LFLAGS)
	@echo 'Finished building target: run'
	@echo ' '

bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

bin/Graph.o: src/Graph.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Graph.o src/Graph.cpp

bin/Graph.o: src/Session.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Session.o src/Session.cpp

bin/Graph.o: src/Agent.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Agent.o src/Agent.cpp

bin/Graph.o: src/Tree.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Tree.o src/Tree.cpp

clean:
	rm -f bin/*


