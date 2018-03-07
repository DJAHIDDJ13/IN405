#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <math.h>
char** rep(char* chemin, int* length){
	DIR* direct = opendir(chemin);
	if(!direct) exit(-1);
	struct dirent* fich = readdir(direct);
	*length = 0;
	if(fich){
		do{
			(*length)++;
			fich = readdir(direct);
		} while(fich);
	}
	closedir(direct);
	
	direct = opendir(chemin);
	if(!direct) exit(-1);
	char** res = malloc(sizeof(char*) * (*length+1));
	fich = readdir(direct);
	int len = strlen(chemin);
	int i = 0;
	do{
		res[i] = malloc(sizeof(char) * (strlen(fich->d_name) + len + 2));
		sprintf(res[i], "%s%s%s",chemin, chemin[strlen(chemin) - 1] == '/'?"":"/",fich->d_name);
		i++;
		fich = readdir(direct);
	} while(fich);
	closedir(direct);
	return res;
}


char* perm(const char* chemin){
	struct stat buffer;
    if (stat(chemin, &buffer) == -1) {
        perror("stat error\n");
        exit(-1);
    }
    int m = buffer.st_mode;
    char* s = malloc(sizeof(char) * 10);
    sprintf(s,"%c%c%c%c%c%c%c%c%c", (m&S_IRUSR)?'r':'-',(m&S_IWUSR)?'w':'-',(m&S_IXUSR)?'x':'-',(m&S_IRGRP)?'r':'-',(m&S_IWGRP)?'w':'-',(m&S_IXGRP)?'x':'-',(m&S_IROTH)?'r':'-',(m&S_IWOTH)?'w':'-',(m&S_IXOTH)?'x':'-');
	return s;
}


long int size(const char * chemin){
	struct stat buffer;
    if (stat(chemin, &buffer) == -1) {
        perror("stat");
        exit(-1);
    }
	//~ int *size = malloc(sizeof(int) * 5);
	//~ for(int i=0; i<5; i++){
		//~ size[i] = tempSize %1024;
		//~ tempSize /= 1024;
	//~ }
	//~ char *s = malloc(sizeof(char) * 200);
	//~ if(size[4])sprintf(s,"%dTo", size[4]);
	//~ if(size[3])sprintf(s,"%dGo", size[3]);
	//~ if(size[2])sprintf(s,"%dMo", size[2]);
	//~ if(size[1])sprintf(s,"%dKo", size[1]);
	//~ if(size[0])sprintf(s,"%do", size[0]);
	return buffer.st_size;
}
char* getFileName(char* chemin){
	char* s = malloc(sizeof(char) * (strlen(chemin) +1 ));
	strcpy(s, chemin);
	int i=strlen(chemin)-1;
	if (s[strlen(chemin)-1] == '/'){ 
		s[strlen(chemin)-1] = '\0';
		i--;
	}
	while(s[i]!='/' && (i--)>=0);
	return s+i+1;
}
char* prop(const char * chemin){
	struct stat buffer;
    if (stat(chemin, &buffer) == -1) {
        perror("stat");
        exit(-1);
    }
    struct passwd *name = getpwuid(buffer.st_uid);
	return name->pw_name;
}
char* type(const char *chemin){
	struct stat buffer;
    if (stat(chemin, &buffer) == -1) {
        perror("stat");
        exit(-1);
    }
	char *s = malloc(sizeof(char)*4);
    switch (buffer.st_mode & S_IFMT) {
		case S_IFBLK:  sprintf(s,"BLK");break;
		case S_IFCHR:  sprintf(s,"CHR");break;
		case S_IFDIR:  sprintf(s,"DIR");break;
		case S_IFIFO:  sprintf(s,"FIF");break;
		case S_IFLNK:  sprintf(s,"LNK");break;
		case S_IFREG:  sprintf(s,"REG");break;
		case S_IFSOCK: sprintf(s,"SOC");break;
		default:       sprintf(s,"UNK");break;
    }
	return s;
}
int main(int argc, char** argv){
	if(argc != 2)return -1;
	int len;
	long int maxLen;
	char** s = rep(argv[1], &len);
	if(len){
		maxLen = size(s[0]);
		for(int i=1; i<len; i++){
			if(maxLen< size(s[i]))
				maxLen = size(s[i]);
		}
	}
	else
		maxLen = 1;
	int max = (int)(log((double)maxLen)/log(10.0)) + 1;
	for(int i=0; i<len; i++){
		printf("%s %s %s %*ld %s\n",type(s[i]),perm(s[i]), prop(s[i]), max, size(s[i]), getFileName(s[i]));
	}
	return 0;
}
