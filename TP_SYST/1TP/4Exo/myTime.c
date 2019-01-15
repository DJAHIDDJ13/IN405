#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
	struct timeval s_tv, e_tv;
	pid_t pid = fork();
	
	if(pid < 0) {
		perror("Fork error!\n");
		exit(-1);
	}
	gettimeofday(&s_tv, NULL);
	if(pid == 0) {
		if(argc < 2) {
			perror("No argument supplied!\n");
			exit(-1);
		}
		// executer commande
		if(execvp(argv[1], argv+1) < 0) {
			perror("Error while executing command\n");
			exit(-1);
		}
		exit(0);
	}
	wait(NULL);
	gettimeofday(&e_tv, NULL);
	long long time = e_tv.tv_sec*1000LL + e_tv.tv_usec/1000 - (s_tv.tv_sec*1000LL + s_tv.tv_usec/1000);
	printf("time: %lld ms\n", time);
    return 0;
}
