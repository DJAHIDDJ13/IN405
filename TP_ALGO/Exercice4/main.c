#include <stdio.h>
#include <stdlib.h>

typedef struct {
		double coef;
		int degre;
} Monome;

typedef struct cellule {
	Monome monome;
	struct cellule* suiv;
	struct cellule* pred;
}* Polynome;
// 2
int degMon(Monome m) {
	return m.degre;
}

double coefMon(Monome m) {
	return m.coef;
}

// 3
Monome monCourant(Polynome p) {
	Monome nullElm = {.coef=-1.0, .degre=-1};
	return p? p->monome : nullElm;
}

Monome monSuivant(Polynome p) {
	Monome nullElm = {.coef=-1.0, .degre=-1};
	return p? (p->suiv? p->suiv->monome : nullElm) : nullElm;
}

Monome monPredcedent(Polynome p) {
	Monome nullElm = {.coef=-1.0, .degre=-1};
	return p? (p->pred? p->pred->monome : nullElm) : nullElm;
}

// 4
Polynome creerPoly() {
	return NULL;
} 

_Bool videPoly(Polynome p) {
	return p == NULL;
}


Polynome inserMonPoly(Polynome p, Monome m) {
	Polynome res = p;
	
	Polynome node = malloc(sizeof(struct cellule));
	node->monome = m;
	node->suiv = NULL;
	node->pred = NULL;
	if(videPoly(p))
		return node;

	while(degMon(p->monome) < degMon(m) && p->suiv){
		p = p->suiv;
	}
		
	if(videPoly(p->suiv)){
		if(videPoly(p->pred)){
			if(degMon(p->monome) < degMon(m)){
				p->suiv = node;
				node->pred = p;
			} else if (degMon(p->monome) > degMon(m)){
				p->pred = node;
				node->suiv = p;
				res = node;
			} else {
				free(node);
				p->monome.coef += m.coef;
			}
		} else {
			p->suiv = node;
			node->pred = p;
		}
	} else if(degMon(p->monome) == degMon(m)) {
		free(node);
		p->monome.coef += m.coef;
	} else {
		Polynome ptl = p->pred;
		p->pred = node;
		node->suiv = p;
		node->pred = ptl;
		if(ptl)
			ptl->suiv = node;
	}
	
	return res;
}

Polynome rechMonPoly(Polynome p, Monome m) {
	while(p) {
		if(coefMon(m) == coefMon(p->monome) && degMon(m) == degMon(p->monome))
			return p;
		p = p->suiv;
	}
	return NULL;
}
// 5
void affichMon(Monome m) {
	if(m.degre == 0)
		printf("%g", coefMon(m));
	else
		printf("%g*x^%d", coefMon(m), degMon(m));
}

void affichPoly(Polynome p) {
	if(videPoly(p)) {
		printf("vide\n");
		return;
	}
	while(p) {
		affichMon(p->monome);
		p = p->suiv;
		printf("%s", p?" + ":"");
	}
	printf("\n");
}

int main(int argc, char** argv) {
	Polynome p = creerPoly();
	Monome test[6] = {
					{.coef=-2.5, .degre=2},
					{.coef=13, .degre=0},
					{.coef=1, .degre=8},
					{.coef=-7, .degre=13},
					{.coef=1, .degre=8}
				};
	for(int i=0; i<5; i++){
		p = inserMonPoly(p, test[i]);
	}
	printf("%p\n", rechMonPoly(p, test[2]));

	affichPoly(p);
	return 1;
}
