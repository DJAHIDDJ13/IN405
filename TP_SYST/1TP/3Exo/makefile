
main: main.o nFork.o
	gcc -o main main.o nFork.o

main.o: main.c nFork.h
	gcc -c main.c

nFork.o: nFork.c nFork.h
	gcc -c nFork.c

.PHONY: clean

clean:
	rm -f *.o main
