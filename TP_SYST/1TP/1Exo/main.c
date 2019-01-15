// TD1.1 Pointeurs sur fonctions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 5 // nbr des elm de tab
#define MIN 5
#define MAX 31 // taille max de chaine

// 1)
typedef struct {
	int ent;
	char nom[MAX];
} Fiche;

void affiche_tab(Fiche* tab) {
	for(int i=0; i<N; i++) {
		printf("\t%s - %d\n", tab[i].nom, tab[i].ent);
	}
	printf("\n");
}

int comp_str(const void* ch1, const void* ch2) {
	Fiche* f1 = (Fiche*) ch1;
	Fiche* f2 = (Fiche*) ch2;
	return strcmp(f1->nom, f2->nom);
} 
int comp_int(const void* int1, const void* int2) {
	Fiche* f1 = (Fiche*) int1;
	Fiche* f2 = (Fiche*) int2;
	return f1->ent - f2->ent;
}

int main(int argc, char** argv) {
	// init
	srand(time(NULL));
	
	// 2)
	Fiche tab[N];
	for(int i=0; i<N; i++) {
		int len = MIN + rand()%(MAX-MIN-1); // longueur de chaine;
		
		for(int j=0; j<len; j++) 
			tab[i].nom[j] = 'a' + rand() % ('z' - 'a');
		tab[i].nom[len] = 0;
		tab[i].ent = rand()%100;
	}
	printf("Avant:\n");
	affiche_tab(tab);
	
	// 3)
	// a)
	qsort(tab, N, sizeof(Fiche), comp_str);
	
	// b)
	printf("Sorted by name: \n");
	affiche_tab(tab);
	
	// c)
	qsort(tab, N, sizeof(Fiche), comp_int);
	
	// d)
	printf("Sorted by int: \n");
	affiche_tab(tab);
	
	return 0;
}
