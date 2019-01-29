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
	
	MAT fw = floyd_warshall(g2);
	for(int i=0; i<fw.width; i++) {
		for(int j=0; j<fw.height; j++) {
			printf("%d ", fw.mat[j][i]);
		}
		printf("\n");
	}
    return 0;
}
