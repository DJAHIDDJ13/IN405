#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
//NBR totale des processus cree est: m*n
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
	for(int i=0; i<m*n; i++){
		pid_t pid = fork();
		if(pid == -1){
			perror("fork");
			exit(-1);
		}
		
		if(pid){
			cmpt ++;
			printf("Processus fils, PID: %d\n",pid);
		}
		else{
			exit(0);
		}
	}
	while(wait(NULL)>=0);
	printf("%d\n",cmpt);
	exit(cmpt);
}
