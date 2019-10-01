#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "nFork.h"

int main(int argc, char** argv) {
	// lecture argument
	int n = 0;
	if(argc < 2) {
		printf("No arguments supplied!\n");
	} else {
		n = atoi(argv[1]);
	}
	while(n < 1) {
		printf("Invalid argument enter new one: ");
		scanf("%d", &n);
	}
	// nFork
	int id = nFork(n);
	if(id != 0) {
		printf("[%d] my parent is %d\n", id, getppid());
		exit(0);
	}
	// wait for children
	while(wait(NULL) > 0);
	return 0;
}
