
CC = g++ -g -c
LC = g++ -g

all: bump reduce

bump: bump_main.o Poset.o Node.o
	$(LC) -o $@ $^

%.o: %.cpp
	$(CC) -o $@ $<

Poset.o: Poset.hpp

Node.o: Node.hpp Poset.hpp

clean:
	rm -rf *.o bump
