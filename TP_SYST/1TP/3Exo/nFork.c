// TD1.3 Arborescence de processus
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int nFork(int nbProcs) {
	for(int i=1; i<=nbProcs; i++) {
		int pid = 0;
		if((pid = fork()) < 0) {
			perror("Fork error");
			exit(-1);
		}
		if(pid == 0) { // fils
			return i;
		}
	}
	return 0;
}

