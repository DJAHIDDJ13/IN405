#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int elm;
	struct node* suiv;
	struct node* prev;
} LISTE; 

LISTE* create_list() {
	return NULL;
}

LISTE* push(LISTE* l, int n) {
	LISTE* m = malloc(sizeof(LISTE));
	m->elm = n;
	
	if(l == NULL) {
		m->suiv = m;
		m->prev = m;
		return m;
	}
	m->suiv = l;
	m->prev = l->prev;
		
	l->prev = m;
	
	return m;
}

LISTE* pop(LISTE* l) {
	if(!l){
		return NULL;
	}
	if(l->suiv == l){
		free(l);
		return NULL;
	}
	
	LISTE* m = l;
	l->prev->suiv = l->suiv;
	l->suiv->prev = l->prev;
	free(m);
	
	return l->suiv;
}

void show_list(LISTE* l) {
	if(l == NULL){
		printf("vide\n");
		return;
	}
	LISTE* m = l;
	while(l->prev != m){
		printf("%d ", l->elm);
		l = l->prev;
	}
	printf("%d", l->elm);
	printf("\n");
}

int nb_occurences(LISTE* l ,int elm) {
	int s = 0;
	LISTE* m = l;
	while(l->prev != m){
		if(l->elm == elm)
			s++;
		l = l->prev;
	}
	return (l->elm == elm)?s+1:s;
}

int main() {
	LISTE* l = create_list();
	int n;
	printf("Combien des elements: ");
	scanf("%d", &n);
	printf("Entrer les elements: (-1 pour depiler)\n");
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
