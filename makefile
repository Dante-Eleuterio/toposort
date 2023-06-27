CC = g++
LDLIBS = -lcgraph  -lgvc -lcdt

toposort: main.o
	$(CC) -o toposort main.o $(LDLIBS)

main.o : main.cpp graphs.h
	$(CC) -c main.cpp

clean:
	rm -rf *.o *.a toposort

purge: clean
	rm -rf toposort
