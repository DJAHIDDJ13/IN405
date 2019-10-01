#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int dirSize(const char* file) {
	struct stat stt;
	if(lstat(file, &stt) < 0) {
		perror("stat error\n");
		exit(-1);
	}
	int total_size = stt.st_size;
	
	if(S_ISDIR(stt.st_mode)) {
		DIR* dir = opendir(file);
		if(dir < 0) {
			switch(errno) {
				case EACCES: 
					perror("permission error!\n");
					break;
				case ENOENT:
					perror("directory does not exist!\n");
					break;
				default:
					perror("can't open directory\n");
			}
			exit(EXIT_FAILURE);
		}
		
		struct dirent* ent;

		while((ent = readdir(dir)) != NULL) {
			char filepath[512] = {0};
			sprintf(filepath, "%s%s%s", file, (file[strlen(file)-1] == '/')? "":"/", ent->d_name);
			if(strcmp(ent->d_name ,".") == 0 || strcmp(ent->d_name ,"..") == 0) {
				continue;
			}
			total_size += dirSize(filepath);
		}
		printf("%-8d %s\n", total_size, file);
		closedir(dir);
	}
	
	return total_size;
}

int main(int argc, char** argv) {
	char dirname[256] = ".";
	if(argc > 1) {
		strcpy(dirname, argv[1]);
		if(strlen(argv[1]) > 255) {
			perror("Filename too long\n");
			exit(-1);
		}
	}
	//printf("%s\n", dirname);
	dirSize(dirname);
	
	return EXIT_SUCCESS;
}
