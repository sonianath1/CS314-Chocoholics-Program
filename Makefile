CC=g++
FLAGS=-std=c++17 -g -Wall
SOURCES=main.cpp database.cpp entities.cpp 
TESTSOURCES=test_main.cpp database.cpp entities.cpp database_test.cpp entities_test.cpp  
OBJS=main.o database.o entities.o 
TESTOBJS=test_main.o database.o entities.o database_test.o entities_test.o
DEPS=database.h entities.h error.h node.h

all: chocanprogram chocanprogramtest

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

chocanprogram: $(OBJS)
	$(CC) -o $@ $^ $(FLAGS)

chocanprogramtest: $(TESTOBJS)
	$(CC) -o $@ $^ $(FLAGS)

clean cls:
	rm -f chocanprogram chocanprogramtest *.o *.~ \#*

