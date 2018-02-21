#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include "se_fichier.h"
SE_FICHIER SE_ouverture(const char* chemin, int acces){
	SE_FICHIER fich;
	fich.chemin = malloc(sizeof(char)*(strlen(chemin)+1));
	strcpy(fich.chemin, chemin);
	fich.acces = acces;
	fich.descripteur = open(chemin, acces |O_CREAT, 0766);
	return fich;
}
int SE_fermeture(SE_FICHIER fichier){
	return close(fichier.descripteur);
}
int SE_suppression(const char * chemin){
	return remove(chemin);
} 
int SE_lectureCaractere(SE_FICHIER fichier, char* caractere){
	return read(fichier.descripteur,caractere,1);
}
int SE_ecritureCaractere (SE_FICHIER fichier,const char caractere){
	return write(fichier.descripteur,&caractere,1);
}

