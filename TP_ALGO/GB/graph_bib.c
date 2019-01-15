#include <stdlib.h>

#include "graph_bib.h"

// Les fonctions d'utilités
MAT creer_matrice(int w, int h, size_t s) {
    MAT m;
    m.elm_size = s;
    m.width = w;
    m.height = h;
    m.mat = malloc(sizeof(void*) * h);
    for(int i=0; i<h; i++) {
        m.mat[i] = malloc(s * w);
        for(int j=0; j<w; j++) {
            m.mat[i][j] = 0;
        }
    }
    return m;
}

NODE* push(NODE* n, int v, int w) {
    NODE* t = malloc(sizeof(NODE));
    t->v = v;
    t->w = w;
    t->suiv = n;
    return t;
}

NODE* pop(NODE* n) {
    if(n == NULL)
        return NULL;
    NODE* t = n->suiv;
    free(n);
    return t;
}
// Les fonctions de control des graphes
GRAPH_VxV creer_graphe_vxv(int nbr_v, size_t element_size, int type) {
    GRAPH_VxV res;
    res.type = type;
    res.arc = creer_matrice(nbr_v, nbr_v, element_size);
    if(type & GB_WEIGHTED) {
        res.weight  = creer_matrice(nbr_v, nbr_v, element_size);
    }
    return res;
}

GRAPH_VxV ajout_arc_vxv(GRAPH_VxV g, int x, int y, TElement w) {
    if(x >= 0 && y >= 0 && x < g.arc.width && y < g.arc.height) {
        g.arc.mat[x][y] = 1;
        if(!(g.type & GB_DIRECTED)) {
            g.arc.mat[y][x] = 1;
        }
        if(g.type & GB_WEIGHTED) {
            g.weight.mat[x][y] = w;
        }
    }
    return g;
}
GRAPH_VxV supp_arc_vxv(GRAPH_VxV g, int x, int y) {
    if(x >= 0 && y >= 0 && x < g.arc.width && y < g.arc.height) {
        g.arc.mat[x][y] = 0;
        if(!(g.type & GB_DIRECTED)) {
            g.arc.mat[y][x] = 0;
        }
        if(g.type & GB_WEIGHTED) {
            g.weight.mat[x][y] = 0;
        }
    }
    return g;
}

GRAPH_VxA creer_graphe_vxa(char* nom_fich) {
    GRAPH_VxA g;
    FILE* f;
    if((f = fopen(nom_fich, "r") < 0) {
        fprintf(stderr, "%s: file doesn't exist\n", nom_fich);
        exit(-1);
    }

    return g;
}

