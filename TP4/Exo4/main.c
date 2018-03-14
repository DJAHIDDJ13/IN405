#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	struct tms buf;
	pid_t pid = fork();
	if(pid){
		while(wait(NULL)>=0);
		times(&buf);
		printf("\nuser time for child = %ld\nsystem time for child = %ld\n",buf.tms_cutime, buf.tms_cstime);
		exit(0);
	}
	else{
		system("ls -R /usr/lib");
		exit(0);
	}

}
