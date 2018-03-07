#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lireRep(char* chemin, _Bool showHidden){
	char* s = malloc(sizeof(char) * 256);
	DIR* direct = opendir(chemin);
	if(!direct) return -1;
	struct dirent* fich = readdir(direct);
	if(!fich) return -1;
	do{
		strcpy(s,fich->d_name);
		if(s[0]=='.'){
			if(showHidden)
				printf("%s\n", s);
		}
		else{
			printf("%s\n", s);
		}
		fich = readdir(direct);
	} while(fich);
	return closedir(direct);
}
int main(int argc, char** argv){
	if(argc == 1){
		if(lireRep("/",1)==-1)
			perror("Error!\n");
	} else if(argc == 2){
		if(lireRep(argv[1],0)==-1)
			perror("Error!\n");		
	} else if(argc == 3){
		if(lireRep(argv[1],!strcmp("-a",argv[2]))==-1)
			perror("Error!\n");
	} else{
		perror("Too many arguments\n");
	}
	return 0;
}
