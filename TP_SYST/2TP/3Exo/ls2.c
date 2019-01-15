// TD5.5 Exploration de répertoire
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv) {
	char dirname[256] = ".";
	if(argc > 1) {
		strcpy(dirname, argv[1]);
		if(strlen(argv[1]) > 255) {
			perror("Filename too long\n");
			exit(-1);
		}
	}
	DIR* dir;
	struct dirent* ent;
	
	if((dir = opendir(dirname)) != NULL) {
		while((ent = readdir(dir)) != NULL) {
			char filepath[512] = {0};
			sprintf(filepath, "%s%s%s", dirname, (dirname[strlen(dirname)-1] == '/')? "":"/", ent->d_name);
			struct stat buf;
			stat(filepath, &buf);
			

			printf("%d %s\n", buf.st_mode, ent->d_name);
		}
		closedir(dir);
	} else {
		perror("Could not open directory\n");
		exit(-1);
	}
	return 0;
}
