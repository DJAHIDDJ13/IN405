#include <stdio.h>
#include <stdlib.h>
#include "graph_bib.h"


int main() {
	GRAPH_LIST g1 = lire_graphe_liste("graph_file");
	GRAPH_VxV g2 = lire_graphe_vxv("graph_file");
	GRAPH_VxA g3 = lire_graphe_vxa("graph_file");

	ecrire_graphe_liste("res1", g1);
	ecrire_graphe_vxv("res2", g2);
	ecrire_graphe_vxa("res3", g3);
	
	int* niv = niveaux(g1);
	if(niv == NULL) {
		printf("contains cycles\n");
	} else {
		for(int i=0; i<g1.nbr_sommets; i++)
			printf("%d ", niv[i]);
		printf("\n");
		free(niv);
	}
	free_graphe_liste(g1);
	free_graphe_vxv(g2);
	free_graphe_vxa(g3);
    return 0;
}
