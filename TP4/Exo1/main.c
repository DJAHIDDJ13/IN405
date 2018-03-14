#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
int main(){		
	int fd[2];
	pipe(fd);
	
	pid_t pid = fork();
	srand(getpid());

	if(pid == -1){
		perror("fork\n");
		exit(-1);
	}
	if(pid){
		printf("Hello world!\n");
		printf("Mon PID est %d et celui de mon fils est %d!\n",getpid(),pid);
		close(fd[1]);
		int received;
		if(read(fd[0], &received, sizeof(int)) == 0){
			perror("nothing received\n");
			exit(-1);
		} else {
			printf("parent received %d\n", received);
		}
	} else {
		printf("Hello world!\n");		
		printf("Mon PID est %d et celui de mon pere est %d\n",getpid(),getppid());
		int randomNum = rand()%1000;
		printf("child created %d\n",randomNum);
		close(fd[0]);
		write(fd[1], &randomNum, sizeof(int));
	}
	return 0;
}
