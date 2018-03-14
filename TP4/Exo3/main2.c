#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
//NBR totale des processus cree est: m + m*n
int main(int argc, char **argv){
	if(argc != 3){
		perror("arguments\n");
		exit(-1);
	}
	int m = atoi(argv[1]), n = atoi(argv[2]);
	if(!m || !n){
		perror("arguments\n");
		exit(-1);
	}
	int cmpt = 0;
	for(int i=0; i<m; i++){
		pid_t pidFils = fork();
		if(pidFils == -1){
			perror("fork");
			exit(-1);
		}
		
		if(pidFils){
			printf("Created child process %d\n", pidFils);
		}
		else {
			for(int i=0; i<n; i++){
				pid_t pidPetitFils = fork();
				if(pidFils == -1){
					perror("fork");
					exit(-1);
				}
				
				if(pidPetitFils){
					printf("Created %d's child PID: %d\n", getpid(), pidPetitFils);
				}
				else {
					exit(1);
				}
			}
			int cmptFils = 0;
			int status;
			while(wait(&status)>=0){
				cmptFils += status;
			}
			exit(cmptFils);
		}		
	}
	int status;
	while(wait(&status)>=0){
		cmpt += status;
	}
	printf("%d\n",cmpt);
	exit(cmpt);
}
