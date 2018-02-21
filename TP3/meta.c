#include <sys/types.h> 
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int affMeta(const char *chemin){
	struct stat buffer;
    if (stat(chemin, &buffer) == -1) {
        perror("stat");
        return -1;
    }
    printf("le fichier est : ");
    switch (buffer.st_mode & S_IFMT) {
		case S_IFBLK:  printf("device de bloc\n");            break;
		case S_IFCHR:  printf("device de caractère\n");       break;
		case S_IFDIR:  printf("répertoire\n");                break;
		case S_IFIFO:  printf("FIFO\n");                      break;
		case S_IFLNK:  printf("lien symbolique\n");           break;
		case S_IFREG:  printf("fichier regulier\n");          break;
		case S_IFSOCK: printf("socket\n");                    break;
		default:       printf("pas de types\n");              break;
    }
	return 0;
}
int affPerm(const char* chemin){
	struct stat buffer;
    if (stat(chemin, &buffer) == -1) {
        perror("stat error\n");
        return -1;
    }
    int m = buffer.st_mode;
    printf("Permission: ");
    printf("%c%c%c", (m&S_IRUSR)?'r':'-',(m&S_IWUSR)?'w':'-',(m&S_IXUSR)?'x':'-');
    printf("%c%c%c", (m&S_IRGRP)?'r':'-',(m&S_IWGRP)?'w':'-',(m&S_IXGRP)?'x':'-');
    printf("%c%c%c\n", (m&S_IROTH)?'r':'-',(m&S_IWOTH)?'w':'-',(m&S_IXOTH)?'x':'-');
	return 0;
}
int affProp(const char * chemin){
	struct stat buffer;
    if (stat(chemin, &buffer) == -1) {
        perror("stat");
        return -1;
    }
    printf("Proprietaire: %u\n", buffer.st_uid);
	return 0;
}
int affSize(const char * chemin){
	struct stat buffer;
    if (stat(chemin, &buffer) == -1) {
        perror("stat");
        return -1;
    }
    int tempSize = buffer.st_size;
	int *size = malloc(sizeof(int) * 5);
	for(int i=0; i<5; i++){
		size[i] = tempSize %1024;
		tempSize /= 1024;
	}
	printf("Taille: ");
	if(size[4])printf("%dTo ", size[4]);
	if(size[3])printf("%dGo ", size[3]);
	if(size[2])printf("%dMo ", size[2]);
	if(size[1])printf("%dKo ", size[1]);
	if(size[0])printf("%do", size[0]);
	printf("\n");
	return 0;
}
int main(int argc, char** argv){
	if(argc != 2)
		return 0;
	printf("Nom de fichier %s\n", argv[1]);
	affMeta(argv[1]);
	affPerm(argv[1]);
	affProp(argv[1]);
	affSize(argv[1]);
	return 0;
}
