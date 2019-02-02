// TD5.3 Structure de filesystem

/****************************************************************************
*
* $Id: fsTest.c 1897 2010-11-18 09:57:58Z phil $
*
****************************************************************************/
//static char rcsId[] = "@(#) $Id: fsTest.c 1897 2010-11-18 09:57:58Z phil $";
/***************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*****************************************************************************************
 * 1)
 * Le programme commence par la creation de fichier toto
 * et apres l'ecriture de l'alphabet
 * puis il ecrit l'offset qui est 26
 * apres apres il ecris les 5 premier caractéres de fichier ("abcde")
 * apres on ecrase les caractéres de 5 a 9 ("fghi") par "ABCD"
 * on ecrit l'offset qui est 9 (5 + 4)
 * on avance 1million octet l'offset de fichier et on ecrit de 100000009 a 10000012 "FIN"
 * puis on ferme le fichier
 * 
 * 2)
 * La taille: 10000029 octets ~ 10mb
 * 
 * 3)
 * nombre de blocs 19532
 * 
 * 5) resultat de (od -c toto)
 * 0000000   a   b   c   d   e   A   B   C   D   j   k   l   m   n   o   p
 * 0000020   q   r   s   t   u   v   w   x   y   z  \0  \0  \0  \0  \0  \0
 * 0000040  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
 * *
 * 46113220  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0   F   I   N
 * 46113235
******************************************************************************************/
int main() {
	char ch[10];
	int desc;
	off_t pos;
	/* création (ou écrasement) du fichier "toto" */
	desc = open("toto", O_RDWR | O_CREAT, 0777);
	if (desc == -1) { perror("open"); exit(2); }
	
	/* écriture d’une chaîne de 26 caractères dans "toto" */
	write(desc, "abcdefghijklmnopqrstuvwxyz", 26);
	
	/* position courante dans le fichier? */
	pos = lseek(desc, 0, SEEK_CUR);
	printf("position 1 : %ld\n", pos);
	
	/* replacement au début du fichier */
	pos = lseek(desc, 0, SEEK_SET);
	read(desc, ch, 5);
	
	/* on borne la chaîne de caractères pour éviter le débordement mémoire */
	ch[9]=0;
	printf("caracteres lus : %s\n", ch);
	
	/* écrasement de 4 caractères */
	write(desc, "ABCD", 4);
	
	/* position courante ? */
	pos = lseek(desc, 0, SEEK_CUR);
	printf("position 2 : %ld\n", pos);
	
	/* avancée de dix millions d’octets */
	lseek(desc, 10000000, SEEK_END);
	write(desc, "FIN", 3);
	close(desc);
	
	return 0;
}
