#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct cellule {
		int fact;
		int nbOcc;
		struct cellule *suiv;
	}* Liste;
	
typedef struct {
		int val;
		Liste factPremier;
} elementTab;

typedef struct tabListe {
	elementTab elm;
	struct tabListe* suiv;
} TabListe;

void affichFact(Liste l) {
	while(l){
		printf("%d^%d%s", l->fact, l->nbOcc, (l->suiv)?"*":"");
		l = l->suiv;
	}
}

void affichTabListe(TabListe *t) {
		while(t) {
			printf("%d = ", t->elm.val);
			affichFact(t->elm.factPremier);
			printf("\n");
			t = t->suiv;
		}
}

Liste decomp(int n) {
	if(n<2) return NULL;
	Liste d = malloc(sizeof(struct cellule));
	Liste res = d;
	d->suiv = NULL;
	int limit = (int)sqrt(n);
	for(int f=2; f<=limit; f++){
		int nb = 0;
		while(n%f == 0){
			nb++;
			n = n/f;
		}
		if(nb){
			d->fact = f;
			d->nbOcc = nb;
			if(n != 1) {
				d->suiv = malloc(sizeof(struct cellule));
				d = d->suiv;
				d->suiv = NULL;
			}
		}
	}
	if(n != 1){
		d->fact = n;
		d->nbOcc = 1;
	}
	return res;
}

int min(int a, int b){
	return (a<b)?a:b;
}

Liste intersection(Liste a, Liste b) {
	Liste res = malloc(sizeof(struct cellule));
	Liste d = res;
	d->fact  = -1;
	while(a && b) {
		if(a->fact == b->fact){
			d->fact = a->fact;
			d->nbOcc = min(a->nbOcc, b->nbOcc);
			a = a->suiv;
			b = b->suiv;
		} else if(a->fact < b->fact) {
			a = a->suiv;
		} else {
			b = b->suiv;
		}
	}
	if(d->fact == -1){
		free(d);
		return NULL;
	}
	return res;
}

int PGCD(Liste a, Liste b) {
	Liste s = intersection(a, b);
	int res = 1;
	while(s){
		res *= (int)pow(s->fact, s->nbOcc);
		s = s->suiv;
	}
	return res;
}
int PGCD_Tab(TabListe* t){
	if(!t) return 1;
	int pgcd = t->elm.val;
	t = t->suiv;
	while(t){
		pgcd = PGCD(decomp(pgcd), decomp(t->elm.val));
		t = t->suiv;
	}
	return pgcd;
}
TabListe* tabFact(int *tab, int n){
	if(n == 0) return NULL;
	TabListe* t = malloc(sizeof(TabListe));
	TabListe* res = t;
	for(int i=0; i<n; i++) {
		t->elm.val = tab[i];
		t->elm.factPremier = decomp(tab[i]);
		if(i!=n-1){
			t->suiv = malloc(sizeof(TabListe));
			t = t->suiv;
		}
	}
	return res;
}
int main(int argc, char** argv){
	int choix;
	printf("1: decomposition d'un nombre\n");
	printf("2: decomposition d'un tableau\n");
	printf("3: intersection entre deux nombres\n");
	printf("4: PGCD plusieurs nombres\n");
	printf("Entrer un choix : ");
	
	scanf("%d", &choix);
	switch(choix){
	case 1:
		printf("entrer un nombre. n = ");
		int n;
		scanf("%d", &n);
		printf("La decomposition: \n");
		affichFact(decomp(n));
	break;
	
	case 2:
		printf("Combien des nombres? n = ");
		int s;
		scanf("%d", &s);
		int *tab = malloc(sizeof(int));
		printf("Entrer Les nombres: \n");
		for(int i=0; i<s; i++){
			int k;
			scanf("%d", &k);
			tab[i] = k;
		}
		printf("Le resultat: \n");
		TabListe *t = tabFact(tab, s);
		affichTabListe(t);
	break;
	
	case 3:
		printf("Entrer les nombres: \n");
		int a, b;
		printf("a = ");
		scanf("%d", &a);
		printf("b = ");
		scanf("%d", &b);
		printf("L'intersection de a et b: \n");
		affichFact(intersection(decomp(a), decomp(b)));
	break;
	case 4:
		printf("Combien des nombres? n = ");
		int f;
		scanf("%d", &f);
		int *ta = malloc(sizeof(int));
		printf("Entrer Les nombres: \n");
		for(int i=0; i<f; i++){
			int k;
			scanf("%d", &k);
			ta[i] = k;
		}
		TabListe *table = tabFact(ta, f);
		printf("PGCD(");
		for(int i=0; i<f; i++){
			printf("%d%s", ta[i], (i==f-1)?"":",");
		}
		printf(") = %d\n", PGCD_Tab(table));
	break;
	default:
		printf("INVALIDE CHOICE\n");
	}
}
