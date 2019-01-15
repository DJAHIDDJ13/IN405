#include <stdio.h>
#include <stdlib.h>
#include "graph_bib.h"


int main() {
    GRAPH_VxV g = creer_graphe_vxv(5, sizeof(TElement), GB_WEIGHTED | GB_MULTI);
    g = ajout_arc_vxv(g,1,1,2);
    g = ajout_arc_vxv(g,1,1,2);
    g = supp_arc_vxv(g, 1,1);
    for(int i=0; i<g.arc.height; i++) {
        for(int j=0; j<g.arc.width; j++) {
            printf("%d ", g.arc.mat[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    for(int i=0; i<g.arc.height; i++) {
        for(int j=0; j<g.arc.width; j++) {
            printf("%d ", g.weight.mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}
