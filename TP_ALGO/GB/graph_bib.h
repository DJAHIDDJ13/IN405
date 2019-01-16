#ifndef GRAPH_BIB_H
#define GRAPH_BIB_H

#include <sys/types.h>
#define TElement int
#define MAX 200

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
    size_t elm_size;
    TElement w;
    struct node* suiv;
} NODE;

// Structure de graphe
#define GB_DIRECTED 1
#define GB_MULTI 2
#define GB_WEIGHTED 4

typedef struct {
    int type;
    int nbr_sommets;
    NODE** list;
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
GRAPH_VxV lire_graphe_vxv(char* nom_fich);
GRAPH_VxA lire_graphe_vxa(char* nom_fich);
GRAPH_LIST lire_graphe_liste(char* nom_fich);
#endif // GRAPH_BIB_H
