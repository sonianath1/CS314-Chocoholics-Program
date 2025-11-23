CC=g++
FLAGS=-std=c++17 -g -Wall
SOURCES=main.cpp database.cpp entities.cpp
OBJS=main.o database.o entities.cpp
DEPS=database.h entities.h error.h node.h

all:
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

chocanprogram: $(OBJS)
	$(CC) -o $@ $^ $(FLAGS)

clean cls:
	rm -f chocanprogram *.o *.~ \#*

