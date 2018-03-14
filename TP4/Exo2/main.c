#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	pid_t pids[10];
	int i;
	int n = 10;

	for(i = 0; i < n; ++i) {
		if ((pids[i] = fork()) < 0) {
			perror("fork");
			exit(-1);
		}
		else if (pids[i] == 0) {
			srand(getpid());
			int sleepSec = rand()%10;
			sleep(sleepSec);
			printf("PID = %d, sleep time = %d\n", getpid(), sleepSec);
			exit(sleepSec);
		}
	}

	int status;
	pid_t pid;
	while (n > 0) {
		pid = wait(&status);
		if(pid == -1){
			perror("wait ERROR\n");
			exit(-1);
		}
		if(WIFEXITED(status)){
			printf("Child with PID %ld exited with status %d.\n", (long)pid, WEXITSTATUS(status));
		}
		else{
			printf("Child with PID %ld did not exit\n", (long)pid);
		}
		--n;
	}
}
