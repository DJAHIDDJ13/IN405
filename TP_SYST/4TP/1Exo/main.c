#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#define MAX_LEN 100
#define NBR_CLIENTS 7
#define NBR_CHAIRS 7
#define TEMPS_COIFF 10
#define CLIENT_SLEEP_MIN 1

char* readline(int fd, char res[MAX_LEN]) {
	struct timeval tv;
	fd_set fdread;
	FD_ZERO(&fdread);
	FD_SET(fd, &fdread);
	tv.tv_sec = 0;
	tv.tv_sec = 0;
	int sel = select(fd+1, &fdread, NULL, NULL, &tv);
	if(sel < 0) {
		perror("select error!\n");
		exit(EXIT_FAILURE);
	}
	if(sel == 0) {
		res[0] = '\0';
		return res;
	}
	read(fd, res, sel);
	res[sel] = '\0';
	
	return res;
}

void client_sleep(int out) {
	int r = rand() % 10 + CLIENT_SLEEP_MIN;
	sleep(r);
}
void client(int id, int in, int out) {
	pid_t pid = getpid();
	srand(pid);

	client_sleep(out);
	printf("[%d]Entering..\n", id);
	char buf[MAX_LEN] = {0};
	sprintf(buf, "ENTER %d\n", id);
	write(out, buf, strlen(buf)+1);
	
	
}

void coiffe() {
	int r = rand() % TEMPS_COIFF;
	sleep(r);
}


int main(int argc, char* argv[]) {	
	// les chaises et le fauteuil
	int chairs[NBR_CHAIRS+1] = {0};
	
	int child_pipe[NBR_CLIENTS][2];
	int parent_pipe[NBR_CLIENTS][2];
	
	int in[NBR_CLIENTS];
	int out[NBR_CLIENTS];
	
	// creation des clients
	for(int i=0; i<NBR_CLIENTS; i++) {
		if(pipe(child_pipe[i]) || pipe(parent_pipe[i])) {
			perror("pipe error");
			exit(EXIT_FAILURE);
		}
		out[i] = child_pipe[i][1];
		in[i] = parent_pipe[i][0];
		
		pid_t pid = fork();
		if(pid < 0) {
			fprintf(stderr, "%d: Fork error\n", __LINE__);
			exit(EXIT_FAILURE);
		}
		if(pid == 0) {
			client(i+1, child_pipe[i][0], parent_pipe[i][1]);
			exit(EXIT_SUCCESS);
		}
	}
	int served = 0;
	// wait for child processes
	while(served < NBR_CLIENTS) {
		if(chairs[0]) {
			coiffe();
			printf("SENT DONE TO %d\n", chairs[0]);
			write(out[chairs[0]], "DONE\n", 6);
			for(int i=0; i<NBR_CHAIRS-1 && chairs[i]; i++) {
				chairs[i] = chairs[i+1];
			}
			printf("next = %d\n", chairs[0]);
			served ++;
		}
		
		// update chairs
		for(int i=0; i<NBR_CLIENTS; i++) {
			char buf[MAX_LEN] = {0};
			strcpy(buf, readline(in[i], buf));
			
			if(strstr(buf, "ENTER")) {
				int id = -1;
				sscanf(buf, "ENTER %d\n", &id);
				printf("READ ENTER FROM %d\n", id);
				int j;
				for(j=0; j<NBR_CHAIRS && chairs[j]; j++);
				if(j < NBR_CHAIRS)
					chairs[j] = id;
				else {
					strcpy(buf, "FULL\n");
					write(out[i], buf, 6);
				}
			}
		}
	}
	
	printf("OUT\n");
	while(wait(NULL) > 0);
	
	return EXIT_SUCCESS;
}
