// TD5.4 Copie de fichier
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define TAILLE 512

int main(int argc, char** argv) {
	int src_fd, dest_fd;
	if(argc < 3) {
		perror("No arguments supplied!\n");
		exit(-1);
	}
	
	src_fd = open(argv[1], O_RDONLY);
	if(src_fd < 0) {
		if(errno == ENOENT) {
			fprintf(stderr, "%s: file doesn't exist\n", argv[1]);
		} else if(errno == EACCES) {
			fprintf(stderr, "%s: you don't have the rights to this file\n", argv[1]);
		} else {
			fprintf(stderr, "%s: other problem with open\n", argv[1]);			
		}
		exit(-1);
	}
	if(access(argv[2], F_OK) != -1) {
		fprintf(stderr, "%s: file already exists\n", argv[2]);
		exit(-1);
	}
	dest_fd = open(argv[2], O_WRONLY | O_CREAT, 0666);
	
	// copy
	void *c = malloc(TAILLE);
	while(read(src_fd, c, TAILLE)) {
		write(dest_fd, c, TAILLE);
	}
	
	free(c);
	close(src_fd);
	close(dest_fd);
	return 0;
}
