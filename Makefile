CC = gcc
AR = ar
OBJECTS_MAIN = graph.o
FLAGS = -Wall -g

all: graph

graph: $(OBJECTS_MAIN)
	$(CC) $(flags)  -o graph $(OBJECTS_MAIN)

graph.o: graph.c
	$(CC) $(flags)  -c graph.c

run:
	./graph -> out.txt

run_memory_leak:
	valgrind ./graph -> out.txt

.PHONY: clean all

clean:
	rm -f *.o *.a *.so graph
