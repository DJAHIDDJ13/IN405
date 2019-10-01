#include "ipcTools.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void die(char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	// gen key
	key_t key;
	if((key = ftok("main.c", 'Q')) == -1)
		die("ftok");
		
	// get semaphore
	int semid;
	if((semid = semalloc(key, 0)) < 0)
		die("semalloc");
	
	int* shmem = (int*) shmalloc(key, sizeof(int));
	printf("shmem initialized to 0\n");
	*shmem = 0;
	// fork child process
	pid_t pid;
	if((pid = fork()) < 0)
		die("fork");
		
	if(pid == 0) { // child
		sleep(1);
		printf("child changing shmem to 1\n");
		*shmem = 1;
		// deblocage de semaphore
		printf("child deblocking\n");
		V(semid);
		
		// exit
		exit(EXIT_SUCCESS);
	}
	// parent
	// blockage de semaphore
	printf("Parent blocking\n");
	P(semid);
	
	// show and exit
	printf("shmem = %d\n", *shmem);
	
	// free
	semfree(semid);
	shmfree(key);
	
	return EXIT_SUCCESS;
}
