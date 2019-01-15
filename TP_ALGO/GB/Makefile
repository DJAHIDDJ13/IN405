main: main.o graph_bib.o
	gcc -o main main.o main.c

main.o: main.c graph_bib.h
	gcc -c main.c
	
graph_bib.o: graph_bib.c graph_bib.h
	gcc -c graph_bib.c
	
