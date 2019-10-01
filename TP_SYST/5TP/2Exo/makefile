fumeurs: ipcTools.o fumeurs.o
	gcc -o fumeurs fumeurs.o ipcTools.o  -Wall -g

ipcTools.o: ipcTools.c ipcTools.h
	gcc -c ipcTools.c -Wall -g

fumeurs.o: fumeurs.c ipcTools.h
	gcc -c fumeurs.c -Wall -g
