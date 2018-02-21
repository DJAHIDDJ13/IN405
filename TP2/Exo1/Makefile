main: se_fichier.o main.o
	gcc -g -Wall main.o se_fichier.o -o main
	
se_fichier.o: se_fichier.c se_fichier.h
	gcc -g -Wall -c se_fichier.c
	
main.o: main.c
	gcc -g -Wall -c main.c 

clean:
	rm -f *.o main

editeur: 
	geany *.c *.h &
