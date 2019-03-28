#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "ipcTools.h"

int semalloc(key_t key, int valInit) {
	int semid = semget(key, 0, 0);
	if(semid == -1) {
		semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
	}
		//~ union semun semopts;
	//~ semopts.val = valInit;
	
	//~ if(semctl(semid, 0, SETVAL, semopts, 0) < 0) {
		//~ printf("%s\n")
		//~ return -1;
	//~ }
	return semid;
}

void P(int semid) {
	struct sembuf p = {0, -1, SEM_UNDO};
	if(semop(semid, &p, 1) < 0) {
		perror("semop");
		exit(EXIT_FAILURE);
	}
}

void V(int semid) {
	struct sembuf v = {0, +1, SEM_UNDO};
	if(semop(semid, &v, 1) < 0) {
		perror("semop");
		exit(EXIT_FAILURE);
	}	
}

int semfree(int semid) {
	return semctl(semid, 0, IPC_RMID, 0);
}

void *shmalloc(key_t key, int size) {
	int shmid = shmget(key, size, IPC_CREAT | 0666);
	if(shmid < 0) {
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	
	void *shmptr = shmat(shmid, NULL, 0);
	if(shmptr < 0) {
		perror("shmat");
		exit(EXIT_FAILURE);
	}
	return shmptr;
}

int shmfree(key_t key) {
	int shmid = shmget(key, 0, 0);
	if(shmid < 0) {
		return -1;
	}
	return shmctl(shmid, IPC_RMID, NULL);
}
