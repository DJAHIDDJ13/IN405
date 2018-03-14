#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
int main(){
	pid_t pid = fork();
	if(pid){
		sleep(3);
		kill(pid,SIGSTOP);
		sleep(5);
		kill(pid,SIGCONT);
		while(wait(NULL)>=0);
		exit(0);
	} else {
		for(int i=1; i<=5; i++){
			sleep(1);
			printf("%d\n",i);
		}
		exit(0);
	}
	
}
