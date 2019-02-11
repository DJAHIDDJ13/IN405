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
int fin = 0; // booleen de fin
int charge = 0; // nbr des paquets a charger 

// empaqueteur
void fabrique_paquet(int id) {
	int alea = random() % TEMPS_MAX_FAB + 1;
	sleep(alea);
	printf("[%d]paquet: %ds\n", id, alea);
}
void empaqueteur() {
	srand(getpid());

	pid_t parent = getppid();
	for(int i=0; i<NBPAQUETS; i++) {
		fabrique_paquet(i+1);
		kill(parent, SIGUSR1); // envoi de signal de fabrication
	}
	
	kill(parent, SIGUSR2); // envoi de signal de fin
	puts("FIN EMPQ");
}

// chargeur
void charger_paquet(int id) {
	int alea = random() % TEMPS_MAX_CHG + 1;
	sleep(alea);
	printf("[%d]charge: %ds\n", id, alea);
}

void handle_signal(int signum) {
	if(signum == SIGUSR1)
		charge ++;
	else
		fin = 1;
}

void chargeur() {
	srand(getpid());

	struct sigaction act;
	bzero(&act, sizeof(struct sigaction));
	act.sa_handler = handle_signal;
	act.sa_flags = SA_RESTART;

	sigaction(SIGUSR1, &act, NULL);	
	sigaction(SIGUSR2, &act, NULL);
	int ordre = 1;
	while(!fin || charge) {
		if(charge) {
			charger_paquet(ordre);
			charge --;
			ordre ++;
		}
	}
	puts("FIN CHRG");
}

// handler pour le pere
void previentChargeur(int signum) {
	kill(chrg, signum); // informer le chargeur
}


int main(int argc, char* argv[]) {
	// handlers
	struct sigaction act;
	bzero(&act, sizeof(struct sigaction));
	act.sa_handler = previentChargeur;
	act.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	

	// creer l'empaqueteur
	empq = fork();
	if(empq < 0) {
		perror("fork err!\n");
		exit(EXIT_FAILURE);
	} else if(empq == 0) {
		empaqueteur();
		exit(EXIT_SUCCESS);
	}
	
	// creer le chargeur
	chrg = fork();
	if(chrg < 0) {
		perror("fork err!\n");
		exit(EXIT_FAILURE);
	} else if(chrg == 0) {
		chargeur();
		exit(EXIT_SUCCESS);
	}
	//~ for(int i=0; i<100; i++)
		//~ sleep(1);
	// attendre les fils
	int d = wait(NULL);
	printf("%s\n", strerror(errno));
	while(d > 0) {
		printf("%d\n", d);
		d = wait(NULL);
	}
	
	//~ waitpid(empq, NULL, 0);
	//~ waitpid(chrg, NULL, 0);
	//~ printf("%s\n", strerror(errno));
	//~ puts("FIN");
	
	getchar();
	return EXIT_SUCCESS;
}
