// TD1.2 Variables et processus
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	int n = 0;
	int pid = 0;
	
	if((pid = fork()) < 0) {
		perror("Fork error");
		exit(-1);
	}
	
	if(pid == 0) { // fils
		n = getpid();
		printf("[%d] Exiting...\n", n);
	} else { // pére
		waitpid(pid, NULL, 0);
		printf("n = %d\n", n);
	}
	return 0;
}
