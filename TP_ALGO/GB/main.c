#include <stdio.h>
#include <stdlib.h>
#include "graph_bib.h"


int main() {
	lire_graphe_liste("graph_file");
	GRAPH_VxV g1 = lire_graphe_vxv("graph_file");
	GRAPH_VxA g2 = lire_graphe_vxa("graph_file");
	
    return 0;
}
