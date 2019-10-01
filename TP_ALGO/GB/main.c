#include <stdio.h>
#include <stdlib.h>
#include "graph_bib.h"

int cmp(void* a, void* b) {
	return *(int*)(a) - *(int*)(b);
}

int main() {	
	GRAPH_LIST g1 = lire_graphe_liste("graph_file");
	//~ GRAPH_LIST g1 = generate_graphe_liste(10);

	ecrire_graphe_liste("res1", g1);

	
	int *p = malloc(sizeof(int ) * g1.nbr_sommets);
	TElement *dist = malloc(sizeof(int ) * g1.nbr_sommets);
	dijkstra(p,dist, g1, 0, cmp);
	for(int i=0; i< g1.nbr_sommets; i++) {
		printf("%d(%d) ", p[i], dist[i]);
	}
	printf("\n");
	
	free_graphe_liste(g1);
    return 0;
}















	//~ int* niv = niveaux(g1);
	//~ if(niv == NULL) {
		//~ printf("contains cycles\n");
	//~ } else {
		//~ for(int i=0; i<g1.nbr_sommets; i++)
			//~ printf("%d ", niv[i]);
		//~ printf("\n");
		//~ free(niv);
	//~ }
