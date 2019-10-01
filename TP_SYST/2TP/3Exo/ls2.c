// TD5.5 Exploration de répertoire
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>



void get_permission(mode_t perm, char res[10]) {
	//~ res[0] = (S_ISREG(perm))? '-':(S_ISDIR(perm))? 'd':(S_ISBLK(perm))? 'b':(S_ISFIFO(perm))? 'p':(S_ISLNK(perm))? 'l':'s';
	res[0] = (S_ISDIR(perm))? 'd': '-';
	
	res[1] = (S_IRUSR & perm)? 'r': '-';
	res[2] = (S_IWUSR & perm)? 'w': '-';
	res[3] = (S_IXUSR & perm)? 'x': '-';
	
	res[4] = (S_IRGRP & perm)? 'r': '-';
	res[5] = (S_IWGRP & perm)? 'w': '-';
	res[6] = (S_IXGRP & perm)? 'x': '-';
	
	res[7] = (S_IROTH & perm)? 'r': '-';
	res[8] = (S_IWOTH & perm)? 'w': '-';
	res[9] = (S_IXOTH & perm)? 'x': '-';

	res[10] = '\0';
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
	DIR* dir;
	struct dirent* ent;
	
	if((dir = opendir(dirname)) != NULL) {
		while((ent = readdir(dir)) != NULL) {
			char filepath[512] = {0};
			sprintf(filepath, "%s%s%s", dirname, (dirname[strlen(dirname)-1] == '/')? "":"/", ent->d_name);
			struct stat buf;
			stat(filepath, &buf);
			char perm[10];
			get_permission(buf.st_mode, perm);

			printf("%s %ld %ldo %s\n", perm, buf.st_nlink, buf.st_size, ent->d_name);
		}
		closedir(dir);
	} else {
		perror("Could not open directory\n");
		exit(-1);
	}
	return 0;
}
