/* parse.c
    GNC: S --> aAb/bBa
            A --> aA/bB
            B --> aB/ba
ex: aabab
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
#define WORD_MAX 100

void error(char *message);
void next_c(void);
void check(char cc);
void S(void);
void A(void);
void B(void);

/*-----variables globales-----*/

static char c, word[WORD_MAX];
static int position;


int main(int argc, char const *argv[]) //*argv[] veut dire un tableau de pointeurs
{
	if(argc != 2)
		exit(-1);
	strcat(word, argv[1]);
	strcat(word, "$");
	position = 0; // inutile car le mot static veut dire que c'est deja initialisé a 0

	printf("pret a analyser %s\n", word);
	next_c();

	S();
	
	if (c == '$')
	{
		printf("mot accepte\n");
	}else{
		printf("mot refuse, (fin du mot attendue)\n");
	}

	return 0;
}


void error(char *message){
	printf("%s\n", message);
	exit(0);
}


void next_c(void) {
	c =  word[position++];
	#if (DEBUG > 0)
		printf("next_c(): c = %c\n", c);
	#endif
}

void check(char cc) {
	if(c == '$')
		return;
	if(c != cc)
		printf("Error: found %c, expected %d\n", c, cc);
	else 
		next_c();
}

void S(void){
	
#if (DEBUG > 0)
	printf("S\n");
#endif	

	switch(c){
		case 'a': 
			next_c();
			A();
			check('b');
		break;
		case 'b': 
			next_c();
			B();
			check('a');
		break;

		default: error("error dans S(): a ou b attendu\n");
	}
}

void A(){
#if (DEBUG > 0)
	printf("A\n");
#endif
	switch(c){
		case 'a':
			next_c();
			A();
		break;
		case 'b':
			next_c();
			B();
		break;
		default: error("error dans A(): a ou b attendu\n");
	}
}

void B(){
#if (DEBUG > 0)
	printf("B\n");
#endif
	switch(c){
		case 'a':
			next_c();
			B();
		break;
		case 'b':
			next_c();
			check('a');
			next_c();
		break;
		default: error("a ou b\n");
	}
}
