#include "ipcTools.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NBR_FUM 3

#define TABAC 1
#define PAPIER 2
#define ALLUM 4

void die(char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void fumeur(int id) {
	int stock = 0 | ((id+1)*(id+1));
	printf("%d\n", stock);
	printf("%d %d %d\n", stock & TABAC, stock & PAPIER, stock & ALLUM);
}

int main(int argc, char** argv) {
	int table = 0;
	pid_t fum[NBR_FUM];
	for(int i=0; i<NBR_FUM; i++) {
		if((fum[i] = fork()) < 0 ) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if(fum[i] == 0) {
			// fumeurs
			fumeur(i);
			exit(EXIT_SUCCESS);
		}
	}
	// rep
	return EXIT_SUCCESS;
}
