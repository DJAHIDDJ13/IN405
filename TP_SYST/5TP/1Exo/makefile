main: ipcTools.o main.o
	gcc -o main main.o ipcTools.o  -Wall -g

ipcTools.o: ipcTools.c ipcTools.h
	gcc -c ipcTools.c -Wall -g

main.o: main.c ipcTools.h
	gcc -c main.c -Wall -g
