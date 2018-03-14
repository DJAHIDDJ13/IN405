#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
//NBR totale des processus cree est: m + m*n + m*n*m
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
					for(int i=0; i<m; i++){
						pid_t pidPetitPetitFils = fork();
						if(pidFils == -1){
							perror("fork");
							exit(-1);
						}
						if(pidPetitPetitFils){
							printf("Created %d's child which is %d's child.. PID: %d\n",getpid(),getppid(), pidPetitPetitFils);
						} else {
							exit(0);
						}
					}
					while(wait(NULL)>0);
					exit(0);
				}
			}
			while(wait(NULL)>0);
			exit(0);
		}		
	}
	while(wait(NULL)>0);
	exit(0);
}
