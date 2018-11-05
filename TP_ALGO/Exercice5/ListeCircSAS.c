#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int elm;
	struct node* suiv;
} LISTE; 

LISTE* create_list() {
	LISTE* l = malloc(sizeof(LISTE));
	l->elm = -1;
	l->suiv = l;
	return l;
}

LISTE* push(LISTE* l, int n) {
	LISTE* m = malloc(sizeof(LISTE));
	m->elm = n;
	m->suiv = l->suiv;
	
	l->suiv = m;
	
	return l;
}

LISTE* pop(LISTE* l) {
	if(l->suiv == l){
		return l;
	}
	
	LISTE* m = l->suiv;
	l->suiv = l->suiv->suiv;
	free(m);
	return l;
}

void show_list(LISTE* l) {
	if(l == NULL){
		printf("vide\n");
		return;
	}
	l = l->suiv;
	while(l->elm != -1){
		printf("%d ", l->elm);
		l = l->suiv;
	}
	printf("\n");
}

int nb_occurences(LISTE* l ,int elm){
	int s = 0;
	l = l->suiv;
	while(l->elm != -1){
		if(l->elm == elm)
			s++;
		l = l->suiv;
	}
	return s;
}
int main() {
	LISTE* l = create_list();
	int n;
	printf("Combien des elements: ");
	scanf("%d", &n);
	printf("Entrer les elements (-1 pour depiler): \n");
	for(int i=0; i<n; i++){
		int e;
		scanf("%d", &e);
		l = (e == -1)? pop(l):push(l,e);
	}
	printf("liste: ");
	show_list(l);
	
	int o;
	printf("L'element a rechercer: ");
	scanf("%d", &o);

	printf("nombre d'occ de %d est: %d\n",o, nb_occurences(l, o));
}
