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
	
	int* a = tri_top_list(g1);
	if(a == NULL) {
		printf("Le graphe contient des cycles!\n");
		return 0;
	} else {
		for(int i=0; i<g1.nbr_sommets; i++)
			printf("%d ", a[i]);
		printf("\n");
	}
	free(a);
    return 0;
}
