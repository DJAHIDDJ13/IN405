#ifndef GRAPH_BIB_H
#define GRAPH_BIB_H

#include <sys/types.h>
#define TElement int

// Les structures
// structure de matrice
typedef struct {
    size_t elm_size;
    TElement** mat;
    int width;
    int height;
} MAT;

// structure de liste
typedef struct node {
    int v;
    TElement w;
    struct node* suiv;
} NODE;

// Structure de graphe
#define GB_DIRECTED 1
#define GB_MULTI 2
#define GB_WEIGHTED 4

typedef struct {
    int type;
    int vertices_num;
    NODE** graph;
} GRAPH_LIST;

typedef struct {
    int type;
    MAT arc;
    MAT weight;
} GRAPH_VxV;

typedef struct {
    int type;
    MAT arc;
    TElement* weight;
} GRAPH_VxA;

// Les prototypes
GRAPH_VxV creer_graphe_vxv(int nbr_v, size_t element_size, int type);
GRAPH_VxV ajout_arc_vxv(GRAPH_VxV g, int x, int y, TElement w);
GRAPH_VxV supp_arc_vxv(GRAPH_VxV g, int x, int y);
GRAPH_VxA creer_graphe_vxa(char* nom_fich);
#endif // GRAPH_BIB_H
