#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){		
	pid_t pid = fork();
	srand(getpid());
	if(pid == -1){
		perror("fork\n");
		exit(-1);
	}
	
	if(pid){
		printf("Hello world!\n");
		printf("Mon PID est %d et celui de mon fils est %d!\n",getpid(),pid);
		int received;
		if (wait(&received) >= 0){
			printf("received %d\n", WEXITSTATUS(received));
		}
	}
	else {
		printf("Hello world!\n");		
		printf("Mon PID est %d et celui de mon pere est %d\n",getpid(),getppid());
		int randomNum = rand()%50+1;
		printf("Created %d\n",randomNum);
		exit(randomNum);
		//~ exit(256); we get 0 cuz its the maximum
	}
}
