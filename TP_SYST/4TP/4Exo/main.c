#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define NBPAQUETS 10 // nbr des paquets
#define TEMPS_MAX_FAB 5 // en secondes
#define TEMPS_MAX_CHG 10 // en secondes

pid_t empq, chrg; // les pids de empaqueteur et chargeur

// empaqueteur
void fabrique_paquet(int id) {
	int alea = random() % TEMPS_MAX_FAB + 1;
	sleep(alea);
	printf("[%d]paquet: %ds\n", id, alea);
}
void empaqueteur(int out) {
	srand(getpid());

	//~ pid_t parent = getppid();
	for(int i=0; i<NBPAQUETS; i++) {
		fabrique_paquet(i+1);
		write(out, "READY", 6);
	}
	write(out, "FIN", 4);
	puts("FIN EMPQ");
}

// chargeur
void charger_paquet(int id) {
	int alea = random() % TEMPS_MAX_CHG + 1;
	sleep(alea);
	printf("[%d]charge: %ds\n", id, alea);
}


void chargeur(int in) {
	srand(getpid());

	int charge = 0;
	int ordre = 1;
	int fin = 0;
	
	char buf[7] = {0};
	while(!fin || charge) {
		read(in, buf, 6);
		if(strcmp(buf, "READY") == 0) {
			charge ++;
		} else {
			fin = 1;
		}
		if(charge > 0) {
			charger_paquet(ordre);
			charge --;
			ordre ++;
		}
	}
	puts("FIN CHRG");
}



int main(int argc, char* argv[]) {

	int fd[2];
	if(pipe(fd) < 0) {
		perror("pipe error!\n");
		exit(EXIT_FAILURE);
	}
	
	// creer l'empaqueteur
	empq = fork();
	if(empq < 0) {
		perror("fork err!\n");
		exit(EXIT_FAILURE);
	} else if(empq == 0) {
		empaqueteur(fd[1]);
		exit(EXIT_SUCCESS);
	}
	
	// creer le chargeur
	chrg = fork();
	if(chrg < 0) {
		perror("fork err!\n");
		exit(EXIT_FAILURE);
	} else if(chrg == 0) {
		chargeur(fd[0]);
		exit(EXIT_SUCCESS);
	}
	
	// attendre les fils
	while(wait(NULL) > 0);
	
	puts("FIN");
	return EXIT_SUCCESS;
}
